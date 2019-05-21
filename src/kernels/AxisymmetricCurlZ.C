//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "AxisymmetricCurlZ.h"

registerMooseObject("ZapdosApp", AxisymmetricCurlZ);

template <>
InputParameters
validParams<AxisymmetricCurlZ>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

AxisymmetricCurlZ::AxisymmetricCurlZ(const InputParameters & parameters) : Kernel(parameters) {}

AxisymmetricCurlZ::~AxisymmetricCurlZ() {}

Real
AxisymmetricCurlZ::computeQpResidual()
{
  return _test[_i][_qp] * (_u[_qp] / _q_point[_qp](0) + _grad_u[_qp](0));
}

Real
AxisymmetricCurlZ::computeQpJacobian()
{
  return _test[_i][_qp] * (_phi[_j][_qp] / _q_point[_qp](0) + _grad_phi[_j][_qp](0));
}
