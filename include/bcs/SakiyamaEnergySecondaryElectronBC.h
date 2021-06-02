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
 *  Kinetic secondary electron for mean electron energy boundary condition
 */
class SakiyamaEnergySecondaryElectronBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  SakiyamaEnergySecondaryElectronBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// If true, secondary electron energy is equal to electron energy
  const bool Te_dependent;
  /// Number of ions defined
  const unsigned int _num_ions;
  /// Material name of secondary electron coefficients
  const std::vector<std::string> _se_coeff_names;
  /// Material value of secondary electron coefficient
  std::vector<const ADMaterialProperty<Real> *> _se_coeff;

  /// Electron density
  const ADVariableValue & _em;
  /// Ion density variables
  std::vector<MooseVariable *> _ip_var;
  /// Ion density values
  std::vector<const ADVariableValue *> _ip;

  /// Charge sign of the ions
  std::vector<const MaterialProperty<Real> *> _sgnip;
  /// Mobility coefficient of the ions
  std::vector<const ADMaterialProperty<Real> *> _muip;
  /// Custom secondary electron energy
  const Real _user_se_energy;
  /// Equal to 1 when the drift velocity is direct towards the wall and zero otherwise
  Real _a;
  /// Term for secondary electron energy
  ADReal _se_energy;
  /// Ion flux
  ADRealVectorValue _ion_flux;

  const ADMaterialProperty<RealVectorValue> & _electric_field;
};
