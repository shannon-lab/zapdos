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
 *  Generic drift-diffusion equation that contains both
 *  an electric field driven advection term and a diffusion term
 */
class DriftDiffusion : public ADKernel
{
public:
  static InputParameters validParams();

  DriftDiffusion(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Position units
  const Real _r_units;

  /// Mobility coefficient
  const ADMaterialProperty<Real> & _mu;
  /// Charge sign of the species
  const MaterialProperty<Real> & _sign;
  /// Custom mobility coefficient, if needed
  ADMaterialProperty<Real> _user_mu;
  /// Custom charge sign of the species, if need
  MaterialProperty<Real> _user_sign;
  /// Diffusion coefficient
  const ADMaterialProperty<Real> & _diffusivity;
  /// Custom diffusion coefficient
  ADMaterialProperty<Real> _user_diff;

  const ADMaterialProperty<RealVectorValue> & _electric_field;
};
