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

#pragma once

#include "AuxScalarKernel.h"
#include "SplineInterpolation.h"

class AuxInitialConditionScalar;

template <>
InputParameters validParams<AuxInitialConditionScalar>();

class AuxInitialConditionScalar : public AuxScalarKernel
{
public:
  AuxInitialConditionScalar(const InputParameters & parameters);

protected:
  virtual Real computeValue();
  Real _value;
};
