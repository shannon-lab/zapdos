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

#include "BovineConvection.h"

template<>
InputParameters validParams<BovineConvection>()
{
  InputParameters params = validParams<Kernel>();

  //  params.addRequiredCoupledVar("some_variable", "The gradient of this variable will be used as the velocity vector.");
  return params;
}

BovineConvection::BovineConvection(const std::string & name,
                       InputParameters parameters) :
    Kernel(name, parameters),
    
    // Input file scalars
    
    // Material properties
    
    _velocity(getMaterialProperty<RealVectorValue>("velocity"))

    /*    _velocity_coeff(getMaterialProperty<Real>("velocity_coeff")),
	  _potential_mult(getMaterialProperty<Real>("potential_mult")), */
    
    // Coupled variables
    
    /*    _some_variable_id(coupled("some_variable")),
	  _grad_some_variable(coupledGradient("some_variable")) */
{}

Real BovineConvection::computeQpResidual()
{
   
  return -_u[_qp]*_velocity[_qp]*_grad_test[_i][_qp];
}

Real BovineConvection::computeQpJacobian()
{
  return -_phi[_j][_qp]*_velocity[_qp]*_grad_test[_i][_qp];
}

/* Real BovineConvection::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _some_variable_id)
  {
    return -_u[_qp]*_velocity_coeff[_qp]*_grad_phi[_j][_qp]*_potential_mult[_qp]*_grad_test[_i][_qp];
  }
  
  return 0.0; 
} */

