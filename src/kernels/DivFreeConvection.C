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

#include "DivFreeConvection.h"

template<>
InputParameters validParams<DivFreeConvection>()
{
  InputParameters params = validParams<Kernel>();

  // params.addRequiredCoupledVar("some_variable", "The gradient of this variable will be used as the velocity vector.");
  return params;
}

DivFreeConvection::DivFreeConvection(const InputParameters & parameters) :
    Kernel(parameters),
    
    // Material properties
    
    /*    _velocity_coeff(getMaterialProperty<Real>("velocity_coeff")),
	  _potential_mult(getMaterialProperty<Real>("potential_mult")), */

    _velocity(getMaterialProperty<RealVectorValue>("velocity"))
    
    // Coupled variables
    
    /*    _some_variable_id(coupled("some_variable")),
	  _grad_some_variable(coupledGradient("some_variable")) */
{}

Real DivFreeConvection::computeQpResidual()
{

  /* Note that the residual below is specific for electron convection because the
  constants used in the formulation are specific to electrons. This convection kernel
  does assume that the divergence of velocity is zero like is assumed in the 
  moose tutorials and examples that I've looked at. Make sure to include appropriate
  boundary conditions to match this kernel. */
   
  return _velocity[_qp]*_grad_u[_qp]*_test[_i][_qp];
}

Real DivFreeConvection::computeQpJacobian()
{
  return _velocity[_qp]*_grad_phi[_j][_qp]*_test[_i][_qp];
}

/* Real DivFreeConvection::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _some_variable_id)
  {
    return _velocity_coeff[_qp]*_potential_mult[_qp]*_grad_phi[_j][_qp]*_grad_u[_qp]*_test[_i][_qp];
  }
  
  return 0.0;
} */

