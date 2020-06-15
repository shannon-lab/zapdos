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

class ElectronEnergyTermRate : public ADKernel
{
public:
  static InputParameters validParams();

  ElectronEnergyTermRate(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const Real _r_units;
  const bool & _elastic;
  const Real & _threshold_energy;
  Real _energy_change;

  const ADMaterialProperty<Real> & _n_gas;
  const ADMaterialProperty<Real> & _rate_coefficient;

  const ADVariableValue & _em;
  const ADVariableValue & _v;
  const ADVariableGradient & _grad_em;
};
