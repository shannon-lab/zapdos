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
 *  Electron energy diffusion term
 *  that assumes a thermal conductivity of
 *  K = 3/2 D_e n_e
 */
class ThermalConductivityDiffusion : public ADKernel
{
public:
  static InputParameters validParams();

  ThermalConductivityDiffusion(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

private:

  /// Position units
  Real _r_units;
  /// Coefficient relating diffusion coefficient * density to thermal conductivity
  Real _coeff;
  /// Diffusion coefficient
  const ADMaterialProperty<Real> & _diffem;
  /// Electron density
  const ADVariableValue & _em;
  /// Gradient of electron density
  const ADVariableGradient & _grad_em;
};
