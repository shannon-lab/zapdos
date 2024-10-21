#include "Reactant3BodyScalar.h"

registerMooseObject("CraneApp", Reactant3BodyScalar);

template <>
InputParameters
validParams<Reactant3BodyScalar>()
{
  InputParameters params = validParams<ODEKernel>();
  params.addRequiredCoupledVar("v", "Coupled variable 1.");
  params.addRequiredCoupledVar("w", "Coupled variable 2.");
  params.addCoupledVar("rate_coefficient", 0, "Coupled reaction coefficient (if equation-based).");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coefficient.");
  params.addParam<bool>("v_eq_u", false, "Whether or not u = v.");
  params.addParam<bool>("w_eq_u", false, "Whether or not u = v.");
  params.addParam<bool>(
      "rate_constant_equation", false, "True if rate constant is provided by equation.");
  return params;
}

Reactant3BodyScalar::Reactant3BodyScalar(const InputParameters & parameters)
  : ODEKernel(parameters),
    _v_var(isCoupledScalar("v") ? coupledScalar("v") : -1),
    _v(coupledScalarValue("v")),
    _w_var(isCoupledScalar("w") ? coupledScalar("w") : -1),
    _w(coupledScalarValue("w")),
    _rate_coefficient(coupledScalarValue("rate_coefficient")),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _v_eq_u(getParam<bool>("v_eq_u")),
    _w_eq_u(getParam<bool>("w_eq_u")),
    _rate_constant_equation(getParam<bool>("rate_constant_equation"))
{
}

Real
Reactant3BodyScalar::computeQpResidual()
{
  return -_stoichiometric_coeff * _rate_coefficient[_i] * _u[_i] * _v[_i] * _w[_i];
}

Real
Reactant3BodyScalar::computeQpJacobian()
{
  if (_v_eq_u && _w_eq_u)
  {
    return -_stoichiometric_coeff * _rate_coefficient[_i] * 3.0 * std::pow(_u[_i], 2.0);
  }
  else if (_v_eq_u && !_w_eq_u)
  {
    return -_stoichiometric_coeff * _rate_coefficient[_i] * 2.0 * _u[_i] * _w[_i];
  }
  else if (!_v_eq_u && _w_eq_u)
  {
    return -_stoichiometric_coeff * _rate_coefficient[_i] * 2.0 * _u[_i] * _v[_i];
  }
  else
  {
    return -_stoichiometric_coeff * _rate_coefficient[_i] * _v[_i] * _w[_i];
  }
}

Real
Reactant3BodyScalar::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (isCoupledScalar("v") && isCoupledScalar("w"))
  {
    if (!_v_eq_u && !_w_eq_u)
    {
      if (_v_var != _w_var)
      {
        if (jvar == _v_var)
          return -_stoichiometric_coeff * _rate_coefficient[_i] * _u[_i] * _w[_i];
        else if (jvar == _w_var)
          return -_stoichiometric_coeff * _rate_coefficient[_i] * _u[_i] * _v[_i];
        else
          return 0.0;
      }
      else
      {
        if (jvar == _v_var)
          return -_stoichiometric_coeff * _rate_coefficient[_i] * _u[_i] * 2.0 * _v[_i];
        else
          return 0.0;
      }
    }
    else
      return 0.0;
  }
  else if (isCoupledScalar("v") && !isCoupledScalar("w"))
  {
    if (jvar == _v_var && !_v_eq_u)
    {
      return -_stoichiometric_coeff * _rate_coefficient[_i] * _u[_i] * _w[_i];
    }
    else
      return 0.0;
  }
  else if (!isCoupledScalar("v") && isCoupledScalar("w"))
  {
    if (jvar == _w_var && !_w_eq_u)
      return -_stoichiometric_coeff * _rate_coefficient[_i] * _u[_i] * _v[_i];
    else
      return 0.0;
  }
  else
    return 0.0;
}
