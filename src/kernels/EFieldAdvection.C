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

#include "EFieldAdvection.h"

template<>
InputParameters validParams<EFieldAdvection>()
{
  InputParameters params = validParams<Kernel>();
  //params.addRequiredParam<std::string>("mobility","What mobility to use");
  params.addRequiredParam<std::string>("var_name_string","The name of the kernel variable. Required to import the correct advection_coefficient from the material properties file.");
  params.addRequiredCoupledVar("potential", "The gradient of the potential will be used to compute the advection velocity.");
  return params;
}

EFieldAdvection::EFieldAdvection(const InputParameters & parameters) :
    Kernel(parameters),
    
    // Input Parameters
    
    // Material properties

    _advection_coeff(getMaterialProperty<Real>("EFieldAdvectionCoeff_"+getParam<std::string>("var_name_string"))),
    
    // Coupled variables
    
    _potential_id(coupled("potential")),
    _grad_potential(coupledGradient("potential"))
{}

Real EFieldAdvection::computeQpResidual()
{   
  return _advection_coeff[_qp]*_u[_qp]*-_grad_potential[_qp]*-_grad_test[_i][_qp];
}

Real EFieldAdvection::computeQpJacobian()
{
  return _advection_coeff[_qp]*_phi[_j][_qp]*-_grad_potential[_qp]*-_grad_test[_i][_qp];
}

Real EFieldAdvection::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
  return _advection_coeff[_qp]*_u[_qp]*-_grad_phi[_j][_qp]*-_grad_test[_i][_qp];
  }
  return 0.0; 
}

