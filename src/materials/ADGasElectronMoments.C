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

template <ComputeStage compute_stage>
InputParameters
ADGasElectronMoments<compute_stage>::validParams()
{
  InputParameters params = ADMaterial<compute_stage>::validParams();

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

template <ComputeStage compute_stage>
ADGasElectronMoments<compute_stage>::ADGasElectronMoments(const InputParameters & parameters)
  : ADMaterial<compute_stage>(parameters),
    _potential_units(getParam<std::string>("potential_units")),
    _time_units(getParam<Real>("time_units")),
    _use_moles(getParam<bool>("use_moles")),
    _muem(declareADProperty<Real>("muem")),
    _d_muem_d_actual_mean_en(declareADProperty<Real>("d_muem_d_actual_mean_en")),
    _diffem(declareADProperty<Real>("diffem")),
    _d_diffem_d_actual_mean_en(declareADProperty<Real>("d_diffem_d_actual_mean_en")),
    _mumean_en(declareADProperty<Real>("mumean_en")),
    _diffmean_en(declareADProperty<Real>("diffmean_en")),
    _sgnmean_en(declareADProperty<Real>("sgnmean_en")),
    _sgnem(declareADProperty<Real>("sgnem")),
    _d_mumean_en_d_actual_mean_en(declareADProperty<Real>("d_mumean_en_d_actual_mean_en")),
    _d_diffmean_en_d_actual_mean_en(declareADProperty<Real>("d_diffmean_en_d_actual_mean_en")),
    //_massem(declareProperty<Real>("massem")),
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

template <ComputeStage compute_stage>
void
ADGasElectronMoments<compute_stage>::computeQpProperties()
{
  //_massem[_qp] = 9.11e-31;

  //_e[_qp] = 1.6e-19;
  //_eps[_qp] = 8.85e-12;
  //_sgnem[_qp] = -1.;


  _d_muem_d_actual_mean_en[_qp] =
      _mu_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp])) * _voltage_scaling *
      _time_units;
  _diffem[_qp] = _diff_interpolation.sample(std::exp(_mean_en[_qp] - _em[_qp])) * _time_units;
  _muem[_qp] =
      _mu_interpolation.sample(std::exp(_mean_en[_qp] - _em[_qp])) * _voltage_scaling * _time_units;
  _mumean_en[_qp] = 5.0/3.0 * _muem[_qp];
  _diffmean_en[_qp] = 5.0/3.0 * _diffem[_qp];

  _sgnmean_en[_qp] = -1.0;
  _sgnem[_qp] = -1.0;
  _d_diffem_d_actual_mean_en[_qp] =
      _diff_interpolation.sampleDerivative(std::exp(_mean_en[_qp] - _em[_qp])) * _time_units;
  _d_mumean_en_d_actual_mean_en[_qp] = 5.0/3.0 * _d_muem_d_actual_mean_en[_qp]; 
  _d_diffmean_en_d_actual_mean_en[_qp] = 5.0/3.0 * _d_diffem_d_actual_mean_en[_qp]; 
}
