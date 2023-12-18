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

class LinearCombinationAuxKernel : public AuxKernel
{
public:
  LinearCombinationAuxKernel(const InputParameters & parameters);

  static InputParameters validParams();

  virtual Real computeValue() override;

protected:
  const std::vector<Real> _weights;
  const unsigned int _num_vars;
  const Real _bias;
  std::vector<const MooseVariable *> _vars;
  std::vector<const VariableValue *> _var_vals;
};
