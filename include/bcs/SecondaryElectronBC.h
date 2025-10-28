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
 *  Kinetic secondary electron boundary condition
 */
class SecondaryElectronBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  SecondaryElectronBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Reflection coefficient for electrons
  const Real & _r;
  /// Reflection coefficient for ions
  const Real & _r_ion;
  /// Number of ions defined
  const unsigned int _num_ions;
  /// Material name of secondary electron coefficients
  const std::vector<std::string> _se_coeff_names;
  /// Material value of secondary electron coefficient
  std::vector<const ADMaterialProperty<Real> *> _se_coeff;
  /// Electron mean energy density
  const ADVariableValue & _mean_en;
  /// Ion density values
  std::vector<const ADVariableValue *> _ip;
  /// Gradient of ion density values
  std::vector<const ADVariableGradient *> _grad_ip;

  /// Mobility coefficient of the electrons
  const ADMaterialProperty<Real> & _muem;
  /// Mass of electrons
  const MaterialProperty<Real> & _massem;
  /// Charge sign of the ions
  std::vector<const MaterialProperty<Real> *> _sgnip;
  /// Mobility coefficient of the ions
  std::vector<const ADMaterialProperty<Real> *> _muip;
  /// Temperature of ions
  std::vector<const ADVariableValue *> _Tip;
  /// Mass of ions
  std::vector<const MaterialProperty<Real> *> _massip;

  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;

  /// Equal to 1 when the electron drift velocity is direct towards the wall and zero otherwise
  Real _a;
  /// Equal to 1 when the ion drift velocity is direct towards the wall and zero otherwise
  Real _b;
  /// Electron thermal velocity
  ADReal _v_thermal;
  /// Ion flux
  ADReal _ion_flux;
  /// Gamma electron density (electrons emitted by the surface)
  ADReal _n_gamma;
};
