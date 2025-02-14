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
 *  Generic artificial electric field driven advection term
 *  (Densities must be in logarithmic form)
 */
class EFieldArtDiff : public ADKernel
{
public:
  static InputParameters validParams();

  EFieldArtDiff(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Gradient of the coupled potential
  const ADVariableGradient & _grad_potential;

  /// Scaling factor for the artificial diffusion
  const Real & _scale;
  /// Position units
  const Real _r_units;

  /// Mobility coefficient
  const ADMaterialProperty<Real> & _mu;
};
