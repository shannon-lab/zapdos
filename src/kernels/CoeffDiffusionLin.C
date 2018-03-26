#include "CoeffDiffusionLin.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", CoeffDiffusionLin);

template <>
InputParameters
validParams<CoeffDiffusionLin>()
{
  InputParameters params = validParams<Diffusion>();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

CoeffDiffusionLin::CoeffDiffusionLin(const InputParameters & parameters)
  : Diffusion(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _diffusivity(getMaterialProperty<Real>("diff" + _var.name()))
{
}

CoeffDiffusionLin::~CoeffDiffusionLin() {}

Real
CoeffDiffusionLin::computeQpResidual()
{
  return -_diffusivity[_qp] * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] * _r_units;
}

Real
CoeffDiffusionLin::computeQpJacobian()
{
  return -_diffusivity[_qp] * _grad_phi[_j][_qp] * _r_units * -_grad_test[_i][_qp] * _r_units;
}
