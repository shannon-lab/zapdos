//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElectronEnergyLossFromElastic.h"

registerMooseObject("ZapdosApp", ElectronEnergyLossFromElastic);

InputParameters
ElectronEnergyLossFromElastic::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("potential", "The potential.");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription(
      "Electron energy loss term for elastic collisions using Townsend coefficient "
      "(Densities must be in logarithmic form)");
  return params;
}

ElectronEnergyLossFromElastic::ElectronEnergyLossFromElastic(const InputParameters & parameters)
  : ADKernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _diffem(getADMaterialProperty<Real>("diffem")),
    _muem(getADMaterialProperty<Real>("muem")),
    _alpha_iz(getADMaterialProperty<Real>("alpha_iz")),
    _massem(getMaterialProperty<Real>("massem")),
    _massGas(getMaterialProperty<Real>("massGas")),
    _alpha_el(getADMaterialProperty<Real>("alpha_el")),

    _grad_potential(adCoupledGradient("potential")),
    _em(adCoupledValue("em")),
    _grad_em(adCoupledGradient("em"))
{
}

ADReal
ElectronEnergyLossFromElastic::computeQpResidual()
{
  ADReal electron_flux_mag = (-_muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_em[_qp]) -
                              _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units)
                                 .norm();
  ADReal Eel = -3.0 * _massem[_qp] / _massGas[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]);
  ADReal el_term = _alpha_el[_qp] * electron_flux_mag * Eel;

  return -_test[_i][_qp] * el_term;
}
