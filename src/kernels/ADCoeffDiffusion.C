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
// defineADValidParams(
//    ADCoeffDiffusion,
//    ADKernel,
//    params.addRequiredParam<Real>("position_units", "Units of position.");
//    params.addClassDescription("Same as CoeffDiffusion, but the Jacobian is computed using forward
//    "
//                               "automatic differentiation."););

InputParameters
ADCoeffDiffusion::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

ADCoeffDiffusion::ADCoeffDiffusion(const InputParameters & parameters)
  : ADKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _diffusivity(getADMaterialProperty<Real>("diff" + _var.name()))
{
}

// ADRealVectorValue
// ADCoeffDiffusion::precomputeQpResidual()
ADReal
ADCoeffDiffusion::computeQpResidual()
{
  return -_diffusivity[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
         _r_units;
}
