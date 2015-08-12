#include "ElectronDiffusiveFlux.h"

template<>
InputParameters validParams<ElectronDiffusiveFlux>()
{
  InputParameters params = validParams<AuxKernel>();
  
  params.addRequiredCoupledVar("em","The electron density");
  
  return params;
}

ElectronDiffusiveFlux::ElectronDiffusiveFlux(const InputParameters & parameters) :
    AuxKernel(parameters),
    
    _diff(1800.0/1e4),
    _grad_em(coupledGradient("em"))
{
}

Real
ElectronDiffusiveFlux::computeValue()
{
  return -_diff*_grad_em[_qp](0);
}

 
