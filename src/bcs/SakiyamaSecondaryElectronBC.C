//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SakiyamaSecondaryElectronBC.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", SakiyamaSecondaryElectronBC);

template <>
InputParameters
validParams<SakiyamaSecondaryElectronBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  // params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("mean_en", "The mean energy.");
  params.addRequiredCoupledVar("ip", "The ion density.");
  params.addCoupledVar("neutral_gas", "Name of the neutrial gas");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<bool>(
      "variable_temp",
      false,
      "Does the temperature of the species change based on Wannier's formulation");
  params.addParam<Real>("users_gamma",
                        "A secondary electron emission coeff. only used for this BC.");
  params.addClassDescription("Kinetic secondary electron boundary condition"
                             "(Based on DOI: https://doi.org/10.1116/1.579300)");
  return params;
}

SakiyamaSecondaryElectronBC::SakiyamaSecondaryElectronBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    // Coupled Variables
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),
    _mean_en(coupledValue("mean_en")),
    _mean_en_id(coupled("mean_en")),
    //_ip_var(*getVar("ip", 0)),
    //_ip(coupledValue("ip")),
    //_grad_ip(coupledGradient("ip")),
    //_ip_id(coupled("ip")),

    _muem(getMaterialProperty<Real>("muem")),
    _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    //_sgnip(getMaterialProperty<Real>("sgn" + _ip_var.name())),
    //_muip(getMaterialProperty<Real>("mu" + _ip_var.name())),
    //_Dip(getMaterialProperty<Real>("diff" + _ip_var.name())),
    _a(0.5),
    _v_thermal(0),
    _ion_flux(0, 0, 0),
    _n_gamma(0),
    _d_v_thermal_d_u(0),
    _d_v_thermal_d_mean_en(0),
    _d_ion_flux_d_potential(0, 0, 0),
    _d_ion_flux_d_ip(0, 0, 0),
    _d_n_gamma_d_potential(0),
    _d_n_gamma_d_ip(0),
    _d_n_gamma_d_u(0),
    _d_n_gamma_d_mean_en(0),
    _actual_mean_en(0),
    _user_se_coeff(getParam<Real>("users_gamma")),

    _kb(getMaterialProperty<Real>("k_boltz")),
    _massNeutral(getMaterialProperty<Real>("mass" + (*getVar("neutral_gas", 0)).name())),
    //_massip(getMaterialProperty<Real>("mass" + _ip_var.name())),
    //_T(getMaterialProperty<Real>("T" + _ip_var.name())),
    _variable_temp(getParam<bool>("variable_temp")),
    _temp(0),
    _d_temp_d_potential(0),
    _d_v_thermal_d_potential(0)
{
  _num_ions = coupledComponents("ip");

  _ip.resize(_num_ions);
  _ip_var.resize(_num_ions);
  _muip.resize(_num_ions);
  _sgnip.resize(_num_ions);
  _ion_id.resize(_num_ions);
  _massip.resize(_num_ions);
  _Tip.resize(_num_ions);
  _gradip.resize(_num_ions);

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip_var[i] = getVar("ip", i);
    _ip[i] = &coupledValue("ip", i);
    _gradip[i] = &coupledGradient("ip", i);
    _muip[i] = &getMaterialProperty<Real>("mu" + (*getVar("ip", i)).name());
    _ion_id[i] = _ip_var[i]->number();
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ip", i)).name());
    _massip[i] = &getMaterialProperty<Real>("mass" + (*getVar("ip", i)).name());
    _Tip[i] = &getMaterialProperty<Real>("T" + (*getVar("ip", i)).name());
  }
}

