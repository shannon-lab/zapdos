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

#include "SrcSecondOrderReaction.h"

template<>
InputParameters validParams<SrcSecondOrderReaction>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("reaction_coeff", "The reaction coefficient for this reaction");
  params.addRequiredParam<Real>("stoich_coeff", "The stoichiometric gain/loss coefficient for this specie");
  params.addRequiredCoupledVar("reactant1", "Reactant 1");
  params.addRequiredCoupledVar("reactant2", "Reactant 2");
  return params;
}

SrcSecondOrderReaction::SrcSecondOrderReaction(const InputParameters & parameters) :
    Kernel(parameters),
    
    _reaction_coeff(getParam<Real>("reaction_coeff")),
    _stoich_coeff(getParam<Real>("stoich_coeff")),
    _reactant1(coupledValue("reactant1")),
    _reactant2(coupledValue("reactant2")),
    _reactant1_id(coupled("reactant1")),
    _reactant2_id(coupled("reactant2"))
{}

Real
SrcSecondOrderReaction::computeQpResidual()
{
  return _test[_i][_qp]*_stoich_coeff*_reaction_coeff*_reactant1[_qp]*_reactant2[_qp];
}

Real
SrcSecondOrderReaction::computeQpJacobian()
{
  return 0.0;
}

Real
SrcSecondOrderReaction::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _reactant1_id)
  {
    return _test[_i][_qp]*_stoich_coeff*_reaction_coeff*_reactant2[_qp]*_phi[_j][_qp];
  }
  
  if (jvar == _reactant2_id)
  {
    return _test[_i][_qp]*_stoich_coeff*_reaction_coeff*_reactant1[_qp]*_phi[_j][_qp];
  }
  
  return 0.0;
}
