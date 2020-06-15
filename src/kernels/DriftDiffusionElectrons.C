//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DriftDiffusionElectrons.h"

registerMooseObject("ZapdosApp", DriftDiffusionElectrons);

InputParameters
DriftDiffusionElectrons::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar(
      "potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredCoupledVar("mean_en",
                               "The log of the product of mean energy times electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position");
  params.addClassDescription("Electron specific drift-diffusion equation that contains both"
                             "electric field driven advection and diffusion term"
                             "(Densities must be in log form)");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

DriftDiffusionElectrons::DriftDiffusionElectrons(const InputParameters & parameters)
  : ADKernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _muem(getADMaterialProperty<Real>("muem")),
    _sign(getMaterialProperty<Real>("sgnem")),
    _diffem(getADMaterialProperty<Real>("diffem")),

    _grad_potential(adCoupledGradient("potential")),
    _mean_en(adCoupledValue("mean_en"))
{
}

ADReal
DriftDiffusionElectrons::computeQpResidual()
{
  return _muem[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * _r_units *
             -_grad_test[_i][_qp] * _r_units -
         _diffem[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
             _r_units;
}
