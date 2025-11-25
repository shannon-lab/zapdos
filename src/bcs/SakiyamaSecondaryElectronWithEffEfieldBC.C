//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SakiyamaSecondaryElectronWithEffEfieldBC.h"

registerMooseObject("ZapdosApp", SakiyamaSecondaryElectronWithEffEfieldBC);

InputParameters
SakiyamaSecondaryElectronWithEffEfieldBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredCoupledVar("ions", "A list of ion densities in log form");
  params.addRequiredCoupledVar("electric_field_x", "The electric field in the x-direction");
  params.addCoupledVar("electric_field_y",
                       0,
                       "The electric field in the y-direction"); // only required in 2D and 3D
  params.addCoupledVar("electric_field_z",
                       0,
                       "The electric field in the z-direction"); // only required in 3D
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<std::vector<std::string>>(
      "emission_coeffs",
      "The secondary electron emission coefficient for each ion provided in `ions`");
  params.addClassDescription("Kinetic secondary electron boundary condition"
                             " (Based on [!cite](sakiyama2006corona))");
  return params;
}

SakiyamaSecondaryElectronWithEffEfieldBC::SakiyamaSecondaryElectronWithEffEfieldBC(
    const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _Ex(adCoupledValue("electric_field_x")),
    _Ey(adCoupledValue("electric_field_y")),
    _Ez(adCoupledValue("electric_field_z")),

    _a(0.5),
    _ion_flux(0, 0, 0),
    _se_coeff_names(getParam<std::vector<std::string>>("emission_coeffs"))
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
SakiyamaSecondaryElectronWithEffEfieldBC::computeQpResidual()
{
  ADRealVectorValue EField(_Ex[_qp], _Ey[_qp], _Ez[_qp]);

  _ion_flux.zero();
  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    using std::exp;
    if (_normals[_qp] * (*_sgnip[i])[_qp] * EField >= 0.0)
    {
      _a = 1.0;
    }
    else
    {
      _a = 0.0;
    }

    _ion_flux += _a * (*_user_se_coeff[i])[_qp] * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * EField *
                 _r_units * exp((*_ip[i])[_qp]);
  }

  return -_test[_i][_qp] * _r_units * _ion_flux * _normals[_qp];
}
