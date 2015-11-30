#include "ChargeSourceMoles.h"

template<>
InputParameters validParams<ChargeSourceMoles>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("charged", "The charged species");
  return params;
}

ChargeSourceMoles::ChargeSourceMoles(const InputParameters & parameters) :
  Kernel(parameters),

  _charged_var(*getVar("charged",0)),
  _charged(coupledValue("charged")),
  _charged_id(coupled("charged")),

  _e(getMaterialProperty<Real>("e")),
  _sgn(getMaterialProperty<Real>("sgn"+_charged_var.name())),
  _N_A(getMaterialProperty<Real>("N_A"))
{}

ChargeSourceMoles::~ChargeSourceMoles()
{}

Real
ChargeSourceMoles::computeQpResidual()
{
  return -_test[_i][_qp] *_e[_qp] *_sgn[_qp] * _N_A[_qp] * std::exp(_charged[_qp]);
}

Real
ChargeSourceMoles::computeQpJacobian()
{
  return 0.0;
}

Real
ChargeSourceMoles::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _charged_id) 
    return -_test[_i][_qp] * _e[_qp] * _sgn[_qp] * _N_A[_qp] * std::exp(_charged[_qp]) * _phi[_j][_qp];
  else
    return 0.0;
}
