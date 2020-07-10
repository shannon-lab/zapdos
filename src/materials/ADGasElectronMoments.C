//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADGasElectronMoments.h"
#include "MooseUtils.h"

registerADMooseObject("ZapdosApp", ADGasElectronMoments);

InputParameters
ADGasElectronMoments::validParams()
{
  InputParameters params = ADMaterial::validParams();

  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<bool>("use_moles",
                                "Whether to use units of moles as opposed to # of molecules.");
  params.addRequiredParam<FileName>(
      "property_tables_file", "The file containing interpolation tables for material properties.");

  params.addParam<Real>("time_units", 1, "Units of time");
  params.addRequiredCoupledVar("em",
                               "Species concentration needed to calculate the poisson source");
  params.addRequiredCoupledVar("mean_en", "The electron mean energy in log form.");

  params.addClassDescription("Material properties of electrons"
                             "(Defines reaction properties with rate coefficients)");

  return params;
}

ADGasElectronMoments::ADGasElectronMoments(const InputParameters & parameters)
  : ADMaterial(parameters),
    _potential_units(getParam<std::string>("potential_units")),
    _time_units(getParam<Real>("time_units")),
    _use_moles(getParam<bool>("use_moles")),
    _muem(declareADProperty<Real>("muem")),
    _diffem(declareADProperty<Real>("diffem")),
    _mumean_en(declareADProperty<Real>("mumean_en")),
    _diffmean_en(declareADProperty<Real>("diffmean_en")),
    _sgnmean_en(declareProperty<Real>("sgnmean_en")),
    _sgnem(declareProperty<Real>("sgnem")),
    _em(adCoupledValue("em")),
    _mean_en(adCoupledValue("mean_en"))
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
ADGasElectronMoments::computeQpProperties()
{
  _sgnmean_en[_qp] = -1.0;
  _sgnem[_qp] = -1.0;

  // For interpolated values the derivative propagation needs to be explicitly defined.

  // Electron diffusion coefficient - value and derivatives
  _diffem[_qp].value() =
      _diff_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) * _time_units;

  _diffem[_qp].derivatives() =
      _diff_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
      std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
      (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) * _time_units;

  // Electron mobility - value and derivatives
  _muem[_qp].value() =
      _mu_interpolation.sample(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
      _voltage_scaling * _time_units;

  _muem[_qp].derivatives() =
      _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp].value() - _em[_qp].value())) *
      std::exp(_mean_en[_qp].value() - _em[_qp].value()) *
      (_mean_en[_qp].derivatives() - _em[_qp].derivatives()) * _voltage_scaling * _time_units;

  // Mean electron energy diffusivity and mobility:
  _diffmean_en[_qp].value() = 5.0 / 3.0 * _diffem[_qp].value();

  _diffmean_en[_qp].derivatives() = 5.0 / 3.0 * _diffem[_qp].derivatives();

  _mumean_en[_qp].value() = 5.0 / 3.0 * _muem[_qp].value();

  _mumean_en[_qp].derivatives() = 5.0 / 3.0 * _muem[_qp].derivatives();
}
