//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AccelerationByAveraging.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", AccelerationByAveraging);
/*
This acceleration scheme is based on Equation 25 in paper
DOI: https://doi.org/10.1116/1.587101 with a gamma of 1.0.

The idea behind this acceleration is to calculate the average
rate of change of a given density for a specified number of
cycles and then increase the current density by the average
rate of charge times an accelerated amount of time.

This method is meant to accelerate the initial conditions to
a better initial conditions near the beginning of the simulation.
*/

template <>
InputParameters
validParams<AccelerationByAveraging>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("density_at_start_cycle", "The accelerated density at the start of the cycle in log form");
  params.addRequiredCoupledVar("density_at_end_cycle", "The accelerated density at the end of the cycle in log form");
  params.addRequiredParam<Real>("time_of_averaging",
                        "The time difference of the averaging");
  params.addRequiredParam<Real>("time_of_acceleration",
                        "The time of acceleration");
  params.addClassDescription("An acceleration scheme based averaging a density over a periodic cycle");
  return params;
}

AccelerationByAveraging::AccelerationByAveraging(const InputParameters & parameters)
  : Kernel(parameters),
    _density_at_start_cycle(coupledValue("density_at_start_cycle")),
    _density_at_end_cycle(coupledValue("density_at_end_cycle")),
    _time_average(getParam<Real>("time_of_averaging")),
    _time_accleration(getParam<Real>("time_of_acceleration"))
{
}

AccelerationByAveraging::~AccelerationByAveraging() {}

Real
AccelerationByAveraging::computeQpResidual()
{
  Real _average_rate_of_change = (std::exp(_density_at_end_cycle[_qp]) - std::exp(_density_at_start_cycle[_qp])) / _time_average;

  return _test[_i][_qp] * (std::exp(_u[_qp]) - std::exp(_density_at_start_cycle[_qp]) - _time_accleration * _average_rate_of_change);
}

Real
AccelerationByAveraging::computeQpJacobian()
{
  return _test[_i][_qp] * std::exp(_u[_qp]) * _phi[_j][_qp];
}
