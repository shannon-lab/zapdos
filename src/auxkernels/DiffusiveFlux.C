//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DiffusiveFlux.h"

registerMooseObject("ZapdosApp", DiffusiveFlux);

template <>
InputParameters
validParams<DiffusiveFlux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("density_log", "The variable representing the log of the density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  return params;
}

DiffusiveFlux::DiffusiveFlux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),

    // Coupled variables

    _grad_density_log(coupledGradient("density_log")),
    _density_var(*getVar("density_log", 0)),
    _density_log(coupledValue("density_log")),

    // Material properties

    _diff(getMaterialProperty<Real>("diff" + _density_var.name()))
{
}

Real
DiffusiveFlux::computeValue()
{
  return -_diff[_qp] * std::exp(_density_log[_qp]) * _grad_density_log[_qp](0) * _r_units * 6.02e23;
}
