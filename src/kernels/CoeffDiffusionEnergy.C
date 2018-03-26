#include "CoeffDiffusionEnergy.h"

registerMooseObject("ZapdosApp", CoeffDiffusionEnergy);

template <>
InputParameters
validParams<CoeffDiffusionEnergy>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("em", "The log of the electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

CoeffDiffusionEnergy::CoeffDiffusionEnergy(const InputParameters & parameters)
  : Kernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _diffel(getMaterialProperty<Real>("diffmean_en")),
    _d_diffel_d_actual_mean_en(getMaterialProperty<Real>("d_diffmean_en_d_actual_mean_en")),

    _em(coupledValue("em")),
    _em_id(coupled("em")),

    _d_diffel_d_u(0),
    _d_diffel_d_em(0)
{
}

CoeffDiffusionEnergy::~CoeffDiffusionEnergy() {}

Real
CoeffDiffusionEnergy::computeQpResidual()
{
  return -_diffel[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
         _r_units;
}

Real
CoeffDiffusionEnergy::computeQpJacobian()
{
  _d_diffel_d_u = _d_diffel_d_actual_mean_en[_qp] * std::exp(_u[_qp] - _em[_qp]) * _phi[_j][_qp];

  return -_diffel[_qp] * (std::exp(_u[_qp]) * _grad_phi[_j][_qp] * _r_units +
                          std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp] * _r_units) *
             -_grad_test[_i][_qp] * _r_units -
         _d_diffel_d_u * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
             _r_units;
}

Real
CoeffDiffusionEnergy::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _em_id)
  {
    _d_diffel_d_em =
        _d_diffel_d_actual_mean_en[_qp] * std::exp(_u[_qp] - _em[_qp]) * -_phi[_j][_qp];

    return -_d_diffel_d_em * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
           _r_units;
  }

  else
    return 0.;
}
