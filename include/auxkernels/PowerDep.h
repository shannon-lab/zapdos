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
class PowerDepTempl : public AuxKernel
{
public:
  PowerDepTempl(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~PowerDepTempl() {}
  virtual Real computeValue() override;

protected:
  Real _r_units;

  MooseVariable & _density_var;
  const VariableValue & _density_log;
  const VariableGradient & _grad_density_log;
  const ADMaterialProperty<RealVectorValue> & _electric_field;
  const GenericMaterialProperty<Real, is_ad> & _mu;
  const MaterialProperty<Real> & _sgn;
  const GenericMaterialProperty<Real, is_ad> & _diff;
  bool _art_diff;
  std::string _potential_units;
  RealVectorValue _current;
  Real _voltage_scaling;
};

typedef PowerDepTempl<false> PowerDep;
typedef PowerDepTempl<true> ADPowerDep;
