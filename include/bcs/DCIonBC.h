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
 *  Electric field driven outflow boundary condition
 */
class DCIonBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  DCIonBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Gradient of the coupled potential
  const ADVariableGradient & _grad_potential;
  /// Mobility coefficient
  const ADMaterialProperty<Real> & _mu;
  /// Charge sign of the species
  const MaterialProperty<Real> & _sgn;
  /// Equal to 1 when the drift velocity is direct towards the wall and zero otherwise
  Real _a;
};
