//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Gas.h"
#include "MooseUtils.h"

registerADMooseObject("ZapdosApp", Gas);

InputParameters
Gas::validParams()
{
  InputParameters params = ADMaterial::validParams();

  params.addParam<Real>(
      "user_relative_permittivity", 1.0, "Multiplies the permittivity of free space.");
  // params.addRequiredParam<bool>("townsend","Whether to use the townsend formulation for the rate
  // terms.");
  params.addRequiredParam<bool>("interp_trans_coeffs",
                                "Whether to interpolate transport "
                                "coefficients as a function of the mean "
                                "energy. If false, coeffs are constant.");
  params.addRequiredParam<bool>("interp_elastic_coeff",
                                "Whether to interpolate the elastic collision townsend coefficient "
                                "as a function of the mean energy. If false, coeffs are constant.");
  params.addRequiredParam<bool>("ramp_trans_coeffs",
                                "Whether to ramp the non-linearity of coming "
                                "from the electron energy dependence of the "
                                "transport coefficients.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<bool>("use_moles",
                                "Whether to use units of moles as opposed to # of molecules.");
  params.addRequiredParam<FileName>(
      "property_tables_file", "The file containing interpolation tables for material properties.");

  params.addParam<Real>("user_se_coeff", 0.15, "The secondary electron emission coefficient.");
  params.addParam<Real>("user_work_function", 5.00, "The work function.");
  params.addParam<Real>("user_field_enhancement", 1, "The field enhancement factor.");

  params.addParam<Real>("user_Richardson_coefficient", 1.20173E6, "The Richardson coefficient.");
  params.addParam<Real>("user_cathode_temperature", 300, "The cathode temperature in Kelvin.");

  params.addParam<Real>("user_T_gas", 300, "The gas temperature in Kelvin.");
  params.addParam<Real>("user_p_gas", 1.01e5, "The gas pressure in Pascals.");

  params.addCoupledVar("em", "Species concentration needed to calculate the poisson source");
  params.addCoupledVar("mean_en", "The electron mean energy in log form.");
  params.addCoupledVar("ip", "The ion density.");
  params.addClassDescription("Material properties of electron and ions for argon gas"
                             "(Defines reaction properties with Townsend coefficients)");
  return params;
}

