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
  //params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("mean_en", "The mean energy.");
  params.addRequiredCoupledVar("ip", "The ion density.");
  params.addCoupledVar("neutral_gas", "Name of the neutrial gas");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<bool>("variable_temp", false,
       "Does the temperature of the species change based on Wannier's formulation");
  params.addParam<Real>("users_gamma", "A secondary electron emission coeff. only used for this BC.");
  params.addClassDescription(
    "Kinetic secondary electron boundary condition"
    "(Based on DOI: https://doi.org/10.1116/1.579300)");
  return params;
}

SakiyamaSecondaryElectronBC::SakiyamaSecondaryElectronBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    //_r(getParam<Real>("r")),

    // Coupled Variables
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),
    _mean_en(coupledValue("mean_en")),
    _mean_en_id(coupled("mean_en")),
    _ip_var(*getVar("ip", 0)),
    _ip(coupledValue("ip")),
    _grad_ip(coupledGradient("ip")),
    _ip_id(coupled("ip")),

    _muem(getMaterialProperty<Real>("muem")),
    _d_muem_d_actual_mean_en(getMaterialProperty<Real>("d_muem_d_actual_mean_en")),
    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _sgnip(getMaterialProperty<Real>("sgn" + _ip_var.name())),
    _muip(getMaterialProperty<Real>("mu" + _ip_var.name())),
    _Dip(getMaterialProperty<Real>("diff" + _ip_var.name())),
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
    _massNeutral(getMaterialProperty<Real>("mass" + (*getVar("neutral_gas",0)).name())),
    _massip(getMaterialProperty<Real>("mass" + _ip_var.name())),
    _T(getMaterialProperty<Real>("T" + _ip_var.name())),
    _variable_temp(getParam<bool>("variable_temp")),
    _temp(0),
    _d_temp_d_potential(0),
    _d_v_thermal_d_potential(0)
{
}

Real
SakiyamaSecondaryElectronBC::computeQpResidual()
{
  if (_normals[_qp] * 1.0 * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  if (_variable_temp)
  {
    _temp = _T[_qp] + (_massip[_qp] + _massNeutral[_qp]) / (5.0*_massip[_qp] + 3.0*_massNeutral[_qp]) *
                             (_massNeutral[_qp] * std::pow((_muip[_qp] * (_grad_potential[_qp] * _r_units).norm()),2) / _kb[_qp]);
  }
  else
  {
    _temp = _T[_qp];  // Needs to be changed.
  }

  _v_thermal = std::sqrt(8 * _kb[_qp] * _temp / (M_PI * _massip[_qp]));

  _ion_flux = (_a * _sgnip[_qp] * _muip[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_u[_qp]) * _normals[_qp]);
  //            + 0.25 * _v_thermal * std::exp(_u[_qp]);
  //_ion_flux = _sgnip[_qp] * _muip[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_ip[_qp]) -
  //            _Dip[_qp] * std::exp(_ip[_qp]) * _grad_ip[_qp] * _r_units;


  return  -_test[_i][_qp] * _r_units * _a * _user_se_coeff * _ion_flux *
             _normals[_qp];
}

Real
SakiyamaSecondaryElectronBC::computeQpJacobian()
{
  if (_normals[_qp] * 1.0 * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  return 0.;
}

Real
SakiyamaSecondaryElectronBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_id)
  {
    if (_normals[_qp] * 1.0 * -_grad_potential[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    if (_variable_temp)
    {
      Real _d_grad_potential_d_potential_mag = _grad_potential[_qp] * _r_units * _grad_phi[_j][_qp] * _r_units / (_grad_phi[_j][_qp] * _r_units).norm();

      _d_temp_d_potential = (_massip[_qp] + _massNeutral[_qp]) / (5.0*_massip[_qp] + 3.0*_massNeutral[_qp]) *
                               (_massNeutral[_qp] * std::pow((_muip[_qp] * _d_grad_potential_d_potential_mag),2) / _kb[_qp]);
    }
    else
    {
      _d_temp_d_potential = 0;
    }


    _d_v_thermal_d_potential = std::sqrt(8 * _kb[_qp] * _d_temp_d_potential / (M_PI * _massip[_qp]));

    //_d_ion_flux_d_potential = (_a * _sgnip[_qp] * _muip[_qp] * -_grad_phi[_j][_qp] * _r_units * std::exp(_u[_qp]) * _normals[_qp])
    //            + 0.25 * _d_v_thermal_d_potential * std::exp(_u[_qp]);

    _d_ion_flux_d_potential = _sgnip[_qp] * _muip[_qp] * -_grad_phi[_j][_qp] * _r_units * std::exp(_ip[_qp]);

    return -_test[_i][_qp] * _r_units * _a * _user_se_coeff * _d_ion_flux_d_potential * _normals[_qp];
  }

  else if (jvar == _mean_en_id)
  {
    if (_normals[_qp] * 1.0 * -_grad_potential[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    return 0.;
  }

  else if (jvar == _ip_id)
  {
    if (_normals[_qp] * 1.0 * -_grad_potential[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    if (_variable_temp)
    {
      _temp = _T[_qp] + (_massip[_qp] + _massNeutral[_qp]) / (5.0*_massip[_qp] + 3.0*_massNeutral[_qp]) *
                               (_massNeutral[_qp] * std::pow((_muip[_qp] * (_grad_potential[_qp] * _r_units).norm()),2) / _kb[_qp]);
    }
    else
    {
      _temp = _T[_qp];  // Needs to be changed.
    }

    _v_thermal = std::sqrt(8 * _kb[_qp] * _temp / (M_PI * _massip[_qp]));

    _d_ion_flux_d_ip = (_a * _sgnip[_qp] * _muip[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_u[_qp]) * _phi[_j][_qp] * _normals[_qp]);
    //            + 0.25 * _v_thermal * std::exp(_u[_qp]) * _phi[_j][_qp];

    //_d_ion_flux_d_ip = _sgnip[_qp] * _muip[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_u[_qp]) * _phi[_j][_qp] -
    //            _Dip[_qp] * (std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_ip[_qp] * _r_units + std::exp(_ip[_qp]) * _grad_phi[_j][_qp] * _r_units);

    return -_test[_i][_qp] * _r_units * _a * _user_se_coeff *
        _d_ion_flux_d_ip * _normals[_qp];
  }

  else
    return 0.0;
}
