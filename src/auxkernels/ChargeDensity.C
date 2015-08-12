#include "ChargeDensity.h"

template<>
InputParameters validParams<ChargeDensity>()
{
  InputParameters params = validParams<AuxKernel>();
  
  params.addRequiredCoupledVar("electron_density","The electron density");
  params.addRequiredCoupledVar("ion_density","The ion density");
  
  return params;
}

ChargeDensity::ChargeDensity(const InputParameters & parameters) :
    AuxKernel(parameters),
    
    _e(1.6e-19),
    _electron_density(coupledValue("electron_density")),
    _ion_density(coupledValue("ion_density"))
{
}

Real
ChargeDensity::computeValue()
{
  return _e*(std::exp(_ion_density[_qp])-std::exp(_electron_density[_qp]));
}

 
