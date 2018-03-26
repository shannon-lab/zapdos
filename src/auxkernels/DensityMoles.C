#include "DensityMoles.h"

registerMooseObject("ZapdosApp", DensityMoles);

template <>
InputParameters
validParams<DensityMoles>()
{
  InputParameters params = validParams<Density>();

  params.addRequiredParam<bool>("use_moles", "Whether to convert from units of moles to #.");
  return params;
}

DensityMoles::DensityMoles(const InputParameters & parameters)
  : Density(parameters),

    _convert_moles(getParam<bool>("use_moles")),
    _N_A(getMaterialProperty<Real>("N_A"))
{
}

Real
DensityMoles::computeValue()
{
  if (_convert_moles)
    return Density::computeValue() * _N_A[_qp];

  else
    return Density::computeValue();
}
