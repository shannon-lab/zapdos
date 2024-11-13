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
 *  Ion thermal diffusion boundary condition
 */
class HagelaarIonDiffusionBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  HagelaarIonDiffusionBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Reflection coefficient
  const Real & _r;
  /// Boltzmann constant
  const MaterialProperty<Real> & _kb;
  /// Ion temperature
  const ADMaterialProperty<Real> & _T;
  /// Mass of ions
  const MaterialProperty<Real> & _mass;
  /// Ion thermal velocity
  ADReal _v_thermal;
  /// Custom ion thermal velocity, if needed
  const Real & _user_velocity;
};
