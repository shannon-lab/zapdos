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

#include "ADKernel.h"

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class CoeffDiffusionForShootMethod : public ADKernel
{
public:
  static InputParameters validParams();

  CoeffDiffusionForShootMethod(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const Real _r_units;

  MooseVariable & _density_var;
  const ADMaterialProperty<Real> & _diffusivity;
};
