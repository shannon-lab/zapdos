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

#include "ADIntegratedBC.h"

/**
 *  Boundary condition where the flux at the boundary is equal to the
 *  bulk dift-diffusion equation
 */
class DriftDiffusionDoNothingBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  DriftDiffusionDoNothingBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Mobility coefficient
  const ADMaterialProperty<Real> & _mu;
  /// Charge sign of the species
  const MaterialProperty<Real> & _sign;
  /// User input for the a custom mobility coefficient
  ADMaterialProperty<Real> _user_mu;
  /// User input for the a custom charge sign of the species
  MaterialProperty<Real> _user_sign;
  /// Diffusion coefficient
  const ADMaterialProperty<Real> & _diffusivity;
  /// User input for the a custom diffusion coefficient
  ADMaterialProperty<Real> _user_diff;

  const ADMaterialProperty<RealVectorValue> & _electric_field;
};
