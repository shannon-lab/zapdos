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

#ifndef EFIELDADVAUX_H
#define EFIELDADVAUX_H

#include "AuxKernel.h"

class EFieldAdvAux;

template<>
InputParameters validParams<EFieldAdvAux>();

class EFieldAdvAux : public AuxKernel
{
 public:

  EFieldAdvAux(const InputParameters & parameters);

 protected:

  virtual Real computeValue();
  
  // Coupled variables

  MooseVariable & _density_var;
  VariableValue & _density_log;
  VariableGradient & _grad_potential;

  // Material properties

  const MaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _sgn;
};

#endif //EFIELDADVAUX_H
