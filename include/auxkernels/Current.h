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
 *  Returns the electric current associated with the flux of the specified species
 */
template <bool is_ad>
class CurrentTempl : public AuxKernel
{
public:
  CurrentTempl(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~CurrentTempl() {}
  virtual Real computeValue() override;

protected:
  /// The component of the current
  const int _component;
  /// The scaling units for the position
  const Real _r_units;
  /// The coupled density variable
  const MooseVariable & _density_var;
  /// The value of the coupled density variable
  const VariableValue & _density_log;
  /// The gradient of the coupled density variable
  const VariableGradient & _grad_density_log;
  /// The gradient of the coupled potential
  const VariableGradient & _grad_potential;
  /// The mobility coefficient
  const GenericMaterialProperty<Real, is_ad> & _mu;
  /// The charge sign of the coupled species
  const MaterialProperty<Real> & _sgn;
  /// The diffusion coefficient
  const GenericMaterialProperty<Real, is_ad> & _diff;
  /// True if an artifical diffusion term is needed
  bool _art_diff;
};

typedef CurrentTempl<false> Current;
typedef CurrentTempl<true> ADCurrent;
