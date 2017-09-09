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

#ifndef ABSVALUEAUX_H
#define ABSVALUEAUX_H

#include "AuxKernel.h"

class AbsValueAux;

template <>
InputParameters validParams<AbsValueAux>();

class AbsValueAux : public AuxKernel
{
public:
  AbsValueAux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

private:
  const VariableValue & _u;
};

#endif // ABSVALUEAUX_H
