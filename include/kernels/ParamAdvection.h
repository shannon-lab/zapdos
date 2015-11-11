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

#ifndef PARAMADVECTION_H
#define PARAMADVECTION_H

#include "Kernel.h"

class ParamAdvection;

template<>
InputParameters validParams<ParamAdvection>();

class ParamAdvection : public Kernel
{
 public:

  ParamAdvection(const InputParameters & parameters);

 protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  RealVectorValue _velocity;
};

#endif //PARAMADVECTION_H
