#include "ChargeSourceMoles_KV.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", ChargeSourceMoles_KV);

template <>
InputParameters
validParams<ChargeSourceMoles_KV>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("charged", "The charged species");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  return params;
}

ChargeSourceMoles_KV::ChargeSourceMoles_KV(const InputParameters & parameters)
  : Kernel(parameters),

    _charged_var(*getVar("charged", 0)),
    _charged(coupledValue("charged")),
    _charged_id(coupled("charged")),

    _e(getMaterialProperty<Real>("e")),
    _sgn(getMaterialProperty<Real>("sgn" + _charged_var.name())),
    _N_A(getMaterialProperty<Real>("N_A")),
    _potential_units(getParam<std::string>("potential_units"))
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;
}

ChargeSourceMoles_KV::~ChargeSourceMoles_KV() {}

Real
ChargeSourceMoles_KV::computeQpResidual()
{
  return -_test[_i][_qp] * _e[_qp] * _sgn[_qp] * _N_A[_qp] * std::exp(_charged[_qp]) /
         _voltage_scaling;
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
    return -_test[_i][_qp] * _e[_qp] * _sgn[_qp] * _N_A[_qp] * std::exp(_charged[_qp]) *
           _phi[_j][_qp] / _voltage_scaling;
  else
    return 0.0;
}
