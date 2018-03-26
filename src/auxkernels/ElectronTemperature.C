#include "ElectronTemperature.h"

registerMooseObject("ZapdosApp", ElectronTemperature);

template <>
InputParameters
validParams<ElectronTemperature>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredCoupledVar("electron_density", "The electron density");
  params.addRequiredCoupledVar("mean_en", "The logarathmic representation of the mean energy.");

  return params;
}

ElectronTemperature::ElectronTemperature(const InputParameters & parameters)
  : AuxKernel(parameters),

    _electron_density(coupledValue("electron_density")),
    _mean_en(coupledValue("mean_en"))
{
}

Real
ElectronTemperature::computeValue()
{
  return 2.0 / 3 * std::exp(_mean_en[_qp] - _electron_density[_qp]);
}
