//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ElectronTransportCoefficients.h"
#include "MooseUtils.h"
#include "Zapdos.h"

registerMooseObject("ZapdosApp", ElectronTransportCoefficients);

InputParameters
ElectronTransportCoefficients::validParams()
{
  InputParameters params = Material::validParams();

  params.addRequiredParam<bool>("interp_trans_coeffs",
                                "Whether to interpolate transport "
                                "coefficients as a function of the mean "
                                "energy. If false, coeffs are constant.");
  params.addRequiredParam<bool>("ramp_trans_coeffs",
                                "Whether to ramp the non-linearity of coming "
                                "from the electron energy dependence of the "
                                "transport coefficients.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<bool>("use_moles",
                                "Whether to use units of moles as opposed to # of molecules.");
  params.addRequiredParam<FileName>(
      "property_tables_file", "The file containing interpolation tables for material properties.");

  params.addParam<Real>("time_units", 1, "Units of time");

  params.addCoupledVar("T_gas", 300, "The background gas temperature in Kelvin.");
  params.addCoupledVar(
      "p_gas",
      1.01e5,
      "The background gas pressure in Pascals (defaulted to 1 standard atmosphere).");

  params.addRequiredCoupledVar("electrons", "The electron density in log form");
  params.addRequiredCoupledVar("electron_energy", "The mean electron energy density in log form");

  params.addParam<Real>("user_electron_mobility", 0, "The electron mobility coefficient.");
  params.addParam<Real>("user_electron_diffusion_coeff", 0, "The electron diffusion coefficient.");
  params.addParam<bool>("pressure_dependent_electron_coeff",
                        false,
                        "Are the values for the electron mobility and diffusion coefficient "
                        "dependent on gas pressure");
  params.addClassDescription("Transport coefficients and material properties of electrons and "
                             "electron mean energy density.");

  return params;
}

ElectronTransportCoefficients::ElectronTransportCoefficients(const InputParameters & parameters)
  : Material(parameters),
    _interp_trans_coeffs(getParam<bool>("interp_trans_coeffs")),
    _ramp_trans_coeffs(getParam<bool>("ramp_trans_coeffs")),
    _potential_units(getParam<std::string>("potential_units")),
    _time_units(getParam<Real>("time_units")),

    _T_gas(coupledValue("T_gas")),
    _p_gas(coupledValue("p_gas")),
    _use_moles(getParam<bool>("use_moles")),

    _user_muem(getParam<Real>("user_electron_mobility")),
    _user_diffem(getParam<Real>("user_electron_diffusion_coeff")),
    _pressure_dependent(getParam<bool>("pressure_dependent_electron_coeff")),

    _muem(declareADProperty<Real>("mu" + (*getVar("electrons", 0)).name())),
    _diffem(declareADProperty<Real>("diff" + (*getVar("electrons", 0)).name())),
    _mumean_en(declareADProperty<Real>("mu" + (*getVar("electron_energy", 0)).name())),
    _diffmean_en(declareADProperty<Real>("diff" + (*getVar("electron_energy", 0)).name())),
    _massem(declareProperty<Real>("mass" + (*getVar("electrons", 0)).name())),

    _sgnem(declareProperty<Real>("sgn" + (*getVar("electrons", 0)).name())),
    _sgnmean_en(declareProperty<Real>("sgn" + (*getVar("electron_energy", 0)).name())),

    _em(adCoupledValue("electrons")),
    _mean_en(adCoupledValue("electron_energy"))
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;

  std::vector<Real> actual_mean_energy;
  std::vector<Real> mu;
  std::vector<Real> diff;

  std::string file_name = getParam<FileName>("property_tables_file");
  MooseUtils::checkFileReadable(file_name);
  const char * charPath = file_name.c_str();
  std::ifstream myfile(charPath);
  Real value;

  if (myfile.is_open())
  {
    while (myfile >> value)
    {
      actual_mean_energy.push_back(value);
      myfile >> value;
      mu.push_back(value);
      myfile >> value;
      diff.push_back(value);
    }
    myfile.close();
  }

  else
    mooseError("Unable to open file");

  _mu_interpolation.setData(actual_mean_energy, mu);
  _diff_interpolation.setData(actual_mean_energy, diff);
}

