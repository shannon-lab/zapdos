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
    
  _muem(380.0/1e4), // Morrow, Ebert
  _diff(1800.0/1e4), // Morrow, Ebert
  _alpha(0.0),
  _Pe(0.0),
  _vd_mag(0.0),
  _delta(0.0),
    _grad_potential(coupledGradient("potential")),
    _grad_em(coupledGradient("em"))
{
}

Real
ElectronArtDiffusiveFlux::computeValue()
{
  _vd_mag = std::abs(_muem*_grad_potential[_qp].size());
  // _Pe = _vd_mag*_current_elem->hmax()/_diff;
  // _alpha = std::min(1.0,_Pe/6.0);
  // _delta = _alpha*_vd_mag*_current_elem->hmax()/2.0;
  _delta = _vd_mag*_current_elem->hmax()/2.0;

  return -_delta*_grad_em[_qp](0);
}

 
