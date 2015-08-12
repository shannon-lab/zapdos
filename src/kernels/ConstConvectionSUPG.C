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

#include "ConstConvectionSUPG.h"

template<>
InputParameters validParams<ConstConvectionSUPG>()
{
  InputParameters params = validParams<Kernel>();

  return params;
}

ConstConvectionSUPG::ConstConvectionSUPG(const InputParameters & parameters) :
    Kernel(parameters),
    
    // Input file scalars
    
    // Material properties

    _velocity(getMaterialProperty<RealVectorValue>("velocity")),
    _alpha(getMaterialProperty<Real>("alpha")),
    _velocity_norm(getMaterialProperty<RealVectorValue>("velocity_norm"))
    
    // Coupled variables
    
    // Unique to kernel
{
/*    _velocity(0) = 1.0;
    _velocity(1) = 0.0;
    _velocity(2) = 0.0; */
}

Real ConstConvectionSUPG::computeQpResidual()
{   
  return _alpha[_qp]*_current_elem->hmax()*_velocity_norm[_qp]*_grad_test[_i][_qp]*_velocity[_qp]*_grad_u[_qp];
}

Real ConstConvectionSUPG::computeQpJacobian()
{
  return _alpha[_qp]*_current_elem->hmax()*_velocity_norm[_qp]*_grad_test[_i][_qp]*_velocity[_qp]*_grad_phi[_j][_qp];
}

/* Real ConstConvectionSUPG::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _some_variable_id)
  {
    return -_u[_qp]*_velocity_coeff[_qp]*_grad_phi[_j][_qp]*_potential_mult[_qp]*_grad_test[_i][_qp];
  }
  
  return 0.0; 
} */

