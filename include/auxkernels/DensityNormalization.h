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
 *  Normalize variables expressed in logarithmic form (n) by a
 *  postprocessor value (pp_value) in the form of:
 *
 *  f * (exp(n) / pp_value) - shift
 *
 *  where f and shift are user defined normalization and
 *  shifting factors, respectively (the default values being
 *  f = 1. and shift = 0.)
 */
class DensityNormalization : public AuxKernel
{
public:
  DensityNormalization(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

  /// Coupled density value
  const VariableValue & _density;

  /// Denominator to normalize to
  const Real * _pp_on_source;

  /// A factor to shift the normilization by
  const Real * _shift;

  /// A factor to multiply the normilization by
  Real _normal_factor;
};
