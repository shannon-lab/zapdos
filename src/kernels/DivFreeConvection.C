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

  params.addRequiredCoupledVar("some_variable", "The gradient of this variable will be used as the velocity vector.");
  return params;
}

DivFreeConvection::DivFreeConvection(const std::string & name,
                       InputParameters parameters) :
    Kernel(name, parameters),
    _some_variable_id(coupled("some_variable")),
    _grad_some_variable(coupledGradient("some_variable"))
{}

Real DivFreeConvection::computeQpResidual()
{

  /* Note that the residual below is specific for electron convection because the
  constants used in the formulation are specific to electrons. This convection kernel
  does not assume that the divergence of velocity is zero like is assumed in the 
  moose tutorials and examples that I've looked at. Make sure to include appropriate
  boundary conditions to match this kernel. Second note: I'm introducing a factor of 1.0e4
  because I am scaling the electron density and the potential so that there approximate
  magnitudes are equal */
   
  return (0.0382+2.9e5/760.0)/(1.0e4)*1.0e4*_grad_some_variable[_qp]*_grad_u[_qp]*_test[_i][_qp];
}

Real DivFreeConvection::computeQpJacobian()
{
  return (0.0382+2.9e5/760.0)/(1.0e4)*1.0e4*_grad_some_variable[_qp]*_grad_phi[_j][_qp]*_test[_i][_qp];
}

Real DivFreeConvection::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _some_variable_id)
  {
    return (0.0382+2.9e5/760.0)/(1.0e4)*1.0e4*_grad_phi[_j][_qp]*_grad_u[_qp]*_test[_i][_qp];;
  }
  
  return 0.0;
}

