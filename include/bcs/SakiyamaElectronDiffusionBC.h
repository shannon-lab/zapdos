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
class SakiyamaElectronDiffusionBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  SakiyamaElectronDiffusionBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Electron mean energy density
  const ADVariableValue & _mean_en;
  /// Mass of electrons
  const MaterialProperty<Real> & _massem;
  /// Elementary charge
  const MaterialProperty<Real> & _e;
  /// Electron thermal velocity
  ADReal _v_thermal;
};
