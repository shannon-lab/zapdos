#include "Product3BodyScalarLog.h"

registerMooseObject("CraneApp", Product3BodyScalarLog);

template <>
InputParameters
validParams<Product3BodyScalarLog>()
{
  InputParameters params = validParams<ODEKernel>();
  params.addCoupledVar("v", 0, "Coupled variable 1.");
  params.addCoupledVar("w", 0, "Coupled variable 2.");
  params.addCoupledVar("x", 0, "Coupled variable 3.");
  params.addCoupledVar("rate_coefficient", 0, "Coupled reaction coefficient (if equation-based).");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coefficient.");
  params.addParam<bool>("v_eq_u", false, "Whether or not v = u.");
  params.addParam<bool>("w_eq_u", false, "Whether or not w = u.");
  params.addParam<bool>("x_eq_u", false, "Whether or not x = u.");
  params.addParam<bool>(
      "rate_constant_equation", false, "True if rate constant is provided by equation.");
  return params;
}

Product3BodyScalarLog::Product3BodyScalarLog(const InputParameters & parameters)
  : ODEKernel(parameters),
    _v_var(isCoupledScalar("v") ? coupledScalar("v") : 0),
    _v(coupledScalarValue("v")),
    _w_var(isCoupledScalar("w") ? coupledScalar("w") : 0),
    _w(coupledScalarValue("w")),
    _x_var(isCoupledScalar("x") ? coupledScalar("x") : 0),
    _x(coupledScalarValue("x")),
    _rate_coefficient(coupledScalarValue("rate_coefficient")),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _v_eq_u(getParam<bool>("v_eq_u")),
    _w_eq_u(getParam<bool>("w_eq_u")),
    _x_eq_u(getParam<bool>("x_eq_u")),
    _v_coupled(isCoupledScalar("v") ? true : false),
    _w_coupled(isCoupledScalar("w") ? true : false),
    _x_coupled(isCoupledScalar("x") ? true : false),
    _rate_constant_equation(getParam<bool>("rate_constant_equation"))
{
}

Real
Product3BodyScalarLog::computeQpResidual()
{
  return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(_v[_i] + _w[_i] + _x[_i]);
}

Real
Product3BodyScalarLog::computeQpJacobian()
{
  Real power;

  power = 0.0;

  if (_v_coupled && _v_eq_u)
  {
    power += 1;
  }

  if (_w_coupled && _w_eq_u)
  {
    power += 1;
  }

  if (_x_coupled && _x_eq_u)
  {
    power += 1;
  }

  return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(_v[_i] + _w[_i] + _x[_i]) *
         power;
}

Real
Product3BodyScalarLog::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real power;

  if (_v_coupled && !_v_eq_u && jvar == _v_var)
  {
    power += 1;
  }

  if (_w_coupled && !_w_eq_u && jvar == _w_var)
  {
    power += 1;
  }

  if (_x_coupled && !_x_eq_u && jvar == _x_var)
  {
    power += 1;
  }

  return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(_v[_i] + _w[_i] + _x[_i]) *
         power;
}
