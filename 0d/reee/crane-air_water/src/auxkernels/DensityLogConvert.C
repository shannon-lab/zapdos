#include "DensityLogConvert.h"

registerMooseObject("CraneApp", DensityLogConvert);

template <>
InputParameters
validParams<DensityLogConvert>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("density_log", "The log of a density variable.");
  params.addRequiredParam<bool>("use_moles", "Whether to convert from units of moles to #.");
  return params;
}

DensityLogConvert::DensityLogConvert(const InputParameters & parameters)
  : AuxKernel(parameters),
    _density_log(coupledValue("density_log")),
    _convert_moles(getParam<bool>("use_moles"))
    // _N_A(getMaterialProperty<Real>("N_A"))
{
}

Real
DensityLogConvert::computeValue()
{
  if (_convert_moles)
    return std::exp(_density_log[_qp]) * 6.022e23;

  else
    return std::exp(_density_log[_qp]);
}
