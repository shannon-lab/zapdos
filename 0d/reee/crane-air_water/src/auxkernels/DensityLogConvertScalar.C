#include "DensityLogConvertScalar.h"

registerMooseObject("CraneApp", DensityLogConvertScalar);

template <>
InputParameters
validParams<DensityLogConvertScalar>()
{
  InputParameters params = validParams<AuxScalarKernel>();
  params.addRequiredCoupledVar("density_log", "The log of a density variable.");
  params.addRequiredParam<bool>("use_moles", "Whether to convert from units of moles to #.");
  return params;
}

DensityLogConvertScalar::DensityLogConvertScalar(const InputParameters & parameters)
  : AuxScalarKernel(parameters),
    _density_log(coupledScalarValue("density_log")),
    _convert_moles(getParam<bool>("use_moles"))
    // _N_A(getMaterialProperty<Real>("N_A"))
{
}

Real
DensityLogConvertScalar::computeValue()
{
  if (_convert_moles)
    return std::exp(_density_log[_i]) * 6.022e23;

  else
    return std::exp(_density_log[_i]);
}
