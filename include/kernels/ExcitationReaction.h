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
 *  Rate of production of metastables from excitation using Townsend coefficients
 *  (Densities must be in logarithmic form)
 */
class ExcitationReaction : public ADKernel
{
public:
  static InputParameters validParams();

  ExcitationReaction(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Position units
  const Real _r_units;

  /// Background gas density
  const MaterialProperty<Real> & _n_gas;
  /// Diffusion coefficient of electrons
  const ADMaterialProperty<Real> & _diffem;
  /// Mobility coefficient of electrons
  const ADMaterialProperty<Real> & _muem;
  /// Townsend coefficient for excitation
  const ADMaterialProperty<Real> & _alpha_source;

  /// Electron mean energy density
  const ADVariableValue & _mean_en;
  /// Gradient of the coupled potential
  const ADVariableGradient & _grad_potential;
  /// Electron density
  const ADVariableValue & _em;
  /// Gradient of the electron density
  const ADVariableGradient & _grad_em;
  /// True if the variable is the reactant
  const bool & _reactant;
};
