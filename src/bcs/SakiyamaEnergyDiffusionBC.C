//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SakiyamaEnergyDiffusionBC.h"

registerMooseObject("ZapdosApp", SakiyamaEnergyDiffusionBC);

InputParameters
SakiyamaEnergyDiffusionBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredCoupledVar("em", "The electron density.");
  params.deprecateCoupledVar("em", "electrons", "06/01/2024");
  params.addRequiredCoupledVar("electrons", "The electron density in log form");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Kinetic advective electron energy boundary condition"
                             "(Based on DOI: https://doi.org/10.1116/1.579300)");
  return params;
}

SakiyamaEnergyDiffusionBC::SakiyamaEnergyDiffusionBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    // Coupled Variables
    _em(adCoupledValue("electrons")),

    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _v_thermal(0)
{
}

ADReal
SakiyamaEnergyDiffusionBC::computeQpResidual()
{

  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_u[_qp] - _em[_qp]) / (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units * ((5.0 / 3.0) * 0.25 * _v_thermal * std::exp(_u[_qp]));
}
