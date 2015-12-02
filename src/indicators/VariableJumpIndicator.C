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

#include "VariableJumpIndicator.h"

template<>
InputParameters validParams<VariableJumpIndicator>()
{
  InputParameters params = validParams<JumpIndicator>();
  return params;
}


VariableJumpIndicator::VariableJumpIndicator(const InputParameters & parameters) :
    JumpIndicator(parameters)
{
}


Real
VariableJumpIndicator::computeQpIntegral()
{
  Real jump = _u[_qp] - _u_neighbor[_qp];

  return jump*jump;
}


