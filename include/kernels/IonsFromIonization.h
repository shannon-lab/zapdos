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
 *  Rate of production of ions from ionization using Townsend coefficients
 *  (Ion density must be in logarithmic form)
 */
class IonsFromIonization : public ADKernel
{
public:
  static InputParameters validParams();

  IonsFromIonization(const InputParameters & parameters);

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
  const ADMaterialProperty<RealVectorValue> & _electric_field;

  /// Electron mean energy density
  const ADVariableValue & _mean_en;
  /// Electron density
  const ADVariableValue & _em;
  /// Gradient of the electron density
  const ADVariableGradient & _grad_em;
};
