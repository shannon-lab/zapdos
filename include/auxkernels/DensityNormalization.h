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
 *  Normalize variables expressed in log form
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

  /// A factor to multiple the normilization by
  Real _normal_factor;
};
