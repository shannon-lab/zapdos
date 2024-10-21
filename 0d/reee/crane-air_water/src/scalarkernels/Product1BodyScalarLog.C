#include "Product1BodyScalarLog.h"

registerMooseObject("CraneApp", Product1BodyScalarLog);

template <>
InputParameters
validParams<Product1BodyScalarLog>()
{
  InputParameters params = validParams<ODEKernel>();
  params.addRequiredCoupledVar("v", "Coupled variable 1.");
  params.addCoupledVar("rate_coefficient", 0, "Coupled reaction coefficient (if equation-based).");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coefficient.");
  params.addParam<bool>("v_eq_u", false, "Whether or not u = v.");
  params.addParam<bool>("rate_constant_equation", false, "True if rate constant is provided by equation.");
  return params;
}

Product1BodyScalarLog::Product1BodyScalarLog(const InputParameters & parameters)
  : ODEKernel(parameters),
    _v_var(isCoupledScalar("v") ? coupledScalar("v") : 0),
    _v(coupledScalarValue("v")),
    _rate_coefficient(coupledScalarValue("rate_coefficient")),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _v_eq_u(getParam<bool>("v_eq_u")),
    _v_coupled(isCoupledScalar("v") ? true : false),
    _rate_constant_equation(getParam<bool>("rate_constant_equation"))
{
}

Real
Product1BodyScalarLog::computeQpResidual()
{
  return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(_v[_i]);
}

Real
Product1BodyScalarLog::computeQpJacobian()
{
  Real power, eq_u_mult, gas_mult;
  power = 0.0;
  eq_u_mult = 0.0;
  gas_mult = 0.0;

  if (_v_coupled && _v_eq_u)
  {
    power += 1;
    eq_u_mult += _v[_i];
  }
  else
    gas_mult += _v[_i];

  //return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(gas_mult) * power * std::exp(eq_u_mult);
  return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(gas_mult + eq_u_mult) * power;

  // Real mult1;
  // Real power, eq_u_mult, gas_mult;
  // Real rate_constant;
  // power = 0.0;
  // eq_u_mult = 1.0;
  // gas_mult = 1.0;
  //
  // if (isCoupledScalar("v"))
  //   mult1 = _v[_i];
  // else
  //   mult1 = _n_gas;
  //
  // if (isCoupledScalar("v") && _v_eq_u)
  // {
  //   power += 1.0;
  //   eq_u_mult = mult1;
  // }
  // else
  //   gas_mult *= mult1;
  //
  // // if (_rate_constant_equation)
  // rate_constant = _rate_coefficient[_i];
  // else
  //   rate_constant = _data.reaction_coefficient();

  // return -_stoichiometric_coeff * rate_constant * gas_mult * power * std::pow(eq_u_mult, power-1);
}

Real
Product1BodyScalarLog::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real power;
  Real gas_mult,off_diag;
  // Real rate_constant;
  power = 0;
  gas_mult = 0;
  off_diag = 0;

  if (_v_coupled && !_v_eq_u && jvar==_v_var)
  {
    power += 1;
    off_diag += _v[_i];
  }
  else
    gas_mult += _v[_i];

  //return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(gas_mult) * power * std::exp(off_diag);
  return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(gas_mult + off_diag) * power;

  // Real power, mult1, deriv_factor, other_factor;
  // Real rate_constant;
  // power = 0;
  // other_factor = 1;
  // deriv_factor = 1;
  // if (isCoupledScalar("v"))
  //   mult1 = _v[_i];
  // else
  //   mult1 = _n_gas;
  //
  // if (jvar == _v_var && !_v_eq_u)
  // {
  //   power += 1;
  //   deriv_factor = mult1;
  // }
  // else
  //   other_factor *= mult1;
  //
  // // if (_rate_constant_equation)
  // rate_constant = _rate_coefficient[_i];
  // // else
  // //   rate_constant = _data.reaction_coefficient();
  //
  // return -_stoichiometric_coeff * rate_constant * other_factor * power
  //   * std::pow(deriv_factor, power-1);
}
