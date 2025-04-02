//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "IonsFromIonization.h"

registerMooseObject("ZapdosApp", IonsFromIonization);

InputParameters
IonsFromIonization::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("mean_en", "The electron mean energy.");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription(
      "Rate of production of ions from ionization using Townsend coefficients "
      "(Ion density must be in logarithmic form)");
  return params;
}

IonsFromIonization::IonsFromIonization(const InputParameters & parameters)
  : ADKernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _diffem(getADMaterialProperty<Real>("diffem")),
    _muem(getADMaterialProperty<Real>("muem")),
    _alpha_iz(getADMaterialProperty<Real>("alpha_iz")),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),

    _mean_en(adCoupledValue("mean_en")),
    _em(adCoupledValue("em")),
    _grad_em(adCoupledGradient("em"))
{
}

ADReal
IonsFromIonization::computeQpResidual()
{
  ADReal electron_flux_mag = (-_muem[_qp] * _electric_field[_qp] * _r_units * std::exp(_em[_qp]) -
                              _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units)
                                 .norm();
  ADReal iz_term = _alpha_iz[_qp] * electron_flux_mag;

  return -_test[_i][_qp] * iz_term;
}
