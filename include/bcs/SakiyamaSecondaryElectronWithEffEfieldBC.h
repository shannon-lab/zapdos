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
 *  with an effective electric field for ions
 */
class SakiyamaSecondaryElectronWithEffEfieldBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  SakiyamaSecondaryElectronWithEffEfieldBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  Real _r_units;
  /// x-component of the electric field
  const ADVariableValue & _Ex;
  /// y-component of the electric field
  const ADVariableValue & _Ey;
  /// z-component of the electric field
  const ADVariableValue & _Ez;
  /// Ion density values
  std::vector<const ADVariableValue *> _ip;
  /// Equal to 1 when the drift velocity is direct towards the wall and zero otherwise
  Real _a;
  /// Ion flux
  ADRealVectorValue _ion_flux;
  /// Secondary electron coefficient
  Real _user_se_coeff;
   /// Charge sign of the ions
  std::vector<const MaterialProperty<Real> *> _sgnip;
  /// Mobility coefficient of the ions
  std::vector<const ADMaterialProperty<Real> *> _muip;
  /// Number of ions defined
  unsigned int _num_ions;
};
