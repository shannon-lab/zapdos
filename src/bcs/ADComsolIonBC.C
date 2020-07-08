//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADComsolIonBC.h"

// MOOSE includes
#include "MooseVariable.h"

registerADMooseObject("ZapdosApp", ADComsolIonBC);

defineADLegacyParams(ADComsolIonBC);

InputParameters
ADComsolIonBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Kinetic advective ion boundary condition"
                             "(Based on DOI:https://doi.org/10.1103/PhysRevE.62.1452)");
  return params;
}

ADComsolIonBC::ADComsolIonBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    // Coupled Variables
    _grad_potential(adCoupledGradient("potential")),

    _mu(getADMaterialProperty<Real>("mu" + _var.name())),
    _e(getMaterialProperty<Real>("e")),
    _sgn(getMaterialProperty<Real>("sgn" + _var.name())),
    _kb(getMaterialProperty<Real>("k_boltz")),
    _T(getADMaterialProperty<Real>("T" + _var.name())),
    _mass(getMaterialProperty<Real>("mass" + _var.name()))
{
  _a = 0.0;
}

ADReal
ADComsolIonBC::computeQpResidual()
{
  if (_normals[_qp] * _sgn[_qp] * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }

  _v_thermal = std::sqrt(8 * _kb[_qp] * _T[_qp] / (M_PI * _mass[_qp]));

  return _test[_i][_qp] * _r_units * std::exp(_u[_qp]) *
         (_a * _sgn[_qp] * _mu[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
          0.5 * _v_thermal);
}
