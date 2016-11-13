#include "Density.h"

template<>
InputParameters validParams<Density>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredCoupledVar("density_log","The variable representing the log of the density.");
  return params;
}

Density::Density(const InputParameters & parameters) :
    AuxKernel(parameters),

    _density_log(coupledValue("density_log"))
{
}

Real
Density::computeValue()
{
  return std::exp(_density_log[_qp]);
}
