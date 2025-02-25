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
 *  Linearly combine coupled variables with user provided weights and a bias
 */
class LinearCombinationAuxKernel : public AuxKernel
{
public:
  LinearCombinationAuxKernel(const InputParameters & parameters);

  static InputParameters validParams();

  virtual Real computeValue() override;

protected:
  /// Weighting term for each coupled variable
  const std::vector<Real> _weights;
  /// Number of coupled variables
  const unsigned int _num_vars;
  /// A bias term to shift the wieghted sum
  const Real _bias;
  /// Value of coupled variables
  std::vector<const VariableValue *> _var_vals;
};
