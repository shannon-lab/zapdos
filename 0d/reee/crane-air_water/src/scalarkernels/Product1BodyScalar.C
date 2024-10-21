#include "Product1BodyScalar.h"

registerMooseObject("CraneApp", Product1BodyScalar);

template <>
InputParameters
validParams<Product1BodyScalar>()
{
  InputParameters params = validParams<ODEKernel>();
  params.addRequiredCoupledVar("v", "Coupled variable 1.");
  params.addCoupledVar("rate_coefficient", 0, "Coupled reaction coefficient (if equation-based).");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coefficient.");
  params.addParam<bool>("v_eq_u", false, "Whether or not u = v.");
  params.addParam<bool>(
      "rate_constant_equation", false, "True if rate constant is provided by equation.");
  return params;
}

Product1BodyScalar::Product1BodyScalar(const InputParameters & parameters)
  : ODEKernel(parameters),
    _v_var(isCoupledScalar("v") ? coupledScalar("v") : -1),
    _v(coupledScalarValue("v")),
    _rate_coefficient(coupledScalarValue("rate_coefficient")),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _v_eq_u(getParam<bool>("v_eq_u")),
    _rate_constant_equation(getParam<bool>("rate_constant_equation"))
{
}

Real
Product1BodyScalar::computeQpResidual()
{
  return -_stoichiometric_coeff * _rate_coefficient[_i] * _v[_i];
}

Real
Product1BodyScalar::computeQpJacobian()
{
  Real power, eq_u_mult, gas_mult;

  power = 0.0;
  eq_u_mult = 1.0;
  gas_mult = 1.0;

  if (isCoupledScalar("v") && _v_eq_u)
  {
    power += 1.0;
    eq_u_mult = _v[_i];
  }
  else
    gas_mult *= _v[_i];

  return -_stoichiometric_coeff * _rate_coefficient[_i] * gas_mult * power *
         std::pow(eq_u_mult, power - 1);
}

Real
Product1BodyScalar::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real power, deriv_factor, other_factor;
  power = 0;
  other_factor = 1;
  deriv_factor = 1;

  if (jvar == _v_var && !_v_eq_u)
  {
    power += 1;
    deriv_factor = _v[_i];
  }
  else
    other_factor *= _v[_i];

  return -_stoichiometric_coeff * _rate_coefficient[_i] * other_factor * power *
         std::pow(deriv_factor, power - 1);
}
