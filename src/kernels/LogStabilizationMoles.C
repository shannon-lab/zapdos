//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "LogStabilizationMoles.h"

registerMooseObject("ZapdosApp", LogStabilizationMoles);

template <>
InputParameters
validParams<LogStabilizationMoles>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("offset",
                                "The offset parameter that goes into the exponential function");
  return params;
}

LogStabilizationMoles::LogStabilizationMoles(const InputParameters & parameters)
  : Kernel(parameters), _offset(getParam<Real>("offset"))
{
}

LogStabilizationMoles::~LogStabilizationMoles() {}

Real
LogStabilizationMoles::computeQpResidual()
{
  return -_test[_i][_qp] * std::exp(-(_offset + _u[_qp]));
}

Real
LogStabilizationMoles::computeQpJacobian()
{
  return -_test[_i][_qp] * std::exp(-(_offset + _u[_qp])) * -_phi[_j][_qp];
}
