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

  _mu(getMaterialProperty<Real>("mu"+_var.name())),
  _sgn(getMaterialProperty<Real>("sgn"+_var.name())),
  _diff(getMaterialProperty<Real>("diff" + _var.name())),
  // _vthermal_ip(getMaterialProperty<Real>("vthermal_ip")),
  _a(0.0),

  // coupled variables

  _grad_potential(coupledGradient("potential")),
  _potential_id(coupled("potential")),
  _grad_em(coupledGradient("em")),
  _em_id(coupled("em"))
{}

Real
GradMeanEnZeroBC::computeQpResidual()
{
  if ( _normals[_qp] * _sgn[_qp] * -_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  return _test[_i][_qp] * (_a * _mu[_qp] * _sgn[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) - _diff[_qp] * std::exp(_u[_qp]) * _grad_em[_qp]) * _normals[_qp];
}

Real
GradMeanEnZeroBC::computeQpJacobian()
{
  if ( _normals[_qp] * _sgn[_qp] * -_grad_potential[_qp] > 0.0) {
    _a = 1.0;
  }
  else {
    _a = 0.0;
  }

  return _test[_i][_qp] * (_a * _mu[_qp] * _sgn[_qp] * -_grad_potential[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] - _diff[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_em[_qp]) * _normals[_qp];
}

Real
GradMeanEnZeroBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id) {
    if ( _normals[_qp] * _sgn[_qp] * -_grad_potential[_qp] > 0.0) {
      _a = 1.0;
    }
    else {
      _a = 0.0;
    }
  return _test[_i][_qp] * (_a * _mu[_qp] * _sgn[_qp] * -_grad_phi[_j][_qp] * std::exp(_u[_qp]) * _normals[_qp]);
  }

  else if (jvar == _em_id)
  {
    return _test[_i][_qp] * -_diff[_qp] * std::exp(_u[_qp]) * _grad_phi[_j][_qp] * _normals[_qp];
  }

  else {
    return 0.0;
  }
}
