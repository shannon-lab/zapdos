//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DielectricBCWithEffEfield.h"
#include "Zapdos.h"

registerMooseObject("ZapdosApp", DielectricBCWithEffEfield);

InputParameters
DielectricBCWithEffEfield::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("dielectric_constant", "The dielectric constant of the material.");
  params.addRequiredParam<Real>("thickness", "The thickness of the material.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredCoupledVar("electron_energy", "The mean energy.");
  params.addRequiredCoupledVar("electrons", "The electron density.");
  params.addRequiredCoupledVar("ions", "A list of ion densities in log form");

  params.addRequiredCoupledVar("Ex", "The EField in the x-direction");
  params.addCoupledVar("Ey", "The EField in the y-direction"); // only required in 2D and 3D
  params.addCoupledVar("Ez", "The EField in the z-direction"); // only required in 3D

  params.addParam<std::vector<std::string>>(
      "emission_coeffs",
      "The secondary electron emission coefficient for each ion provided in `ions`");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addClassDescription("Time integrated dielectric boundary condition"
                             " (Based on [!cite](lymberopoulos1994modeling))");
  return params;
}

DielectricBCWithEffEfield::DielectricBCWithEffEfield(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _r_units(1. / getParam<Real>("position_units")),

    _u_old(_var.slnOld()),
    _grad_u_old(_var.gradSlnOld()),

    _mean_en(adCoupledValue("electron_energy")),
    _mean_en_old((*getVar("electron_energy", 0)).slnOld()),
    _em(adCoupledValue("electrons")),
    _em_old((*getVar("electrons", 0)).slnOld()),

    _Ex(adCoupledValue("Ex")),
    _Ex_old((*getVar("Ex", 0)).slnOld()),

    _Ey(isCoupled("Ey") ? adCoupledValue("Ey") : _ad_zero),
    _Ey_old(isCoupled("Ey") ? (*getVar("Ey", 0)).slnOld() : _zero),

    _Ez(isCoupled("Ez") ? adCoupledValue("Ez") : _ad_zero),
    _Ez_old(isCoupled("Ez") ? (*getVar("Ez", 0)).slnOld() : _zero),

    _epsilon_0(getADMaterialProperty<Real>("diff" + _var.name())),

    _massem(getMaterialProperty<Real>("massem")),
    _se_coeff_names(getParam<std::vector<std::string>>("emission_coeffs")),

    _epsilon_d(getParam<Real>("dielectric_constant")),
    _thickness(getParam<Real>("thickness")),
    _a(0.5),
    _a_old(0.5),
    _ion_flux(0, 0, 0),
    _ion_flux_old(0, 0, 0),
    _v_thermal(0),
    _v_thermal_old(0),
    _em_flux(0, 0, 0),
    _em_flux_old(0, 0, 0),
    _potential_units(getParam<std::string>("potential_units")),
    _num_ions(coupledComponents("ions"))
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;

  _ip.resize(_num_ions);
  _ip_old.resize(_num_ions);
  _muip.resize(_num_ions);
  _sgnip.resize(_num_ions);
  _user_se_coeff.resize(_num_ions);

  for (unsigned int i = 0; i < _num_ions; ++i)
  {
    _ip[i] = &adCoupledValue("ions", i);
    _ip_old[i] = &(*getVar("ions", i)).slnOld();
    _muip[i] = &getADMaterialProperty<Real>("mu" + (*getVar("ions", i)).name());
    _sgnip[i] = &getMaterialProperty<Real>("sgn" + (*getVar("ions", i)).name());
    _user_se_coeff[i] = &getADMaterialProperty<Real>(_se_coeff_names[i]);
  }
}

ADReal
DielectricBCWithEffEfield::computeQpResidual()
{

  ADRealVectorValue EField(_Ex[_qp], _Ey[_qp], _Ez[_qp]);
  RealVectorValue EField_old(_Ex_old[_qp], _Ey_old[_qp], _Ez_old[_qp]);

  _ion_flux.zero();
  _ion_flux_old.zero();
  _em_flux.zero();
  _em_flux_old.zero();
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

    _temp_flux =
        _a * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * EField * _r_units * std::exp((*_ip[i])[_qp]);

    _ion_flux += _temp_flux;

    _em_flux -= (*_user_se_coeff[i])[_qp] * _temp_flux;

    if (_normals[_qp] * (*_sgnip[i])[_qp] * EField_old >= 0.0)
    {
      _a_old = 1.0;
    }
    else
    {
      _a_old = 0.0;
    }

    _temp_flux = _a_old * (*_sgnip[i])[_qp] * (*_muip[i])[_qp] * EField_old * _r_units *
                 std::exp((*_ip_old[i])[_qp]);

    _ion_flux_old += _temp_flux;

    _em_flux_old -= (*_user_se_coeff[i])[_qp] * _temp_flux;
  }

  _v_thermal = std::sqrt(8 * ZAPDOS_CONSTANTS::e * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) /
                         (libMesh::pi * _massem[_qp]));

  _em_flux += (0.25 * _v_thermal * std::exp(_em[_qp]) * _normals[_qp]);

  _v_thermal_old =
      std::sqrt(8 * ZAPDOS_CONSTANTS::e * 2.0 / 3 * std::exp(_mean_en_old[_qp] - _em_old[_qp]) /
                (libMesh::pi * _massem[_qp]));

  _em_flux_old += (0.25 * _v_thermal_old * std::exp(_em_old[_qp]) * _normals[_qp]);

  ADRealVectorValue _int = (ZAPDOS_CONSTANTS::e * ZAPDOS_CONSTANTS::N_A / _voltage_scaling) * _dt *
                           (0.5 * (_ion_flux - _em_flux) + 0.5 * (_ion_flux_old - _em_flux_old));

  return _test[_i][_qp] * _r_units *
         (-_epsilon_0[_qp] * _grad_u_old[_qp] * _normals[_qp] +
          (_epsilon_d / _thickness) * (_u[_qp] - _u_old[_qp]) - _int * _normals[_qp]);
}
