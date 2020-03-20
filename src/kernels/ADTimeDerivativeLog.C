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

defineADLegacyParams(ADTimeDerivativeLog);

template <ComputeStage compute_stage>
InputParameters
ADTimeDerivativeLog<compute_stage>::validParams()
{
  InputParameters params = ADTimeDerivative<compute_stage>::validParams();
  // params.addParam<bool>("lumping", false, "True for mass matrix lumping, false otherwise.");
  params.addClassDescription("Generic accumulation term for variables in log form.");
  return params;
}

template <ComputeStage compute_stage>
ADTimeDerivativeLog<compute_stage>::ADTimeDerivativeLog(const InputParameters & parameters)
  : ADTimeDerivative<compute_stage>(parameters)
{
}

// ADRealVectorValue
// ADTimeDerivativeLog<compute_stage>::precomputeQpResidual()
template <ComputeStage compute_stage>
ADReal
ADTimeDerivativeLog<compute_stage>::precomputeQpResidual()
{
  return std::exp(_u[_qp]) * ADTimeDerivative<compute_stage>::precomputeQpResidual();
}
