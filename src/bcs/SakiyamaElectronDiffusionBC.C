//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SakiyamaElectronDiffusionBC.h"

registerMooseObject("ZapdosApp", SakiyamaElectronDiffusionBC);

InputParameters
SakiyamaElectronDiffusionBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredCoupledVar("mean_en", "The mean energy.");
  params.deprecateCoupledVar("mean_en", "electron_energy", "06/01/2024");
  params.addRequiredCoupledVar("electron_energy", "The mean electron energy density in log form");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Kinetic electron boundary condition"
                             "(Based on DOI: https://doi.org/10.1116/1.579300)");
  return params;
}

SakiyamaElectronDiffusionBC::SakiyamaElectronDiffusionBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    // Coupled Variables
    _mean_en(adCoupledValue("electron_energy")),

    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e")),
    _v_thermal(0)
{
}

ADReal
SakiyamaElectronDiffusionBC::computeQpResidual()
{

  _v_thermal =
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units * (0.25 * _v_thermal * std::exp(_u[_qp]));
}
