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

/**
 *  The derivative of the generic diffusion term used to calculate the
 *  sensitivity value for the shoothing method
 */
class CoeffDiffusionForShootMethod : public ADKernel
{
public:
  static InputParameters validParams();

  CoeffDiffusionForShootMethod(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Position units
  const Real _r_units;

  /// Density variable to be accelerated
  MooseVariable & _density_var;
  /// Diffusion coefficient
  const ADMaterialProperty<Real> & _diffusivity;
};
