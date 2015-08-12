#include "ElectronAdvectiveFlux.h"

template<>
InputParameters validParams<ElectronAdvectiveFlux>()
{
  InputParameters params = validParams<AuxKernel>();
  
  params.addRequiredCoupledVar("electron_density","The electron density");
  params.addRequiredCoupledVar("potential","The potential");
  
  return params;
}

ElectronAdvectiveFlux::ElectronAdvectiveFlux(const InputParameters & parameters) :
    AuxKernel(parameters),

    _muem(380.0/1e4),
    _electron_density(coupledValue("electron_density")),
    _grad_potential(coupledGradient("potential"))
{
}

Real
ElectronAdvectiveFlux::computeValue()
{
  return -_muem*-_grad_potential[_qp](0)*_electron_density[_qp];
}

 
