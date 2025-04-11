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
 *  Kinetic electron mean energy boundary condition
 */
class HagelaarEnergyBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  HagelaarEnergyBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Reflection coefficient
  const Real & _r;

  /// Electron density
  const ADVariableValue & _em;
  /// Mass of electrons
  const MaterialProperty<Real> & _massem;
  /// Elementary charge
  const MaterialProperty<Real> & _e;
  /// Mobility coefficient of electron mean energy density
  const ADMaterialProperty<Real> & _mumean_en;

  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;

  /// Equal to 1 when the drift velocity is direct towards the wall and zero otherwise
  Real _a;
  /// Electron thermal velocity
  ADReal _v_thermal;
};
