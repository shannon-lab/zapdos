//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADCoeffDiffusionLin.h"

registerADMooseObject("ZapdosApp", ADCoeffDiffusionLin);

// defineADLegacyParams(ADCoeffDiffusionLin);
// defineADValidParams(
//    ADCoeffDiffusionLin,
//    ADKernel,
//    params.addRequiredParam<Real>("position_units", "Units of position.");
//    params.addClassDescription("Same as CoeffDiffusionLin, but the Jacobian is computed using
//    forward "
//                               "automatic differentiation."););

template <ComputeStage compute_stage>
InputParameters
ADCoeffDiffusionLin<compute_stage>::validParams()
{
  InputParameters params = ADKernel<compute_stage>::validParams();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

template <ComputeStage compute_stage>
ADCoeffDiffusionLin<compute_stage>::ADCoeffDiffusionLin(const InputParameters & parameters)
  : ADKernel<compute_stage>(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _diffusivity(getADMaterialProperty<Real>("diff" + _var.name()))
{
}

// ADRealVectorValue
// ADCoeffDiffusionLin<compute_stage>::precomputeQpResidual()
template <ComputeStage compute_stage>
ADReal
ADCoeffDiffusionLin<compute_stage>::computeQpResidual()
{
  return -_diffusivity[_qp] * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] * _r_units;
}
