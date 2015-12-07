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

#include "Position.h"

template<>
InputParameters validParams<Position>()
{
  InputParameters params = validParams<AuxKernel>();
  return params;
}

Position::Position(const InputParameters & parameters) :
    AuxKernel(parameters)
{
}

Real
Position::computeValue()
{
  if (isNodal())
    return (*_current_node)(0);
  else
    return _q_point[_qp](0);
}
