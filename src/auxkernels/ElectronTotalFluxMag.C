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

    _muem(getMaterialProperty<Real>("muem")),
    _diffem(getMaterialProperty<Real>("diffem")),
    _em(coupledValue("em")),
    _grad_potential(coupledGradient("potential")),
    _grad_em(coupledGradient("em"))
{
}

Real
ElectronTotalFluxMag::computeValue()
{
  return std::sqrt((-_muem[_qp]*-_grad_potential[_qp]*_em[_qp]-_diffem[_qp]*_grad_em[_qp])*(-_muem[_qp]*-_grad_potential[_qp]*_em[_qp]-_diffem[_qp]*_grad_em[_qp]));
}

 
