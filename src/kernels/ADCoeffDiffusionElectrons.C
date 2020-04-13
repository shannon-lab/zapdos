//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADCoeffDiffusionElectrons.h"

registerADMooseObject("ZapdosApp", ADCoeffDiffusionElectrons);

InputParameters
ADCoeffDiffusionElectrons::validParams()
{
  InputParameters params = ADKernel::validParams();
  // params.addRequiredCoupledVar("mean_en", "The log of the product of mean energy times electron
  // density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

ADCoeffDiffusionElectrons::ADCoeffDiffusionElectrons(const InputParameters & parameters)
  : ADKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _diffem(getADMaterialProperty<Real>("difftest"))
//_mean_en(adcoupledValue("mean_en")),
{
}

ADReal
ADCoeffDiffusionElectrons::computeQpResidual()
{
  return -_diffem[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
         _r_units;
}
