#include "ChargeDensity.h"

template<>
InputParameters validParams<ChargeDensity>()
{
  InputParameters params = validParams<AuxKernel>();
  
  params.addRequiredCoupledVar("electron_density","The electron density");
  params.addRequiredCoupledVar("ion_density","The ion density");
  
  return params;
}

ChargeDensity::ChargeDensity(const std::string & name, InputParameters parameters) :
    AuxKernel(name,parameters),
    
    _electron_density(coupledValue("electron_density")),
    _ion_density(coupledValue("ion_density")),
    _coulomb_charge(getMaterialProperty<Real>("coulomb_charge"))
{
}

Real
ChargeDensity::computeValue()
{
  return _coulomb_charge[_qp]*(_ion_density[_qp]-_electron_density[_qp]);
}

 
