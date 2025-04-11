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
 *  Rate of production of electrons from ionization using Townsend coefficients
 *  (Electron density must be in logarithmic form)
 */
class ElectronsFromIonization : public ADKernel
{
public:
  static InputParameters validParams();

  ElectronsFromIonization(const InputParameters & parameters);

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
  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;
  /// Custom diffusion coefficient
  ADMaterialProperty<Real> _user_diffem;
  /// Custom mobility coefficient
  ADMaterialProperty<Real> _user_muem;
  /// Custom Townsend coefficient for ionization
  ADMaterialProperty<Real> _user_alpha_iz;

  /// Electron mean energy density
  const ADVariableValue & _mean_en;
  /// Electron density
  const ADVariableValue & _em;
  /// Gradient of the electron density
  const ADVariableGradient & _grad_em;
};
