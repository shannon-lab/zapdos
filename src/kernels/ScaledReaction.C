//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ScaledReaction.h"

registerMooseObject("ZapdosApp", ScaledReaction);

InputParameters
ScaledReaction::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredParam<Real>("collision_freq", "The ion-neutral collision frequency.");
  params.addClassDescription(
      "The multiple of a given variable "
      "(Used for calculating the effective ion potential for a given collision frequency)");
  return params;
}

ScaledReaction::ScaledReaction(const InputParameters & parameters)
  : ADKernel(parameters),

    _nu(getParam<Real>("collision_freq"))

{
}

ADReal
ScaledReaction::computeQpResidual()
{
  return _test[_i][_qp] * _nu * _u[_qp];
}
