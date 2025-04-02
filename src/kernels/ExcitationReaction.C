//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ExcitationReaction.h"

registerMooseObject("ZapdosApp", ExcitationReaction);

InputParameters
ExcitationReaction::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("mean_en", "The electron mean energy.");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredParam<bool>("reactant", "Checks if the variable is the reactant.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription(
      "Rate of production of metastables from excitation using Townsend coefficients "
      "(Densities must be in logarithmic form)");
  return params;
}

ExcitationReaction::ExcitationReaction(const InputParameters & parameters)
  : ADKernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _n_gas(getMaterialProperty<Real>("n_gas")),
    _diffem(getADMaterialProperty<Real>("diffem")),
    _muem(getADMaterialProperty<Real>("muem")),
    _alpha_source(getADMaterialProperty<Real>("alpha_ex")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),
    _mean_en(adCoupledValue("mean_en")),
    _em(adCoupledValue("em")),
    _grad_em(adCoupledGradient("em")),
    _reactant(getParam<bool>("reactant"))
{
}

ADReal
ExcitationReaction::computeQpResidual()
{
  ADReal electron_flux_mag = (-_muem[_qp] * _electric_field[_qp] * _r_units * std::exp(_em[_qp]) -
                              _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units)
                                 .norm();

  // Determines if the impacted species is the reactant or a product,
  // defining townsend coefficient accordingly.
  // Currently only accepts townsend coefficients for electron-impact excitation
  // reactions with the neutral background gas, and the reverse reaction
  // ("deexcitation"). Will be generalized into separate class
  // ("ElectronImpactReaction") to accept any townsend coefficient for any
  // generic electron-impact reaction.
  if (_reactant)
  {
    ADReal alpha = _alpha_source[_qp] / _n_gas[_qp] * std::exp(_u[_qp]);
    ADReal iz_term = alpha * electron_flux_mag;
    return _test[_i][_qp] * iz_term;
  }
  else
  {
    ADReal alpha = _alpha_source[_qp];
    ADReal iz_term = alpha * electron_flux_mag;
    return -_test[_i][_qp] * iz_term;
  }
}
