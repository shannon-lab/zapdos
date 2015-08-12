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

#ifndef SECONDORDERREACTION_H
#define SECONDORDERREACTION_H

#include "Kernel.h"

// Forward Declaration
class SecondOrderReaction;

template<>
InputParameters validParams<SecondOrderReaction>();

class SecondOrderReaction : public Kernel
{
public:
  SecondOrderReaction(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  
  // The reaction coefficient
  Real _reaction_coeff;
  
  // Coupling variable
  VariableValue & _reactant_two;
  
  // Coupling identifier for the second reactant
  unsigned int _reactant_two_id;

};
#endif //SECONDORDERREACTION_H
