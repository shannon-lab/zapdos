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

    _muem(getMaterialProperty<Real>("muem")),
    _electron_density(coupledValue("electron_density")),
    _grad_potential(coupledGradient("potential"))
{
}

Real
ElectronAdvectiveFlux::computeValue()
{
  return -_muem[_qp]*-_grad_potential[_qp](0)*std::exp(_electron_density[_qp]);
}

 
