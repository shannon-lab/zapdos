#include "ReactantThirdOrder.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", ReactantThirdOrder);

template <>
InputParameters
validParams<ReactantThirdOrder>()
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

ReactantThirdOrder::ReactantThirdOrder(const InputParameters & parameters)
  : Kernel(parameters),
    _reaction_coeff(getMaterialProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _v(coupledValue("v")),
    _w(coupledValue("w")),
    _v_id(coupled("v")),
    _w_id(coupled("w")),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _v_eq_u(getParam<bool>("_v_eq_u")),
    _w_eq_u(getParam<bool>("_w_eq_u"))
{
}

Real
ReactantThirdOrder::computeQpResidual()
{
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _v[_qp] * _w[_qp] *
         _u[_qp];
}

Real
ReactantThirdOrder::computeQpJacobian()
{
  Real power, gas_mult;

  power = 1.0;
  gas_mult = 1.0; // multiplies the rest of the variables (!= _u)
  if (_v_eq_u)
  {
    power += 1.0;
  }
  else
    gas_mult *= _v[_qp];

  if (_w_eq_u)
  {
    power += 1.0;
  }
  else
    gas_mult *= _w[_qp];

  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * power *
         std::pow(_u[_qp], power - 1) * gas_mult * _phi[_j][_qp];
}

Real
ReactantThirdOrder::computeQpOffDiagJacobian(unsigned int jvar)
{
  Real aval;
  aval = -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * _phi[_j][_qp];

  if (!_v_eq_u && !_w_eq_u)
  {
    if (jvar == _v_id && jvar == _w_id)
      return aval * _u[_qp] * 2.0 * _v[_qp];
    else if (jvar == _v_id && jvar != _w_id)
      return aval * _u[_qp] * _w[_qp];
    else if (jvar != _v_id && jvar == _w_id)
      return aval * _u[_qp] * _v[_qp];
    else
      return 0.0;
  }
  else if (_v_eq_u && !_w_eq_u)
  {
    if (jvar == _w_id)
      return aval * _u[_qp] * _v[_qp];
    else
      return 0.0;
  }
  else if (!_v_eq_u && _w_eq_u)
  {
    if (jvar == _v_id)
      return aval * _u[_qp] * _w[_qp];
    else
      return 0.0;
  }
  else
    return 0.0;
}
