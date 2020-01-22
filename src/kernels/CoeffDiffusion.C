//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "CoeffDiffusion.h"

// MOOSE includes
#include "MooseVariable.h"

registerMooseObject("ZapdosApp", CoeffDiffusion);

template <>
InputParameters
validParams<CoeffDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addRequiredParam<Real>("position_units", "Units of position.");
  params.addClassDescription("Generic diffusion term"
                             "(Densities must be in log form)");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

CoeffDiffusion::CoeffDiffusion(const InputParameters & parameters)
  : Diffusion(parameters),

    _r_units(1. / getParam<Real>("position_units")),

    _diffusivity(getMaterialProperty<Real>("diff" + _var.name()))
{
}

CoeffDiffusion::~CoeffDiffusion() {}

Real
CoeffDiffusion::computeQpResidual()
{
  return -_diffusivity[_qp] * std::exp(_u[_qp]) * _grad_u[_qp] * _r_units * -_grad_test[_i][_qp] *
         _r_units;
}

Real
CoeffDiffusion::computeQpJacobian()
{
  return -_diffusivity[_qp] *
         (std::exp(_u[_qp]) * _grad_phi[_j][_qp] * _r_units +
          std::exp(_u[_qp]) * _phi[_j][_qp] * _grad_u[_qp] * _r_units) *
         -_grad_test[_i][_qp] * _r_units;
}
