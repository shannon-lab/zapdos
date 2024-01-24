//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElectronEnergyTermElasticRate.h"

registerMooseObject("ZapdosApp", ElectronEnergyTermElasticRate);

InputParameters
ElectronEnergyTermElasticRate::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("electron_species", "The impacting (electron) species.");
  params.addRequiredCoupledVar("target_species", "The target species in this elasic reaction.");
  params.addRequiredParam<std::string>("reaction", "The reaction that is adding/removing energy.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription(
      "Electron energy loss term for elastic collisions using reaction rate coefficients "
      "(Densities must be in logarithmic form)");
  return params;
}

ElectronEnergyTermElasticRate::ElectronEnergyTermElasticRate(const InputParameters & parameters)
  : ADKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _rate_coefficient(getADMaterialProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _electron(adCoupledValue("electron_species")),
    _target(adCoupledValue("target_species")),
    _massIncident(getADMaterialProperty<Real>("mass" + (*getVar("electron_species", 0)).name())),
    _massTarget(getADMaterialProperty<Real>("mass" + (*getVar("target_species", 0)).name()))
{
}

ADReal
ElectronEnergyTermElasticRate::computeQpResidual()
{
  ADReal energy_elastic = -3.0 * (_massIncident[_qp] / _massTarget[_qp]) * 2.0 / 3.0 *
                          std::exp(_u[_qp] - _electron[_qp]);

  return -_test[_i][_qp] * _rate_coefficient[_qp] * std::exp(_target[_qp]) *
         std::exp(_electron[_qp]) * energy_elastic;
}
