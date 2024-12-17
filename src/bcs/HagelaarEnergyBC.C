//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "HagelaarEnergyBC.h"

registerADMooseObject("ZapdosApp", HagelaarEnergyBC);

InputParameters
HagelaarEnergyBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("electrons", "The electron density in log form");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Kinetic electron mean energy boundary condition"
                             " (Based on [!cite](hagelaar2000boundary))");
  return params;
}

HagelaarEnergyBC::HagelaarEnergyBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    // Coupled Variables
    _grad_potential(adCoupledGradient("potential")),
    _em(adCoupledValue("electrons")),

    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _mumean_en(getADMaterialProperty<Real>("mumean_en"))
{
  _a = 0.5;
  _v_thermal = 0.0;
}

ADReal
HagelaarEnergyBC::computeQpResidual()
{
  if (_normals[_qp] * -1.0 * -_grad_potential[_qp] > 0.0)
  {
    _a = 1.0;
  }
  else
  {
    _a = 0.0;
  }
  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units * (1. - _r) / (1. + _r) *
         (-(2. * _a - 1.) * _mumean_en[_qp] * -_grad_potential[_qp] * _r_units * _normals[_qp] +
          5. / 6. * _v_thermal) *
         std::exp(_u[_qp]);
}
