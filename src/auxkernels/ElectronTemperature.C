//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElectronTemperature.h"

registerMooseObject("ZapdosApp", ElectronTemperature);

InputParameters
ElectronTemperature::validParams()
{
  InputParameters params = AuxKernel::validParams();

  params.addRequiredCoupledVar("electrons", "The electron density in log form");
  params.addRequiredCoupledVar("electron_energy", "The mean electron energy density in log form");
  params.addClassDescription("Returns the electron temperature");

  return params;
}

ElectronTemperature::ElectronTemperature(const InputParameters & parameters)
  : AuxKernel(parameters),

    _electron_density(coupledValue("electrons")),
    _mean_en(coupledValue("electron_energy"))
{
}

Real
ElectronTemperature::computeValue()
{
  return 2.0 / 3 * std::exp(_mean_en[_qp] - _electron_density[_qp]);
}
