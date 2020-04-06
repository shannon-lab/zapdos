//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Diffusion.h"

class CoeffDiffusionForShootMethod;

template <>
InputParameters validParams<CoeffDiffusionForShootMethod>();

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class CoeffDiffusionForShootMethod : public Diffusion
{
public:
  CoeffDiffusionForShootMethod(const InputParameters & parameters);
  virtual ~CoeffDiffusionForShootMethod();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Real _r_units;

  MooseVariable & _density_var;
  const MaterialProperty<Real> & _diffusivity;
};
