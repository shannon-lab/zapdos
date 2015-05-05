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
  
  // params.addRequiredCoupledVar("potential", "The electrical potential");

  return params;
}


ArtificialDiff::ArtificialDiff(const std::string & name, InputParameters parameters) :
    Diffusion(name, parameters),
    
    // Input Parameters
    
    // Material Properties
   
    _velocity(getMaterialProperty<RealVectorValue>("velocity")),
    _tau(getMaterialProperty<Real>("tau"))
 
    // Coupled Variables
    
    //_grad_potential(coupledGradient("potential"))
{
}

ArtificialDiff::~ArtificialDiff()
{
}

Real
ArtificialDiff::computeQpResidual()
{
  // Use the MaterialProperty references we stored earlier
  // return _delta*_current_elem->hmax()*_grad_potential[_qp].size()* Diffusion::computeQpResidual();
  if (!_crosswind)
  {
    return _tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp]*_velocity[_qp]*_grad_u[_qp];
  }
  if (_crosswind)
  {
    return _tau[_qp]*(_velocity[_qp]*_grad_test[_i][_qp] + _velocity[_qp]*_grad_u[_qp] / ( _grad_u[_qp].size() * _grad_u[_qp].size() ) * _grad_u[_qp] * _grad_test[_i][_qp] ) * _velocity[_qp] * _grad_u[_qp];
  } 
}

Real
ArtificialDiff::computeQpJacobian()
{
  // Use the MaterialProperty references we stored earlier
  // return _delta*_current_elem->hmax()*_grad_potential[_qp].size()*Diffusion::computeQpJacobian();
  if (!_crosswind)
  {
    return _tau[_qp]*_velocity[_qp]*_grad_test[_i][_qp]*_velocity[_qp]*_grad_phi[_j][_qp];
  }
  if (_crosswind)
  {
    return _tau[_qp]*(_velocity[_qp]*_grad_test[_i][_qp] + _velocity[_qp]*_grad_u[_qp] / ( _grad_u[_qp].size() * _grad_u[_qp].size() ) * _grad_u[_qp] * _grad_test[_i][_qp] ) * _velocity[_qp] * _grad_u[_qp];
  
}