Real
SakiyamaSecondaryElectronBC::computeQpResidual()
{
  _ion_flux.zero();
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    if (_normals[_qp] * (*_sgnip[i])[_qp] * -_grad_potential[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    if (_variable_temp)
    {
      _temp = (*_Tip[i])[_qp] +
              ((*_massip[i])[_qp] + _massNeutral[_qp]) /
                  (5.0 * (*_massip[i])[_qp] + 3.0 * _massNeutral[_qp]) *
                  (_massNeutral[_qp] *
                   std::pow(((*_muip[i])[_qp] * (_grad_potential[_qp] * _r_units).norm()), 2) /
                   _kb[_qp]);
    }
    else
    {
      _temp = (*_Tip[i])[_qp]; // Needs to be changed.
    }

    _v_thermal = std::sqrt(8 * _kb[_qp] * _temp / (M_PI * (*_massip[i])[_qp]));

    _ion_flux += _a * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_potential[_qp] * _r_units *
                 std::exp((*_ip[i])[_qp]);
  }

  return -_test[_i][_qp] * _r_units * _a * _user_se_coeff * _ion_flux * _normals[_qp];
}

Real
SakiyamaSecondaryElectronBC::computeQpJacobian()
{
  return 0.;
}

Real
SakiyamaSecondaryElectronBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  _iter = std::find(_ion_id.begin(), _ion_id.end(), jvar);
  if (jvar == _potential_id)
  {
    Real _d_grad_potential_d_potential_mag = _grad_potential[_qp] * _r_units * _grad_phi[_j][_qp] *
                                             _r_units / (_grad_phi[_j][_qp] * _r_units).norm();

    _ion_flux.zero();
    for (unsigned int i = 0; i < _num_ions; ++i)
    {
      if (_normals[_qp] * (*_sgnip[i])[_qp] * -_grad_potential[_qp] > 0.0)
      {
        _a = 1.0;
      }
      else
      {
        _a = 0.0;
      }

      if (_variable_temp)
      {
        _d_temp_d_potential +=
            ((*_massip[i])[_qp] + _massNeutral[_qp]) /
            (5.0 * (*_massip[i])[_qp] + 3.0 * _massNeutral[_qp]) *
            (_massNeutral[_qp] *
             std::pow(((*_muip[i])[_qp] * _d_grad_potential_d_potential_mag), 2) / _kb[_qp]);
      }
      else
      {
        _d_temp_d_potential = 0;
      }

      _d_v_thermal_d_potential =
          std::sqrt(8 * _kb[_qp] * _d_temp_d_potential / (M_PI * (*_massip[i])[_qp]));

      _d_ion_flux_d_potential = (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_phi[_j][_qp] *
                                _r_units * std::exp((*_ip[i])[_qp]);
    }

    return -_test[_i][_qp] * _r_units * _a * _user_se_coeff * _d_ion_flux_d_potential *
           _normals[_qp];
  }

  else if (_iter != _ion_id.end())
  {
    _ip_index = std::distance(_ion_id.begin(), _iter);
    if (_normals[_qp] * (*_sgnip[_ip_index])[_qp] * -_grad_potential[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    if (_variable_temp)
    {
      _temp =
          (*_Tip[_ip_index])[_qp] +
          ((*_massip[_ip_index])[_qp] + _massNeutral[_qp]) /
              (5.0 * (*_massip[_ip_index])[_qp] + 3.0 * _massNeutral[_qp]) *
              (_massNeutral[_qp] *
               std::pow(((*_muip[_ip_index])[_qp] * (_grad_potential[_qp] * _r_units).norm()), 2) /
               _kb[_qp]);
    }
    else
    {
      _temp = (*_Tip[_ip_index])[_qp]; // Needs to be changed.
    }

    _v_thermal = std::sqrt(8 * _kb[_qp] * _temp / (M_PI * (*_massip[_ip_index])[_qp]));

    _d_ion_flux_d_ip = _a * (*_sgnip[_ip_index])[_qp] * (*_muip[_ip_index])[_qp] *
                       -_grad_potential[_qp] * _r_units * std::exp((*_ip[_ip_index])[_qp]) *
                       _phi[_j][_qp];

    return -_test[_i][_qp] * _r_units * _a * _user_se_coeff * _d_ion_flux_d_ip * _normals[_qp];
  }

  else
    return 0.0;
}
