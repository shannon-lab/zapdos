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

class MultiPeriodAverager : public GeneralPostprocessor
{
public:
  static InputParameters validParams();

  MultiPeriodAverager(const InputParameters & parameters);

  virtual void initialize() override {}
  virtual void execute() override;
  using Postprocessor::getValue;
  virtual Real getValue() const override;

protected:
  /// The current post-processor value
  Real _value;
  /// Where we are going to be storing the next average while we calculate it
  Real _temp_value;
  /// The number of periods that have passed
  Real _period_count;
  /// The time when the next period starts
  Real _next_period_start;
  /// The counter for how many periods have passed since we last updated
  Real _cyclic_period_count;
  /// inverse of the frequency
  const Real _period;
  /// the number of periods over which we are averaging
  Real _num_periods;
  /// The previous post process value of the post processor we are averaging over several periods
  const PostprocessorValue & _pps_value_old;
};
