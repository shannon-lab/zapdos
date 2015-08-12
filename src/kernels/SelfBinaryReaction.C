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

#include "SelfBinaryReaction.h"

template<>
InputParameters validParams<SelfBinaryReaction>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("reaction_coeff", "The reaction coefficient of the medium");
  return params;
}

SelfBinaryReaction::SelfBinaryReaction(const InputParameters & parameters) :
    Kernel(parameters),
    
    _reaction_coeff(getParam<Real>("reaction_coeff"))
{}

Real
SelfBinaryReaction::computeQpResidual()
{
  return _test[_i][_qp]*2.0*_reaction_coeff*_u[_qp]*_u[_qp];
}

Real
SelfBinaryReaction::computeQpJacobian()
{
  return _test[_i][_qp]*2.0*2.0*_reaction_coeff*_u[_qp]*_phi[_j][_qp];
}