void
ElectronTransportCoefficients::computeQpProperties()
{
  _massem[_qp] = 9.11e-31;
  Real N_inverse = (ZAPDOS_CONSTANTS::k_boltz * _T_gas[_qp]) / _p_gas[_qp];

  _sgnem[_qp] = -1.;
  _sgnmean_en[_qp] = -1.;

  // With the exception of temperature/energy (generally in eV), all properties are in standard SI
  // units unless otherwise indicated

  if (_pressure_dependent) // If the mobility and diff. does depend on pressure
  {

    if (_interp_trans_coeffs)
    {
      if (_ramp_trans_coeffs)
      {
        _muem[_qp].value() =
            (std::tanh(_t / 1e-6) *
                 _mu_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) +
             (1. - std::tanh(_t / 1e-6)) * .0352) *
            _voltage_scaling * _time_units * N_inverse;
        _muem[_qp].derivatives() =
            std::tanh(_t / 1e-6) *
            _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
            std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
            (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) * _voltage_scaling *
            _time_units * N_inverse;
        _diffem[_qp].value() =
            std::tanh(_t / 1e-6) *
                _diff_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) +
            (1. - std::tanh(_t / 1e-6)) * .30 * _time_units * N_inverse;
        _diffem[_qp].derivatives() = std::tanh(_t / 1e-6) *
                                     _diff_interpolation.sampleDerivative(
                                         std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
                                     std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
                                     (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) *
                                     _time_units * N_inverse;
      }
      else
      {
        _muem[_qp].value() =
            _mu_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
            _voltage_scaling * _time_units * N_inverse;
        _muem[_qp].derivatives() =
            _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
            std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
            (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) * _voltage_scaling *
            _time_units * N_inverse;
        _diffem[_qp].value() =
            _diff_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
            _time_units * N_inverse;
        _diffem[_qp].derivatives() = _diff_interpolation.sampleDerivative(
                                         std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
                                     std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
                                     (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) *
                                     _time_units * N_inverse;
      }
    }
    else
    {
      _muem[_qp].value() = _user_muem * _voltage_scaling * _time_units * N_inverse;
      _muem[_qp].derivatives() = 0.0;
      _diffem[_qp].value() = _user_diffem * _time_units * N_inverse;
      _diffem[_qp].derivatives() = 0.0;
    }
  }

  else // If the mobility and diff. does not depend on pressure
  {

    if (_interp_trans_coeffs)
    {
      if (_ramp_trans_coeffs)
      {
        _muem[_qp].value() =
            (std::tanh(_t / 1e-6) *
                 _mu_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) +
             (1. - std::tanh(_t / 1e-6)) * .0352) *
            _voltage_scaling * _time_units;
        _muem[_qp].derivatives() =
            std::tanh(_t / 1e-6) *
            _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
            std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
            (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) * _voltage_scaling * _time_units;
        _diffem[_qp].value() =
            std::tanh(_t / 1e-6) *
                _diff_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) +
            (1. - std::tanh(_t / 1e-6)) * .30 * _time_units;
        _diffem[_qp].derivatives() = std::tanh(_t / 1e-6) *
                                     _diff_interpolation.sampleDerivative(
                                         std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
                                     std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
                                     (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) *
                                     _time_units;
      }
      else
      {
        _muem[_qp].value() =
            _mu_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
            _voltage_scaling * _time_units;
        _muem[_qp].derivatives() =
            _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
            std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
            (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) * _voltage_scaling * _time_units;
        _diffem[_qp].value() =
            _diff_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
            _time_units;
        _diffem[_qp].derivatives() = _diff_interpolation.sampleDerivative(
                                         std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
                                     std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
                                     (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) *
                                     _time_units;
      }
    }
    else
    {
      _muem[_qp].value() = _user_muem * _voltage_scaling * _time_units;
      _muem[_qp].derivatives() = 0.0;
      _diffem[_qp].value() = _user_diffem * _time_units;
      _diffem[_qp].derivatives() = 0.0;
    }
  }

  // From Hagelaar: The below approximations can be derived assumption Maxwell EEDF, const
  // momentum-transfer frequency, and constant kinetic pressure.
  _mumean_en[_qp].value() = 5.0 / 3.0 * _muem[_qp].value();
  _diffmean_en[_qp].value() = 5.0 / 3.0 * _diffem[_qp].value();
  if (_interp_trans_coeffs)
  {
    _mumean_en[_qp].derivatives() = 5.0 / 3.0 * _muem[_qp].derivatives();
    _diffmean_en[_qp].derivatives() = 5.0 / 3.0 * _diffem[_qp].derivatives();
  }
  else
  {
    _mumean_en[_qp].derivatives() = 0.0;
    _diffmean_en[_qp].derivatives() = 0.0;
  }
}
