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
class ProcRateForRateCoeffTempl : public AuxKernel
{
public:
  ProcRateForRateCoeffTempl(const InputParameters & parameters);

  static InputParameters validParams();

  virtual Real computeValue() override;

protected:
  const VariableValue & _v;
  const VariableValue & _w;
  const GenericMaterialProperty<Real, is_ad> & _reaction_coeff;
};

typedef ProcRateForRateCoeffTempl<false> ProcRateForRateCoeff;
typedef ProcRateForRateCoeffTempl<true> ADProcRateForRateCoeff;
