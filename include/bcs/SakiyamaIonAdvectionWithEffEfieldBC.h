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

class SakiyamaIonAdvectionWithEffEfieldBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  SakiyamaIonAdvectionWithEffEfieldBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  Real _r_units;

  // Coupled variables

  const ADVariableValue & _Ex;
  const ADVariableValue & _Ey;
  const ADVariableValue & _Ez;

  const ADMaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _sgn;

  Real _a;
};
