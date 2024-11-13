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
 *  Electron energy loss term for inelastic collisions 
 *  using reaction rate coefficients. Threshold energy is the energy lost in Volts in a single 
 *  collision (Densities must be in logarithmic form)
 */
class ElectronEnergyTermRate : public ADKernel
{
public:
  static InputParameters validParams();

  ElectronEnergyTermRate(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Position units
  const Real _r_units;
  /// True for elastic collisions
  const bool & _elastic;
  /// Threshold energy of reaction, if needed
  const Real & _threshold_energy;
  /// Energy exchange during collision
  Real _energy_change;
  /// Density of background gas
  const ADMaterialProperty<Real> & _n_gas;
  /// Reaction coefficient
  const ADMaterialProperty<Real> & _rate_coefficient;
  /// Electron density
  const ADVariableValue & _em;
  /// Density of colliding gas
  const ADVariableValue & _v;
  /// Gradient of electron density
  const ADVariableGradient & _grad_em;
};
