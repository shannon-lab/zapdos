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

#include "MultipliedTimeIntegratedPostprocessor.h"

/*
 *  Integrates a Postprocessor value over a period in time using trapezoidal rule.
 */
class PeriodicTimeIntegratedPostprocessor : public MultipliedTimeIntegratedPostprocessor
{
public:
  static InputParameters validParams();

  PeriodicTimeIntegratedPostprocessor(const InputParameters & parameters);

  virtual void execute() override;

protected:
  /// the period of time over which to integrate
  const Real _period;
  /// the total number of periods that have occured
  unsigned int _period_count;
  /// the point in the time when the next period begins
  Real _next_period_start;
};
