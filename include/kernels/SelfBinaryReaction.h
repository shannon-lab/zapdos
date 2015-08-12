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

#ifndef SELFBINARYREACTION_H
#define SELFBINARYREACTION_H

#include "Kernel.h"

// Forward Declaration
class SelfBinaryReaction;

template<>
InputParameters validParams<SelfBinaryReaction>();

class SelfBinaryReaction : public Kernel
{
public:
  SelfBinaryReaction(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
  // The reaction coefficient
  Real _reaction_coeff;

};
#endif //SELFBINARYREACTION_H
