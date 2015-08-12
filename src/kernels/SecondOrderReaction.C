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

#include "SecondOrderReaction.h"

template<>
InputParameters validParams<SecondOrderReaction>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("reaction_coeff", "The reaction coefficient of the medium");
  params.addRequiredCoupledVar("reactant_two", "The reactant reacting with the equations variable");
  return params;
}

SecondOrderReaction::SecondOrderReaction(const InputParameters & parameters) :
    Kernel(parameters),
    
    _reaction_coeff(getParam<Real>("reaction_coeff")),
    // Couple to the second reactant
    _reactant_two(coupledValue("reactant_two")),
    // Get the ID for the off-jacobian calculations
    _reactant_two_id(coupled("reactant_two"))
{}

Real
SecondOrderReaction::computeQpResidual()
{
  return _test[_i][_qp]*_reaction_coeff*_reactant_two[_qp]*_u[_qp];
}

Real
SecondOrderReaction::computeQpJacobian()
{
  return _test[_i][_qp]*_reaction_coeff*_reactant_two[_qp]*_phi[_j][_qp];
}

Real
SecondOrderReaction::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _reactant_two_id)
  {
    return _test[_i][_qp]*_reaction_coeff*_phi[_j][_qp]*_u[_qp];
  }
  
  return 0.0;
}
