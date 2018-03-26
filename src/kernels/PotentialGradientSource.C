#include "PotentialGradientSource.h"

registerMooseObject("ZapdosApp", PotentialGradientSource);

template <>
InputParameters
validParams<PotentialGradientSource>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("potential", "The potential.");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

PotentialGradientSource::PotentialGradientSource(const InputParameters & parameters)
  : Kernel(parameters),
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential"))
{
}

PotentialGradientSource::~PotentialGradientSource() {}

Real
PotentialGradientSource::computeQpResidual()
{
  return -_test[_i][_qp] * _grad_potential[_qp] * _grad_potential[_qp];
}

Real
PotentialGradientSource::computeQpJacobian()
{
  return 0.;
}

Real
PotentialGradientSource::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
    return -_test[_i][_qp] * 2. * _grad_potential[_qp] * _grad_phi[_j][_qp];

  else
    return 0.;
}
