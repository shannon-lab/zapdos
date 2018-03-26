#include "EFieldArtDiff.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", EFieldArtDiff);

template <>
InputParameters
validParams<EFieldArtDiff>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("potential",
                               "The potential for calculating the advection velocity.");
  params.addParam<Real>("scale", 1., "Amount to scale artificial diffusion.");
  params.addRequiredParam<Real>("position_units", "Units of position");
  return params;
}

EFieldArtDiff::EFieldArtDiff(const InputParameters & parameters)
  : Kernel(parameters),

    // Coupled variables

    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),
    _scale(getParam<Real>("scale")),
    _r_units(1. / getParam<Real>("position_units")),

    // Material properties

    _mu(getMaterialProperty<Real>("mu" + _var.name()))
{
}

EFieldArtDiff::~EFieldArtDiff() {}

Real
EFieldArtDiff::computeQpResidual()
{
  Real vd_mag = _mu[_qp] * _grad_potential[_qp].norm() * _r_units;
  Real delta = vd_mag * _current_elem->hmax() / (2.0 * _r_units);

  return -_grad_test[_i][_qp] * _r_units * (-delta * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units) *
         _scale;
}

Real
EFieldArtDiff::computeQpJacobian()
{
  Real vd_mag = _mu[_qp] * _grad_potential[_qp].norm() * _r_units;
  Real delta = vd_mag * _current_elem->hmax() / (_r_units * 2.0);

  return -_grad_test[_i][_qp] * _r_units *
         (-delta * (std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp] * _r_units +
                    std::exp(_u[_qp]) * _grad_phi[_j][_qp] * _r_units)) *
         _scale;
}

Real
EFieldArtDiff::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    Real vd_mag = _mu[_qp] * _grad_potential[_qp].norm() * _r_units;
    Real d_vd_mag_d_potential =
        _mu[_qp] * _grad_potential[_qp] * _grad_phi[_j][_qp] * _r_units /
        (_grad_potential[_qp].norm() + std::numeric_limits<double>::epsilon());
    Real d_delta_d_potential = _current_elem->hmax() / (_r_units * 2.0) * d_vd_mag_d_potential;

    return -_grad_test[_i][_qp] * _r_units * -d_delta_d_potential * std::exp(_u[_qp]) *
           _grad_u[_qp] * _r_units * _scale;
  }
  else
    return 0.0;
}
