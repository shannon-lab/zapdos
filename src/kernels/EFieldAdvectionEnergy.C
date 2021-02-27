//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EFieldAdvectionEnergy.h"

registerMooseObject("ZapdosApp", EFieldAdvectionEnergy);

InputParameters
EFieldAdvectionEnergy::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addRequiredCoupledVar(
      "potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredParam<Real>("position_units", "Units of position");
  params.addClassDescription("Electron energy specific electric field driven advection term"
                             "(Densities must be in log form)");
  return params;
}

EFieldAdvectionEnergy::EFieldAdvectionEnergy(const InputParameters & parameters)
  : ADKernelGrad(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _muel(getADMaterialProperty<Real>("mumean_en")),
    _sign(getMaterialProperty<Real>("sgnem")),

    // Coupled variables
    _grad_potential(adCoupledGradient("potential"))
{
}

ADRealVectorValue
EFieldAdvectionEnergy::precomputeQpResidual()
{
  // We're going to multiply by _grad_test in ADKernelGrad
  return _muel[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * _r_units * -1. *
         _r_units;
}
