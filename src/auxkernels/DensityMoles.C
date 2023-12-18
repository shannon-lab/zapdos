//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DensityMoles.h"

registerMooseObject("ZapdosApp", DensityMoles);

InputParameters
DensityMoles::validParams()
{
  InputParameters params = Density::validParams();

  params.addRequiredParam<bool>("use_moles", "Whether to convert from units of moles to #.");
  params.addClassDescription("Returns physical densities in units of #/m$^3$");
  return params;
}

DensityMoles::DensityMoles(const InputParameters & parameters)
  : Density(parameters),

    _convert_moles(getParam<bool>("use_moles")),
    _N_A(getMaterialProperty<Real>("N_A"))
{
}

Real
DensityMoles::computeValue()
{
  if (_convert_moles)
    return Density::computeValue() * _N_A[_qp];

  else
    return Density::computeValue();
}
