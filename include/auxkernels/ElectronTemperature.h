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

class ElectronTemperature;

template <>
InputParameters validParams<ElectronTemperature>();

class ElectronTemperature : public AuxKernel
{
public:
  ElectronTemperature(const InputParameters & parameters);

  virtual ~ElectronTemperature() {}

protected:
  virtual Real computeValue();

  const VariableValue & _electron_density;
  const VariableValue & _mean_en;
};
