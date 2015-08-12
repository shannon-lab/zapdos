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

#include "ConstConvection.h"

template<>
InputParameters validParams<ConstConvection>()
{
  InputParameters params = validParams<Kernel>();

  return params;
}

ConstConvection::ConstConvection(const InputParameters & parameters) :
    Kernel(parameters),
    
    _velocity(1.0,0.0,0.0)
    
    // Input file scalars
    
    // Material properties
    
    // Coupled variables
    
    // Unique to kernel
{
/*    _velocity(0) = 1.0;
    _velocity(1) = 0.0;
    _velocity(2) = 0.0; */
}

Real ConstConvection::computeQpResidual()
{   
  return -_u[_qp]*_velocity*_grad_test[_i][_qp];
}

Real ConstConvection::computeQpJacobian()
{
  return -_phi[_j][_qp]*_velocity*_grad_test[_i][_qp];
}

/* Real ConstConvection::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _some_variable_id)
  {
    return -_u[_qp]*_velocity_coeff[_qp]*_grad_phi[_j][_qp]*_potential_mult[_qp]*_grad_test[_i][_qp];
  }
  
  return 0.0; 
} */

