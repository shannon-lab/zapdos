#include "Reactant2BodyScalarLog.h"

registerMooseObject("CraneApp", Reactant2BodyScalarLog);

template <>
InputParameters
validParams<Reactant2BodyScalarLog>()
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

Reactant2BodyScalarLog::Reactant2BodyScalarLog(const InputParameters & parameters)
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
Reactant2BodyScalarLog::computeQpResidual()
{
  return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(_u[_i] + _v[_i]);
}

Real
Reactant2BodyScalarLog::computeQpJacobian()
{
  Real power;

  power = 1;
  if (_v_coupled && _v_eq_u)
  {
    power += 1;
  }

  return -_stoichiometric_coeff * _rate_coefficient[_i] * power * std::exp(_u[_i] + _v[_i]);
}

Real
Reactant2BodyScalarLog::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real power;

  power = 0.0;

  if (_v_coupled && !_v_eq_u && jvar == _v_var)
  {
    power += 1;
  }

  return -_stoichiometric_coeff * _rate_coefficient[_i] * std::exp(_u[_i] + _v[_i]) * power;
}
