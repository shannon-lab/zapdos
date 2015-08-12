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

    _muem(380.0/1e4),
    _diff(1800.0/1e4), // Morrow, Ebert
    _em(coupledValue("em")),
    _grad_potential(coupledGradient("potential")),
    _grad_em(coupledGradient("em"))
{
}

Real
ElectronTotalFlux::computeValue()
{
  return -_muem*-_grad_potential[_qp](0)*_em[_qp]-_diff*_grad_em[_qp](0);
}

 
