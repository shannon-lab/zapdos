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
 *  Amount of power deposited into a user specified specie by Joule Heating
 */
template <bool is_ad>
class PowerDepTempl : public AuxKernel
{
public:
  PowerDepTempl(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~PowerDepTempl() {}
  virtual Real computeValue() override;

protected:
  /// Scaling units for the position
  const Real _r_units;

  /// Coupled density variable
  const MooseVariable & _density_var;
  /// Value of the coupled density variable
  const VariableValue & _density_log;
  /// Gradient of the coupled density variable
  const VariableGradient & _grad_density_log;
  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;
  /// Mobility coefficient
  const GenericMaterialProperty<Real, is_ad> & _mu;
  /// Charge sign of the coupled species
  const MaterialProperty<Real> & _sgn;
  /// Diffusion coefficient
  const GenericMaterialProperty<Real, is_ad> & _diff;
  /// True if an artifical diffusion term is needed
  const bool _art_diff;
  /// Scaling units for the potential (V or kV)
  const std::string _potential_units;
  /// Term for the current
  RealVectorValue _current;
  /// Scaling value for the potential
  Real _voltage_scaling;
};

typedef PowerDepTempl<false> PowerDep;
typedef PowerDepTempl<true> ADPowerDep;
