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
// #include "SplineInterpolation.h"

class MoleFraction;

template <>
InputParameters validParams<MoleFraction>();

class MoleFraction : public AuxScalarKernel
{
public:
  MoleFraction(const InputParameters & parameters);

protected:
  virtual Real computeValue();
  const VariableValue & _neutral_density;
  const VariableValue & _species_density;
};
