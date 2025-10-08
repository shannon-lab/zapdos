
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
 * This postprocessor computes a side integral of current density.
 */
class SideCurrent : public SideIntegralVariablePostprocessor
{
public:
  SideCurrent(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpIntegral();

  /// Name of the mobility coefficient for electrons
  const std::string _mobility;
  /// Mobility coefficient for electrons
  const MaterialProperty<Real> & _mobility_coef;

  /// Scaling units for the position
  const Real _r_units;
  /// Reflection coefficient
  const Real _r;
  /// Thermal velocity of the electrons
  Real _ve_thermal;
  /*
   *  Charge sign of the ions
   *  TODO: This variable calls the material property labeled
   *        "sgnArp". This term is outdated as Zapdos no longer
   *        assumes only argon plasmas
   */
  const MaterialProperty<Real> & _sgn;
  /// Equal to 1 when the electron drift velocity is direct towards the wall and zero otherwise
  Real _a;
  /// Equal to 1 when the ion drift velocity is direct towards the wall and zero otherwise
  Real _b;

  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;

  /// Electron energy density
  const VariableValue & _mean_en;

  /// Number of ions defined
  unsigned int _num_ions;
  /// Ion density values
  std::vector<const VariableValue *> _ions;
  /// Gradient of ion density values
  std::vector<const VariableGradient *> _grad_ions;
  /// Mobility coefficient of the ions
  std::vector<const MaterialProperty<Real> *> _mu_ions;
  /// Charge sign of the ions
  std::vector<const MaterialProperty<Real> *> _sgn_ions;
  /// Mass of ions
  std::vector<const MaterialProperty<Real> *> _mass_ions;
  /// Temperature of ions
  std::vector<const VariableValue *> _T_ions;

  /// Ion flux
  Real _ion_flux;
};
