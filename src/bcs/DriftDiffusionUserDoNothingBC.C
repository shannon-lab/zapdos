//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DriftDiffusionUserDoNothingBC.h"

registerMooseObject("ZapdosApp", DriftDiffusionUserDoNothingBC);

template <>
InputParameters
validParams<DriftDiffusionUserDoNothingBC>()
{
  InputParameters params = validParams<DriftDiffusionDoNothingBC>();
  params.addRequiredParam<Real>("mu", "The mobility.");
  params.addRequiredParam<Real>("diff", "The diffusivity.");
  params.addRequiredParam<Real>("sign", "The charge sign of the drift-diffusing particle.");
  params.addClassDescription("Boundary condition where the flux at the boundary is equal to the "
                             "bulk dift-diffusion equation"
                             "with constant user defined coefficients");
  return params;
}

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

DriftDiffusionUserDoNothingBC::DriftDiffusionUserDoNothingBC(const InputParameters & parameters)
  : DriftDiffusionDoNothingBC(parameters)
{
  _mu.resize(_fe_problem.getMaxQps(), Real(getParam<Real>("mu")));
  _diffusivity.resize(_fe_problem.getMaxQps(), Real(getParam<Real>("diff")));
  _sign.resize(_fe_problem.getMaxQps(), Real(getParam<Real>("sign")));
}
