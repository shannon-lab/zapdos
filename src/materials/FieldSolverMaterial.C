#include "FieldSolverMaterial.h"

registerMooseObject("ZapdosApp", FieldSolverMaterial);

InputParameters
FieldSolverMaterial::validParams()
{
  InputParameters params = ADMaterial::validParams();
  params.addClassDescription(
      "FieldSolverMaterial provides an electric field property for Zapdos objects. This enables "
      "an interface to an external electromagnetic field solver for all Zapdos objects. Default is "
      "an electrostatic interface, where the `potential` coupled variable parameter must be "
      "provided.");
  MooseEnum solver("electrostatic electromagnetic", "electrostatic");
  params.addParam<MooseEnum>(
      "solver", solver, "Electrostatic or electromagnetic field solver (default = electrostatic).");
  params.addCoupledVar("potential", "Electrostatic potential variable.");
  params.addCoupledVar("electric_field",
                       "Electric field variable provided by electromagnetic solver.");
  params.addParam<std::string>("property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  return params;
}

FieldSolverMaterial::FieldSolverMaterial(const InputParameters & parameters)
  : Material(parameters),
    _grad_potential(isCoupled("potential") ? adCoupledGradient("potential") : _ad_grad_zero),
    _electric_field(isCoupled("electric_field") ? adCoupledVectorValue("electric_field")
                                                : _ad_grad_zero),
    _field(declareADProperty<RealVectorValue>(getParam<std::string>("property_name"))),
    _mode(getParam<MooseEnum>("solver"))
{
  enum ComparisonEnum
  {
    ELECTROSTATIC,
    ELECTROMAGNETIC
  };

  if (_mode == ELECTROSTATIC && parameters.isParamSetByUser("electric_field") &&
      !parameters.isParamSetByUser("potential"))
  {
    paramError("solver",
               "Solver mode is electrostatic, but electric field was provided. Please either "
               "change the mode or provide a potential variable.");
  }
  else if (_mode == ELECTROMAGNETIC && parameters.isParamSetByUser("potential") &&
           !parameters.isParamSetByUser("electric_field"))
  {
    paramError("solver",
               "Solver mode is electromagnetic, but potential was provided. Please either change "
               "the mode or provide an electric field variable.");
  }
  else if (parameters.isParamSetByUser("electric_field") &&
           parameters.isParamSetByUser("potential"))
  {
    paramError("solver",
               "Both electric field and potential variables have been provided. Please provide "
               "only one, consistent with the solver mode parameter.");
  }
  else if (!parameters.isParamSetByUser("electric_field") &&
           !parameters.isParamSetByUser("potential"))
  {
    paramError("solver",
               "Neither potential nor electric field variables are defined. Please provide a "
               "variable for field determination.");
  }
}

void
FieldSolverMaterial::computeQpProperties()
{
  if (isParamValid("potential"))
  {
    _field[_qp] = -_grad_potential[_qp];
  }
  else if (isParamValid("electric_field"))
  {
    _field[_qp] = _electric_field[_qp];
  }
}
