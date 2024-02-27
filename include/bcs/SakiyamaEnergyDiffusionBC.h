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

#include "ADIntegratedBC.h"

class SakiyamaEnergyDiffusionBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  SakiyamaEnergyDiffusionBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const Real _r_units;

  // Coupled variables
  const ADVariableValue & _em;

  const MaterialProperty<Real> & _massem;
  const MaterialProperty<Real> & _e;

  ADReal _v_thermal;
};
