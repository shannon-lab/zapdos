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
 *  Reaction rate for two body collisions in units of #/m^{3}s. User can pass
 *  choice of elastic, excitation, or ionization reaction rate coefficients
 */
template <bool is_ad>
class ProcRateForRateCoeffTempl : public AuxKernel
{
public:
  ProcRateForRateCoeffTempl(const InputParameters & parameters);

  static InputParameters validParams();

  virtual Real computeValue() override;

protected:
  /// First body variable
  const VariableValue & _v;
  /// Second body variable
  const VariableValue & _w;
  /// Reaction rate coefficient
  const GenericMaterialProperty<Real, is_ad> & _reaction_coeff;
};

typedef ProcRateForRateCoeffTempl<false> ProcRateForRateCoeff;
typedef ProcRateForRateCoeffTempl<true> ADProcRateForRateCoeff;
