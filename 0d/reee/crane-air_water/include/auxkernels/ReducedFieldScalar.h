//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "AuxScalarKernel.h"

// Forward Declarations
class ReducedFieldScalar;

template <>
InputParameters validParams<ReducedFieldScalar>();

/**
 * Explicit solve of ODE:
 *
 * dy/dt = -\lambda y  (using forward Euler)
 */
class ReducedFieldScalar : public AuxScalarKernel
{
public:
  ReducedFieldScalar(const InputParameters & parameters);
  virtual ~ReducedFieldScalar();

protected:
  virtual Real computeValue();

  const VariableValue & _electron_density;
  const VariableValue & _gas_density;
};
