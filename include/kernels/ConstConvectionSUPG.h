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

#ifndef CONSTCONVECTIONSUPG_H
#define CONSTCONVECTIONSUPG_H

#include "Kernel.h"

class ConstConvectionSUPG;

template<>
InputParameters validParams<ConstConvectionSUPG>();

class ConstConvectionSUPG : public Kernel
{
public:

  ConstConvectionSUPG(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();
  
  // Input file scalars
  
  // Material properties
  
  // Coupled variables

  // Unique to kernel
  
  const MaterialProperty<RealVectorValue> & _velocity;
  const MaterialProperty<Real> & _alpha;
  const MaterialProperty<RealVectorValue> & _velocity_norm;
};

#endif //CONSTCONVECTIONSUPG_H
