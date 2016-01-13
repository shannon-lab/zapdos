#include "HagelaarAnodicBC.h"

template<>
InputParameters validParams<HagelaarAnodicBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addRequiredParam<Real>("r", "The reflection coefficient");
    params.addRequiredCoupledVar("potential","The electric potential");
    params.addCoupledVar("mean_en", "The mean energy.");
    return params;
}

HagelaarAnodicBC::HagelaarAnodicBC(const InputParameters & parameters) :
  IntegratedBC(parameters),

  _r(getParam<Real>("r")),

// Coupled Variables
  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential")),
  _mean_en(coupledValue("mean_en")),
  _mean_en_id(coupled("mean_en")),

  _muem(getMaterialProperty<Real>("muem")),
  _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
  _mem(getMaterialProperty<Real>("mem")),
  _e(getMaterialProperty<Real>("e")),
  _a(0.5),
  _v_thermal(0),
  _d_v_thermal_d_u(0),
  _d_v_thermal_d_mean_en(0)
{}

Real
HagelaarAnodicBC::computeQpResidual()
{
  if ( _normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  _v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _mem[_qp]));

  return _test[_i][_qp] * (1. - _r) / (1. + _r) * (-(2 * _a - 1) * _muem[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) * _normals[_qp] + 0.5 * _v_thermal * std::exp(_u[_qp]));
}

Real
HagelaarAnodicBC::computeQpJacobian()
{
  if ( _normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  _v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _mem[_qp]));
  _d_v_thermal_d_u = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _mem[_qp]) * -_phi[_j][_qp];

  return _test[_i][_qp] * (1. - _r) / (1. + _r) * (-(2 * _a - 1) * _muem[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] * _normals[_qp] + 0.5 * _v_thermal * std::exp(_u[_qp]) * _phi[_j][_qp] + 0.5 * _d_v_thermal_d_u * std::exp(_u[_qp]));
}

Real
HagelaarAnodicBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    if ( _normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0) {
      _a = 1.0;
    }
    else {
      _a = 0.0;
    }

    return _test[_i][_qp] * (1. - _r) / (1. + _r) * (-(2 * _a - 1) * _muem[_qp] * -_grad_phi[_j][_qp] * std::exp(_u[_qp]) * _normals[_qp]);
  }

  else if (jvar == _mean_en_id)
  {
    _v_thermal = std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _mem[_qp]));
    _d_v_thermal_d_mean_en  = 0.5 / _v_thermal * 8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _mem[_qp]) * _phi[_j][_qp];

    return _test[_i][_qp] * (1. - _r) / (1. + _r) * (0.5 * _d_v_thermal_d_mean_en * std::exp(_u[_qp]));
  }

  else
    return 0.0;
}
