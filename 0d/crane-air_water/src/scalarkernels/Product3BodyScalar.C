#include "Product3BodyScalar.h"

registerMooseObject("CraneApp", Product3BodyScalar);

template <>
InputParameters
validParams<Product3BodyScalar>()
{
  InputParameters params = validParams<ODEKernel>();
  params.addRequiredCoupledVar("v", "Coupled variable 1.");
  params.addRequiredCoupledVar("w", "Coupled variable 2.");
  params.addRequiredCoupledVar("x", "Coupled variable 3.");
  params.addCoupledVar("rate_coefficient", 0, "Coupled reaction coefficient (if equation-based).");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coefficient.");
  params.addParam<bool>("v_eq_u", false, "Whether or not v = u.");
  params.addParam<bool>("w_eq_u", false, "Whether or not w = u.");
  params.addParam<bool>("x_eq_u", false, "Whether or not x = u.");
  params.addParam<bool>(
      "rate_constant_equation", false, "True if rate constant is provided by equation.");
  return params;
}

Product3BodyScalar::Product3BodyScalar(const InputParameters & parameters)
  : ODEKernel(parameters),
    _v_var(isCoupledScalar("v") ? coupledScalar("v") : -1),
    _v(coupledScalarValue("v")),
    _w_var(isCoupledScalar("w") ? coupledScalar("w") : -1),
    _w(coupledScalarValue("w")),
    _x_var(isCoupledScalar("x") ? coupledScalar("x") : -1),
    _x(coupledScalarValue("x")),
    _rate_coefficient(coupledScalarValue("rate_coefficient")),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _v_eq_u(getParam<bool>("v_eq_u")),
    _w_eq_u(getParam<bool>("w_eq_u")),
    _x_eq_u(getParam<bool>("x_eq_u")),
    _rate_constant_equation(getParam<bool>("rate_constant_equation"))
{
}

Real
Product3BodyScalar::computeQpResidual()
{
  return -_stoichiometric_coeff * _rate_coefficient[_i] * _v[_i] * _w[_i] * _x[_i];
}

Real
Product3BodyScalar::computeQpJacobian()
{
  Real power, eq_u_mult, gas_mult;
  Real rate_constant;
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

  if (isCoupledScalar("w") && _w_eq_u)
  {
    power += 1.0;
    eq_u_mult = _w[_i];
  }
  else
    gas_mult *= _w[_i];

  if (isCoupledScalar("x") && _x_eq_u)
  {
    power += 1.0;
    eq_u_mult = _x[_i];
  }
  else
    gas_mult *= _x[_i];

  return -_stoichiometric_coeff * _rate_coefficient[_i] * gas_mult * power *
         std::pow(eq_u_mult, power - 1);
}

Real
Product3BodyScalar::computeQpOffDiagJacobian(unsigned int jvar)
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

  if (jvar == _w_var && !_w_eq_u)
  {
    power += 1;
    deriv_factor = _w[_i];
  }
  else
    other_factor *= _w[_i];

  if (jvar == _x_var && !_x_eq_u)
  {
    power += 1;
    deriv_factor = _x[_i];
  }
  else
    other_factor *= _x[_i];

  return -_stoichiometric_coeff * _rate_coefficient[_i] * other_factor * power *
         std::pow(deriv_factor, power - 1);
}
