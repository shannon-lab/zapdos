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

#ifndef SRCSECONDORDERREACTION_H
#define SRCSECONDORDERREACTION_H

#include "Kernel.h"

// Forward Declaration
class SrcSecondOrderReaction;

template<>
InputParameters validParams<SrcSecondOrderReaction>();

class SrcSecondOrderReaction : public Kernel
{
public:
  SrcSecondOrderReaction(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  
  // The reaction coefficient
  Real _reaction_coeff;
  
  // The stoichiometric coeff
  Real _stoich_coeff;
  
  // coupling variables
  VariableValue & _reactant1;
  VariableValue & _reactant2;
  
  // Coupling variable IDs
  unsigned int _reactant1_id;
  unsigned int _reactant2_id;

};
#endif //SRCSECONDORDERREACTION_H
