//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "ElementIntegralVariablePostprocessor.h"

// Forward Declarations
class RelativeElementL2Difference;

template <>
InputParameters validParams<RelativeElementL2Difference>();

/**
 * Computes the L2-Norm difference between two solution fields.
 */
class RelativeElementL2Difference : public ElementIntegralVariablePostprocessor
{
public:
  static InputParameters validParams();

  RelativeElementL2Difference(const InputParameters & parameters);

  virtual Real getValue() override;

protected:
  virtual Real computeQpIntegral() override;

  /// The variable to compare to
  const VariableValue & _other_var;
};
