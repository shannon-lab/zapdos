#include "DriftDiffusionElectrons.h"

registerMooseObject("ZapdosApp", DriftDiffusionElectrons);

template <>
InputParameters
validParams<DriftDiffusionElectrons>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar(
      "potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredCoupledVar("mean_en",
                               "The log of the product of mean energy times electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

DriftDiffusionElectrons::DriftDiffusionElectrons(const InputParameters & parameters)
  : Kernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _muem(getMaterialProperty<Real>("muem")),
    _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
    _sign(getMaterialProperty<Real>("sgnem")),
    _diffem(getMaterialProperty<Real>("diffem")),
    _d_diffem_d_actual_mean_en(getMaterialProperty<Real>("d_diffem_d_actual_mean_en")),

    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential")),
    _mean_en(coupledValue("mean_en")),
    _mean_en_id(coupled("mean_en")),

    _d_actual_mean_en_d_mean_en(0),
    _d_muem_d_mean_en(0),
    _d_actual_mean_en_d_u(0),
    _d_muem_d_u(0),
    _d_diffem_d_u(0),
    _d_diffem_d_mean_en(0)
{
}

DriftDiffusionElectrons::~DriftDiffusionElectrons() {}

Real
DriftDiffusionElectrons::computeQpResidual()
{
  return _muem[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * _r_units *
             -_grad_test[_i][_qp] * _r_units -
         _diffem[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
             _r_units;
}

Real
DriftDiffusionElectrons::computeQpJacobian()
{
  _d_actual_mean_en_d_u = std::exp(_mean_en[_qp] - _u[_qp]) * -_phi[_j][_qp];
  _d_muem_d_u = _d_muem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_u;
  _d_diffem_d_u =
      _d_diffem_d_actual_mean_en[_qp] * std::exp(_mean_en[_qp] - _u[_qp]) * -_phi[_j][_qp];

  return (_d_muem_d_u * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * _r_units +
          _muem[_qp] * _sign[_qp] * std::exp(_u[_qp]) * _phi[_j][_qp] * -_grad_potential[_qp] *
              _r_units) *
             -_grad_test[_i][_qp] * _r_units -
         _diffem[_qp] * (std::exp(_u[_qp]) * _grad_phi[_j][_qp] * _r_units +
                         std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp] * _r_units) *
             -_grad_test[_i][_qp] * _r_units -
         _d_diffem_d_u * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
             _r_units;
}

Real
DriftDiffusionElectrons::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    return _muem[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_phi[_j][_qp] * _r_units *
           -_grad_test[_i][_qp] * _r_units;
  }
  else if (jvar == _mean_en_id)
  {
    _d_actual_mean_en_d_mean_en = std::exp(_mean_en[_qp] - _u[_qp]) * _phi[_j][_qp];
    _d_muem_d_mean_en = _d_muem_d_actual_mean_en[_qp] * _d_actual_mean_en_d_mean_en;
    _d_diffem_d_mean_en =
        _d_diffem_d_actual_mean_en[_qp] * std::exp(_mean_en[_qp] - _u[_qp]) * _phi[_j][_qp];

    return _d_muem_d_mean_en * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * _r_units *
               -_grad_test[_i][_qp] * _r_units -
           _d_diffem_d_mean_en * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units *
               -_grad_test[_i][_qp] * _r_units;
  }
  else
  {
    return 0.;
  }
}
