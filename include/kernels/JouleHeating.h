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

#ifndef JOULEHEATING_H
#define JOULEHEATING_H

#include "Kernel.h"

class JouleHeating;

template<>
InputParameters validParams<JouleHeating>();

class JouleHeating : public Kernel
{
 public:

  JouleHeating(const InputParameters & parameters);

 protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();
  
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
  
  // Input file scalars
  
  // Material properties

  const MaterialProperty<Real> & _muem;

  // Coupled variables
  
  unsigned int _potential_id;
  VariableGradient & _grad_potential;
  VariableValue & _em;
  VariableGradient & _grad_em;
  unsigned int _em_id;

  // Unique variables

  Real _T_em;
  Real _D_em;
};

#endif //JOULEHEATING_H
