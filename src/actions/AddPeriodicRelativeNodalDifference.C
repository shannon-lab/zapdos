//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AddPeriodicRelativeNodalDifference.h"
#include "Parser.h"
#include "FEProblem.h"
#include "Factory.h"
#include "MooseEnum.h"
#include "AddVariableAction.h"
#include "Conversion.h"
#include "ActionFactory.h"
#include "MooseObjectAction.h"
#include "MooseApp.h"

#include "libmesh/vector_value.h"

#include "pcrecpp.h"

#include <sstream>
#include <stdexcept>

// libmesh includes
#include "libmesh/libmesh.h"
#include "libmesh/exodusII_io.h"
#include "libmesh/equation_systems.h"
#include "libmesh/nonlinear_implicit_system.h"
#include "libmesh/explicit_system.h"
#include "libmesh/string_to_enum.h"
#include "libmesh/fe.h"

registerMooseAction("ZapdosApp", AddPeriodicRelativeNodalDifference, "add_variable");
registerMooseAction("ZapdosApp", AddPeriodicRelativeNodalDifference, "add_ic");
registerMooseAction("ZapdosApp", AddPeriodicRelativeNodalDifference, "add_kernel");
registerMooseAction("ZapdosApp", AddPeriodicRelativeNodalDifference, "add_aux_kernel");
registerMooseAction("ZapdosApp", AddPeriodicRelativeNodalDifference, "add_control");
registerMooseAction("ZapdosApp", AddPeriodicRelativeNodalDifference, "add_postprocessor");

InputParameters
AddPeriodicRelativeNodalDifference::validParams()
{
  MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
  MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());

  InputParameters params = AddVariableAction::validParams();
  params.addParam<std::vector<NonlinearVariableName>>(
      "periodic_variable_log", {}, "The periodic variables that are in log form.");
  params.addParam<std::vector<NonlinearVariableName>>(
      "periodic_variable", {}, "The periodic variables (Not in log form).");
  params.addParam<Real>(
      "starting_cycle", 0.0, "The number of the cycles before starting the difference calculation");
  params.addRequiredParam<Real>("cycle_frequency", "The cycle's frequency in Hz");
  params.addParam<Real>(
      "num_cycles", 2000.0, "The number of cycles to calculation the difference for.");
  params.addParam<std::vector<SubdomainName>>(
      "block", {}, "The subdomain that this action applies to.");
  params.addClassDescription(
      "This Action automatically adds the necessary objects to calculate the relative"
      " periodic difference. Relative Difference will be outputted as an Postprocessor named: "
      "'var'_periodic_difference");

  return params;
}

AddPeriodicRelativeNodalDifference::AddPeriodicRelativeNodalDifference(const InputParameters & params)
  : Action(params),

    _start_time((1. / getParam<Real>("cycle_frequency")) * getParam<Real>("starting_cycle")),
    _period(1. / getParam<Real>("cycle_frequency")),
    _num_controller_set(getParam<Real>("num_cycles"))
{
}

