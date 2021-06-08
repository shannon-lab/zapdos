//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DielectricBCWithEffEfield.h"

registerMooseObject("ZapdosApp", DielectricBCWithEffEfield);

InputParameters
DielectricBCWithEffEfield::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("dielectric_constant", "The dielectric constant of the material.");
  params.addRequiredParam<Real>("thickness", "The thickness of the material.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addRequiredCoupledVar("mean_en", "The mean energy.");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredCoupledVar("ip", "The ion density.");

  params.addRequiredCoupledVar("Ex", "The EField in the x-direction");
  params.addCoupledVar("Ey", "The EField in the y-direction"); // only required in 2D and 3D
  params.addCoupledVar("Ez", "The EField in the z-direction"); // only required in 3D

  params.addParam<Real>("users_gamma",
                        "A secondary electron emission coeff. only used for this BC.");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  return params;
}

DielectricBCWithEffEfield::DielectricBCWithEffEfield(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _r_units(1. / getParam<Real>("position_units")),

    _u_old(_var.slnOld()),
    _grad_u_old(_var.gradSlnOld()),

    _mean_en(adCoupledValue("mean_en")),
    _mean_en_var(*getVar("mean_en", 0)),
    _mean_en_old(_mean_en_var.slnOld()),
    _em(adCoupledValue("em")),
    _em_var(*getVar("em", 0)),
    _em_old(_em_var.slnOld()),
    _ip(adCoupledValue("ip")),
    _ip_var(*getVar("ip", 0)),
    _ip_old(_ip_var.slnOld()),

    _Ex(adCoupledValue("Ex")),
    _Ex_var(*getVar("Ex", 0)),
    _Ex_old(_Ex_var.slnOld()),

    //_Ey(adCoupledValue("Ey")),
    _Ey(isCoupled("Ey") ? adCoupledValue("Ey") : _ad_zero),
    _Ey_var(*getVar("Ey", 0)),
    //_Ey_old(_Ey_var.slnOld()),
    _Ey_old(isCoupled("Ey") ? _Ey_var.slnOld() : _zero),

    //_Ez(adCoupledValue("Ez")),
    _Ez(isCoupled("Ez") ? adCoupledValue("Ez") : _ad_zero),
    _Ez_var(*getVar("Ez", 0)),
    //_Ez_old(_Ez_var.slnOld()),
    _Ez_old(isCoupled("Ez") ? _Ez_var.slnOld() : _zero),

    _e(getMaterialProperty<Real>("e")),
    _epsilon_0(getADMaterialProperty<Real>("diff" + _var.name())),
    _N_A(getMaterialProperty<Real>("N_A")),

    _sgnip(getMaterialProperty<Real>("sgn" + _ip_var.name())),
    _muip(getADMaterialProperty<Real>("mu" + _ip_var.name())),
    _massem(getMaterialProperty<Real>("massem")),
    _user_se_coeff(getParam<Real>("users_gamma")),

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
    _potential_units(getParam<std::string>("potential_units"))
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;
}

ADReal
DielectricBCWithEffEfield::computeQpResidual()
{

  ADRealVectorValue EField(_Ex[_qp], _Ey[_qp], _Ez[_qp]);

  if (_normals[_qp] * _sgnip[_qp] * EField >= 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  _ion_flux =
      (_a * _sgnip[_qp] * _muip[_qp] * EField * _r_units * std::exp(_ip[_qp]));

  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  _em_flux =
      (0.25 * _v_thermal * std::exp(_em[_qp]) * _normals[_qp]) - (_user_se_coeff * _ion_flux);


  RealVectorValue EField_old(_Ex_old[_qp], _Ey_old[_qp], _Ez_old[_qp]);

  if (_normals[_qp] * _sgnip[_qp] * EField_old >= 0.0)
  {
    _a_old = 1.0;
  }
  else
  {
    _a_old = 0.0;
  }

  _ion_flux_old =
      (_a_old * _sgnip[_qp] * _muip[_qp] * EField_old * _r_units * std::exp(_ip_old[_qp]));


  _v_thermal_old =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en_old[_qp] - _em_old[_qp]) / (M_PI * _massem[_qp]));

  _em_flux_old =
      (0.25 * _v_thermal_old * std::exp(_em_old[_qp]) * _normals[_qp]) - (_user_se_coeff * _ion_flux_old);


  ADRealVectorValue _int = (_e[_qp] * _N_A[_qp] / _voltage_scaling) * _dt *
                           (0.5 * (_ion_flux - _em_flux) + 0.5 * (_ion_flux_old - _em_flux_old));

  return _test[_i][_qp] * _r_units * (-_epsilon_0[_qp] * _grad_u_old[_qp] * _normals[_qp] +
              (_epsilon_d / _thickness) * (_u[_qp] - _u_old[_qp]) - _int * _normals[_qp]);
}
