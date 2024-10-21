#include "Reactant1BodyScalarLog.h"

registerMooseObject("CraneApp", Reactant1BodyScalarLog);

template <>
InputParameters
validParams<Reactant1BodyScalarLog>()
{
  InputParameters params = validParams<ODEKernel>();
  params.addCoupledVar("rate_coefficient", 0, "Coupled reaction coefficient (if equation-based).");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coefficient.");
  params.addParam<bool>(
      "rate_constant_equation", false, "True if rate constant is provided by equation.");
  return params;
}

Reactant1BodyScalarLog::Reactant1BodyScalarLog(const InputParameters & parameters)
  : ODEKernel(parameters),
    _rate_coefficient(coupledScalarValue("rate_coefficient")),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _rate_constant_equation(getParam<bool>("rate_constant_equation"))
{
}

Real
Reactant1BodyScalarLog::computeQpResidual()
{
  return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(_u[_i]);
}

Real
Reactant1BodyScalarLog::computeQpJacobian()
{
  return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(_u[_i]);
}