void
AddPeriodicRelativeNodalDifference::act()
{
  MooseSharedPointer<Action> action;
  MooseSharedPointer<MooseObjectAction> moose_object_action;

  std::vector<NonlinearVariableName> var_log =
      getParam<std::vector<NonlinearVariableName>>("periodic_variable_log");
  std::vector<NonlinearVariableName> var =
      getParam<std::vector<NonlinearVariableName>>("periodic_variable");

  unsigned int number_var_log = var_log.size();
  unsigned int number_var = var.size();

  // The variable type for the aux variables
  auto fe_type = AddVariableAction::feType(_pars);
  auto type = AddVariableAction::variableType(fe_type);
  auto var_params = _factory.getValidParams(type);
  var_params.set<MooseEnum>("order") = "FIRST";
  var_params.set<MooseEnum>("family") = "LAGRANGE";
  var_params.set<std::vector<SubdomainName>>("block") =
      getParam<std::vector<SubdomainName>>("block");

  // Defineding the indexs needed for the periodic controller
  _enable_start.resize(3 * (number_var_log + number_var));
  _enable_end.resize(number_var_log + number_var);

  for (unsigned int i = 0; i < number_var_log; i++)
  {
    std::string var_log_name = var_log[i];

    _enable_start[3 * i] = "*::" + var_log_name + "_previous_cycle_sudo";
    _enable_start[3 * i + 1] = "*::" + var_log_name + "_normalized";
    _enable_start[3 * i + 2] = "*::" + var_log_name + "_previous_cycle_normalized";
  }
  for (unsigned int i = number_var_log; i < (number_var + number_var_log); i++)
  {
    std::string var_name = var[i - number_var_log];

    _enable_start[3 * i] = "*::" + var_name + "_previous_cycle_sudo";
    _enable_start[3 * i + 1] = "*::" + var_name + "_normalized";
    _enable_start[3 * i + 2] = "*::" + var_name + "_previous_cycle_normalized";
  }
  for (unsigned int i = 0; i < number_var_log; i++)
  {
    std::string var_log_name = var_log[i];

    _enable_end[i] = "*::" + var_log_name + "_previous_cycle";
  }
  for (unsigned int i = number_var_log; i < (number_var + number_var_log); i++)
  {
    std::string var_name = var[i - number_var_log];

    _enable_end[i] = "*::" + var_name + "_previous_cycle";
  }

  _enable_start_start_time_index.resize(_enable_start.size());
  _enable_start_end_time_index.resize(_enable_start.size());
  _enable_end_start_time_index.resize(_enable_end.size());
  _enable_end_end_time_index.resize(_enable_end.size());

  // Adding Variables to store previous solutions and normalized solutions
  // Note: A sudo previous solution is needed so that the '_previous_cycle'
  // solutions are not overwritten too soon.
  if (_current_task == "add_variable")
  {
    // Dummy variable for the denominator in QuotientAux
    _problem->addAuxVariable(type, "Dummy_denominator", var_params);

    for (unsigned int cur_num = 0; cur_num < number_var_log; cur_num++)
    {
      std::string var_log_name = var_log[cur_num];
      _problem->addAuxVariable(type, var_log_name + "_previous_cycle", var_params);
      _problem->addAuxVariable(type, var_log_name + "_previous_cycle_sudo", var_params);

      _problem->addAuxVariable(type, var_log_name + "_normalized", var_params);
      _problem->addAuxVariable(type, var_log_name + "_previous_cycle_normalized", var_params);
    }
    for (unsigned int cur_num = 0; cur_num < number_var; cur_num++)
    {
      std::string var_name = var[cur_num];
      _problem->addAuxVariable(type, var_name + "_previous_cycle", var_params);
      _problem->addAuxVariable(type, var_name + "_previous_cycle_sudo", var_params);

      _problem->addAuxVariable(type, var_name + "_normalized", var_params);
      _problem->addAuxVariable(type, var_name + "_previous_cycle_normalized", var_params);
    }
  }

  // Adding IC for the previous solution to avoid a 'divided by zero' for
  // the first cycle.
  else if (_current_task == "add_ic")
  {
    for (unsigned int cur_num = 0; cur_num < number_var_log; cur_num++)
    {
      std::string var_log_name = var_log[cur_num];
      Real initial = -21.;

      addPerviousSolutionsIC(var_log_name + "_previous_cycle", initial);
      addPerviousSolutionsIC(var_log_name + "_previous_cycle_sudo", initial);
    }
    for (unsigned int cur_num = 0; cur_num < number_var; cur_num++)
    {
      std::string var_name = var[cur_num];

      Real initial = 0.0001;

      addPerviousSolutionsIC(var_name + "_previous_cycle", initial);
      addPerviousSolutionsIC(var_name + "_previous_cycle_sudo", initial);
    }
  }

  else if (_current_task == "add_aux_kernel")
  {
    // Adding the Dummy kernel for the denominator in QuotientAux.
    InputParameters params = _factory.getValidParams("ConstantAux");
    params.set<AuxVariableName>("variable") = {"Dummy_denominator"};
    params.set<Real>("value") = 1.;
    params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
    _problem->addAuxKernel("ConstantAux", "Dummy_denominator", params);

    // Adding Kernels to store previous solutions and to normalize solutions
    for (unsigned int cur_num = 0; cur_num < number_var_log; cur_num++)
    {
      std::string var_log_name = var_log[cur_num];

      addPerviousSolutionsKernels(var_log_name + "_previous_cycle_sudo", var_log_name);
      addPerviousSolutionsKernels(var_log_name + "_previous_cycle",
                                  var_log_name + "_previous_cycle_sudo");

      addNormalizationKernels(
          var_log_name + "_normalized", var_log_name, var_log_name + "_NodalAverage", true);
      addNormalizationKernels(var_log_name + "_previous_cycle_normalized",
                              var_log_name + "_previous_cycle",
                              var_log_name + "_previous_cycle_NodalAverage",
                              true);
    }

    for (unsigned int cur_num = 0; cur_num < number_var; cur_num++)
    {
      std::string var_name = var[cur_num];

      addPerviousSolutionsKernels(var_name + "_previous_cycle_sudo", var_name);
      addPerviousSolutionsKernels(var_name + "_previous_cycle", var_name + "_previous_cycle_sudo");

      addNormalizationKernels(
          var_name + "_normalized", var_name, var_name + "_NodalAverage", false);
      addNormalizationKernels(var_name + "_previous_cycle_normalized",
                              var_name + "_previous_cycle",
                              var_name + "_previous_cycle_NodalAverage",
                              false);
    }
  }

  // Adding Postprocessor to calculate nodal average and difference
  else if (_current_task == "add_postprocessor")
  {
    for (unsigned int cur_num = 0; cur_num < number_var_log; cur_num++)
    {
      std::string var_log_name = var_log[cur_num];

      addAverageNodalPP(var_log_name, true);
      addAverageNodalPP(var_log_name + "_previous_cycle", true);

      addRelativePeriodicDiffPP(
          var_log_name + "_normalized", var_log_name + "_previous_cycle_normalized", var_log_name);
    }

    for (unsigned int cur_num = 0; cur_num < number_var; cur_num++)
    {
      std::string var_name = var[cur_num];

      addAverageNodalPP(var_name, false);
      addAverageNodalPP(var_name + "_previous_cycle", false);

      addRelativePeriodicDiffPP(
          var_name + "_normalized", var_name + "_previous_cycle_normalized", var_name);
    }
  }

  // Adding a periodic control, so Auxkernels only are on once par cycle
  else if (_current_task == "add_control")
  {
    for (unsigned int i = 0; i < _num_controller_set; ++i)
    {
      for (MooseIndex(_enable_start) j = 0; j < _enable_start.size(); ++j)
      {
        _enable_start_start_time_index[j] = _start_time + _period * i;
        _enable_start_end_time_index[j] = _start_time + _period * i + (_period * 0.0001);
      }
      for (MooseIndex(_enable_end) j = 0; j < _enable_end.size(); ++j)
      {
        _enable_end_start_time_index[j] =
            (_start_time + _period) + _period * i + (_period * 0.0001);
        _enable_end_end_time_index[j] = (_start_time + _period) + _period * i + (_period * 0.0002);
      }

      if (_enable_start.size() > 0)
      {
        std::string name_num = "PeriodicRelativeDifference_Enable_Begin_" + std::to_string(i);
        bool first_controller;

        if (i == 0)
        {
          first_controller = true;
        }
        else
        {
          first_controller = false;
        }

        AddTimePeriod(_enable_start,
                      _enable_start_start_time_index,
                      _enable_start_end_time_index,
                      name_num,
                      first_controller);
      }

      if (_enable_end.size() > 0)
      {
        std::string name_num = "PeriodicRelativeDifference_Enable_End_" + std::to_string(i);
        bool first_controller;

        if (i == 0)
        {
          first_controller = true;
        }
        else
        {
          first_controller = false;
        }

        AddTimePeriod(_enable_end,
                      _enable_end_start_time_index,
                      _enable_end_end_time_index,
                      name_num,
                      first_controller);
      }
    }
  }
}

