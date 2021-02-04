//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EFieldMagnitudeSource.h"

registerMooseObject("ZapdosApp", EFieldMagnitudeSource);

InputParameters
EFieldMagnitudeSource::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("potential", "The electric potential.");
  params.addClassDescription(
      "Electric field magnitude term based on the electrostatic approximation");
  return params;
}

EFieldMagnitudeSource::EFieldMagnitudeSource(const InputParameters & parameters)
  : ADKernel(parameters), _grad_potential(adCoupledGradient("potential"))
{
}

ADReal
EFieldMagnitudeSource::computeQpResidual()
{
  return -_test[_i][_qp] * _grad_potential[_qp] * _grad_potential[_qp];
}
