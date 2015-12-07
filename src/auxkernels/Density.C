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

    _density_log(coupledValue("density_log")),
    _N_A(getMaterialProperty<Real>("N_A"))
{
}

Real
Density::computeValue()
{
  return std::exp(_density_log[_qp]) * _N_A[_qp];
}
