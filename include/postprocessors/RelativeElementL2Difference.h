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

/**
 * Computes the L2-Norm difference between two solution fields.
 */
class RelativeElementL2Difference : public ElementIntegralVariablePostprocessor
{
public:
  RelativeElementL2Difference(const InputParameters & parameters);

  static InputParameters validParams();

  using Postprocessor::getValue;
  virtual PostprocessorValue getValue() const override;

protected:
  virtual Real computeQpIntegral() override;

  /// The variable to compare to
  const VariableValue & _other_var;
};
