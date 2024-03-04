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
  params.addParam<Real>(
      "cycle_frequency",
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
  // checking if we are on the next period or not if so reset the integral
  if (std::abs(_t - _next_period_start) <= _dt * 1e-3)
  {
    _period_count++;
    _next_period_start = (_period_count + 1) * _period;
    this->_value = 0;
  }
}
