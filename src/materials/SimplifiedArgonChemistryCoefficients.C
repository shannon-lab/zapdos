//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SimplifiedArgonChemistryCoefficients.h"
#include "MooseUtils.h"
#include "Zapdos.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", SimplifiedArgonChemistryCoefficients);

InputParameters
SimplifiedArgonChemistryCoefficients::validParams()
{
  InputParameters params = ADMaterial::validParams();

  params.addRequiredParam<bool>("interp_elastic_coeff",
                                "Whether to interpolate the elastic collision townsend coefficient "
                                "as a function of the mean energy. If false, coeffs are constant.");

  params.addRequiredParam<bool>("use_moles",
                                "Whether to use units of moles as opposed to # of molecules.");
  params.addRequiredParam<FileName>(
      "property_tables_file", "The file containing interpolation tables for material properties.");

  params.addCoupledVar("T_gas", 300, "The background gas temperature in Kelvin.");
  params.addCoupledVar("p_gas", 1.01e5, "The background gas pressure in Pascals.");

  params.addCoupledVar("electrons", "The electron density in log form");
  params.addCoupledVar("electron_energy", "The mean electron energy density in log form");

  params.addClassDescription("Rate and Townsend coefficients for a simplified argon chemistry "
                             "network (includes elastic collision, ionization, and excitation).");
  return params;
}

SimplifiedArgonChemistryCoefficients::SimplifiedArgonChemistryCoefficients(
    const InputParameters & parameters)
  : ADMaterial(parameters),
    _interp_elastic_coeff(getParam<bool>("interp_elastic_coeff")),

    _T_gas(coupledValue("T_gas")),
    _p_gas(coupledValue("p_gas")),
    _use_moles(getParam<bool>("use_moles")),

    _Eiz(declareProperty<Real>("Eiz")),
    _Eex(declareProperty<Real>("Eex")),
    _rate_coeff_elastic(declareProperty<Real>("rate_coeff_elastic")),
    _massGas(declareProperty<Real>("massGas")),

    _iz_coeff_efield_a(declareProperty<Real>("iz_coeff_efield_a")),
    _iz_coeff_efield_b(declareProperty<Real>("iz_coeff_efield_b")),
    _iz_coeff_efield_c(declareProperty<Real>("iz_coeff_efield_c")),
    _iz_coeff_energy_a(declareProperty<Real>("iz_coeff_energy_a")),
    _iz_coeff_energy_b(declareProperty<Real>("iz_coeff_energy_b")),
    _iz_coeff_energy_c(declareProperty<Real>("iz_coeff_energy_c")),
    _el_coeff_energy_a(declareProperty<Real>("el_coeff_energy_a")),
    _el_coeff_energy_b(declareProperty<Real>("el_coeff_energy_b")),
    _el_coeff_energy_c(declareProperty<Real>("el_coeff_energy_c")),
    _alpha_iz(declareADProperty<Real>("alpha_iz")),
    _alpha_ex(declareADProperty<Real>("alpha_ex")),
    _alpha_el(declareADProperty<Real>("alpha_el")),
    _Tem(declareADProperty<Real>("Tem")),

    _n_gas(declareProperty<Real>("n_gas")),
    _kiz(declareADProperty<Real>("kiz")),
    _kex(declareADProperty<Real>("kex")),
    _kArp(declareADProperty<Real>("kArp")),
    _kel(declareADProperty<Real>("kel")),
    _TemVolts(declareADProperty<Real>("TemVolts")),

    _em(isCoupled("electrons") ? adCoupledValue("electrons") : _ad_zero),
    _mean_en(isCoupled("electron_energy") ? adCoupledValue("electron_energy") : _ad_zero)
{
  std::vector<Real> actual_mean_energy;
  std::vector<Real> alpha;
  std::vector<Real> alphaEx;
  std::vector<Real> alphaEl;

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
    }
    myfile.close();
  }

  else
    mooseError("Unable to open file");

  _alpha_interpolation.setData(actual_mean_energy, alpha);
  _alphaEx_interpolation.setData(actual_mean_energy, alphaEx);
  _alphaEl_interpolation.setData(actual_mean_energy, alphaEl);
}

void
SimplifiedArgonChemistryCoefficients::computeQpProperties()
{
  _massGas[_qp] = 40.0 * 1.66e-27;

  if (_use_moles)
    _n_gas[_qp] = _p_gas[_qp] / (8.3145 * _T_gas[_qp]);
  else
    _n_gas[_qp] = _p_gas[_qp] / (ZAPDOS_CONSTANTS::k_boltz * _T_gas[_qp]);

  // With the exception of temperature/energy (generally in eV), all properties are in standard SI
  // units unless otherwise indicated

  // From curve fitting with bolos
  _iz_coeff_efield_a[_qp] = 1.43171672e-1;
  _iz_coeff_efield_b[_qp] = 9.05925536e-1;
  _iz_coeff_efield_c[_qp] = 3.04958892e+6;

  _iz_coeff_energy_a[_qp] = 1.52165930e+8;
  _iz_coeff_energy_b[_qp] = -2.87277596e-1;
  _iz_coeff_energy_c[_qp] = 5.51972192e+1;

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

  _Eiz[_qp] = 15.76;
  _Eex[_qp] = 11.5;

  _rate_coeff_elastic[_qp] = 1e-13;

  _TemVolts[_qp] = 2. / 3. * std::exp(_mean_en[_qp] - _em[_qp]);
  _Tem[_qp] = ZAPDOS_CONSTANTS::e * _TemVolts[_qp] / ZAPDOS_CONSTANTS::k_boltz;

  _kiz[_qp] = 2.34e-14 * std::pow(_TemVolts[_qp], .59) * std::exp(-17.44 / _TemVolts[_qp]);
  _kex[_qp] = 2.48e-14 * std::pow(_TemVolts[_qp], .33) * std::exp(-12.78 / _TemVolts[_qp]);
  _kArp[_qp] = 2.48e-14 * std::pow(_TemVolts[_qp], .33) * std::exp(-12.78 / _TemVolts[_qp]);

  _kel[_qp].value() = 1e-13; // Approximate elastic rate coefficient
  _kel[_qp].derivatives() = 0.;
  if (_use_moles)
  {
    _kiz[_qp] = _kiz[_qp] * ZAPDOS_CONSTANTS::N_A;
    _kex[_qp] = _kex[_qp] * ZAPDOS_CONSTANTS::N_A;
    _kArp[_qp] = _kArp[_qp] * ZAPDOS_CONSTANTS::N_A;
    _kel[_qp] = _kel[_qp] * ZAPDOS_CONSTANTS::N_A;
  }
}
