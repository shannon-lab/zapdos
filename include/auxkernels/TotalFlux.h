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

template <bool is_ad>
class TotalFluxTempl : public AuxKernel
{
public:
  TotalFluxTempl(const InputParameters & parameters);

  static InputParameters validParams();

  virtual Real computeValue() override;

protected:
  /// Component of the flux
  const int _component;
  /// Coupled density variable
  const MooseVariable & _density_var;
   /// Value of the coupled density variable
  const VariableValue & _density_log;
  /// Gradient of the coupled density variable
  const VariableGradient & _grad_density_log;
  /// Gradient of coupled potential
  const VariableGradient & _grad_potential;
  /// Mobility coefficient
  const GenericMaterialProperty<Real, is_ad> & _mu;
  /// Charge sign of the coupled species
  const MaterialProperty<Real> & _sgn;
  /// Diffusion coefficient
  const GenericMaterialProperty<Real, is_ad> & _diff;
};

typedef TotalFluxTempl<false> TotalFlux;
typedef TotalFluxTempl<true> ADTotalFlux;
