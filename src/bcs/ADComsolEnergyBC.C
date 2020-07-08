//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADComsolEnergyBC.h"

registerADMooseObject("ZapdosApp", ADComsolEnergyBC);

defineADLegacyParams(ADComsolEnergyBC);

InputParameters
ADComsolEnergyBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("em", "The electron density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

ADComsolEnergyBC::ADComsolEnergyBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    // Coupled Variables
    _grad_potential(adCoupledGradient("potential")),
    _em(adCoupledValue("em")),

    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e"))
{
  _v_thermal = 0.0;
}

ADReal
ADComsolEnergyBC::computeQpResidual()
{
  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units * (1. - _r) / (1. + _r) * 5. / 6. * _v_thermal *
         std::exp(_u[_qp]);
}
