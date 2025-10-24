//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "HeavySpecies.h"
#include "MooseUtils.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", HeavySpecies);
registerMooseObject("ZapdosApp", ADHeavySpecies);

template <bool is_ad>
InputParameters
HeavySpeciesTempl<is_ad>::validParams()
{
  InputParameters params = Material::validParams();

  params.addRequiredParam<std::string>("heavy_species_name", "The name of the heavy species");
  params.addRequiredParam<Real>("heavy_species_mass", "Mass of the heavy species");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<Real>("heavy_species_charge", "Charge of heavy species.");
  params.addParam<Real>("time_units", 1, "Units of time");
  params.addParam<Real>("mobility", "The species mobility (if applicable).");
  params.addParam<Real>("diffusivity", "The species diffusivity (if applicable).");

  params.addCoupledVar("heavy_species_T", 300, "The species temperature in Kelvin.");
  params.addCoupledVar("heavy_species_p", 1.01e5, "The species pressure in Pascals (defaulted to 1 standard atmosphere).");

  params.addClassDescription("Material properties of ions and neutral species");
  return params;
}

template <bool is_ad>
HeavySpeciesTempl<is_ad>::HeavySpeciesTempl(const InputParameters & parameters)
  : Material(parameters),
    _user_massHeavy(getParam<Real>("heavy_species_mass")),
    _user_sgnHeavy(getParam<Real>("heavy_species_charge")),
    _potential_units(getParam<std::string>("potential_units")),
    _massHeavy(declareProperty<Real>("mass" + getParam<std::string>("heavy_species_name"))),

    _sgnHeavy(declareProperty<Real>("sgn" + getParam<std::string>("heavy_species_name"))),
    _muHeavy(
        declareGenericProperty<Real, is_ad>("mu" + getParam<std::string>("heavy_species_name"))),
    _diffHeavy(
        declareGenericProperty<Real, is_ad>("diff" + getParam<std::string>("heavy_species_name"))),

    _temperatureHeavy(coupledGenericValue<is_ad>("heavy_species_T")),
    _pressureHeavy(coupledGenericValue<is_ad>("heavy_species_p")),

    _time_units(getParam<Real>("time_units"))

{
  if (isParamValid("mobility") && isParamValid("diffusivity"))
  {
    _calc_mobility = false;
    _calc_diffusivity = false;
  }
  else if (isParamValid("mobility") && !isParamValid("diffusivity"))
  {
    _calc_mobility = false;
    _calc_diffusivity = true;
  }
  else if (!isParamValid("mobility") && isParamValid("diffusivity"))
  {
    _calc_mobility = true;
    _calc_diffusivity = false;
  }
  else
  {
    _calc_mobility = true;
    _calc_diffusivity = true;
  }
}

template <bool is_ad>
void
HeavySpeciesTempl<is_ad>::computeQpProperties()
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;

  _massHeavy[_qp] = _user_massHeavy;
  _sgnHeavy[_qp] = _user_sgnHeavy;

  if (!_calc_mobility && !_calc_diffusivity)
  {
    _diffHeavy[_qp] = getParam<Real>("diffusivity") * _time_units;
    _muHeavy[_qp] = getParam<Real>("mobility") * _voltage_scaling * _time_units;
  }
  else if (_calc_mobility && !_calc_diffusivity)
  {
    _diffHeavy[_qp] = getParam<Real>("diffusivity") * _time_units;
    _muHeavy[_qp] =
        _diffHeavy[_qp] * 1.602e-19 / (_temperatureHeavy[_qp] * 1.3807e-23) * _voltage_scaling;
  }
  else if (!_calc_mobility && _calc_diffusivity)
  {
    _muHeavy[_qp] = getParam<Real>("mobility") * _voltage_scaling * _time_units;
    _diffHeavy[_qp] = _muHeavy[_qp] * _temperatureHeavy[_qp] * 1.3807e-23 /
                      (_user_sgnHeavy * 1.602e-19) / _voltage_scaling;
  }
  else
  {
    // If no mobility or diffusivity values are given, values are computed for Argon based on
    // Richards and Sawin paper
    _muHeavy[_qp] = 1444. * _voltage_scaling * _time_units /
                    (10000. * 760. * _pressureHeavy[_qp] /
                     1.01E5); // units of m^2/(kV*s) if _voltage_scaling = 1000

    _diffHeavy[_qp] = 0.004 * _time_units /
                      (760. * _pressureHeavy[_qp] / 1.01E5); // covert to m^2 and include press
  }
}

template class HeavySpeciesTempl<false>;
template class HeavySpeciesTempl<true>;
