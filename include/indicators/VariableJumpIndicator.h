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

#ifndef VARIABLEJUMPINDICATOR_H
#define VARIABLEJUMPINDICATOR_H

#include "JumpIndicator.h"

class VariableJumpIndicator;

template<>
InputParameters validParams<VariableJumpIndicator>();

class VariableJumpIndicator :
  public JumpIndicator
{
public:
  VariableJumpIndicator(const InputParameters & parameters);
  virtual ~VariableJumpIndicator(){};

protected:

  virtual Real computeQpIntegral();
};

#endif /* VARIABLEJUMPINDICATOR_H */
