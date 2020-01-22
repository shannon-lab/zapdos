//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "CoeffDiffusionLin.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", CoeffDiffusionLin);

template <>
InputParameters
validParams<CoeffDiffusionLin>()
{
  InputParameters params = validParams<Diffusion>();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Generic linear diffusion term"
                             "(Values are NOT in log form)");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

CoeffDiffusionLin::CoeffDiffusionLin(const InputParameters & parameters)
  : Diffusion(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _diffusivity(getMaterialProperty<Real>("diff" + _var.name()))
{
}

CoeffDiffusionLin::~CoeffDiffusionLin() {}

Real
CoeffDiffusionLin::computeQpResidual()
{
  return -_diffusivity[_qp] * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] * _r_units;
}

Real
CoeffDiffusionLin::computeQpJacobian()
{
  return -_diffusivity[_qp] * _grad_phi[_j][_qp] * _r_units * -_grad_test[_i][_qp] * _r_units;
}
