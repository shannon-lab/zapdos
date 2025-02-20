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

registerMooseObject("ZapdosApp", SakiyamaEnergySecondaryElectronBC);

InputParameters
SakiyamaEnergySecondaryElectronBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<std::vector<std::string>>(
      "emission_coeffs",
      "The secondary electron emission coefficient for each ion provided in `ions`");
  params.addRequiredParam<bool>(
      "Tse_equal_Te", "The secondary electron temperature equal the electron temperature in eV");
  params.addParam<Real>(
      "secondary_electron_energy", 1.0, "The secondary electron temperature in eV");
  params.addRequiredCoupledVar("electrons", "The electron density in log form");
  params.addRequiredCoupledVar("ions", "A list of ion densities in log form");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<std::string>("field_property_name",
                               "field_solver_interface_property",
                               "Name of the solver interface material property.");
  params.addClassDescription(
      "Kinetic secondary electron for mean electron energy boundary condition"
      " (Based on [!cite](sakiyama2007nonthermal))");
  return params;
}

SakiyamaEnergySecondaryElectronBC::SakiyamaEnergySecondaryElectronBC(
    const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    Te_dependent(getParam<bool>("Tse_equal_Te")),
    _num_ions(coupledComponents("ions")),
    _se_coeff_names(getParam<std::vector<std::string>>("emission_coeffs")),
    // Coupled Variables

    _em(adCoupledValue("electrons")),

    _user_se_energy(getParam<Real>("secondary_electron_energy")),
    _a(0.5),
    _se_energy(0),
    _ion_flux(0, 0, 0),

    _electric_field(
        getADMaterialProperty<RealVectorValue>(getParam<std::string>("field_property_name")))
{

  if (_se_coeff_names.size() != _num_ions)
    mooseError("SakiyamaEnergySecondaryElectronBC with name ",
               name(),
               ": The lengths of `ions` and `emission_coeffs` "
               "must be the same");
  _ip.resize(_num_ions);
  _ip_var.resize(_num_ions);
  _muip.resize(_num_ions);
  _sgnip.resize(_num_ions);
  _se_coeff.resize(_num_ions);

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip_var[i] = getVar("ions", i);
    _ip[i] = &adCoupledValue("ions", i);
    _muip[i] = &getADMaterialProperty<Real>("mu" + (*getVar("ions", i)).name());
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ions", i)).name());
    _se_coeff[i] = &getADMaterialProperty<Real>(_se_coeff_names[i]);
  }
}

ADReal
SakiyamaEnergySecondaryElectronBC::computeQpResidual()
{
  _ion_flux.zero();
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    if (_normals[_qp] * (*_sgnip[i])[_qp] * _electric_field[_qp] > 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    _ion_flux += (*_se_coeff[i])[_qp] * _a * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] *
                 _electric_field[_qp] * _r_units * std::exp((*_ip[i])[_qp]);
  }

  if (Te_dependent)
  {
    _se_energy = std::exp(_u[_qp] - _em[_qp]);
  }
  else
  {
    _se_energy = _user_se_energy;
  }

  return -_test[_i][_qp] * _r_units * (5.0 / 3.0) * _se_energy * _ion_flux * _normals[_qp];
}
