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

// MOOSE includes
#include "SideIntegralVariablePostprocessor.h"

/**
 * This postprocessor computes a side integral of the mass flux.
 */
class SideTotFluxIntegral : public SideIntegralVariablePostprocessor
{
public:
  SideTotFluxIntegral(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpIntegral();

  /// Name of the mobility coefficient for electrons
  std::string _mobility;
  /// Mobility coefficient for electrons
  const MaterialProperty<Real> & _mobility_coef;

  /// Scaling units for the position
  const Real _r_units;
  /// Reflection coefficient
  const Real _r;
  /// Boltzmann constant
  const MaterialProperty<Real> & _kb;
  /// Temperature of ions
  const MaterialProperty<Real> & _T_heavy;
  /// Mass of ions
  const MaterialProperty<Real> & _mass;
  /// Thermal velocity of ions
  Real _v_thermal;
  /// User defined thermal velocity of ions
  const Real _user_velocity;
  /// Elementary charge
  const MaterialProperty<Real> & _e;
  /// Charge sign of the ions
  const MaterialProperty<Real> & _sgn;
  /// Equal to 1 when the ion drift velocity is direct towards the wall and zero otherwise
  Real _a;

  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;
};
