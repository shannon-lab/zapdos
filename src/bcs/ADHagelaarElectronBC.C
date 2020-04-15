//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADHagelaarElectronBC.h"

registerADMooseObject("ZapdosApp", ADHagelaarElectronBC);

defineADLegacyParams(ADHagelaarElectronBC);

InputParameters
ADHagelaarElectronBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredParam<Real>("r", "The reflection coefficient");
  params.addRequiredCoupledVar("potential", "The electric potential");
  params.addRequiredCoupledVar("mean_en", "The mean energy.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Kinetic electron boundary condition"
                             "(Based on DOI:https://doi.org/10.1103/PhysRevE.62.1452)");
  return params;
}

ADHagelaarElectronBC::ADHagelaarElectronBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _r_units(1. / getParam<Real>("position_units")),
    _r(getParam<Real>("r")),

    // Coupled Variables
    _grad_potential(adCoupledGradient("potential")),
    _mean_en(adCoupledValue("mean_en")),

    _muem(getADMaterialProperty<Real>("muem")),
    _massem(getMaterialProperty<Real>("massem")),
    _e(getMaterialProperty<Real>("e"))
{
  _a = 0.0;
  _v_thermal = 0.0;
}

ADReal
ADHagelaarElectronBC::computeQpResidual()
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
      std::sqrt(8 * _e[_qp] * 2.0 / 3 * std::exp(_mean_en[_qp] - _u[_qp]) / (M_PI * _massem[_qp]));

  return _test[_i][_qp] * _r_units * (1. - _r) / (1. + _r) *
         (-(2 * _a - 1) * _muem[_qp] * -_grad_potential[_qp] * _r_units * std::exp(_u[_qp]) *
              _normals[_qp] +
          0.5 * _v_thermal * std::exp(_u[_qp]));
}
