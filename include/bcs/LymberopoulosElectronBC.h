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
 *  Simpified kinetic electron boundary condition
 */
class LymberopoulosElectronBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  LymberopoulosElectronBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Recombination coefficient (in units of m/s)
  const Real _ks;
  /// secondary electron coefficients
  const std::vector<Real> _gamma;
  /// Number of ions defined
  const unsigned int _num_ions;

  /// Ion density variables
  std::vector<MooseVariable *> _ion_var;
  /// Ion density values
  std::vector<const ADVariableValue *> _ion;

  const ADMaterialProperty<RealVectorValue> & _electric_field;

  const ADMaterialProperty<RealVectorValue> & _electric_field;

  /// Charge sign of the ions
  std::vector<const MaterialProperty<Real> *> _sgnion;
  /// Mobility coefficient of the ions
  std::vector<const ADMaterialProperty<Real> *> _muion;
  /// Ion flux
  ADRealVectorValue _ion_flux;
};
