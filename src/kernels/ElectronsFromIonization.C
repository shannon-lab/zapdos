//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElectronsFromIonization.h"

registerMooseObject("ZapdosApp", ElectronsFromIonization);

InputParameters
ElectronsFromIonization::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addCoupledVar("mean_en", 3, "The electron mean energy.");
  params.addRequiredCoupledVar("em", "The electron density in logarithmic form.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<bool>("use_material_props", true, "Whether to use a material for properties.");
  params.addParam<Real>("muem", "The mobility.");
  params.addParam<Real>("diffem", "The diffusivity.");
  params.addParam<Real>("alpha_iz", "The Townsend ionization coefficient.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription(
      "Rate of production of electrons from ionization using Townsend coefficients "
      "(Electron density must be in logarithmic form)");
  return params;
}

ElectronsFromIonization::ElectronsFromIonization(const InputParameters & parameters)
  : ADKernel(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _diffem(getParam<bool>("use_material_props") ? getADMaterialProperty<Real>("diffem")
                                                 : _user_diffem),
    _muem(getParam<bool>("use_material_props") ? getADMaterialProperty<Real>("muem") : _user_muem),
    _alpha_iz(getParam<bool>("use_material_props") ? getADMaterialProperty<Real>("alpha_iz")
                                                   : _user_alpha_iz),
    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name"))),
    _mean_en(adCoupledValue("mean_en")),
    _em(adCoupledValue("em")),
    _grad_em(adCoupledGradient("em"))
{
  if (!(getParam<bool>("use_material_props")))
  {
    auto max_qps = _fe_problem.getMaxQps();
    _user_diffem.resize(max_qps);
    _user_muem.resize(max_qps);
    _user_alpha_iz.resize(max_qps);
    for (decltype(max_qps) qp = 0; qp < max_qps; ++qp)
    {
      _user_diffem[qp] = getParam<Real>("diffem");
      _user_muem[qp] = getParam<Real>("muem");
      _user_alpha_iz[qp] = getParam<Real>("alpha_iz");
    }
  }
}

// When modifying electron or potential units, nothing should be needed to be done here provided
// that material properties are properly done.
ADReal
ElectronsFromIonization::computeQpResidual()
{
  ADReal electron_flux_mag = (-_muem[_qp] * _electric_field[_qp] * _r_units * std::exp(_em[_qp]) -
                              _diffem[_qp] * std::exp(_em[_qp]) * _grad_em[_qp] * _r_units)
                                 .norm();
  ADReal iz_term = _alpha_iz[_qp] * electron_flux_mag;

  return -_test[_i][_qp] * iz_term;
}
