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

class ElectronEnergyLossFromElastic : public ADKernel
{
public:
  static InputParameters validParams();

  ElectronEnergyLossFromElastic(const InputParameters & parameters);

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
  /// Mass of electrons
  const MaterialProperty<Real> & _massem;
  /// Mass of neutral gas
  const MaterialProperty<Real> & _massGas;
  /// Townsend coefficient for elastic collisions
  const ADMaterialProperty<Real> & _alpha_el;
  const ADMaterialProperty<RealVectorValue> & _electric_field;

  /// Electron density
  const ADVariableValue & _em;
  /// Gradient of the electron density
  const ADVariableGradient & _grad_em;
};
