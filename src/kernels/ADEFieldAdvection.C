//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADEFieldAdvection.h"

registerADMooseObject("ZapdosApp", ADEFieldAdvection);

template <ComputeStage compute_stage>
InputParameters
ADEFieldAdvection<compute_stage>::validParams()
{
  InputParameters params = ADKernel<compute_stage>::validParams();
  params.addRequiredCoupledVar(
      "potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription(
      "Generic electric field driven advection term. (Densities must be in log form.)");
  return params;
}

template <ComputeStage compute_stage>
ADEFieldAdvection<compute_stage>::ADEFieldAdvection(const InputParameters & parameters)
  : ADKernel<compute_stage>(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _mu(getADMaterialProperty<Real>("mu" + _var.name())),
    _sign(getADMaterialProperty<Real>("sgn" + _var.name())),
    _grad_potential(adCoupledGradient("potential"))
{
}

// ADRealVectorValue
// ADEFieldAdvection<compute_stage>::precomputeQpResidual()
template <ComputeStage compute_stage>
ADReal
ADEFieldAdvection<compute_stage>::computeQpResidual()
{
  return _mu[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * _r_units *
         -_grad_test[_i][_qp] * _r_units;
}
