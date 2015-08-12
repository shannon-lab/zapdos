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

#ifndef SRCSELFBINARYREACTION_H
#define SRCSELFBINARYREACTION_H

#include "Kernel.h"

// Forward Declaration
class SrcSelfBinaryReaction;

template<>
InputParameters validParams<SrcSelfBinaryReaction>();

class SrcSelfBinaryReaction : public Kernel
{
public:
  SrcSelfBinaryReaction(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  
  // The reaction coefficient
  Real _reaction_coeff;
  
  // The stoichiometric coeff
  Real _stoich_coeff;
  
  // Singe coupling variable
  VariableValue & _sole_reactant;
  
  // Coupling variable ID
  unsigned int _sole_reactant_id;

};
#endif //SRCSELFBINARYREACTION_H
