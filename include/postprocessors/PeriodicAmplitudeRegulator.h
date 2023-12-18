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

class PeriodicAmplitudeRegulator : public GeneralPostprocessor
{
public:
  static InputParameters validParams();

  PeriodicAmplitudeRegulator(const InputParameters & parameters);

  virtual void initialize() override {}
  virtual void execute() override;
  virtual Real getValue() const override;

protected:
  /// the value you want _pps_value to be
  const Real _reff_value;
  /// the number of cycles after which this starts to modify its value
  const Real _start_cycle;
  /// the number of cycles between value modifications
  const Real _cycles_between;
  /// the previous post processor value
  /// using this since we intend to use this with a periodic integrateor
  /// and that sets the value to 0 on the start of a new cycle
  const PostprocessorValue & _pps_value;
  /// The period of the cycles
  const Real _period;
  /// The number of periods that have passed
  Real _period_count;
  /// The next periods start time
  Real _next_period_start;
  /// The time at which we will modify the value next
  Real _next_modification_start;
  /// The postprocessor value
  Real _value;
};