// Setting ICs for the previous and sudo previous solutions
void
AddPeriodicRelativeNodalDifference::addPerviousSolutionsIC(const std::string & variable_name,
                                                           const Real & initial)
{
  InputParameters params = _factory.getValidParams("ConstantIC");
  params.set<VariableName>("variable") = variable_name;
  params.set<Real>("value") = initial;
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addInitialCondition("ConstantIC", variable_name + "_ic", params);
}

// Setting AuxKernels for the previous and sudo previous solutions
void
AddPeriodicRelativeNodalDifference::addPerviousSolutionsKernels(const std::string & variable_name,
                                                                const std::string & var_old_name)
{
  InputParameters params = _factory.getValidParams("QuotientAux");
  params.set<AuxVariableName>("variable") = {variable_name};
  params.set<std::vector<VariableName>>("numerator") = {var_old_name};
  params.set<std::vector<VariableName>>("denominator") = {"Dummy_denominator"};
  params.set<bool>("enable") = false;
  params.set<ExecFlagEnum>("execute_on", true) = {EXEC_TIMESTEP_BEGIN};
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addAuxKernel("QuotientAux", variable_name, params);
}

// Setting AuxKernels to normalize solutions
void
AddPeriodicRelativeNodalDifference::addNormalizationKernels(const std::string & variable_name,
                                                            const std::string & source,
                                                            const std::string & averaged,
                                                            const bool & log)
{
  if (log)
  {
    InputParameters params = _factory.getValidParams("DensityNormalization");
    params.set<AuxVariableName>("variable") = {variable_name};
    params.set<std::vector<VariableName>>("Density") = {source};
    params.set<PostprocessorName>("normalization") = {averaged};
    params.set<bool>("enable") = false;
    params.set<ExecFlagEnum>("execute_on", true) = {EXEC_TIMESTEP_BEGIN};
    params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
    _problem->addAuxKernel("DensityNormalization", variable_name, params);
  }
  else
  {
    InputParameters params = _factory.getValidParams("NormalizationAux");
    params.set<AuxVariableName>("variable") = {variable_name};
    params.set<std::vector<VariableName>>("source_variable") = {source};
    params.set<PostprocessorName>("normalization") = {averaged};
    params.set<bool>("enable") = false;
    params.set<ExecFlagEnum>("execute_on", true) = {EXEC_TIMESTEP_BEGIN};
    params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
    _problem->addAuxKernel("NormalizationAux", variable_name, params);
  }
}

