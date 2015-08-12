#include "ElectronArtDiffusiveFlux.h"

template<>
InputParameters validParams<ElectronArtDiffusiveFlux>()
{
  InputParameters params = validParams<AuxKernel>();
  
  params.addRequiredCoupledVar("em","The electron density");
  params.addRequiredCoupledVar("potential","The potential");
  
  return params;
}

ElectronArtDiffusiveFlux::ElectronArtDiffusiveFlux(const InputParameters & parameters) :
    AuxKernel(parameters),

    _muem(getMaterialProperty<Real>("muem")),
    _diffem(getMaterialProperty<Real>("diffem")),
    _alpha(0.0),
    _Pe(0.0),
    _vd_mag(0.0),
    _delta(0.0),
    _grad_potential(coupledGradient("potential")),
    _em(coupledValue("em")),
    _grad_em(coupledGradient("em"))
{
}

Real
ElectronArtDiffusiveFlux::computeValue()
{
  _vd_mag = std::abs(_muem[_qp]*_grad_potential[_qp].size());
  _Pe = _vd_mag*_current_elem->hmax()/_diffem[_qp];
  _alpha = std::min(1.0,_Pe/6.0);
  _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;

  return -_delta*std::exp(_em[_qp])*_grad_em[_qp](0);
}

 
