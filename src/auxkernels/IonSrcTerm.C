#include "IonSrcTerm.h"

template<>
InputParameters validParams<IonSrcTerm>()
{
  InputParameters params = validParams<AuxKernel>();
  
  params.addRequiredCoupledVar("potential", "The potential");
  params.addRequiredCoupledVar("electron_density", "The electron density");

  return params;
}

IonSrcTerm::IonSrcTerm(const InputParameters & parameters) :
    AuxKernel(parameters),
    
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
  return std::exp(-1.0/(_grad_potential[_qp].size()+1.0e-6))*_grad_potential[_qp].size()*_electron_density[_qp];
}
