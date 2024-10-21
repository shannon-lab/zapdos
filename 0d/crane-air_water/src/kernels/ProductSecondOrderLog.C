#include "ProductSecondOrderLog.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", ProductSecondOrderLog);

template <>
InputParameters
validParams<ProductSecondOrderLog>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("v", "The first variable that is reacting to create u.");
  params.addRequiredCoupledVar("w", "The second variable that is reacting to create u.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  params.addParam<bool>("_v_eq_u", false, "If v == u.");
  params.addParam<bool>("_w_eq_u", false, "If w == u.");
  return params;
}

ProductSecondOrderLog::ProductSecondOrderLog(const InputParameters & parameters)
  : Kernel(parameters),
    _v(coupledValue("v")),
    _w(coupledValue("w")),
    _v_id(coupled("v")),
    _w_id(coupled("w")),
    _reaction_coeff(getMaterialProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _v_eq_u(getParam<bool>("_v_eq_u")),
    _w_eq_u(getParam<bool>("_w_eq_u"))
{
}

Real
ProductSecondOrderLog::computeQpResidual()
{
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * std::exp(_v[_qp]) *
         std::exp(_w[_qp]);
}

Real
ProductSecondOrderLog::computeQpJacobian()
{
  Real power;
  power = 0.0;

  if (_v_eq_u)
    power += 1.0;

  if (_w_eq_u)
    power += 1.0;

  if (!_v_eq_u && !_w_eq_u)
  {
    return 0.0;
  }
  else
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * power * _reaction_coeff[_qp] *
           std::exp(_v[_qp]) * std::exp(_w[_qp]) * _phi[_j][_qp];
  }
}

Real
ProductSecondOrderLog::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real power;
  power = 0;

  if (!_v_eq_u && jvar == _v_id)
    power += 1;

  if (!_w_eq_u && jvar == _w_id)
    power += 1;

  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * std::exp(_v[_qp]) *
         std::exp(_w[_qp]) * power * _phi[_j][_qp];
}
