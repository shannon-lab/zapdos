//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADCoeffDiffusion.h"

registerADMooseObject("ZapdosApp", ADCoeffDiffusion);

// defineADLegacyParams(ADCoeffDiffusion);
//defineADValidParams(
//    ADCoeffDiffusion,
//    ADKernel,
//    params.addRequiredParam<Real>("position_units", "Units of position.");
//    params.addClassDescription("Same as CoeffDiffusion, but the Jacobian is computed using forward "
//                               "automatic differentiation."););

template <ComputeStage compute_stage>
InputParameters
ADCoeffDiffusion<compute_stage>::validParams()
{
  InputParameters params = ADKernel<compute_stage>::validParams();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

template <ComputeStage compute_stage>
ADCoeffDiffusion<compute_stage>::ADCoeffDiffusion(const InputParameters & parameters)
  : ADKernel<compute_stage>(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _diffusivity(getADMaterialProperty<Real>("diff" + _var.name()))
{
}

//ADRealVectorValue
//ADCoeffDiffusion<compute_stage>::precomputeQpResidual()
template <ComputeStage compute_stage>
ADReal
ADCoeffDiffusion<compute_stage>::computeQpResidual()
{
  return -_diffusivity[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] * _r_units;
}