Gas::Gas(const InputParameters & parameters)
  : ADMaterial(parameters),
    // _townsend(getParam<bool>("townsend")),
    _interp_trans_coeffs(getParam<bool>("interp_trans_coeffs")),
    _interp_elastic_coeff(getParam<bool>("interp_elastic_coeff")),
    _ramp_trans_coeffs(getParam<bool>("ramp_trans_coeffs")),
    _potential_units(getParam<std::string>("potential_units")),
    _user_se_coeff(getParam<Real>("user_se_coeff")),
    _user_work_function(getParam<Real>("user_work_function")),
    _user_field_enhancement(getParam<Real>("user_field_enhancement")),

    _user_Richardson_coefficient(getParam<Real>("user_Richardson_coefficient")),
    _user_cathode_temperature(getParam<Real>("user_cathode_temperature")),

    _user_T_gas(getParam<Real>("user_T_gas")),
    _user_p_gas(getParam<Real>("user_p_gas")),
    _use_moles(getParam<bool>("use_moles")),

    _muem(declareADProperty<Real>("muem")),
    _diffem(declareADProperty<Real>("diffem")),
    _muArp(declareADProperty<Real>("muArp")),
    _diffArp(declareADProperty<Real>("diffArp")),
    _Eiz(declareProperty<Real>("Eiz")),
    _Eex(declareProperty<Real>("Eex")),
    _Ar(declareProperty<Real>("Ar")),
    _mumean_en(declareADProperty<Real>("mumean_en")),
    _diffmean_en(declareADProperty<Real>("diffmean_en")),
    _rate_coeff_elastic(declareProperty<Real>("rate_coeff_elastic")),
    _massem(declareProperty<Real>("massem")),
    _massGas(declareProperty<Real>("massGas")),
    _massArp(declareProperty<Real>("massArp")),
    _se_coeff(declareProperty<Real>("se_coeff")),
    _work_function(declareProperty<Real>("work_function")),
    _field_enhancement(declareProperty<Real>("field_enhancement")),

    _Richardson_coefficient(declareProperty<Real>("Richardson_coefficient")),
    _cathode_temperature(declareProperty<Real>("cathode_temperature")),

    _se_energy(declareProperty<Real>("se_energy")),

    _e(declareProperty<Real>("e")),
    _eps(declareProperty<Real>("eps")),
    _k_boltz(declareProperty<Real>("k_boltz")),
    _Avogadro(declareProperty<Real>("Avogadro")),
    _vthermal_em(declareProperty<Real>("vthermal_em")),
    _vthermal_ip(declareProperty<Real>("vthermal_ip")),
    _iz_coeff_efield_a(declareProperty<Real>("iz_coeff_efield_a")),
    _iz_coeff_efield_b(declareProperty<Real>("iz_coeff_efield_b")),
    _iz_coeff_efield_c(declareProperty<Real>("iz_coeff_efield_c")),
    _iz_coeff_energy_a(declareProperty<Real>("iz_coeff_energy_a")),
    _iz_coeff_energy_b(declareProperty<Real>("iz_coeff_energy_b")),
    _iz_coeff_energy_c(declareProperty<Real>("iz_coeff_energy_c")),
    _N_A(declareProperty<Real>("N_A")),
    _el_coeff_energy_a(declareProperty<Real>("el_coeff_energy_a")),
    _el_coeff_energy_b(declareProperty<Real>("el_coeff_energy_b")),
    _el_coeff_energy_c(declareProperty<Real>("el_coeff_energy_c")),
    _alpha_iz(declareADProperty<Real>("alpha_iz")),
    _alpha_ex(declareADProperty<Real>("alpha_ex")),
    _alpha_el(declareADProperty<Real>("alpha_el")),
    _sgnem(declareProperty<Real>("sgnem")),
    _sgnmean_en(declareProperty<Real>("sgnmean_en")),
    _sgnArp(declareProperty<Real>("sgnArp")),
    _diffpotential(declareADProperty<Real>("diffpotential")),
    _actual_mean_energy(declareADProperty<Real>("actual_mean_energy")),
    _TArp(declareADProperty<Real>("TArp")),
    _Tem(declareADProperty<Real>("Tem")),
    _T_gas(declareProperty<Real>("T_gas")),
    _p_gas(declareProperty<Real>("p_gas")),
    _n_gas(declareProperty<Real>("n_gas")),
    _kiz(declareADProperty<Real>("kiz")),
    _kex(declareADProperty<Real>("kex")),
    _kel(declareADProperty<Real>("kel")),
    _TemVolts(declareADProperty<Real>("TemVolts")),

    _em(isCoupled("em") ? adCoupledValue("em") : _ad_zero),
    _mean_en(isCoupled("mean_en") ? adCoupledValue("mean_en") : _ad_zero)
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;

  std::vector<Real> actual_mean_energy;
  std::vector<Real> alpha;
  std::vector<Real> alphaEx;
  std::vector<Real> alphaEl;
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
      alpha.push_back(value);
      myfile >> value;
      alphaEx.push_back(value);
      myfile >> value;
      alphaEl.push_back(value);
      myfile >> value;
      mu.push_back(value);
      myfile >> value;
      diff.push_back(value);
    }
    myfile.close();
  }

  else
    mooseError("Unable to open file");

  _alpha_interpolation.setData(actual_mean_energy, alpha);
  _alphaEx_interpolation.setData(actual_mean_energy, alphaEx);
  _alphaEl_interpolation.setData(actual_mean_energy, alphaEl);
  _mu_interpolation.setData(actual_mean_energy, mu);
  _diff_interpolation.setData(actual_mean_energy, diff);
}

