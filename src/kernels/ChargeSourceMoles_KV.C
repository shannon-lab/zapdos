//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ChargeSourceMoles_KV.h"

registerMooseObject("ZapdosApp", ChargeSourceMoles_KV);

InputParameters
ChargeSourceMoles_KV::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addRequiredCoupledVar("charged", "The charged species");
  params.addRequiredParam<std::string>("potential_units", "The potential units.");
  params.addClassDescription(
      "Used for adding charged sources to Poisson’s equation. This kernel "
      "assumes that densities are measured in units of mol/m$^{3}$ as opposed to #/m$^{3}$");
  return params;
}

ChargeSourceMoles_KV::ChargeSourceMoles_KV(const InputParameters & parameters)
  : ADKernel(parameters),
    _charged_var(*getVar("charged", 0)),
    _charged(adCoupledValue("charged")),
    _e(getMaterialProperty<Real>("e")),
    _sgn(getMaterialProperty<Real>("sgn" + _charged_var.name())),
    _N_A(getMaterialProperty<Real>("N_A")),
    _potential_units(getParam<std::string>("potential_units"))
{
  if (_potential_units.compare("V") == 0)
    _voltage_scaling = 1.;
  else if (_potential_units.compare("kV") == 0)
    _voltage_scaling = 1000;
}

ADReal
ChargeSourceMoles_KV::computeQpResidual()
{
  return -_test[_i][_qp] * _e[_qp] * _sgn[_qp] * _N_A[_qp] * std::exp(_charged[_qp]) /
         _voltage_scaling;
}
