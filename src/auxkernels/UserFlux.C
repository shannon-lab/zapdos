//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "UserFlux.h"

registerMooseObject("ZapdosApp", UserFlux);

template <>
InputParameters
validParams<UserFlux>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredCoupledVar("density_log", "The electron density");
  params.addRequiredParam<Real>("mu", "The mobility.");
  params.addRequiredParam<Real>("diff", "The diffusivity.");
  params.addRequiredParam<Real>("sign", "The charge sign of the drift-diffusing particle.");
  params.addRequiredParam<Real>("EField", "The electric field moving the charges.");
  params.addClassDescription(
      "Returns the total flux of defined species that requires constant user defined coefficients");
  return params;
}

UserFlux::UserFlux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _u(coupledValue("density_log")),
    _grad_u(coupledGradient("density_log")),
    _mu(getParam<Real>("mu")),
    _diff(getParam<Real>("diff")),
    _sign(getParam<Real>("sign")),
    _EField(getParam<Real>("EField"))
{
}

Real
UserFlux::computeValue()
{
  return _mu * _sign * _EField * std::exp(_u[_qp]) - _diff * std::exp(_u[_qp]) * _grad_u[_qp](0);
}
