#include "Product2BodyScalarLog.h"

registerMooseObject("CraneApp", Product2BodyScalarLog);

template <>
InputParameters
validParams<Product2BodyScalarLog>()
{
  InputParameters params = validParams<ODEKernel>();
  params.addRequiredCoupledVar("v", "Coupled variable 1.");
  params.addRequiredCoupledVar("w", "Coupled variable 2.");
  params.addCoupledVar("rate_coefficient", 0, "Coupled reaction coefficient (if equation-based).");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coefficient.");
  params.addParam<bool>("v_eq_u", false, "Whether or not u = v.");
  params.addParam<bool>("w_eq_u", false, "Whether or not u = w.");
  params.addParam<bool>(
      "rate_constant_equation", false, "True if rate constant is provided by equation.");
  return params;
}

Product2BodyScalarLog::Product2BodyScalarLog(const InputParameters & parameters)
  : ODEKernel(parameters),
    _v_var(isCoupledScalar("v") ? coupledScalar("v") : 0),
    _v(coupledScalarValue("v")),
    _w_var(isCoupledScalar("w") ? coupledScalar("w") : 0),
    _w(coupledScalarValue("w")),
    _rate_coefficient(coupledScalarValue("rate_coefficient")),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _v_eq_u(getParam<bool>("v_eq_u")),
    _w_eq_u(getParam<bool>("w_eq_u")),
    _v_coupled(isCoupledScalar("v") ? true : false),
    _w_coupled(isCoupledScalar("w") ? true : false),
    _rate_constant_equation(getParam<bool>("rate_constant_equation"))
{
}

Real
Product2BodyScalarLog::computeQpResidual()
{
  return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(_v[_i] + _w[_i]);
}

Real
Product2BodyScalarLog::computeQpJacobian()
{
  Real power;
  power = 0.0;

  // I can really check for _v_eq_u once at the beginning...no need to do it every single iteration.
  if (_v_coupled && _v_eq_u)
  {
    power += 1;
  }

  if (_w_coupled && _w_eq_u)
  {
    power += 1;
  }

  return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(_v[_i] + _w[_i]) * power;
}

Real
Product2BodyScalarLog::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real power;
  power = 0;

  if (_v_coupled && !_v_eq_u && jvar == _v_var)
  {
    power += 1;
  }

  if (_w_coupled && !_w_eq_u && jvar == _w_var)
  {
    power += 1;
  }

  return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(_v[_i] + _w[_i]) * power;
}
