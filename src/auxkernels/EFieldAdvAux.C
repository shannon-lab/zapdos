//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EFieldAdvAux.h"

registerMooseObject("ZapdosApp", EFieldAdvAux);

template <>
InputParameters
validParams<EFieldAdvAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar(
      "potential", "The gradient of the potential will be used to compute the advection velocity.");
  params.addRequiredCoupledVar("density_log", "The variable representing the log of the density.");
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription(
    "Returns the electric field driven advective flux of defined species");
  return params;
}

EFieldAdvAux::EFieldAdvAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _r_units(1. / getParam<Real>("position_units")),

    // Coupled variables

    _density_var(*getVar("density_log", 0)),
    _density_log(coupledValue("density_log")),
    _grad_potential(coupledGradient("potential")),

    // Material properties

    _mu(getMaterialProperty<Real>("mu" + _density_var.name())),
    _sgn(getMaterialProperty<Real>("sgn" + _density_var.name()))
{
}

Real
EFieldAdvAux::computeValue()
{
  return _sgn[_qp] * _mu[_qp] * std::exp(_density_log[_qp]) * -_grad_potential[_qp](0) * _r_units *
         6.02e23;
}
