#include "CoeffDiffusion.h"


template<>
InputParameters validParams<CoeffDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

CoeffDiffusion::CoeffDiffusion(const InputParameters & parameters) :
    Diffusion(parameters),

    _diffusivity(getMaterialProperty<Real>("diff" + _var.name()))
{
}

CoeffDiffusion::~CoeffDiffusion()
{
}

Real
CoeffDiffusion::computeQpResidual()
{
  return -_diffusivity[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * -_grad_test[_i][_qp];
}

Real
CoeffDiffusion::computeQpJacobian()
{
  return -_diffusivity[_qp] * (std::exp(_u[_qp]) * _grad_phi[_j][_qp] + std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp]) * -_grad_test[_i][_qp];
}
