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

/**
 *  Kernel for adding charge density sources to Poisson’s equation
 */
class ChargeSourceMoles_KV : public ADKernel
{
public:
  static InputParameters validParams();

  ChargeSourceMoles_KV(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Coupled charge density variable
  const MooseVariable & _charged_var;
  /// Coupled charge density value
  const ADVariableValue & _charged;

  /// Charge sign of the species
  const MaterialProperty<Real> & _sgn;

  /// Scaling units for the potential (V or kV)
  const std::string & _potential_units;
  /// Scaling value for the potential
  Real _voltage_scaling;
};
