//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PotentialGradientSource.h"

registerMooseObject("ZapdosApp", PotentialGradientSource);

InputParameters
PotentialGradientSource::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("potential", "The potential.");
  params.addClassDescription("Duplicate kernel of 'EFieldMagnitudeSource'");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

PotentialGradientSource::PotentialGradientSource(const InputParameters & parameters)
  : ADKernel(parameters), _grad_potential(adCoupledGradient("potential"))
{
}

ADReal
PotentialGradientSource::computeQpResidual()
{
  return -_test[_i][_qp] * _grad_potential[_qp] * _grad_potential[_qp];
}
