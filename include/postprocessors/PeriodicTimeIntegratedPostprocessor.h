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

class PeriodicTimeIntegratedPostprocessor : public MultipliedTimeIntegratedPostprocessor
{
public:
  static InputParameters validParams();

  PeriodicTimeIntegratedPostprocessor(const InputParameters & parameters);

  virtual void execute() override;

protected:
  const Real _period;
  Real _period_count;
  Real _next_period_start;
};
