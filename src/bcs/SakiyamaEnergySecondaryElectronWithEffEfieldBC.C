//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SakiyamaEnergySecondaryElectronWithEffEfieldBC.h"

registerMooseObject("ZapdosApp", SakiyamaEnergySecondaryElectronWithEffEfieldBC);

InputParameters
SakiyamaEnergySecondaryElectronWithEffEfieldBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addParam<std::vector<std::string>>(
      "emission_coeffs",
      "The secondary electron emission coefficient for each ion provided in `ions`");
  params.addRequiredParam<bool>(
      "Tse_equal_Te", "The secondary electron temperature equal the electron temperature in eV");
  params.addParam<Real>(
      "user_se_energy", 1.0, "The user's value of the secondary electron temperature in eV");
  params.addRequiredCoupledVar("Ex", "The EField in the x-direction");
  params.addCoupledVar("Ey", 0, "The EField in the y-direction"); // only required in 2D and 3D
  params.addCoupledVar("Ez", 0, "The EField in the z-direction"); // only required in 3D
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredCoupledVar("ions", "The ion density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription(
      "Kinetic secondary electron for mean electron energy boundary condition"
      " (Based on [!cite](sakiyama2007nonthermal))");
  return params;
}

SakiyamaEnergySecondaryElectronWithEffEfieldBC::SakiyamaEnergySecondaryElectronWithEffEfieldBC(
    const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    Te_dependent(getParam<bool>("Tse_equal_Te")),

    _Ex(adCoupledValue("Ex")),
    _Ey(adCoupledValue("Ey")),
    _Ez(adCoupledValue("Ez")),

    _em(adCoupledValue("em")),

    _se_coeff_names(getParam<std::vector<std::string>>("emission_coeffs")),
    _user_se_energy(getParam<Real>("user_se_energy")),
    _a(0.5),
    _se_energy(0),
    _ion_flux(0, 0, 0)
{
  _num_ions = coupledComponents("ions");

  _ip.resize(_num_ions);
  _muip.resize(_num_ions);
  _sgnip.resize(_num_ions);
  _user_se_coeff.resize(_num_ions);

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip[i] = &adCoupledValue("ions", i);
    _muip[i] = &getADMaterialProperty<Real>("mu" + (*getVar("ions", i)).name());
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ions", i)).name());
    _user_se_coeff[i] = &getADMaterialProperty<Real>(_se_coeff_names[i]);
  }
}

ADReal
SakiyamaEnergySecondaryElectronWithEffEfieldBC::computeQpResidual()
{
  ADRealVectorValue EField(_Ex[_qp], _Ey[_qp], _Ez[_qp]);

  _ion_flux.zero();
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    if (_normals[_qp] * (*_sgnip[i])[_qp] * EField >= 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    _ion_flux += _a * (*_user_se_coeff[i])[_qp] * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * EField *
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

  return -_test[_i][_qp] * _r_units * (5.0 / 3.0) * _se_energy * _ion_flux * _normals[_qp];
}
