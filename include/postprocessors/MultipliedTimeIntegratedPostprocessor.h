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

#include "GeneralPostprocessor.h"

/**
 * Integrate a post-processor value multiplied by a normalization factor
 * over time using trapezoidal rule
 */
class MultipliedTimeIntegratedPostprocessor : public GeneralPostprocessor
{
public:
  static InputParameters validParams();

  MultipliedTimeIntegratedPostprocessor(const InputParameters & parameters);

  virtual void initialize() override {}
  virtual void execute() override;
  using Postprocessor::getValue;
  virtual Real getValue() const override;

protected:
  /// The total value of the variable
  Real _value;
  /// The normalization factor
  const Real _coeff;
  /// My old value
  const PostprocessorValue & _value_old;

  /// The current post-processor value
  const PostprocessorValue & _pps_value;

  /// The old post-processor value
  const PostprocessorValue & _pps_value_old;
};
