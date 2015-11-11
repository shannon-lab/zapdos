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

#include "ParamAdvection.h"

template<>
InputParameters validParams<ParamAdvection>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("vx","Velocity in x direction.");
  params.addRequiredParam<Real>("vy","Velocity in y direction.");
  params.addRequiredParam<Real>("vz","Velocity in z direction.");
  return params;
}

ParamAdvection::ParamAdvection(const InputParameters & parameters) :
    Kernel(parameters),
    
    _velocity(getParam<Real>("vx"), getParam<Real>("vy"), getParam<Real>("vz"))
{}

Real ParamAdvection::computeQpResidual()
{   
  return _velocity*_u[_qp]*-_grad_test[_i][_qp];
}

Real ParamAdvection::computeQpJacobian()
{
  return _velocity*_phi[_j][_qp]*-_grad_test[_i][_qp];
}
