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
 *  Returns the electron temperature
 */
class ElectronTemperature : public AuxKernel
{
public:
  ElectronTemperature(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~ElectronTemperature() {}

protected:
  virtual Real computeValue() override;

  /// Coupled electron density
  const VariableValue & _electron_density;
  /// Coupled electron mean energy density
  const VariableValue & _mean_en;
};
