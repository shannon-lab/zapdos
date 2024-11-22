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
 *  with an effective electric field for ions
 */
class SakiyamaEnergySecondaryElectronWithEffEfieldBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  SakiyamaEnergySecondaryElectronWithEffEfieldBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  Real _r_units;
  /// If true, secondary electron energy is equal to electron energy
  bool Te_dependent;
  /// x-component of the electric field
  const ADVariableValue & _Ex;
  /// y-component of the electric field
  const ADVariableValue & _Ey;
  /// z-component of the electric field
  const ADVariableValue & _Ez;
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
  /// Secondary electron coefficient
  Real _se_coeff;
  /// Custom secondary electron energy
  Real _user_se_energy;
  /// Equal to 1 when the drift velocity is direct towards the wall and zero otherwise
  Real _a;
  /// Term for secondary electron energy
  ADReal _se_energy;
  /// Ion flux
  ADRealVectorValue _ion_flux;
  /// Number of ions defined
  unsigned int _num_ions;
};
