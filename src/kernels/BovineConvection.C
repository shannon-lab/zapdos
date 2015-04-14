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

  params.addRequiredCoupledVar("some_variable", "The gradient of this variable will be used as the velocity vector.");
  return params;
}

BovineConvection::BovineConvection(const std::string & name,
                       InputParameters parameters) :
    Kernel(name, parameters),
    _some_variable_id(coupled("some_variable")),
    _grad_some_variable(coupledGradient("some_variable"))
{}

Real BovineConvection::computeQpResidual()
{

  /* Note that the residual below is specific for electron convection because the
  constants used in the formulation are specific to electrons. This convection kernel
  does not assume that the divergence of velocity is zero like is assumed in the 
  moose tutorials and examples that I've looked at. Make sure to include appropriate
  boundary conditions to match this kernel */
   
  return -_u[_qp]*(0.0382+2.9e5/760.0)/(1.0e4)*_grad_some_variable[_qp]*_grad_test[_i][_qp];
}

Real BovineConvection::computeQpJacobian()
{
  return -_phi[_j][_qp]*(0.0382+2.9e5/760.0)/(1.0e4)*_grad_some_variable[_qp]*_grad_test[_i][_qp];
}

Real BovineConvection::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _some_variable_id)
  {
    return -_u[_qp]*(0.0382+2.9e5/760.0)/(1.0e4)*_grad_phi[_j][_qp]*_grad_test[_i][_qp];
  }
  
  return 0.0;
}

