//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SakiyamaEnergySecondaryElectronBC.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", SakiyamaEnergySecondaryElectronBC);

template <>
InputParameters
validParams<SakiyamaEnergySecondaryElectronBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("se_coeff", "The secondary electron coefficient");
  params.addRequiredParam<bool>(
      "Tse_equal_Te", "The secondary electron temperature equal the electron temperature in eV");
  params.addParam<Real>(
      "user_se_energy", 1.0, "The user's value of the secondary electron temperature in eV");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredCoupledVar("ip", "The ion density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription(
      "Kinetic secondary electron for mean electron energy boundary condition"
      "(Based on DOI: https://doi.org/10.1116/1.579300)");
  return params;
}

SakiyamaEnergySecondaryElectronBC::SakiyamaEnergySecondaryElectronBC(
    const InputParameters & parameters)
  : IntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    Te_dependent(getParam<bool>("Tse_equal_Te")),

    // Coupled Variables
    _grad_potential(coupledGradient("potential")),
    _potential_id(coupled("potential")),

    _em(coupledValue("em")),
    _em_id(coupled("em")),

    _se_coeff(getParam<Real>("se_coeff")),
    _user_se_energy(getParam<Real>("user_se_energy")),
    _a(0.5),
    _se_energy(0),
    _d_se_energy_d_u(0),
    _d_se_energy_d_em(0),
    _ion_flux(0, 0, 0),
    _d_ion_flux_d_potential(0, 0, 0),
    _d_ion_flux_d_ip(0, 0, 0)
{
  _num_ions = coupledComponents("ip");

  _ip.resize(_num_ions);
  _ip_var.resize(_num_ions);
  _muip.resize(_num_ions);
  _sgnip.resize(_num_ions);
  _ion_id.resize(_num_ions);

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip_var[i] = getVar("ip", i);
    _ip[i] = &coupledValue("ip", i);
    _muip[i] = &getMaterialProperty<Real>("mu" + (*getVar("ip", i)).name());
    _ion_id[i] = _ip_var[i]->number();
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ip", i)).name());
  }
}

Real
SakiyamaEnergySecondaryElectronBC::computeQpResidual()
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

    _ion_flux += _a * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_potential[_qp] * _r_units *
                 std::exp((*_ip[i])[_qp]);
  }

  if (Te_dependent)
  {
    _se_energy = std::exp(_u[_qp] - _em[_qp]);
  }
  else
  {
    _se_energy = _user_se_energy;
  }

  return -_test[_i][_qp] * _r_units * _se_coeff * (5.0 / 3.0) * _se_energy * _ion_flux *
         _normals[_qp];
}

Real
SakiyamaEnergySecondaryElectronBC::computeQpJacobian()
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

    _ion_flux += _a * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_potential[_qp] * _r_units *
                 std::exp((*_ip[i])[_qp]);
  }

  if (Te_dependent)
  {
    _d_se_energy_d_u = std::exp(_u[_qp] - _em[_qp]) * _phi[_j][_qp];
  }
  else
  {
    _d_se_energy_d_u = 0;
  }

  return -_test[_i][_qp] * _r_units * _se_coeff * (5.0 / 3.0) * _d_se_energy_d_u * _ion_flux *
         _normals[_qp];
}

Real
SakiyamaEnergySecondaryElectronBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  _iter = std::find(_ion_id.begin(), _ion_id.end(), jvar);
  if (jvar == _potential_id)
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

      _d_ion_flux_d_potential += _a * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_phi[_j][_qp] *
                                 _r_units * std::exp((*_ip[i])[_qp]);
    }

    if (Te_dependent)
    {
      _se_energy = std::exp(_u[_qp] - _em[_qp]);
    }
    else
    {
      _se_energy = _user_se_energy;
    }

    return -_test[_i][_qp] * _r_units * _se_coeff * (5.0 / 3.0) * _se_energy *
           _d_ion_flux_d_potential * _normals[_qp];
  }

  else if (jvar == _em_id)
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

      _ion_flux += _a * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * -_grad_potential[_qp] * _r_units *
                   std::exp((*_ip[i])[_qp]);
    }

    if (Te_dependent)
    {
      _d_se_energy_d_em = std::exp(_u[_qp] - _em[_qp]) * -_phi[_j][_qp];
    }
    else
    {
      _d_se_energy_d_em = 0;
    }

    return -_test[_i][_qp] * _r_units * _se_coeff * (5.0 / 3.0) * _d_se_energy_d_em * _ion_flux *
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

    if (Te_dependent)
    {
      _se_energy = std::exp(_u[_qp] - _em[_qp]);
    }
    else
    {
      _se_energy = _user_se_energy;
    }

    _d_ion_flux_d_ip = _a * (*_sgnip[_ip_index])[_qp] * (*_muip[_ip_index])[_qp] *
                       -_grad_potential[_qp] * _r_units * std::exp((*_ip[_ip_index])[_qp]) *
                       _phi[_j][_qp];

    return -_test[_i][_qp] * _r_units * _se_coeff * (5.0 / 3.0) * _se_energy * _d_ion_flux_d_ip *
           _normals[_qp];
  }

  else
    return 0.0;
}
