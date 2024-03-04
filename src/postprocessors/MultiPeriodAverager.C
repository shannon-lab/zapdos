//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MultiPeriodAverager.h"

registerMooseObject("ZapdosApp", MultiPeriodAverager);

InputParameters
MultiPeriodAverager::validParams()
{
  InputParameters params = GeneralPostprocessor::validParams();
  params.addClassDescription(
      "Calculate the average value of a post processor over multiple periods");
  params.addParam<Real>("number_of_periods", "The number of periods over which you are averaging");
  params.addParam<PostprocessorName>(
      "value", "The name of the postprocessor you would like to average over multiple periods");
  params.addParam<Real>(
      "cycle_frequency",
      "The frequency of the process. Used to calculate the period over which you are integrating.");
  return params;
}

MultiPeriodAverager::MultiPeriodAverager(const InputParameters & parameters)
  : GeneralPostprocessor(parameters),
    _value(0),
    _temp_value(0),
    _period_count(0),
    _period(1.0 / getParam<Real>("cycle_frequency")),
    _num_periods(getParam<Real>("number_of_periods")),
    _pps_value_old(getPostprocessorValueOld("value"))
{
  _next_period_start = _period;
}

void
MultiPeriodAverager::execute()
{
  // lets check if we have reached the next period
  if (std::abs(_t - _next_period_start) <= _dt * 1e-3)
  {
    _period_count += 1;
    _cyclic_period_count += 1;
    _next_period_start = (_period_count + 1) * _period;
    _temp_value += _pps_value_old / _num_periods;

    /// if its time to update the average reset the temporary values
    if (_cyclic_period_count == _num_periods)
    {
      _value = _temp_value;
      _cyclic_period_count = 0;
      _temp_value = 0;
    }
  }
}

Real
MultiPeriodAverager::getValue() const
{
  return _value;
}
