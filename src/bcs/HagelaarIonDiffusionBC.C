//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "HagelaarIonDiffusionBC.h"

registerADMooseObject("ZapdosApp", HagelaarIonDiffusionBC);

InputParameters
HagelaarIonDiffusionBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addParam<Real>(
      "user_velocity", -1., "Optional parameter if user wants to specify the thermal velocity.");
  params.addClassDescription("Kinetic electron boundary condition"
                             " (Based on [!cite](hagelaar2000boundary))");
  return params;
}

HagelaarIonDiffusionBC::HagelaarIonDiffusionBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    _kb(getMaterialProperty<Real>("k_boltz")),
    _T(getADMaterialProperty<Real>("T" + _var.name())),
    _mass(getMaterialProperty<Real>("mass" + _var.name())),
    _user_velocity(getParam<Real>("user_velocity"))
{
  _v_thermal = 0.0;
}

ADReal
HagelaarIonDiffusionBC::computeQpResidual()
{
  if (_user_velocity > 0.)
    _v_thermal = _user_velocity;
  else
    _v_thermal = std::sqrt(8 * _kb[_qp] * _T[_qp] / (M_PI * _mass[_qp]));

  return _test[_i][_qp] * _r_units * (1. - _r) / (1. + _r) * 0.5 * _v_thermal * std::exp(_u[_qp]);
}
