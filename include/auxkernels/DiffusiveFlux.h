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
 *  Returns the diffusive flux of the specified species
 */
template <bool is_ad>
class DiffusiveFluxTempl : public AuxKernel
{
public:
  DiffusiveFluxTempl(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

  /// component of the flux
  const int _component;

  /// The scaling units for the position
  const Real _r_units;

  /// Gradient of the coupled density variable
  const VariableGradient & _grad_density_log;

  /// Coupled density variable
  MooseVariable & _density_var;

  /// Value of the coupled density variable
  const VariableValue & _density_log;

  /// Diffusion coefficient
  const GenericMaterialProperty<Real, is_ad> & _diff;
};

typedef DiffusiveFluxTempl<false> DiffusiveFlux;
typedef DiffusiveFluxTempl<true> ADDiffusiveFlux;
