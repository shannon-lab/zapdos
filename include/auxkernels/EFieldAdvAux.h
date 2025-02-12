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
class EFieldAdvAuxTempl : public AuxKernel
{
public:
  EFieldAdvAuxTempl(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

  const int _component;
  const Real _r_units;

  // Coupled variables

  MooseVariable & _density_var;
  const VariableValue & _density_log;
  const ADMaterialProperty<RealVectorValue> & _electric_field;

  // Material properties

  const GenericMaterialProperty<Real, is_ad> & _mu;
  const MaterialProperty<Real> & _sgn;
};

typedef EFieldAdvAuxTempl<false> EFieldAdvAux;
typedef EFieldAdvAuxTempl<true> ADEFieldAdvAux;
