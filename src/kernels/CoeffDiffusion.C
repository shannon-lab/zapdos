#include "CoeffDiffusion.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", CoeffDiffusion);

template <>
InputParameters
validParams<CoeffDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

CoeffDiffusion::CoeffDiffusion(const InputParameters & parameters)
  : Diffusion(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _diffusivity(getMaterialProperty<Real>("diff" + _var.name()))
{
}

CoeffDiffusion::~CoeffDiffusion() {}

Real
CoeffDiffusion::computeQpResidual()
{
  return -_diffusivity[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
         _r_units;
}

Real
CoeffDiffusion::computeQpJacobian()
{
  return -_diffusivity[_qp] * (std::exp(_u[_qp]) * _grad_phi[_j][_qp] * _r_units +
                               std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp] * _r_units) *
         -_grad_test[_i][_qp] * _r_units;
}
