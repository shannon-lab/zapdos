#include "GradMeanEnZeroBC.h"

template<>
InputParameters validParams<GradMeanEnZeroBC>()
{
    InputParameters params = validParams<IntegratedBC>();
    params.addRequiredCoupledVar("potential","The electrical potential");
    params.addRequiredCoupledVar("em", "The electron density.");
    return params;
}

GradMeanEnZeroBC::GradMeanEnZeroBC(const InputParameters & parameters) :
  IntegratedBC(parameters),

  _mumean_en(getMaterialProperty<Real>("mumean_en")),
  _d_mumean_en_d_actual_mean_en(getMaterialProperty<Real>("d_mumean_en_d_actual_mean_en")),
  _sgnmean_en(getMaterialProperty<Real>("sgnmean_en")),
  _diffmean_en(getMaterialProperty<Real>("diffmean_en")),
  _d_diffmean_en_d_actual_mean_en(getMaterialProperty<Real>("d_diffmean_en_d_actual_mean_en")),
  // _vthermal_ip(getMaterialProperty<Real>("vthermal_ip")),
  _a(0.0),

  // coupled variables

  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential")),
  _grad_em(coupledGradient("em")),
  _em(coupledValue("em")),
  _em_id(coupled("em")),
  _actual_mean_en(0)
{}

Real
GradMeanEnZeroBC::computeQpResidual()
{
  if ( _normals[_qp] * _sgnmean_en[_qp] * -_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  return _test[_i][_qp] * (_a * _mumean_en[_qp] * _sgnmean_en[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) - _diffmean_en[_qp] * std::exp(_u[_qp]) * _grad_em[_qp]) * _normals[_qp];
}

Real
GradMeanEnZeroBC::computeQpJacobian()
{
  if ( _normals[_qp] * _sgnmean_en[_qp] * -_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  _actual_mean_en = std::exp(_u[_qp] - _em[_qp]);
  return _test[_i][_qp] * (_a * _mumean_en[_qp] * _sgnmean_en[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] + _a * _d_mumean_en_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp] * _sgnmean_en[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) - _diffmean_en[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_em[_qp] - _d_diffmean_en_d_actual_mean_en[_qp] * _actual_mean_en * _phi[_j][_qp] * std::exp(_u[_qp]) * _grad_em[_qp]) * _normals[_qp];
}

Real
GradMeanEnZeroBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id) {
    if ( _normals[_qp] * _sgnmean_en[_qp] * -_grad_potential[_qp] > 0.0) {
      _a = 1.0;
    }
    else {
      _a = 0.0;
    }

  return _test[_i][_qp] * (_a * _mumean_en[_qp] * _sgnmean_en[_qp] * -_grad_phi[_j][_qp] * std::exp(_u[_qp]) * _normals[_qp]);
  }

  else if (jvar == _em_id)
  {
    if ( _normals[_qp] * _sgnmean_en[_qp] * -_grad_potential[_qp] > 0.0)
      _a = 1.0;
    else
      _a = 0.0;

    _actual_mean_en = std::exp(_u[_qp] - _em[_qp]);
    return _test[_i][_qp] * (_a * _d_mumean_en_d_actual_mean_en[_qp] * _actual_mean_en * -_phi[_j][_qp] * _sgnmean_en[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) - _d_diffmean_en_d_actual_mean_en[_qp] * _actual_mean_en * -_phi[_j][_qp] * std::exp(_u[_qp]) * _grad_em[_qp] - _diffmean_en[_qp] * std::exp(_u[_qp]) * _grad_phi[_j][_qp]) * _normals[_qp];
  }

  else
    return 0.0;
}
