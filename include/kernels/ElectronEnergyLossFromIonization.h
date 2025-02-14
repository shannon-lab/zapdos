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
 *  Electron energy loss term for inelastic ionization collisions
 *  using Townsend coefficients, the energy lost in Volts in a single
 *  ionization collision (Densities must be in logarithmic form)
 */
class ElectronEnergyLossFromIonization : public ADKernel
{
public:
  static InputParameters validParams();

  ElectronEnergyLossFromIonization(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Position units
  const Real _r_units;

  /// Diffusion coefficient of electrons
  const ADMaterialProperty<Real> & _diffem;
  /// Mobility coefficient of electrons
  const ADMaterialProperty<Real> & _muem;
  /// Townsend coefficient for ionization
  const ADMaterialProperty<Real> & _alpha_iz;
  /// Energy threshold for ionization
  const MaterialProperty<Real> & _Eiz;
  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;

  /// Electron density
  const ADVariableValue & _em;
  /// Gradient of the electron density
  const ADVariableGradient & _grad_em;
};
