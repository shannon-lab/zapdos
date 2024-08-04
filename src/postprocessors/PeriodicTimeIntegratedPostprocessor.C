//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PeriodicTimeIntegratedPostprocessor.h"

registerMooseObject("ZapdosApp", PeriodicTimeIntegratedPostprocessor);

InputParameters
PeriodicTimeIntegratedPostprocessor::validParams()
{
  InputParameters params = MultipliedTimeIntegratedPostprocessor::validParams();
  params.addClassDescription(
      "Integrate a Postprocessor value over a period in time using trapezoidal rule.");
  params.addRangeCheckedParam<Real>(
      "cycle_frequency",
      "cycle_frequency > 0",
      "The frequency of the process. Used to calculate the period over which you are integrating.");
  return params;
}

PeriodicTimeIntegratedPostprocessor::PeriodicTimeIntegratedPostprocessor(
    const InputParameters & parameters)
  : MultipliedTimeIntegratedPostprocessor(parameters),
    _period(1.0 / getParam<Real>("cycle_frequency")),
    _period_count(0),
    _next_period_start(_period)
{
}

void
PeriodicTimeIntegratedPostprocessor::execute()
{
  // performing the integral
  MultipliedTimeIntegratedPostprocessor::execute();
  // lets check if we will be reaching the next period on the next
  // time step
  if ((_t + _dt - _next_period_start) / _next_period_start >= 1e-6)
  {
    _period_count++;
    _next_period_start = (_period_count + 1) * _period;
    this->_value = 0;
  }
}
