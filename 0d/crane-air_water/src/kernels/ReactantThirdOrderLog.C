#include "ReactantThirdOrderLog.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", ReactantThirdOrderLog);

template <>
InputParameters
validParams<ReactantThirdOrderLog>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("v", "The first variable that is reacting to create u.");
  params.addRequiredCoupledVar("w", "The second variable that is reacting to create u.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  params.addParam<bool>("_v_eq_u", false, "If coupled v == u.");
  params.addParam<bool>("_w_eq_u", false, "If coupled w == u.");
  return params;
}

ReactantThirdOrderLog::ReactantThirdOrderLog(const InputParameters & parameters)
  : Kernel(parameters),
    _reaction_coeff(getMaterialProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _v(coupledValue("v")),
    _w(coupledValue("w")),
    _v_id(coupled("v")),
    _w_id(coupled("w")),
    _v_eq_u(getParam<bool>("_v_eq_u")),
    _w_eq_u(getParam<bool>("_w_eq_u")),
    _stoichiometric_coeff(getParam<Real>("coefficient"))
{
}

Real
ReactantThirdOrderLog::computeQpResidual()
{
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * std::exp(_u[_qp]) *
         std::exp(_v[_qp]) * std::exp(_w[_qp]);
}

Real
ReactantThirdOrderLog::computeQpJacobian()
{
  Real power;

  power = 1;
  if (_v_eq_u)
    power += 1;

  if (_w_eq_u)
    power += 1;

  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * power *
         std::exp(_u[_qp]) * std::exp(_v[_qp]) * std::exp(_w[_qp]) * _phi[_j][_qp];
}

Real
ReactantThirdOrderLog::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (_v_id == _w_id)
  {
    if (jvar == _v_id && !_v_eq_u)
      return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * 2.0 *
             std::exp(_u[_qp]) * std::exp(_v[_qp]) * std::exp(_w[_qp]) * _phi[_j][_qp];
    else
      return 0.0;
  }
  else
  {
    if ((jvar == _v_id && !_v_eq_u) || (jvar == _w_id && !_w_eq_u))
      return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * std::exp(_u[_qp]) *
             std::exp(_v[_qp]) * std::exp(_w[_qp]) * _phi[_j][_qp];
    else
      return 0.0;
  }

  /*
Real power;

power = 0;

if (!_v_eq_u)
  power += 1;

if (!_w_eq_u)
  power += 1;

return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * power *
       std::exp(_u[_qp]) * std::exp(_v[_qp]) * std::exp(_w[_qp]) * _phi[_j][_qp];
       */
}
