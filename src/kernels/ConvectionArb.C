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

#include "ConvectionArb.h"

template<>
InputParameters validParams<ConvectionArb>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredParam<FunctionName>("velocity_function", "the name of the velocity function to utilize");

  return params;
}

ConvectionArb::ConvectionArb(const InputParameters & parameters) :
    Kernel(parameters),

    _velocity(getFunction("velocity_function"))
{
}

Real
ConvectionArb::computeQpResidual()
{
  return -_u[_qp]*_velocity.vectorValue(_t,_qp)*_grad_test[_i][_qp];
}

Real
ConvectionArb::computeQpJacobian()
{
  return -_phi[_j][_qp]*_velocity.vectorValue(_t,_qp)*_grad_test[_i][_qp];
}


