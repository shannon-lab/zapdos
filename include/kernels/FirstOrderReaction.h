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

#ifndef FIRSTORDERREACTION_H
#define FIRSTORDERREACTION_H

#include "Kernel.h"

// Forward Declaration
class FirstOrderReaction;

template<>
InputParameters validParams<FirstOrderReaction>();

class FirstOrderReaction : public Kernel
{
public:
  FirstOrderReaction(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  Real _reaction_coeff;

};
#endif //FIRSTORDERREACTION_H
