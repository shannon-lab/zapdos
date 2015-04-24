/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "ArtificialDiff.h"


template<>
InputParameters validParams<ArtificialDiff>()
{
  // Start with the parameters from our parent
  InputParameters params = validParams<Diffusion>();

  // No parameters are necessary here because we're going to get
  // permeability and viscosity from the Material
  // so we just return params...

  params.addParam<Real>("delta", 0.5, "Prefix multiplier for artificial diffusion term");
  
  params.addRequiredCoupledVar("potential", "The electrical potential");

  return params;
}


ArtificialDiff::ArtificialDiff(const std::string & name, InputParameters parameters) :
    Diffusion(name, parameters),
    
    // Input Parameters

    _delta(getParam<Real>("delta")),
    
    // Material Properties
    
    _velocity_coeff(getMaterialProperty<Real>("velocity_coeff")),
    
    // Coupled Variables
    
    _grad_potential(coupledGradient("potential"))
{
}

ArtificialDiff::~ArtificialDiff()
{
}

Real
ArtificialDiff::computeQpResidual()
{
  // Use the MaterialProperty references we stored earlier
  return _delta*_current_elem->hmax()*_grad_potential[_qp].size()* Diffusion::computeQpResidual();
}

Real
ArtificialDiff::computeQpJacobian()
{
  // Use the MaterialProperty references we stored earlier
  return _delta*_current_elem->hmax()*_grad_potential[_qp].size()*Diffusion::computeQpJacobian();
}
