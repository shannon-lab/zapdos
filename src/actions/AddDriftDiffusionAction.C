//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AddDriftDiffusionAction.h"
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

registerMooseAction("ZapdosApp", AddDriftDiffusionAction, "add_variable");
registerMooseAction("ZapdosApp", AddDriftDiffusionAction, "add_kernel");
registerMooseAction("ZapdosApp", AddDriftDiffusionAction, "add_aux_kernel");
registerMooseAction("ZapdosApp", AddDriftDiffusionAction, "add_material");

namespace DriftDiffusionActionEnums {
  // Setup comparison enum (less overhead than string comparison, when necessary)
  enum ComparisonEnum
  {
    ELECTROSTATIC,
    ELECTROMAGNETIC
  };
}

InputParameters
AddDriftDiffusionAction::validParams()
{
  MooseEnum families(AddVariableAction::getNonlinearVariableFamilies());
  MooseEnum orders(AddVariableAction::getNonlinearVariableOrders());

  InputParameters params = AddVariableAction::validParams();

  params.addParam<std::vector<NonlinearVariableName>>(
      "charged_particle", {}, "User given variable name for energy independent charged particle");
  params.addParam<std::vector<NonlinearVariableName>>(
      "secondary_charged_particles",
      {},
      "These are charged particles whose advection term in determined by"
      " an effective field.");
  params.addParam<std::vector<NonlinearVariableName>>(
      "eff_fields",
      {},
      "The effective fields that only affect their respective secondary"
      " charged particle.");
  params.addParam<NonlinearVariableName>("electrons",
                                         "User given variable name for energy dependent electrons");
  params.addParam<std::string>("field", "The gives the field a variable name");
  MooseEnum field_solver("electrostatic electromagnetic", "electrostatic");
  params.addParam<MooseEnum>(
      "field_solver", field_solver, "Electrostatic or electromagnetic field solver (default = electrostatic).");
  params.addParam<std::string>("field_property_name", "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addParam<std::vector<std::string>>("eff_fields_property_names", "Name of the solver interface material property for the effective fields.");
  params.addParam<bool>(
      "Is_field_unique",
      false,
      "Is the field unique to this block?"
      "If not, then the field variable should be defined in the Variable Block.");
  params.addParam<bool>("First_DriftDiffusionAction_in_block",
                        true,
                        "Is this the first DriftDiffusionAction for this block?"
                        "If not, then the field solver kernels and Position auxkernel will "
                        "NOT be supplied by this action.");
  params.addParam<NonlinearVariableName>("mean_energy",
                                         "The gives the mean energy a variable name");
  params.addParam<std::vector<NonlinearVariableName>>(
      "Neutrals", {}, "The names of the neutrals that should be added");
  params.addParam<std::vector<SubdomainName>>(
      "block", {}, "The subdomain that this action applies to.");
  params.addRequiredParam<Real>("position_units", "Units of position");
  params.addParam<bool>("using_offset", false, "Is the LogStabilizationMoles Kernel being used");
  params.addParam<Real>(
      "offset", 20.0, "The offset parameter that goes into the exponential function");
  params.addRequiredParam<std::string>("potential_units", "Units of potential (V or kV)");
  params.addRequiredParam<bool>("use_moles", "Whether to convert from units of moles to #.");
  params.addParam<std::vector<std::string>>(
      "Additional_Outputs",
      {},
      "Current list of available ouputs options in this action: Current, ElectronTemperature,"
      " EField");
  return params;
}

AddDriftDiffusionAction::AddDriftDiffusionAction(const InputParameters & params) : Action(params) {}

void
AddDriftDiffusionAction::act()
{
  MooseSharedPointer<Action> action;
  MooseSharedPointer<MooseObjectAction> moose_object_action;

  //
  unsigned int _dim = _mesh->dimension();

  // Converting the given names into VariableName
  NonlinearVariableName em_name;
  NonlinearVariableName mean_en_name;
  NonlinearVariableName field_name;

  // Saving the field solver choice
  MooseEnum field_solver = getParam<MooseEnum>("field_solver");

  bool em_present = (isParamValid("electrons") ? true : false);
  bool mean_en_present = (isParamValid("mean_energy") ? true : false);
  bool field_present = (isParamValid("field") ? true : false);
  if (em_present)
    em_name = getParam<NonlinearVariableName>("electrons");
  if (mean_en_present)
    mean_en_name = getParam<NonlinearVariableName>("mean_energy");
  if (field_present)
    field_name = getParam<std::string>("field");
    std::string field_property_name = getParam<std::string>("field_property_name");

  std::vector<NonlinearVariableName> Ions =
      getParam<std::vector<NonlinearVariableName>>("charged_particle");
  std::vector<NonlinearVariableName> Neutrals =
      getParam<std::vector<NonlinearVariableName>>("Neutrals");

  unsigned int number_ions = Ions.size();
  unsigned int number_neutrals = Neutrals.size();

  if (!field_present && (em_present || (number_ions > 0)))
    mooseError("There are electrons or charged_particles that are missing their electric field! Please "
               "check your input.");

  std::vector<NonlinearVariableName> sec_particle =
      getParam<std::vector<NonlinearVariableName>>("secondary_charged_particles");
  std::vector<NonlinearVariableName> eff_fields =
      getParam<std::vector<NonlinearVariableName>>("eff_fields");

  std::vector<std::string> eff_fields_property_names = getParam<std::vector<std::string>>("eff_fields_property_names");


  unsigned int number_sec_particle = sec_particle.size();
  unsigned int number_eff_fields = eff_fields.size();

// TODO: add another != for this for the property names list
  if (number_sec_particle != number_eff_fields)
    mooseError("There are secondary_charged_particles that are missing their corresponding "
               "effective fields (eff_fields)! Please check your input.");

  // Converting the given additional outputs
  std::vector<std::string> Outputs = getParam<std::vector<std::string>>("Additional_Outputs");

  unsigned int number_outputs = Outputs.size();

  // Converting the boolean statements
  bool Using_offset = getParam<bool>("using_offset");
  bool New_field = getParam<bool>("Is_field_unique");
  bool First_Action = getParam<bool>("First_DriftDiffusionAction_in_block");

  // The variable type for the nonlinear scalar variables
  auto fe_type = AddVariableAction::feType(_pars);
  auto type = AddVariableAction::variableType(fe_type);
  auto var_params = _factory.getValidParams(type);
  var_params.set<MooseEnum>("order") = "FIRST";
  var_params.set<MooseEnum>("family") = "LAGRANGE";
  var_params.set<std::vector<SubdomainName>>("block") =
      getParam<std::vector<SubdomainName>>("block");

  // The variable type for the nonlinear vector variables
  auto fe_type_vec = AddVariableAction::feType(_pars);
  auto type_vec = AddVariableAction::variableType(fe_type_vec);
  auto var_params_vec = _factory.getValidParams(type_vec);
  var_params_vec.set<MooseEnum>("order") = "FIRST";
  var_params_vec.set<MooseEnum>("family") = "NEDELEC_ONE";
  var_params_vec.set<std::vector<SubdomainName>>("block") =
      getParam<std::vector<SubdomainName>>("block");

  // The variable type for the aux variables
  auto aux_params = _factory.getValidParams(type);
  aux_params.set<MooseEnum>("order") = "CONSTANT";
  aux_params.set<MooseEnum>("family") = "MONOMIAL";
  aux_params.set<std::vector<SubdomainName>>("block") =
      getParam<std::vector<SubdomainName>>("block");

  if (_current_task == "add_variable")
  {
    // Add the ion variables and their density aux variables
    for (unsigned int cur_num = 0; cur_num < number_ions; cur_num++)
    {
      std::string ion_name = Ions[cur_num];
      _problem->addVariable(type, ion_name, var_params);
      _problem->addAuxVariable(type, ion_name + "_density", aux_params);
    }

    // Add the neutrals variables and their density aux variables
    for (unsigned int cur_num = 0; cur_num < number_neutrals; cur_num++)
    {
      std::string neutrals_name = Neutrals[cur_num];
      _problem->addVariable(type, neutrals_name, var_params);
      _problem->addAuxVariable(type, neutrals_name + "_density", aux_params);
    }

    // Adding electrons, mean energy, and field variables
    if (em_present)
    {
      _problem->addVariable(type, em_name, var_params);
      _problem->addAuxVariable(type, em_name + "_density", aux_params);
    }
    if (mean_en_present)
    {
      _problem->addVariable(type, mean_en_name, var_params);
    }
    if (New_field && field_present && field_solver == DriftDiffusionActionEnums::ELECTROSTATIC)
    {
      _problem->addVariable(type, field_name, var_params);
    }
    if (New_field && field_present && field_solver == DriftDiffusionActionEnums::ELECTROMAGNETIC)
    {
      _problem->addVariable(type, field_name, var_params_vec);
    }

    // Adding charged particles who are effective by an effective potential
    for (unsigned int cur_num = 0; cur_num < number_sec_particle; cur_num++)
    {
      std::string sec_particle_name = sec_particle[cur_num];
      _problem->addVariable(type, sec_particle_name, var_params);
      _problem->addAuxVariable(type, sec_particle_name + "_density", aux_params);
    }

    // Adding the position aux variable, needed if position scaling is used
    if (First_Action)
    {
      if (_dim == 1)
      {
        _problem->addAuxVariable(
            type,
            "position" + Moose::stringify(getParam<std::vector<SubdomainName>>("block")),
            aux_params);
      }
      else
      {
        for (unsigned int component = 0; component < _dim; ++component)
        {
          std::string dir = "x_";
          if (component == 1)
            dir = "y_";
          if (component == 2)
            dir = "z_";
          _problem->addAuxVariable(
              type,
              dir + "position" + Moose::stringify(getParam<std::vector<SubdomainName>>("block")),
              aux_params);
        }
      }
    }

    // Adding variables needed for the additional outputs
    for (unsigned int cur_num = 0; cur_num < number_outputs; cur_num++)
    {
      std::string output_name = Outputs[cur_num];

      if (output_name == "Current")
      {
        if (em_present)
          _problem->addAuxVariable(type, "Current_" + em_name, aux_params);

        for (unsigned int cur_num = 0; cur_num < number_ions; cur_num++)
        {
          std::string ion_name = Ions[cur_num];
          _problem->addAuxVariable(type, "Current_" + ion_name, aux_params);
        }

        for (unsigned int cur_num = 0; cur_num < number_sec_particle; cur_num++)
        {
          std::string sec_particle_name = sec_particle[cur_num];
          _problem->addAuxVariable(type, "Current_" + sec_particle_name, aux_params);
        }
      }

      else if (output_name == "ElectronTemperature")
      {
        _problem->addAuxVariable(type, "e_temp", aux_params);
      }

      else if (output_name == "EField")
      {
        for (unsigned int component = 0; component < _dim; ++component)
        {
          std::string dir = "x";
          if (component == 1)
            dir = "y";
          if (component == 2)
            dir = "z";

          _problem->addAuxVariable(
              type,
              "EField" + dir + Moose::stringify(getParam<std::vector<SubdomainName>>("block")),
              aux_params);
        }
      }

      else if (output_name != "Current" || output_name != "ElectronTemperature" ||
               output_name != "EField")
      {
        mooseError("Currently this action does not have one of the desired outputs or spelling is "
                   "incorrect."
                   " Please input the AuxKernel manually or check spelling.");
      }
    }
  }

  else if (_current_task == "add_kernel")
  {
    // This section adds all necessary kernels for electrons, ions, neutrals,
    // and electron temperature.

    // Adding energy dependent electron kernels, if present in block
    if (em_present)
    {
      addADKernels(em_name, field_property_name, Using_offset, true, false);
      addChargeSourceKernels(field_name, em_name, field_solver);
    }

    // Adding energy electron mean energy kernels, if present in block
    if (mean_en_present)
    {
      addADKernels(mean_en_name, field_property_name, Using_offset, false, true);
    }

    // Adding Kernels for the charged particle
    for (unsigned int cur_num = 0; cur_num < number_ions; cur_num++)
    {
      std::string ion_name = Ions[cur_num];

      addADKernels(ion_name, field_property_name, Using_offset, true, false);
      addChargeSourceKernels(field_name, ion_name, field_solver);
    }

    // Adding the diffusion Kernel for the potential (if electrostatic)
    if (field_present && First_Action && field_solver == DriftDiffusionActionEnums::ELECTROSTATIC)
    {
      InputParameters params = _factory.getValidParams("CoeffDiffusionLin");
      params.set<NonlinearVariableName>("variable") = {field_name};
      params.set<Real>("position_units") = getParam<Real>("position_units");
      params.set<std::vector<SubdomainName>>("block") =
          getParam<std::vector<SubdomainName>>("block");
      _problem->addKernel("CoeffDiffusionLin",
                          field_name + "_diffusion" +
                              Moose::stringify(getParam<std::vector<SubdomainName>>("block")) +
                              "_block",
                          params);
    }
    if (field_present && First_Action && field_solver == DriftDiffusionActionEnums::ELECTROMAGNETIC)
    {
      mooseWarning("Setting up EM field equations has not yet been setup in DriftDiffusionAction, and must be set up manually!");
    }

    // Adding Kernels for the neutrals
    for (unsigned int cur_num = 0; cur_num < number_neutrals; cur_num++)
    {
      std::string neutral_name = Neutrals[cur_num];

      addADKernels(neutral_name, field_property_name, Using_offset, false, false);
    }

    // Adding Kernels for charged particles who are affected by an effective field
    for (unsigned int cur_num = 0; cur_num < number_sec_particle; cur_num++)
    {
      std::string sec_particle_name = sec_particle[cur_num];
      std::string eff_fields_name = eff_fields[cur_num];
      std::string eff_fields_property_name = eff_fields_property_names[cur_num];

      addADKernels(sec_particle_name, eff_fields_property_name, Using_offset, true, false);
      addChargeSourceKernels(field_name, sec_particle_name, field_solver);
    }
  }

  else if (_current_task == "add_aux_kernel")
  {
    // AuxKernels for position;
    if (First_Action)
    {
      if (_dim == 1)
      {
        addPosition("position" + Moose::stringify(getParam<std::vector<SubdomainName>>("block")),
                    0);
      }
      else
      {
        for (unsigned int component = 0; component < _dim; ++component)
        {
          std::string dir = "x_";
          if (component == 1)
            dir = "y_";
          if (component == 2)
            dir = "z_";
          addPosition(dir + "position" +
                          Moose::stringify(getParam<std::vector<SubdomainName>>("block")),
                      component);
        }
      }
    }

    // Adding the aux kernels needed to convert the log form of the densities
    if (em_present)
    {
      addDensityLog(em_name);
    }
    for (unsigned int cur_num = 0; cur_num < number_ions; cur_num++)
    {
      std::string ion_name = Ions[cur_num];
      addDensityLog(ion_name);
    }
    for (unsigned int cur_num = 0; cur_num < number_neutrals; cur_num++)
    {
      std::string neutral_name = Neutrals[cur_num];
      addDensityLog(neutral_name);
      ;
    }
    for (unsigned int cur_num = 0; cur_num < number_sec_particle; cur_num++)
    {
      std::string sec_particle_name = sec_particle[cur_num];
      addDensityLog(sec_particle_name);
    }

    for (unsigned int cur_num = 0; cur_num < number_outputs; cur_num++)
    {
      std::string output_name = Outputs[cur_num];

      // AuxKernels for current
      if (output_name == "Current")
      {
        if (em_present)
        {
          addCurrent(em_name, field_property_name);
        }

        for (unsigned int cur_num = 0; cur_num < number_ions; cur_num++)
        {
          std::string ion_name = Ions[cur_num];
          addCurrent(ion_name, field_property_name);
        }

        for (unsigned int cur_num = 0; cur_num < number_sec_particle; cur_num++)
        {
          std::string sec_particle_name = sec_particle[cur_num];
          std::string eff_fields_property_name = eff_fields_property_names[cur_num];
          addCurrent(sec_particle_name, eff_fields_property_name);
        }
      }

      // Adding Efield Aux kernels
      else if (output_name == "EField")
      {
        for (unsigned int component = 0; component < _dim; ++component)
        {
          std::string dir = "x";
          if (component == 1)
            dir = "y";
          if (component == 2)
            dir = "z";

          addEfield("EField" + dir +
                        Moose::stringify(getParam<std::vector<SubdomainName>>("block")),
                    field_property_name,
                    component);
        }
      }

      // Adding Electron Temperature Aux kernels
      else if (output_name == "ElectronTemperature")
      {
        InputParameters params = _factory.getValidParams("ElectronTemperature");
        params.set<AuxVariableName>("variable") = "e_temp";
        params.set<std::vector<VariableName>>("electron_density") = {em_name};
        params.set<std::vector<VariableName>>("mean_en") = {mean_en_name};
        params.set<std::vector<SubdomainName>>("block") =
            getParam<std::vector<SubdomainName>>("block");
        _problem->addAuxKernel("ElectronTemperature", "e_temp", params);
      }
    }
  }
  else if (_current_task == "add_material")
  {
    if (field_present && First_Action)
    {
      addFieldSolverMaterial(field_name, field_property_name, field_solver, false);

      // Adding material interfaces for charged particles who are affected by an effective field
      for (unsigned int cur_num = 0; cur_num < number_sec_particle; cur_num++)
      {
        std::string eff_fields_name = eff_fields[cur_num];
        std::string eff_fields_property_name = eff_fields_property_names[cur_num];
        addFieldSolverMaterial(eff_fields_name, eff_fields_property_name, field_solver, true);
      }
    }
  }
}

// Adding potentials charge sources
void
AddDriftDiffusionAction::addChargeSourceKernels(const std::string & field_name,
                                                const std::string & charged_particle_name, const MooseEnum & field_solver)
{
  // Add charge source contribution to electrostatic problem only
  if (field_solver == DriftDiffusionActionEnums::ELECTROSTATIC)
  {
    InputParameters params = _factory.getValidParams("ChargeSourceMoles_KV");
    params.set<NonlinearVariableName>("variable") = {field_name};
    params.set<std::vector<VariableName>>("charged") = {charged_particle_name};
    params.set<std::string>("potential_units") = getParam<std::string>("potential_units");
    params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("ChargeSourceMoles_KV", charged_particle_name + "_charge_source", params);
  }
}

/*
 * Adding Kernels for the electrons, energy independent charged particles,
 * neutral particles, and electron mean energy depending on function parameters
 */
void
AddDriftDiffusionAction::addADKernels(const std::string & name,
                                      const std::string & field_property_name,
                                      const bool & Using_offset,
                                      const bool & charged,
                                      const bool & energy)
{
  _problem->haveADObjects(true);

  InputParameters params = _factory.getValidParams("TimeDerivativeLog");
  params.set<NonlinearVariableName>("variable") = {name};
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("TimeDerivativeLog", name + "_time_deriv", params);

  if (charged)
  {
    InputParameters params1 = _factory.getValidParams("EFieldAdvection");
    params1.set<NonlinearVariableName>("variable") = {name};
    params1.set<std::string>("field_property_name") = {field_property_name};
    params1.set<Real>("position_units") = getParam<Real>("position_units");
    params1.set<std::vector<SubdomainName>>("block") =
        getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("EFieldAdvection", name + "_advection", params1);
  }

  InputParameters params2 = _factory.getValidParams("CoeffDiffusion");
  params2.set<NonlinearVariableName>("variable") = {name};
  params2.set<Real>("position_units") = getParam<Real>("position_units");
  params2.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addKernel("CoeffDiffusion", name + "_diffusion", params2);

  if (energy)
  {
    InputParameters params3 = _factory.getValidParams("EFieldAdvection");
    params3.set<NonlinearVariableName>("variable") = {name};
    params3.set<std::string>("field_property_name") = {field_property_name};
    params3.set<Real>("position_units") = getParam<Real>("position_units");
    params3.set<std::vector<SubdomainName>>("block") =
        getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("EFieldAdvection", name + "_advection", params3);

    InputParameters params4 = _factory.getValidParams("JouleHeating");
    params4.set<NonlinearVariableName>("variable") = {name};
    params4.set<std::string>("field_property_name") = {field_property_name};
    params4.set<std::vector<VariableName>>("em") = {getParam<NonlinearVariableName>("electrons")};
    params4.set<std::string>("potential_units") = getParam<std::string>("potential_units");
    params4.set<Real>("position_units") = getParam<Real>("position_units");
    params4.set<std::vector<SubdomainName>>("block") =
        getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("JouleHeating", name + "_joule_heating", params4);
  }

  if (Using_offset && !energy)
  {
    InputParameters params5 = _factory.getValidParams("LogStabilizationMoles");
    params5.set<NonlinearVariableName>("variable") = {name};
    params5.set<Real>("offset") = getParam<Real>("offset");
    params5.set<std::vector<SubdomainName>>("block") =
        getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("LogStabilizationMoles", name + "_log_stabilization", params5);
  }
  else if (Using_offset && energy)
  {
    InputParameters params6 = _factory.getValidParams("LogStabilizationMoles");
    params6.set<NonlinearVariableName>("variable") = {name};
    params6.set<Real>("offset") = (getParam<Real>("offset") - 5.0);
    params6.set<std::vector<SubdomainName>>("block") =
        getParam<std::vector<SubdomainName>>("block");
    _problem->addKernel("LogStabilizationMoles", _name + "_log_stabilization", params6);
  }
}

// Adding the Aux kernels to convert scaled position units
void
AddDriftDiffusionAction::addPosition(const std::string & position_name, const int & component)
{
  InputParameters params = _factory.getValidParams("Position");
  params.set<AuxVariableName>("variable") = {position_name};
  params.set<Real>("position_units") = getParam<Real>("position_units");
  params.set<int>("component") = component;
  _problem->addAuxKernel("Position", position_name, params);
}

// Adding the Aux kernels to convert densities from log form
void
AddDriftDiffusionAction::addDensityLog(const std::string & particle_name)
{
  InputParameters params = _factory.getValidParams("DensityMoles");
  params.set<AuxVariableName>("variable") = particle_name + "_density";
  params.set<std::vector<VariableName>>("density_log") = {particle_name};
  params.set<bool>("use_moles") = getParam<bool>("use_moles");
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addAuxKernel("DensityMoles", particle_name + "_density", params);
}

// Adding the Aux kernels for current
void
AddDriftDiffusionAction::addCurrent(const std::string & particle_name,
                                    const std::string & field_property_name)
{
  InputParameters params = _factory.getValidParams("ADCurrent");
  params.set<AuxVariableName>("variable") = {"Current_" + particle_name};
  params.set<std::string>("field_property_name") = {field_property_name};
  params.set<std::vector<VariableName>>("density_log") = {particle_name};
  params.set<Real>("position_units") = getParam<Real>("position_units");
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addAuxKernel("ADCurrent", "Current_" + particle_name, params);
}

// Adding the Aux kernels for the Efield
void
AddDriftDiffusionAction::addEfield(const std::string & Efield_name,
                                   const std::string & field_property_name,
                                   const int & component)
{
  InputParameters params = _factory.getValidParams("Efield");
  params.set<AuxVariableName>("variable") = {Efield_name};
  params.set<std::string>("field_property_name") = {field_property_name};
  params.set<Real>("position_units") = getParam<Real>("position_units");
  params.set<int>("component") = component;
  params.set<std::string>("potential_units") = getParam<std::string>("potential_units");
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  _problem->addAuxKernel("Efield", Efield_name, params);
}

// Adding the material interface for FieldSolverMaterial
void
AddDriftDiffusionAction::addFieldSolverMaterial(const std::string & field_name, const std::string & field_property_name, const MooseEnum & field_solver, const bool & effective_field)
{
  InputParameters params = _factory.getValidParams("FieldSolverMaterial");
  params.set<MooseEnum>("solver") = {field_solver};
  if (field_solver == DriftDiffusionActionEnums::ELECTROSTATIC)
    params.set<std::vector<VariableName>>("potential") = {field_name};
  if (field_solver == DriftDiffusionActionEnums::ELECTROMAGNETIC)
    params.set<std::vector<VariableName>>("electric_field") = {field_name};
  params.set<std::string>("property_name") = {field_property_name};
  params.set<std::vector<SubdomainName>>("block") = getParam<std::vector<SubdomainName>>("block");
  if (effective_field)
    _problem->addMaterial("FieldSolverMaterial", "FieldSolver_" + name() + "_eff", params);
  else
    _problem->addMaterial("FieldSolverMaterial", "FieldSolver_" + name(), params);
}
