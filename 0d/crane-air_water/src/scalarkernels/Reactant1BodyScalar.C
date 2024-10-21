#include "Reactant1BodyScalar.h"

registerMooseObject("CraneApp", Reactant1BodyScalar);

template <>
InputParameters
validParams<Reactant1BodyScalar>()
{
  InputParameters params = validParams<ODEKernel>();
  params.addCoupledVar("rate_coefficient", 0, "Coupled reaction coefficient (if equation-based).");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coefficient.");
  params.addParam<bool>(
      "rate_constant_equation", false, "True if rate constant is provided by equation.");
  return params;
}

Reactant1BodyScalar::Reactant1BodyScalar(const InputParameters & parameters)
  : ODEKernel(parameters),
    _rate_coefficient(coupledScalarValue("rate_coefficient")),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _rate_constant_equation(getParam<bool>("rate_constant_equation"))
{
}

Real
Reactant1BodyScalar::computeQpResidual()
{
    return -_stoichiometric_coeff * _rate_coefficient[_i] * _u[_i];
}

Real
Reactant1BodyScalar::computeQpJacobian()
{
    return -_stoichiometric_coeff * _rate_coefficient[_i];
}
