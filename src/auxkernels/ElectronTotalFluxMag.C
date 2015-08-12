#include "ElectronTotalFluxMag.h"

template<>
InputParameters validParams<ElectronTotalFluxMag>()
{
  InputParameters params = validParams<AuxKernel>();
  
  params.addRequiredCoupledVar("em","The electron density");
  params.addRequiredCoupledVar("potential","The potential");
  
  return params;
}

ElectronTotalFluxMag::ElectronTotalFluxMag(const InputParameters & parameters) :
    AuxKernel(parameters),

    _muem(380.0/1e4),
    _diff(1800.0/1e4), // Morrow, Ebert
    _em(coupledValue("em")),
    _grad_potential(coupledGradient("potential")),
    _grad_em(coupledGradient("em"))
{
}

Real
ElectronTotalFluxMag::computeValue()
{
  return (-_muem*-_grad_potential[_qp]*_em[_qp]-_diff*_grad_em[_qp]).size();
}

 
