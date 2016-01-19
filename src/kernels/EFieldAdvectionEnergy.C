#include "EFieldAdvectionEnergy.h"

template<>
InputParameters validParams<EFieldAdvectionEnergy>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredCoupledVar("em", "The log of the electron density.");
  return params;
}

EFieldAdvectionEnergy::EFieldAdvectionEnergy(const InputParameters & parameters) :
    Kernel(parameters),

    _muel(getMaterialProperty<Real>("mumean_en")),
    _d_muel_d_actual_mean_en(getMaterialProperty<Real>("d_mumean_en_d_actual_mean_en")),
    _sign(getMaterialProperty<Real>("sgnem")),

    // Coupled variables

    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential")),
    _em(coupledValue("em")),
    _em_id(coupled("em")),

    _d_actual_mean_en_d_em(0),
    _d_muel_d_em(0),
    _d_actual_mean_en_d_u(0),
    _d_muel_d_u(0)
{}

Real EFieldAdvectionEnergy::computeQpResidual()
{
  return _muel[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * -_grad_test[_i][_qp];
}

Real EFieldAdvectionEnergy::computeQpJacobian()
{
  _d_actual_mean_en_d_u = std::exp(_u[_qp] - _em[_qp]) * _phi[_j][_qp];
  _d_muel_d_u = _d_muel_d_actual_mean_en[_qp] * _d_actual_mean_en_d_u;

  return (_d_muel_d_u * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] + _muel[_qp] * _sign[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] * -_grad_potential[_qp]) * -_grad_test[_i][_qp];
}

Real EFieldAdvectionEnergy::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    return _muel[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_phi[_j][_qp] * -_grad_test[_i][_qp];
  }

  if (jvar == _em_id)
  {
    _d_actual_mean_en_d_em = std::exp(_u[_qp] - _em[_qp]) * -_phi[_j][_qp];
    _d_muel_d_em = _d_muel_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;

  return _d_muel_d_em * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * -_grad_test[_i][_qp];
  }

  else
    return 0.0;
}
