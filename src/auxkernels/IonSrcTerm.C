#include "IonSrcTerm.h"

template<>
InputParameters validParams<IonSrcTerm>()
{
  InputParameters params = validParams<AuxKernel>();
  
  params.addRequiredCoupledVar("potential", "The potential");
  params.addRequiredCoupledVar("electron_density", "The electron density");

  return params;
}

IonSrcTerm::IonSrcTerm(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    
    // Material Properties
    
    _potential_mult(getMaterialProperty<Real>("potential_mult")),
    _velocity_coeff(getMaterialProperty<Real>("velocity_coeff")),

    // Coupled Variables
    
    _electron_density(coupledValue("electron_density")),
    _grad_potential(coupledGradient("potential"))
{
}

Real
IonSrcTerm::computeValue()
{
  return fmax(1.0e5 * std::exp(1.0 - 1.0e7/(_potential_mult[_qp]*_grad_potential[_qp].size()+1.0)) - 9697.2,0.0)*_velocity_coeff[_qp]*_potential_mult[_qp]*_grad_potential[_qp].size()*_electron_density[_qp];
}
