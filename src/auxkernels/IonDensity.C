#include "IonDensity.h"

template<>
InputParameters validParams<IonDensity>()
{
  InputParameters params = validParams<AuxKernel>();
  
  params.addRequiredCoupledVar("ion_density","The electron density");
  
  return params;
}

IonDensity::IonDensity(const InputParameters & parameters) :
    AuxKernel(parameters),
    
    _ion_density(coupledValue("ion_density"))
{
}

Real
IonDensity::computeValue()
{
  return std::exp(_ion_density[_qp]);
}

 
