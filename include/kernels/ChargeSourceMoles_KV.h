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

#include "ADKernel.h"

class ChargeSourceMoles_KV : public ADKernel
{
public:
  static InputParameters validParams();

  ChargeSourceMoles_KV(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Coupled variable
  MooseVariable & _charged_var;
  const ADVariableValue & _charged;

  /// Material properties (regular because these are constants)
  const MaterialProperty<Real> & _e;
  const MaterialProperty<Real> & _sgn;
  const MaterialProperty<Real> & _N_A;

  /// Units scaling
  const std::string & _potential_units;
  Real _voltage_scaling;
};
