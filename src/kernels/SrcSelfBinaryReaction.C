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

#include "SrcSelfBinaryReaction.h"

template<>
InputParameters validParams<SrcSelfBinaryReaction>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("reaction_coeff", "The reaction coefficient for this reaction");
  params.addRequiredParam<Real>("stoich_coeff", "The stoichiometric gain/loss coefficient for this specie");
  params.addRequiredCoupledVar("sole_reactant", "The reactant undergoing reaction with itself to produce the variable specie");
  return params;
}

SrcSelfBinaryReaction::SrcSelfBinaryReaction(const InputParameters & parameters) :
    Kernel(parameters),
    
    _reaction_coeff(getParam<Real>("reaction_coeff")),
    _stoich_coeff(getParam<Real>("stoich_coeff")),
    _sole_reactant(coupledValue("sole_reactant")),
    _sole_reactant_id(coupled("sole_reactant"))
{}

Real
SrcSelfBinaryReaction::computeQpResidual()
{
  return _test[_i][_qp]*_stoich_coeff*_reaction_coeff*_sole_reactant[_qp]*_sole_reactant[_qp];
}

Real
SrcSelfBinaryReaction::computeQpJacobian()
{
  return 0.0;
}

Real
SrcSelfBinaryReaction::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _sole_reactant_id)
  {
    return _test[_i][_qp]*_stoich_coeff*_reaction_coeff*2.0*_sole_reactant[_qp]*_phi[_j][_qp];
  }
  
  return 0.0;
}
