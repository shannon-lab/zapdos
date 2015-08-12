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

#ifndef CONSTCONVECTION_H
#define CONSTCONVECTION_H

#include "Kernel.h"

class ConstConvection;

template<>
InputParameters validParams<ConstConvection>();

class ConstConvection : public Kernel
{
public:

  ConstConvection(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();
  
  // Input file scalars
  
  // Material properties
  
  // Coupled variables

  // Unique to kernel
  
  RealVectorValue _velocity;
};

#endif //CONSTCONVECTION_H
