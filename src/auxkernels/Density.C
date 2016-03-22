#include "Density.h"

template<>
InputParameters validParams<Density>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredCoupledVar("density_log","The variable representing the log of the density.");
  params.addRequiredParam<bool>("convert_moles", "Whether to convert from units of moles to #.");
  return params;
}

Density::Density(const InputParameters & parameters) :
    AuxKernel(parameters),

    _convert_moles(getParam<bool>("convert_moles")),
    _density_log(coupledValue("density_log")),
    _N_A(getMaterialProperty<Real>("N_A"))
{
}

Real
Density::computeValue()
{
  if (_convert_moles)
    return std::exp(_density_log[_qp]) * _N_A[_qp];

  else
    return std::exp(_density_log[_qp]);
}
