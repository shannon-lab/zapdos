#include "DriftDiffusionEnergy.h"

registerMooseObject("ZapdosApp", DriftDiffusionEnergy);

template <>
InputParameters
validParams<DriftDiffusionEnergy>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar(
      "potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredCoupledVar("em", "The log of the electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

DriftDiffusionEnergy::DriftDiffusionEnergy(const InputParameters & parameters)
  : Kernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _muel(getMaterialProperty<Real>("mumean_en")),
    _d_muel_d_actual_mean_en(getMaterialProperty<Real>("d_mumean_en_d_actual_mean_en")),
    _sign(getMaterialProperty<Real>("sgnem")),

    _diffel(getMaterialProperty<Real>("diffmean_en")),
    _d_diffel_d_actual_mean_en(getMaterialProperty<Real>("d_diffmean_en_d_actual_mean_en")),

    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential")),
    _em(coupledValue("em")),
    _em_id(coupled("em")),

    _d_actual_mean_en_d_em(0),
    _d_muel_d_em(0),
    _d_actual_mean_en_d_u(0),
    _d_muel_d_u(0),
    _d_diffel_d_u(0),
    _d_diffel_d_em(0)
{
}

DriftDiffusionEnergy::~DriftDiffusionEnergy() {}

Real
DriftDiffusionEnergy::computeQpResidual()
{
  return _muel[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * _r_units *
             -_grad_test[_i][_qp] * _r_units -
         _diffel[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
             _r_units;
}

Real
DriftDiffusionEnergy::computeQpJacobian()
{
  _d_actual_mean_en_d_u = std::exp(_u[_qp] - _em[_qp]) * _phi[_j][_qp];
  _d_muel_d_u = _d_muel_d_actual_mean_en[_qp] * _d_actual_mean_en_d_u;
  _d_diffel_d_u = _d_diffel_d_actual_mean_en[_qp] * std::exp(_u[_qp] - _em[_qp]) * _phi[_j][_qp];

  return (_d_muel_d_u * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * _r_units +
          _muel[_qp] * _sign[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] * -_grad_potential[_qp] *
              _r_units) *
             -_grad_test[_i][_qp] * _r_units -
         _diffel[_qp] * (std::exp(_u[_qp]) * _grad_phi[_j][_qp] * _r_units +
                         std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp] * _r_units) *
             -_grad_test[_i][_qp] * _r_units -
         _d_diffel_d_u * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
             _r_units;
}

Real
DriftDiffusionEnergy::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    return _muel[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_phi[_j][_qp] * _r_units *
           -_grad_test[_i][_qp] * _r_units;
  }
  else if (jvar == _em_id)
  {
    _d_actual_mean_en_d_em = std::exp(_u[_qp] - _em[_qp]) * -_phi[_j][_qp];
    _d_muel_d_em = _d_muel_d_actual_mean_en[_qp] * _d_actual_mean_en_d_em;
    _d_diffel_d_em =
        _d_diffel_d_actual_mean_en[_qp] * std::exp(_u[_qp] - _em[_qp]) * -_phi[_j][_qp];

    return _d_muel_d_em * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * _r_units *
               -_grad_test[_i][_qp] * _r_units -
           _d_diffel_d_em * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
               _r_units;
  }
  else
  {
    return 0.;
  }
}
