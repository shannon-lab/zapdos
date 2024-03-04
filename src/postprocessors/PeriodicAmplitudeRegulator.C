//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PeriodicAmplitudeRegulator.h"

registerMooseObject("ZapdosApp", PeriodicAmplitudeRegulator);

InputParameters
PeriodicAmplitudeRegulator::validParams()
{
  InputParameters params = GeneralPostprocessor::validParams();
  params.addClassDescription("Postprocessor that will modify its value by the ratio of another"
                             "postprocessor to the provided reference value");
  params.addParam<Real>("initial_value", "The initial value for this postprocessor");
  params.addParam<Real>("reference_value",
                        "The value that you want to the 'value' parameter to maintain");
  params.addParam<PostprocessorName>(
      "value", "The name of the postprocessor which will be compared to the reference");
  params.addParam<Real>(
      "start_cycle",
      1,
      "The number of cycles you want to wait before postprocessor value begins to be modified");
  params.addParam<Real>(
      "cycles_between_modification",
      0,
      "The number of cycles between the modifications of the postprocessor value");
  params.addParam<Real>(
      "cycle_frequency",
      "The frequency of the process. Used to calculate the period over which you are integrating.");
  return params;
}

PeriodicAmplitudeRegulator::PeriodicAmplitudeRegulator(const InputParameters & parameters)
  : GeneralPostprocessor(parameters),
    _reff_value(getParam<Real>("reference_value")),
    _start_cycle(getParam<Real>("start_cycle")),
    _cycles_between(getParam<Real>("cycles_between_modification")),
    _pps_value(getPostprocessorValue("value")),
    _period(1.0 / getParam<Real>("cycle_frequency")),
    _period_count(0),
    _value(getParam<Real>("initial_value"))
{
  _next_period_start = _period;
  _next_modification_start = _start_cycle * _period;
}

void
PeriodicAmplitudeRegulator::execute()
{
  // checking if we are within a close precision of the next period start
  if (std::abs(_t - _next_period_start) <= _dt * 1e-3)
  {
    _period_count += 1;
    _next_period_start = (_period_count + 1) * _period;
  }

  // checking if we are within a close precision of the next time to
  // modify the post processor value
  if (std::abs(_t - _next_modification_start) <= _dt * 1e-3)
  {
    _next_modification_start = (_period_count + _cycles_between + 1) * _period;
    this->_value = this->_value * _reff_value / _pps_value;
  }
}

Real
PeriodicAmplitudeRegulator::getValue() const
{
  return this->_value;
}
