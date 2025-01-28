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
 *  Kinetic advective ion boundary condition
 */
class HagelaarIonAdvectionBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  HagelaarIonAdvectionBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Reflection coefficient
  const Real & _r;

  /// Gradient of coupled potential
  const ADVariableGradient & _grad_potential;

  /// Mobility coefficient of ions
  const ADMaterialProperty<Real> & _mu;
  /// Elementary charge
  const MaterialProperty<Real> & _e;
  /// Charge sign of the ions
  const MaterialProperty<Real> & _sgn;
  /// Equal to 1 when the drift velocity is direct towards the wall and zero otherwise
  Real _a;
};
