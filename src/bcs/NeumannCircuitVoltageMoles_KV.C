//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "NeumannCircuitVoltageMoles_KV.h"

// MOOSE includes
#include "Function.h"

registerADMooseObject("ZapdosApp", NeumannCircuitVoltageMoles_KV);

InputParameters
NeumannCircuitVoltageMoles_KV::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<FunctionName>("function", "The function.");
  params.addRequiredParam<UserObjectName>(
      "data_provider",
      "The name of the UserObject that can provide some data to materials, bcs, etc.");

  params.addRequiredCoupledVar("ip", "The ion density.");
  params.deprecateCoupledVar("ip", "ions", "06/01/2024");
  params.addRequiredCoupledVar("ions", "A list of ion densities in log-molar form");

  params.addRequiredCoupledVar("em", "The log of the electron density.");
  params.deprecateCoupledVar("em", "electrons", "06/01/2024");
  params.addRequiredCoupledVar("electrons", "The electron density in log form");

  params.addRequiredCoupledVar(
      "mean_en", "The log of the product of the mean energy and the electron density.");
  params.deprecateCoupledVar("mean_en", "electron_energy", "06/01/2024");
  params.addRequiredCoupledVar("electron_energy", "The mean electron energy density in log form");

  params.addRequiredParam<std::vector<Real>>(
      "emission_coeffs",
      "The secondary electron emission coefficient for each ion provided in `ions`");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addRequiredParam<Real>("r",
                                "The reflection coefficient applied to both electrons and ions");
  params.addRequiredParam<Real>("position_units", "Units of position.");

  return params;
}

NeumannCircuitVoltageMoles_KV::NeumannCircuitVoltageMoles_KV(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _V_bat(getFunction("function")),
    _data(getUserObject<ProvideMobility>("data_provider")),
    _mean_en(adCoupledValue("electron_energy")),
    _em(adCoupledValue("electrons")),
    _se_coeff(getParam<std::vector<Real>>("emission_coeffs")),
    _eps(getMaterialProperty<Real>("eps")),
    _N_A(getMaterialProperty<Real>("N_A")),
    _muem(getADMaterialProperty<Real>("muem")),
    _e(getMaterialProperty<Real>("e")),
    _massem(getMaterialProperty<Real>("massem")),
    _kb(getMaterialProperty<Real>("k_boltz")),

    _potential_units(getParam<std::string>("potential_units")),
    _r(getParam<Real>("r"))
{
  _ion_flux.zero();
  _n_gamma = 0.0;
  _actual_mean_en = 0.0;
  _v_e_th = 0.0;
  _v_i_th = 0.0;
  _a = 0.0;
  _b = 0.0;
  _numerator = 0.0;
  _denominator = 0.0;
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;

  // First we need to initialize all of the ion densities and material properties.
  // Find the number of ions coupled into this BC:
  _num_ions = coupledComponents("ions");

  if (_se_coeff.size() != _num_ions)
    mooseError("NeumannCircuitVoltageMoles_KV with name ", name(), ": The lengths of `ions` and `emission_coeffs` must be "
               "the same");
  // Resize the vectors to store _num_ions values:
  _ip.resize(_num_ions);
  _grad_ip.resize(_num_ions);
  _T_heavy.resize(_num_ions);
  _muip.resize(_num_ions);
  _Dip.resize(_num_ions);
  _sgnip.resize(_num_ions);
  _mass.resize(_num_ions);

  // Retrieve the values for each ion and store in the relevant vectors.
  // Note that these need to be dereferenced to get the values inside the
  // main body of the code.
  // e.g. instead of "_ip[_qp]" it would be "(*_ip[i])[_qp]", where "i"
  // refers to a single ion species.
  for (unsigned int i = 0; i < _ip.size(); ++i)
  {
    _ip[i] = &adCoupledValue("ions", i);
    _grad_ip[i] = &adCoupledGradient("ip", i);
    _T_heavy[i] = &getADMaterialProperty<Real>("T" + (*getVar("ions", i)).name());
    _muip[i] = &getADMaterialProperty<Real>("mu" + (*getVar("ions", i)).name());
    _Dip[i] = &getADMaterialProperty<Real>("diff" + (*getVar("ions", i)).name());
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ions", i)).name());
    _mass[i] = &getMaterialProperty<Real>("mass" + (*getVar("ions", i)).name());
  }
}

ADReal
NeumannCircuitVoltageMoles_KV::computeQpResidual()
{
  if (_normals[_qp] * -1.0 * -_grad_u[_qp] > 0.0)
  {
    _a = 1.0;
    _b = 0.;
  }
  else
  {
    _a = 0.0;
    _b = 1.;
  }

  _ion_flux.zero();
  _n_gamma = 0;
  _secondary_ion = 0;
  _ion_drift = 0;
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ion_flux += _se_coeff[i] *
                 ((*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_u[_qp] * _r_units *
                      std::exp((*_ip[i])[_qp]) -
                  (*_Dip[i])[_qp] * std::exp((*_ip[i])[_qp]) * (*_grad_ip[i])[_qp] * _r_units);

    _secondary_ion +=
        (-1. + (-1. + _a) * _se_coeff[i]) * std::exp((*_ip[i])[_qp]) * (*_muip[i])[_qp];

    _ion_drift += (-1. + (-1. + _a) * _se_coeff[i]) *
                  std::sqrt(8 * _kb[_qp] * (*_T_heavy[i])[_qp] / (M_PI * (*_mass[i])[_qp])) *
                  std::exp((*_ip[i])[_qp]);
  }
  _n_gamma = (1. - _a) * _ion_flux * _normals[_qp] /
             (_muem[_qp] * -_grad_u[_qp] * _r_units * _normals[_qp]);

  _v_e_th = std::sqrt(8 * _data.coulomb_charge() * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) /
                      (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units * _eps[_qp] *
         (-2. * (1. + _r) * _u[_qp] - 2. * (1. + _r) * -_V_bat.value(_t, _q_point[_qp]) +
          _data.electrode_area() * _data.coulomb_charge() * _data.ballast_resist() /
              _voltage_scaling * (-1. + _r) *
              (_N_A[_qp] * _ion_drift + _N_A[_qp] * (std::exp(_em[_qp]) - _n_gamma) * _v_e_th)) /
         (2. * _data.electrode_area() * _data.coulomb_charge() *
          ((-1. + 2. * _a) * _muem[_qp] / _voltage_scaling * _N_A[_qp] *
               (std::exp(_em[_qp]) - _n_gamma) -
           (-1. + 2. * _b) * _secondary_ion / _voltage_scaling * _N_A[_qp]) *
          _data.ballast_resist() * (-1. + _r));
}
