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
    
    _diffem(getMaterialProperty<Real>("diffem")),
    _em(coupledValue("em")),
    _grad_em(coupledGradient("em"))
{
}

Real
ElectronDiffusiveFlux::computeValue()
{
  return -_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp](0);
}

 
