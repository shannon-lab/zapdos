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
 *  Kinetic electron boundary condition
 */
class HagelaarElectronBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  HagelaarElectronBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Reflection coefficient
  const Real & _r;

  /// Gradient of coupled potential
  const ADVariableGradient & _grad_potential;
  /// Electron mean energy density
  const ADVariableValue & _mean_en;

  /// Mobility coefficient of electrons
  const ADMaterialProperty<Real> & _muem;
  /// Mass of electrons
  const MaterialProperty<Real> & _massem;
  /// Elementary charge
  const MaterialProperty<Real> & _e;

  /// Equal to 1 when the drift velocity is direct towards the wall and zero otherwise
  Real _a;
  /// Electron thermal velocity
  ADReal _v_thermal;
};
