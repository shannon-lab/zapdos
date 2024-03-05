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

InputParameters
ElectronTimeDerivative::validParams()
{
  InputParameters params = ADTimeKernel::validParams();
  params.addParam<bool>("lumping", false, "True for mass matrix lumping, false otherwise");
  params.addClassDescription("Generic accumulation term for variables in logarithmic form.");
  return params;
}

ElectronTimeDerivative::ElectronTimeDerivative(const InputParameters & parameters)
  : ADTimeKernel(parameters), _lumping(getParam<bool>("lumping"))
{
}

ADReal
ElectronTimeDerivative::computeQpResidual()
{
  return _test[_i][_qp] * std::exp(_u[_qp]) * _u_dot[_qp];
}
