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

  params.addParam<Real>("user_T_gas", 300, "The gas temperature in Kelvin.");
  params.addCoupledVar("user_p_gas", "The gas pressure in Pascals.");

  params.addCoupledVar("em", "Species concentration needed to calculate the poisson source");
  params.addCoupledVar("mean_en", "The electron mean energy in log form.");
  params.addCoupledVar("ip", "The ion density.");

  params.addParam<Real>("user_electron_mobility", 0, "The electron mobility coefficient.");
  params.addParam<Real>("user_electron_diffusion_coeff", 0, "The electron diffusion coefficient.");
  params.addParam<bool>("pressure_dependent_electron_coeff",
                        false,
                        "Are the values for the electron mobility and diffusion coefficient "
                        "dependent on gas pressure");
  params.addClassDescription("Material properties of electrons"
                             "(Defines reaction properties with rate coefficients)");

  return params;
}

ElectronTransportCoefficients::ElectronTransportCoefficients(const InputParameters & parameters)
  : Material(parameters),
    _interp_trans_coeffs(getParam<bool>("interp_trans_coeffs")),
    _ramp_trans_coeffs(getParam<bool>("ramp_trans_coeffs")),
    _potential_units(getParam<std::string>("potential_units")),
    _time_units(getParam<Real>("time_units")),

    _user_T_gas(getParam<Real>("user_T_gas")),
    _user_p_gas(coupledValue("user_p_gas")),
    _use_moles(getParam<bool>("use_moles")),

    _user_muem(getParam<Real>("user_electron_mobility")),
    _user_diffem(getParam<Real>("user_electron_diffusion_coeff")),
    _pressure_dependent(getParam<bool>("pressure_dependent_electron_coeff")),

    _muem(declareADProperty<Real>("muem")),
    _diffem(declareADProperty<Real>("diffem")),
    _mumean_en(declareADProperty<Real>("mumean_en")),
    _diffmean_en(declareADProperty<Real>("diffmean_en")),
    _massem(declareProperty<Real>("massem")),
    _massGas(declareProperty<Real>("massGas")),

    _sgnem(declareProperty<Real>("sgnem")),
    _sgnmean_en(declareProperty<Real>("sgnmean_en")),
    _diffpotential(declareADProperty<Real>("diffpotential")),
    _actual_mean_energy(declareADProperty<Real>("actual_mean_energy")),
    _T_gas(declareProperty<Real>("T_gas")),
    _p_gas(declareProperty<Real>("p_gas")),

    _em(isCoupled("em") ? adCoupledValue("em") : _ad_zero),
    _mean_en(isCoupled("mean_en") ? adCoupledValue("mean_en") : _ad_zero)
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
  _T_gas[_qp] = _user_T_gas;
  _p_gas[_qp] = _user_p_gas[_qp];
  Real _N_inverse = (ZAPDOS_CONSTANTS::k_boltz * _T_gas[_qp]) / _p_gas[_qp];

  _sgnem[_qp] = -1.;
  _sgnmean_en[_qp] = -1.;
  _diffpotential[_qp] = ZAPDOS_CONSTANTS::eps_0;

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
            _voltage_scaling * _time_units * _N_inverse;
        _muem[_qp].derivatives() =
            std::tanh(_t / 1e-6) *
            _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
            std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
            (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) * _voltage_scaling *
            _time_units * _N_inverse;
        _diffem[_qp].value() =
            std::tanh(_t / 1e-6) *
                _diff_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) +
            (1. - std::tanh(_t / 1e-6)) * .30 * _time_units * _N_inverse;
        _diffem[_qp].derivatives() = std::tanh(_t / 1e-6) *
                                     _diff_interpolation.sampleDerivative(
                                         std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
                                     std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
                                     (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) *
                                     _time_units * _N_inverse;
      }
      else
      {
        _muem[_qp].value() =
            _mu_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
            _voltage_scaling * _time_units * _N_inverse;
        _muem[_qp].derivatives() =
            _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
            std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
            (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) * _voltage_scaling *
            _time_units * _N_inverse;
        _diffem[_qp].value() =
            _diff_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
            _time_units * _N_inverse;
        _diffem[_qp].derivatives() = _diff_interpolation.sampleDerivative(
                                         std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
                                     std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
                                     (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) *
                                     _time_units * _N_inverse;
      }
    }
    else
    {
      _muem[_qp].value() = _user_muem * _voltage_scaling * _time_units * _N_inverse;
      _muem[_qp].derivatives() = 0.0;
      _diffem[_qp].value() = _user_diffem * _time_units * _N_inverse;
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
