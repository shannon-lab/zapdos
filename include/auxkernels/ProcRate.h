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
class ProcRateTempl : public AuxKernel
{
public:
  static InputParameters validParams();

  ProcRateTempl(const InputParameters & parameters);

  virtual Real computeValue() override;

protected:
  Real _r_units;

  const VariableValue & _em;
  const VariableGradient & _grad_em;
  const ADMaterialProperty<RealVectorValue> & _electric_field;
  const GenericMaterialProperty<Real, is_ad> & _muem;
  const MaterialProperty<Real> & _sgnem;
  const GenericMaterialProperty<Real, is_ad> & _diffem;
  const GenericMaterialProperty<Real, is_ad> & _alpha;

  RealVectorValue _em_current;
};

typedef ProcRateTempl<false> ProcRate;
typedef ProcRateTempl<true> ADProcRate;
