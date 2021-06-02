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
 *  Kinetic advective electron energy boundary condition
 */
class HagelaarEnergyAdvectionBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  HagelaarEnergyAdvectionBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Reflection coefficient
  const Real _r;
  /// Number of ions defined
  const unsigned int _num_ions;
  /// Ion density variables
  std::vector<MooseVariable *> _ip_var;
  /// Ion density values
  std::vector<const ADVariableValue *> _ip;
  /// Gradient of ion density values
  std::vector<const ADVariableGradient *> _grad_ip;

  /// Charge sign of the ions
  std::vector<const MaterialProperty<Real> *> _sgnip;
  /// Mobility coefficient of the ions
  std::vector<const ADMaterialProperty<Real> *> _muip;
  /// Diffusion coefficient of the ions
  std::vector<const ADMaterialProperty<Real> *> _Dip;
  /// Material name of secondary electron coefficients
  const std::vector<std::string> _se_coeff_names;
  /// Material value of secondary electron coefficient
  std::vector<const ADMaterialProperty<Real> *> _se_coeff;
  /// Energy of the secondary electrons
  const Real _se_energy;
  /// Mobility coefficient of the electron mean energy density
  const ADMaterialProperty<Real> & _mumean_en;

  const ADMaterialProperty<RealVectorValue> & _electric_field;

  const ADMaterialProperty<RealVectorValue> & _electric_field;

  /// Equal to 1 when the drift velocity is direct towards the wall and zero otherwise
  Real _a;
  /// Ion flux
  ADRealVectorValue _ion_flux;
  /// Electron thermal velocity
  Real _v_thermal;
  /// Gamma electron density (electrons emitted by the surface)
  Real _n_gamma; /// TODO: currently '_n_gamma' is fixed at 0
  /// Total flux from secondary electrons
  ADReal _bc_val;
};
