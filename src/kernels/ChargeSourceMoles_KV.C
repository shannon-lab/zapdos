#include "ChargeSourceMoles_KV.h"

template<>
InputParameters validParams<ChargeSourceMoles_KV>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("charged", "The charged species");
  return params;
}

ChargeSourceMoles_KV::ChargeSourceMoles_KV(const InputParameters & parameters) :
  Kernel(parameters),

  _charged_var(*getVar("charged",0)),
  _charged(coupledValue("charged")),
  _charged_id(coupled("charged")),

  _e(getMaterialProperty<Real>("e")),
  _sgn(getMaterialProperty<Real>("sgn"+_charged_var.name())),
  _N_A(getMaterialProperty<Real>("N_A"))
{}

ChargeSourceMoles_KV::~ChargeSourceMoles_KV()
{}

Real
ChargeSourceMoles_KV::computeQpResidual()
{
  return -_test[_i][_qp] *_e[_qp] *_sgn[_qp] * _N_A[_qp] * std::exp(_charged[_qp]) / 1000.;
}

Real
ChargeSourceMoles_KV::computeQpJacobian()
{
  return 0.0;
}

Real
ChargeSourceMoles_KV::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _charged_id) 
    return -_test[_i][_qp] * _e[_qp] * _sgn[_qp] * _N_A[_qp] * std::exp(_charged[_qp]) * _phi[_j][_qp] / 1000.;
  else
    return 0.0;
}
