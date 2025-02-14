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

#include "AuxKernel.h"

/**
 *  Reaction rate for electron impact collisions in units of #/m^{3}s. User can pass
 *  choice of elastic, excitation, or ionization Townsend coefficients
 */
template <bool is_ad>
class ProcRateTempl : public AuxKernel
{
public:
  static InputParameters validParams();

  ProcRateTempl(const InputParameters & parameters);

  virtual Real computeValue() override;

protected:
  /// The scaling units for the position
  Real _r_units;
  /// Electron density
  const VariableValue & _em;
  /// Gradient of the electron density
  const VariableGradient & _grad_em;
  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;
  /// Electron mobility coefficient
  const GenericMaterialProperty<Real, is_ad> & _muem;
  /// Charge sign of electrons
  const MaterialProperty<Real> & _sgnem;
  /// Electron diffusion coefficient
  const GenericMaterialProperty<Real, is_ad> & _diffem;
  /// Townsend coefficient
  const GenericMaterialProperty<Real, is_ad> & _alpha;
  /// Term for the electron current
  RealVectorValue _em_current;
};

typedef ProcRateTempl<false> ProcRate;
typedef ProcRateTempl<true> ADProcRate;
