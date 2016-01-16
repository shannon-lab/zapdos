#include "CoeffDiffusionEnergy.h"


template<>
InputParameters validParams<CoeffDiffusionEnergy>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("em", "The log of the electron density.");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

CoeffDiffusionEnergy::CoeffDiffusionEnergy(const InputParameters & parameters) :
    Kernel(parameters),

    _diffel(getMaterialProperty<Real>("diffel")),
    _d_diffel_d_actual_mean_en(getMaterialProperty<Real>("d_diffel_d_actual_mean_en")),

    _em(coupledValue("em")),
    _em_id(coupled("em")),

    _d_diffel_d_u(0),
    _d_diffel_d_em(0)
{
}

CoeffDiffusionEnergy::~CoeffDiffusionEnergy()
{
}

Real
CoeffDiffusionEnergy::computeQpResidual()
{
  return -_diffel[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * -_grad_test[_i][_qp];
}

Real
CoeffDiffusionEnergy::computeQpJacobian()
{
  _d_diffel_d_u = _d_diffel_d_actual_mean_en[_qp] * std::exp(_u[_qp] - _em[_qp]) * _phi[_j][_qp];

  return -_diffel[_qp] * (std::exp(_u[_qp]) * _grad_phi[_j][_qp] + std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp]) * -_grad_test[_i][_qp] - _d_diffel_d_u * std::exp(_u[_qp]) * _grad_u[_qp] * -_grad_test[_i][_qp];
}

Real
CoeffDiffusionEnergy::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _em_id)
  {
    _d_diffel_d_em = _d_diffel_d_actual_mean_en[_qp] * std::exp(_u[_qp] - _em[_qp]) * -_phi[_j][_qp];

    return -_d_diffel_d_em * std::exp(_u[_qp]) * _grad_u[_qp] * -_grad_test[_i][_qp];
  }

  else
    return 0.;

}
