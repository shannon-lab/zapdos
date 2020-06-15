//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EFieldAdvectionElectrons.h"

registerMooseObject("ZapdosApp", EFieldAdvectionElectrons);

InputParameters
EFieldAdvectionElectrons::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar(
      "potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredCoupledVar("mean_en", "The log of the mean energy.");
  params.addRequiredParam<Real>("position_units", "The units of position.");
  params.addClassDescription("Electron specific electric field driven advection term"
                             "(Electron density must be in log form)");
  return params;
}

EFieldAdvectionElectrons::EFieldAdvectionElectrons(const InputParameters & parameters)
  : ADKernel(parameters),

    _position_units(1. / getParam<Real>("position_units")),

    _muem(getADMaterialProperty<Real>("muem")),
    _sign(getMaterialProperty<Real>("sgnem")),

    // Coupled variables
    _grad_potential(adCoupledGradient("potential")),
    _mean_en(adCoupledValue("mean_en"))
{
}

ADReal
EFieldAdvectionElectrons::computeQpResidual()
{
  return _muem[_qp] * _sign[_qp] * std::exp(_u[_qp]) * -_grad_potential[_qp] * _position_units *
         -_grad_test[_i][_qp] * _position_units;
}
