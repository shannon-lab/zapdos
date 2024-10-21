//* This file is part of the MOOSE framewo
#include "AddSpecies.h"
#include "FEProblem.h"

registerMooseAction("CraneApp", AddSpecies, "add_variable");
registerMooseAction("CraneApp", AddSpecies, "add_kernel");
registerMooseAction("CraneApp", AddSpecies, "add_scalar_kernel");

template <>
InputParameters
validParams<AddSpecies>()
{
  InputParameters params = validParams<AddVariableAction>();
  params.addRequiredParam<std::vector<NonlinearVariableName>>(
      "species", "The list of primary variables to add");
  params.addRequiredParam<std::vector<Real>>("initial_conditions", "The initial values of each species.");
  params.addParam<std::vector<Real>>("scale_factors", "Specifies scale factors for each variable.");
  params.addParam<bool>("use_scalar", false, "Whether or not to use scalar variables.");
  params.addParam<bool>("add_time_derivatives", false, "Whether or not to add time derivatives as part of this action.");
  params.addParam<bool>("use_log", false, "Whether or not to use logarithmic densities.");
  params.addClassDescription("Adds Variables for all primary species");
  return params;
}

AddSpecies::AddSpecies(const InputParameters & params)
  : AddVariableAction(params),
    _vars(getParam<std::vector<NonlinearVariableName>>("species")),
    _vals(getParam<std::vector<Real>>("initial_conditions")),
    _use_scalar(getParam<bool>("use_scalar")),
    _add_time_derivatives(getParam<bool>("add_time_derivatives")),
    _use_log(getParam<bool>("use_log")),
    _scale_factor(getParam<std::vector<Real>>("scale_factors"))
{
}

void
AddSpecies::act()
{
  if (_current_task == "add_variable")
  {
    std::string family;
    Real scale_factor;
    for (auto i = beginIndex(_vars); i < _vars.size(); ++i)
    {
      if (isParamValid("scale_factors"))
        scale_factor = _scale_factor[i];
      else
        scale_factor = 1.0;

      if (_use_scalar)
        _problem->addScalarVariable(_vars[i], _fe_type.order, scale_factor);
      else
        _problem->addVariable(_vars[i], _fe_type, scale_factor);

      createInitialConditions(_vars[i], _vals[i]);
    }
  }

  // Add time derivatives to the system
  if (_add_time_derivatives)
  {
    if (_current_task == "add_kernel" && !_use_scalar)
    {
      std::string time_kernel = "TimeDerivative";
      if (_use_log)
        time_kernel = time_kernel + "Log";
      for (auto i = beginIndex(_vars); i < _vars.size(); ++i)
      {
        InputParameters params = _factory.getValidParams(time_kernel);
        params.set<NonlinearVariableName>("variable") = _vars[i];
        _problem->addKernel(time_kernel, "dvar"+std::to_string(i)+"_dt", params);
      }
    }
    else if (_current_task == "add_scalar_kernel" && _use_scalar)
    {
      std::string time_kernel = "ODETimeDerivative";
      if (_use_log)
        time_kernel = time_kernel + "Log";
      for (auto i = beginIndex(_vars); i < _vars.size(); ++i)
      {
        InputParameters params = _factory.getValidParams(time_kernel);
        params.set<NonlinearVariableName>("variable") = _vars[i];
        _problem->addScalarKernel(time_kernel, "dvar"+std::to_string(i)+"_dt", params);
      }
    }
  }
}

void
AddSpecies::createInitialConditions(const std::string & var_name, const Real & value)
{
  // Variable name
  // std::string var_name = name();

  // Create the object name
  std::string long_name("");
  long_name += var_name;
  long_name += "_moose";

  // Set the parameters for the action
  InputParameters action_params = _action_factory.getValidParams("AddOutputAction");
  action_params.set<ActionWarehouse *>("awh") = &_awh;

  if (_use_scalar)
    action_params.set<std::string>("type") = "ScalarConstantIC";
  else
    action_params.set<std::string>("type") = "ConstantIC";

  // Create the action
  std::shared_ptr<MooseObjectAction> action = std::static_pointer_cast<MooseObjectAction>(
      _action_factory.create("AddInitialConditionAction", long_name, action_params));

  // Set the required parameters for the object to be created
  action->getObjectParams().set<VariableName>("variable") = var_name;
  // action->getObjectParams().set<Real>("value") = getParam<Real>("initial_condition");
  action->getObjectParams().set<Real>("value") = value;

  // Store the action in the ActionWarehouse
  _awh.addActionBlock(action);
}
