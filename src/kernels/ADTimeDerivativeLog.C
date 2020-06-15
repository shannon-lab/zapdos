//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADTimeDerivativeLog.h"

registerADMooseObject("ZapdosApp", ADTimeDerivativeLog);

InputParameters
ADTimeDerivativeLog::validParams()
{
  InputParameters params = ADTimeDerivative::validParams();
  params.addClassDescription("Generic accumulation term for variables in log form.");
  return params;
}

ADTimeDerivativeLog::ADTimeDerivativeLog(const InputParameters & parameters)
  : ADTimeDerivative(parameters)
{
}

ADReal
ADTimeDerivativeLog::precomputeQpResidual()
{
  return std::exp(_u[_qp]) * ADTimeDerivative::precomputeQpResidual();
}
