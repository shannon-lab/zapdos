#include "ElectronDensity.h"

template<>
InputParameters validParams<ElectronDensity>()
{
  InputParameters params = validParams<AuxKernel>();
  
  params.addRequiredCoupledVar("electron_density","The electron density");
  
  return params;
}

ElectronDensity::ElectronDensity(const InputParameters & parameters) :
    AuxKernel(parameters),
    
    _electron_density(coupledValue("electron_density"))
{
}

Real
ElectronDensity::computeValue()
{
  return std::exp(_electron_density[_qp]);
}

 
