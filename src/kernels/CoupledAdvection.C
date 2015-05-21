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

#include "CoupledAdvection.h"

template<>
InputParameters validParams<CoupledAdvection>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("some_variable", "The gradient of this variable will be used as the velocity vector.");
  return params;
}

CoupledAdvection::CoupledAdvection(const std::string & name,
                       InputParameters parameters) :
    Kernel(name, parameters),
    
    // Input file scalars
    
    // Material properties
    
    // Coupled variables
    
    _some_variable_id(coupled("some_variable")),
    _grad_some_variable(coupledGradient("some_variable"))
{}

Real CoupledAdvection::computeQpResidual()
{
   
  return -_u[_qp]*_grad_some_variable[_qp]*_grad_test[_i][_qp];
}

Real CoupledAdvection::computeQpJacobian()
{
  return -_phi[_j][_qp]*_grad_some_variable[_qp]*_grad_test[_i][_qp];
}

/* Real CoupledAdvection::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _some_variable_id)
  {
    return -_u[_qp]*_grad_some_variable_coeff[_qp]*_grad_phi[_j][_qp]*_potential_mult[_qp]*_grad_test[_i][_qp];
  }
  
  return 0.0; 
} */

