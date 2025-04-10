//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElectronEnergyLossFromExcitation.h"

registerMooseObject("ZapdosApp", ElectronEnergyLossFromExcitation);

InputParameters
ElectronEnergyLossFromExcitation::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription("Electron energy loss term for inelastic excitation collisions "
                             "using Townsend coefficient, the energy lost in Volts in a single "
                             "excitation collision (Densities must be in logarithmic form)");
  return params;
}

ElectronEnergyLossFromExcitation::ElectronEnergyLossFromExcitation(
    const InputParameters & parameters)
  : ADKernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _diffem(getADMaterialProperty<Real>("diffem")),
    _muem(getADMaterialProperty<Real>("muem")),
    _alpha_ex(getADMaterialProperty<Real>("alpha_ex")),
    _Eex(getMaterialProperty<Real>("Eex")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),

    _em(adCoupledValue("em")),
    _grad_em(adCoupledGradient("em"))
{
}

ADReal
ElectronEnergyLossFromExcitation::computeQpResidual()
{
  ADReal electron_flux_mag = (-_muem[_qp] * _electric_field[_qp] * _r_units * std::exp(_em[_qp]) -
                              _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units)
                                 .norm();
  ADReal ex_term = _alpha_ex[_qp] * electron_flux_mag;

  return -_test[_i][_qp] * ex_term * -_Eex[_qp];
}
