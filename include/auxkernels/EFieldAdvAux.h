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
 *  Returns the electric field driven advective flux of the specified species
 */
template <bool is_ad>
class EFieldAdvAuxTempl : public AuxKernel
{
public:
  EFieldAdvAuxTempl(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

  /// Component of the flux
  const int _component;
  /// Scaling units for the position
  const Real _r_units;
  /// Coupled density variable
  const MooseVariable & _density_var;
  /// Value of the coupled density variable
  const VariableValue & _density_log;
  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;
  /// Mobility coefficient
  const GenericMaterialProperty<Real, is_ad> & _mu;
  /// Charge sign of the coupled species
  const MaterialProperty<Real> & _sgn;
};

typedef EFieldAdvAuxTempl<false> EFieldAdvAux;
typedef EFieldAdvAuxTempl<true> ADEFieldAdvAux;
