#include "HeavySpeciesMaterial.h"
#include "MooseUtils.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", HeavySpeciesMaterial);

template <>
InputParameters
validParams<HeavySpeciesMaterial>()
{
  InputParameters params = validParams<Material>();

  params.addRequiredParam<std::string>("heavy_species_name", "The name of the heavy species");
  params.addRequiredParam<Real>("heavy_species_mass", "Mass of the heavy species");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<Real>("heavy_species_charge", "Charge of heavy species.");
  params.addParam<Real>("time_units", 1, "Units of time");
  params.addParam<Real>("mobility", "The species mobility (if applicable).");
  params.addParam<Real>("diffusivity", "The species diffusivity (if applicable).");
  // params.addRequiredParam<FileName>(
      // "reactions_file", "The file containing interpolation tables for material properties.");
  // params.addParam<Real>("user_T_gas", 300, "The gas temperature in Kelvin.");
  // params.addParam<Real>("user_p_gas", 1.01e5, "The gas pressure in Pascals.");
  return params;
}

HeavySpeciesMaterial::HeavySpeciesMaterial(const InputParameters & parameters)
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
    _p_gas(getMaterialProperty<Real>("p_gas")),
    _time_units(getParam<Real>("time_units"))

{
  // std::vector<Real> actual_mean_energy;
  // std::vector<Real> kArIz;
  // std::vector<Real> kArEx;
  // std::vector<Real> kArEl;
  // std::vector<Real> kArExIz;
  // // std::vector<Real> d_alpha_d_actual_mean_energy;
  //
  // std::string file_name = getParam<FileName>("reactions_file");
  // MooseUtils::checkFileReadable(file_name);
  // const char * charPath = file_name.c_str();
  // std::ifstream myfile(charPath);
  // Real value;
  //
  // if (myfile.is_open())
  // {
  //   while (myfile >> value)
  //   {
  //     actual_mean_energy.push_back(value);
  //     myfile >> value;
  //     kArIz.push_back(value);
  //     myfile >> value;
  //     kArEx.push_back(value);
  //     myfile >> value;
  //     kArEl.push_back(value);
  //     myfile >> value;
  //     kArExIz.push_back(value);
  //   }
  //   myfile.close();
  // }
  //
  // else
  //   mooseError("Unable to open file");
  //
  // _kArIz_interpolation.setData(actual_mean_energy, kArIz);
  // _kArEx_interpolation.setData(actual_mean_energy, alphaEx);
  // _kArEl_interpolation.setData(actual_mean_energy, alphaEl);
  // _kArExIz_interpolation.setData(actual_mean_energy, kArExIz);
}

void
HeavySpeciesMaterial::computeQpProperties()
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;

  _massHeavy[_qp] = _user_massHeavy;
  _sgnHeavy[_qp] = _user_sgnHeavy;

  // _T_gas[_qp] = _user_T_gas;
  // _p_gas[_qp] = _user_p_gas;

  _temperatureHeavy[_qp] = _T_gas[_qp];  // Needs to be changed.

  // _n_gas[_qp] = _p_gas[_qp] / (8.3145 * _T_gas[_qp]);

  if (isParamValid("mobility"))
  {
    _muHeavy[_qp] = getParam<Real>("mobility") * _voltage_scaling * _time_units;
  }
  else
  {
    _muHeavy[_qp] =
        1444. * _voltage_scaling * _time_units /
        (10000. * 760. * _p_gas[_qp] / 1.01E5); // units of m^2/(kV*s) if _voltage_scaling = 1000
  }

  if (isParamValid("diffusivity"))
  {
    _diffHeavy[_qp] = getParam<Real>("diffusivity") * _time_units;
  }
  else
  {
    _diffHeavy[_qp] = 0.004 * _time_units / (760. * _p_gas[_qp] / 1.01E5); // covert to m^2 and include press
  }

}
