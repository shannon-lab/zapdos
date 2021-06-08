//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ThermalConductivityDiffusion.h"

registerADMooseObject("ZapdosApp", ThermalConductivityDiffusion);

InputParameters
ThermalConductivityDiffusion::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("em", "The log of the electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Electron energy diffusion term "
                             "that assumes a thermal conductivity of "
                             "$K = 3/2 D_e n_e$ ");
  return params;
}

ThermalConductivityDiffusion::ThermalConductivityDiffusion(const InputParameters & parameters)
  : ADKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _coeff(2.0 / 3.0),

    _diffem(getADMaterialProperty<Real>("diffem")),

    _em(adCoupledValue("em")),
    _grad_em(adCoupledGradient("em"))
{
}

ADReal
ThermalConductivityDiffusion::computeQpResidual()
{
  return -_grad_test[_i][_qp] * _r_units * _coeff * _diffem[_qp] *
          (std::exp(_u[_qp]) * _grad_u[_qp] * _r_units -
           std::exp(_u[_qp] - _em[_qp]) * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units);
}
