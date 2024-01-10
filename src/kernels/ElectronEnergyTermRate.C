//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElectronEnergyTermRate.h"

registerMooseObject("ZapdosApp", ElectronEnergyTermRate);

InputParameters
ElectronEnergyTermRate::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addCoupledVar("v", "The second reactant species.");
  params.addParam<bool>("elastic_collision", false, "If the collision is elastic.");
  params.addRequiredParam<std::string>("reaction", "The reaction that is adding/removing energy.");
  params.addParam<Real>("threshold_energy", 0.0, "Energy required for reaction to take place.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription(
      "Electron energy loss term for inelastic collisions"
      "using reaction rate coefficient; Threshold energy is the energy lost in Volts in a single"
      "collision (Densities must be in logarithmic form)");
  return params;
}

ElectronEnergyTermRate::ElectronEnergyTermRate(const InputParameters & parameters)
  : ADKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _elastic(getParam<bool>("elastic_collision")),
    _threshold_energy(getParam<Real>("threshold_energy")),
    _n_gas(getADMaterialProperty<Real>("n_gas")),
    _rate_coefficient(getADMaterialProperty<Real>("k_" + getParam<std::string>("reaction"))),
    _em(adCoupledValue("em")),
    _v(isCoupled("v") ? adCoupledValue("v") : _ad_zero),
    _grad_em(adCoupledGradient("em"))
{
  if (!_elastic && !isParamValid("threshold_energy"))
    mooseError("ElectronEnergyTerm: Elastic collision set to false, but no threshold energy for "
               "this reaction is provided!");

  _energy_change = _threshold_energy;
}

ADReal
ElectronEnergyTermRate::computeQpResidual()
{
  if (isCoupled("v"))
    return -_test[_i][_qp] * _rate_coefficient[_qp] * std::exp(_v[_qp]) * std::exp(_em[_qp]) *
           _energy_change;
  else
    return -_test[_i][_qp] * _rate_coefficient[_qp] * _n_gas[_qp] * std::exp(_em[_qp]) *
           _energy_change;
}
