#include "EFieldArtDiff.h"

template<>
InputParameters validParams<EFieldArtDiff>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("potential","The potential for calculating the advection velocity.");
  params.addParam<Real>("scale",1.,"Amount to scale artificial diffusion.");
  return params;
}

EFieldArtDiff::EFieldArtDiff(const InputParameters & parameters) :
    Kernel(parameters),

    // Coupled variables

    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),
    _scale(getParam<Real>("scale")),

    // Material properties

    _mu(getMaterialProperty<Real>("mu"+_var.name()))
{
}

EFieldArtDiff::~EFieldArtDiff()
{
}

Real
EFieldArtDiff::computeQpResidual()
{
  Real  vd_mag = _mu[_qp]*_grad_potential[_qp].size();
  Real  delta = vd_mag*_current_elem->hmax()/2.0;

  return -_grad_test[_i][_qp]*(-delta*std::exp(_u[_qp])*_grad_u[_qp]) * _scale;
}

Real
EFieldArtDiff::computeQpJacobian()
{
  Real  vd_mag = _mu[_qp]*_grad_potential[_qp].size();
  Real  delta = vd_mag*_current_elem->hmax()/2.0;

  return -_grad_test[_i][_qp]*(-delta*(std::exp(_u[_qp])*_phi[_j][_qp]*_grad_u[_qp] + std::exp(_u[_qp])*_grad_phi[_j][_qp])) * _scale;
}

Real
EFieldArtDiff::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id) {
    Real  vd_mag = _mu[_qp]*_grad_potential[_qp].size();
    Real  d_vd_mag_d_potential = _mu[_qp]*_grad_potential[_qp]*_grad_phi[_j][_qp]/(_grad_potential[_qp].size()+std::numeric_limits<double>::epsilon());
    Real d_delta_d_potential = _current_elem->hmax()/2.0*d_vd_mag_d_potential;

    return -_grad_test[_i][_qp] * -d_delta_d_potential * std::exp(_u[_qp]) * _grad_u[_qp] * _scale;
  }
  else
    return 0.0;
}
