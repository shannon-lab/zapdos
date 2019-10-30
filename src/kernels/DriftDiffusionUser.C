//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DriftDiffusionUser.h"

registerMooseObject("ZapdosApp", DriftDiffusionUser);

template <>
InputParameters
validParams<DriftDiffusionUser>()
{
  InputParameters params = validParams<DriftDiffusion>();
  params.addRequiredParam<Real>("mu", "The mobility.");
  params.addRequiredParam<Real>("diff", "The diffusivity.");
  params.addRequiredParam<Real>("sign", "The charge sign of the drift-diffusing particle.");
  params.addClassDescription("Generic drift-diffusion equation that contains both"
    "electric field driven advection and diffusion term and that requires constant user defined"
    "mobility and diffusivity"
    "(Densities must be in log form)");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

DriftDiffusionUser::DriftDiffusionUser(const InputParameters & parameters)
  : DriftDiffusion(parameters)
{
  _mu.resize(_fe_problem.getMaxQps(), Real(getParam<Real>("mu")));
  _diffusivity.resize(_fe_problem.getMaxQps(), Real(getParam<Real>("diff")));
  _sign.resize(_fe_problem.getMaxQps(), Real(getParam<Real>("sign")));
}
