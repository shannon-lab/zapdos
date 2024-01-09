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
class DiffusiveFluxTempl : public AuxKernel
{
public:
  DiffusiveFluxTempl(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

  const int _component;
  const Real _r_units;

  // Coupled variables

  const VariableGradient & _grad_density_log;
  MooseVariable & _density_var;
  const VariableValue & _density_log;

  // Material properties

  const GenericMaterialProperty<Real, is_ad> & _diff;
};

typedef DiffusiveFluxTempl<false> DiffusiveFlux;
typedef DiffusiveFluxTempl<true> ADDiffusiveFlux;
