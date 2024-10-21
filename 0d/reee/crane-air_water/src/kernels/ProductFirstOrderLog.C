#include "ProductFirstOrderLog.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("CraneApp", ProductFirstOrderLog);

template <>
InputParameters
validParams<ProductFirstOrderLog>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("v", "The first variable that is reacting to create u.");
  params.addRequiredParam<std::string>("reaction", "The full reaction equation.");
  params.addRequiredParam<Real>("coefficient", "The stoichiometric coeffient.");
  params.addParam<bool>("_v_eq_u", false, "If v == u.");
  return params;
}

ProductFirstOrderLog::ProductFirstOrderLog(const InputParameters & parameters)
  : Kernel(parameters),
    _v(coupledValue("v")),
    _v_id(coupled("v")),
    _reaction_coeff(getMaterialProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _stoichiometric_coeff(getParam<Real>("coefficient")),
    _v_eq_u(getParam<bool>("_v_eq_u"))
{
}

Real
ProductFirstOrderLog::computeQpResidual()
{
  return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * std::exp(_v[_qp]);
}

Real
ProductFirstOrderLog::computeQpJacobian()
{
  Real power;
  power = 0.0;

  if (_v_eq_u)
  {
    power += 1.0;
  }

  if (!_v_eq_u)
  {
    return 0.0;
  }
  else
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * power * _reaction_coeff[_qp] *
           std::exp(_v[_qp]) * _phi[_j][_qp];
  }
}

Real
ProductFirstOrderLog::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (!_v_eq_u && jvar == _v_id)
  {
    return -_test[_i][_qp] * _stoichiometric_coeff * _reaction_coeff[_qp] * std::exp(_v[_qp]) *
           _phi[_j][_qp];
  }
  else
  {
    return 0.0;
  }
}
