#include "ChargeSource.h"

template<>
InputParameters validParams<ChargeSource>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("charged", "The charged species");
  return params;
}

ChargeSource::ChargeSource(const InputParameters & parameters) :
  Kernel(parameters),

  _charged_var(*getVar("charged",0)),
  _charged(coupledValue("charged")),
  _charged_id(coupled("charged")),

  _e(getMaterialProperty<Real>("e")),
  _sgn(getMaterialProperty<Real>("sgn"+_charged_var.name()))
{}

ChargeSource::~ChargeSource()
{}

Real
ChargeSource::computeQpResidual()
{
  return -_test[_i][_qp] *_e[_qp] *_sgn[_qp] * std::exp(_charged[_qp]);
}

Real
ChargeSource::computeQpJacobian()
{
  return 0.0;
}

Real
ChargeSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _charged_id) 
    return -_test[_i][_qp] * _e[_qp] * _sgn[_qp] * std::exp(_charged[_qp]) * _phi[_j][_qp];
  else
    return 0.0;
}
