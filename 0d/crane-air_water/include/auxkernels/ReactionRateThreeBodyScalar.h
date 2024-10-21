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

// Forward Declaration
class ReactionRateThreeBodyScalar;

template <>
InputParameters validParams<ReactionRateThreeBodyScalar>();

class ReactionRateThreeBodyScalar : public AuxScalarKernel
{
public:
  ReactionRateThreeBodyScalar(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  const VariableValue & _v;
  const VariableValue & _w;
  const VariableValue & _z;

  const VariableValue & _rate_coefficient;
  Real _stoichiometric_coeff;
};