// Setting Postprocessor to take to nodal average
void
AddPeriodicRelativeNodalDifference::addAverageNodalPP(const std::string & variable_name,
                                                      const bool & log)
{
  if (log)
  {
    InputParameters params = _factory.getValidParams("AverageNodalDensity");
    params.set<std::vector<VariableName>>("variable") = {variable_name};
    params.set<std::vector<OutputName>>("outputs") = {"none"};
    params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
    _problem->addPostprocessor("AverageNodalDensity", variable_name + "_NodalAverage", params);
  }
  else
  {
    InputParameters params = _factory.getValidParams("AverageNodalVariableValue");
    params.set<std::vector<VariableName>>("variable") = {variable_name};
    params.set<std::vector<OutputName>>("outputs") = {"none"};
    params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
    _problem->addPostprocessor(
        "AverageNodalVariableValue", variable_name + "_NodalAverage", params);
  }
}

// Setting Postprocessor to take to average nodal difference
void
AddPeriodicRelativeNodalDifference::addRelativePeriodicDiffPP(const std::string & variable_name,
                                                              const std::string & var_old_name,
                                                              const std::string & name)
{
  InputParameters params = _factory.getValidParams("AverageNodalDifference");
  params.set<std::vector<VariableName>>("variable") = {variable_name};
  params.set<std::vector<VariableName>>("other_variable") = {var_old_name};
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addPostprocessor("AverageNodalDifference", name + "_periodic_difference", params);
}

void
AddPeriodicRelativeNodalDifference::AddTimePeriod(const std::vector<std::string> & objects,
                                                  const std::vector<Real> & start_times,
                                                  const std::vector<Real> & end_times,
                                                  const std::string & name_num,
                                                  const bool & first_controller)
{
  InputParameters params = _factory.getValidParams("TimePeriod");
  params.set<std::vector<std::string>>("enable_objects") = objects;
  params.set<std::vector<Real>>("start_time") = start_times;
  params.set<std::vector<Real>>("end_time") = end_times;
  params.set<ExecFlagEnum>("execute_on", true) = {EXEC_INITIAL, EXEC_TIMESTEP_BEGIN};
  params.set<bool>("reverse_on_false") = first_controller;
  params.set<bool>("set_sync_times") = true;
  std::shared_ptr<Control> control = _factory.create<Control>("TimePeriod", name_num, params);
  _problem->getControlWarehouse().addObject(control);
}
