//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElectronTimeDerivative.h"

registerMooseObject("ZapdosApp", ElectronTimeDerivative);

template <>
InputParameters
validParams<ElectronTimeDerivative>()
{
  InputParameters params = validParams<TimeKernel>();
  params.addParam<bool>("lumping", false, "True for mass matrix lumping, false otherwise");
  return params;
}

ElectronTimeDerivative::ElectronTimeDerivative(const InputParameters & parameters)
  : TimeKernel(parameters), _lumping(getParam<bool>("lumping"))

{
}

Real
ElectronTimeDerivative::computeQpResidual()
{
  return _test[_i][_qp] * std::exp(_u[_qp]) * _u_dot[_qp];
}

Real
ElectronTimeDerivative::computeQpJacobian()
{
  return _test[_i][_qp] * (std::exp(_u[_qp]) * _phi[_j][_qp] * _u_dot[_qp] +
                           std::exp(_u[_qp]) * _du_dot_du[_qp] * _phi[_j][_qp]);
}
