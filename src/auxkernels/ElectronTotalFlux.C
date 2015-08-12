#include "ElectronTotalFlux.h"

template<>
InputParameters validParams<ElectronTotalFlux>()
{
  InputParameters params = validParams<AuxKernel>();
  
  params.addRequiredCoupledVar("em","The electron density");
  params.addRequiredCoupledVar("potential","The potential");
  
  return params;
}

ElectronTotalFlux::ElectronTotalFlux(const InputParameters & parameters) :
    AuxKernel(parameters),

    _muem(getMaterialProperty<Real>("muem")),
    _diffem(getMaterialProperty<Real>("diffem")),
    _em(coupledValue("em")),
    _grad_potential(coupledGradient("potential")),
    _grad_em(coupledGradient("em"))
{
}

Real
ElectronTotalFlux::computeValue()
{
  return -_muem[_qp]*-_grad_potential[_qp](0)*std::exp(_em[_qp])-_diffem[_qp]*std::exp(_em[_qp])*_grad_em[_qp](0);
}

 