void
Gas::computeQpProperties()
{
  _massem[_qp] = 9.11e-31;
  _massGas[_qp] = 40.0 * 1.66e-27;
  _massArp[_qp] = 40.0 * 1.66e-27;
  _T_gas[_qp] = _user_T_gas;
  _p_gas[_qp] = _user_p_gas;
  _k_boltz[_qp] = 1.38e-23;
  _Avogadro[_qp] = 6.0221409E23;
  if (_use_moles)
    _n_gas[_qp] = _p_gas[_qp] / (8.3145 * _T_gas[_qp]);
  else
    _n_gas[_qp] = _p_gas[_qp] / (_k_boltz[_qp] * _T_gas[_qp]);

  _se_coeff[_qp] = _user_se_coeff;
  _work_function[_qp] = _user_work_function;
  _field_enhancement[_qp] = _user_field_enhancement;

  _Richardson_coefficient[_qp] = _user_Richardson_coefficient;
  _cathode_temperature[_qp] = _user_cathode_temperature;

  _se_energy[_qp] = 2. * 3. / 2.; // Emi uses 2 Volts coming off the wall (presumably for Te).
                                  // Multiply by 3/2 to get mean_en
  _e[_qp] = 1.6e-19;
  _eps[_qp] = 8.85e-12;
  _sgnem[_qp] = -1.;
  _sgnmean_en[_qp] = -1.;
  _sgnArp[_qp] = 1.;
  _diffpotential[_qp] = _eps[_qp];

  _TArp[_qp] = 300;

  // With the exception of temperature/energy (generally in eV), all properties are in standard SI
  // units unless otherwise indicated

  if (_interp_trans_coeffs)
  {
    if (_ramp_trans_coeffs)
    {
      _muem[_qp].value() =
          (std::tanh(_t / 1e-6) *
               _mu_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) +
           (1. - std::tanh(_t / 1e-6)) * .0352) *
          _voltage_scaling;
      _muem[_qp].derivatives() =
          std::tanh(_t / 1e-6) *
          _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
          std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
          (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) * _voltage_scaling;
      _diffem[_qp].value() =
          std::tanh(_t / 1e-6) *
              _diff_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) +
          (1. - std::tanh(_t / 1e-6)) * .30;
      _diffem[_qp].derivatives() =
          std::tanh(_t / 1e-6) *
          _diff_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
          std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
          (_mean_en[_qp].derivatives() - _em[_qp].derivatives());
    }
    else
    {
      _muem[_qp].value() =
          _mu_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
          _voltage_scaling;
      _muem[_qp].derivatives() =
          _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
          std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
          (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) * _voltage_scaling;
      _diffem[_qp].value() =
          _diff_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value()));
      _diffem[_qp].derivatives() =
          _diff_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
          std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
          (_mean_en[_qp].derivatives() - _em[_qp].derivatives());
    }
  }
  else
  {
    // From bolos at atmospheric pressure and an EField of 2e5 V/m
    _muem[_qp].value() =
        0.0352103411399 * _voltage_scaling; // units of m^2/(kV*s) if _voltage_scaling = 1000
    _muem[_qp].derivatives() = 0.0;
    _diffem[_qp].value() = 0.297951680159;
    _diffem[_qp].derivatives() = 0.0;
  }

  // From Richards and Sawin, muArp*pressure = 1444 cm^2*Torr/(V*s) and diffArp*pressure = 40
  // cm^2*Torr/s. Use pressure = 760 torr.
  _muArp[_qp] =
      1444. * _voltage_scaling /
      (10000. * 760. * _p_gas[_qp] / 1.01E5); // units of m^2/(kV*s) if _voltage_scaling = 1000
  _diffArp[_qp] = 0.004 / (760. * _p_gas[_qp] / 1.01E5); // covert to m^2 and include press

  // 100 times less than electrons
  // _muArp[_qp] = 3.52e-4;
  // _diffArp[_qp] = 2.98e-3;

  // From curve fitting with bolos
  _iz_coeff_efield_a[_qp] = 1.43171672e-1;
  _iz_coeff_efield_b[_qp] = 9.05925536e-1;
  _iz_coeff_efield_c[_qp] = 3.04958892e+6;

  // if (_townsend) {
  _iz_coeff_energy_a[_qp] = 1.52165930e+8;
  _iz_coeff_energy_b[_qp] = -2.87277596e-1;
  _iz_coeff_energy_c[_qp] = 5.51972192e+1;
  // }
  // else {
  //       _iz_coeff_energy_a[_qp] = 1.43878529e-11;
  //       _iz_coeff_energy_b[_qp] = -2.70610234e-1;
  //       _iz_coeff_energy_c[_qp] = 7.64727794e+1;
  // }

  _actual_mean_energy[_qp] = std::exp(_mean_en[_qp] - _em[_qp]);
  _alpha_iz[_qp].value() =
      _alpha_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value()));
  _alpha_iz[_qp].derivatives() =
      _alpha_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
      std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
      (_mean_en[_qp].derivatives() - _em[_qp].derivatives());
  _alpha_ex[_qp].value() =
      _alphaEx_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value()));
  _alpha_ex[_qp].derivatives() =
      _alphaEx_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
      std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
      (_mean_en[_qp].derivatives() - _em[_qp].derivatives());
  if (_interp_elastic_coeff)
  {
    _alpha_el[_qp].value() =
        _alphaEl_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value()));
    _alpha_el[_qp].derivatives() = _alphaEl_interpolation.sampleDerivative(
                                       std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
                                   std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
                                   (_mean_en[_qp].derivatives() - _em[_qp].derivatives());
  }
  else
  {
    _alpha_el[_qp].value() = 5e8;
    _alpha_el[_qp].derivatives() = 0.0;
  }

  _el_coeff_energy_a[_qp] = 1.60638169e-13;
  _el_coeff_energy_b[_qp] = 3.17917979e-1;
  _el_coeff_energy_c[_qp] = 4.66301096;

  _N_A[_qp] = 6.02e23;
  _Ar[_qp] = 1.01e5 / (300 * 1.38e-23);
  _Eiz[_qp] = 15.76;
  _Eex[_qp] = 11.5;

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

  _rate_coeff_elastic[_qp] = 1e-13;

  _TemVolts[_qp] = 2. / 3. * std::exp(_mean_en[_qp] - _em[_qp]);
  _Tem[_qp] = _e[_qp] * _TemVolts[_qp] / _k_boltz[_qp];

  _kiz[_qp] = 2.34e-14 * std::pow(_TemVolts[_qp], .59) * std::exp(-17.44 / _TemVolts[_qp]);
  _kex[_qp] = 2.48e-14 * std::pow(_TemVolts[_qp], .33) * std::exp(-12.78 / _TemVolts[_qp]);
  _kel[_qp].value() = 1e-13; // Approximate elastic rate coefficient
  _kel[_qp].derivatives() = 0.;
  if (_use_moles)
  {
    _kiz[_qp] = _kiz[_qp] * _N_A[_qp];
    _kex[_qp] = _kex[_qp] * _N_A[_qp];
    _kel[_qp] = _kel[_qp] * _N_A[_qp];
  }
}
