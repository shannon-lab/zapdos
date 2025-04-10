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
 *  Electron energy loss term for inelastic excitation collisions
 *  using Townsend coefficient, the energy lost in Volts in a single
 *  excitation collision (Densities must be in logarithmic form)
 */
class ElectronEnergyLossFromExcitation : public ADKernel
{
public:
  static InputParameters validParams();

  ElectronEnergyLossFromExcitation(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Position units
  const Real _r_units;

  /// Diffusion coefficient of electrons
  const ADMaterialProperty<Real> & _diffem;
  /// Mobility coefficient of electrons
  const ADMaterialProperty<Real> & _muem;
  /// Townsend coefficient for excitation
  const ADMaterialProperty<Real> & _alpha_ex;
  /// Energy threshold for excitation
  const MaterialProperty<Real> & _Eex;
  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;

  /// Electron density
  const ADVariableValue & _em;
  /// Gradient of the electron density
  const ADVariableGradient & _grad_em;
};
