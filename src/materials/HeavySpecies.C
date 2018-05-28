#include "HeavySpecies.h"
#include "MooseUtils.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", HeavySpecies);

template <>
InputParameters
validParams<HeavySpecies>()
{
  InputParameters params = validParams<Material>();

  params.addRequiredParam<std::string>("heavy_species_name", "The name of the heavy species");
  params.addRequiredParam<Real>("heavy_species_mass", "Mass of the heavy species");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<Real>("heavy_species_charge", "Charge of heavy species.");
  return params;
}

HeavySpecies::HeavySpecies(const InputParameters & parameters)
  : Material(parameters),
    _user_massHeavy(getParam<Real>("heavy_species_mass")),
    _user_sgnHeavy(getParam<Real>("heavy_species_charge")),
    _potential_units(getParam<std::string>("potential_units")),
    _massHeavy(declareProperty<Real>("mass" + getParam<std::string>("heavy_species_name"))),
    _temperatureHeavy(declareProperty<Real>("T" + getParam<std::string>("heavy_species_name"))),
    _sgnHeavy(declareProperty<Real>("sgn" + getParam<std::string>("heavy_species_name"))),
    _muHeavy(declareProperty<Real>("mu" + getParam<std::string>("heavy_species_name"))),
    _diffHeavy(declareProperty<Real>("diff" + getParam<std::string>("heavy_species_name"))),
    _T_gas(getMaterialProperty<Real>("T_gas")),
    _p_gas(getMaterialProperty<Real>("p_gas"))
{
}

void
HeavySpecies::computeQpProperties()
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;

  _massHeavy[_qp] = _user_massHeavy;
  _sgnHeavy[_qp] = _user_sgnHeavy;

  _temperatureHeavy[_qp] = _T_gas[_qp];

  _muHeavy[_qp] =
      1444. * _voltage_scaling /
      (10000. * 760. * _p_gas[_qp] / 1.01E5); // units of m^2/(kV*s) if _voltage_scaling = 1000
  _diffHeavy[_qp] = 0.004 / (760. * _p_gas[_qp] / 1.01E5); // covert to m^2 and include press
}
