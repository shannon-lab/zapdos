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

#include "AuxKernel.h"

class ReactionRateTwoBody;

template <>
InputParameters validParams<ReactionRateTwoBody>();

class ReactionRateTwoBody : public AuxKernel
{
public:
  ReactionRateTwoBody(const InputParameters & parameters);

  virtual ~ReactionRateTwoBody() {}
  virtual Real computeValue();

protected:
  const VariableValue & _v;
  const VariableValue & _w;
  const MaterialProperty<Real> & _reaction_coeff;
};

