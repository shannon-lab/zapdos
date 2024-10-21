#include "ScalarDiffusion.h"

registerMooseObject("CraneApp", ScalarDiffusion);

template <>
InputParameters
validParams<ScalarDiffusion>()
{
  InputParameters params = validParams<ODEKernel>();
  params.addRequiredParam<Real>("rate", "The rate of diffusion.");
  return params;
}

ScalarDiffusion::ScalarDiffusion(const InputParameters & parameters)
  : ODEKernel(parameters), _rate(getParam<Real>("rate"))
{
}

Real
ScalarDiffusion::computeQpResidual()
{
  return _rate * _u[_i];
}

Real
ScalarDiffusion::computeQpJacobian()
{
  return _rate;
}

Real
ScalarDiffusion::computeQpOffDiagJacobian(unsigned int)
{
  return 0;
}
