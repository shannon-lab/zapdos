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

// Forward Declarations
class ADComsolEnergyBC;

declareADValidParams(ADComsolEnergyBC);

class ADComsolEnergyBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();
  ADComsolEnergyBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  Real _r_units;
  Real _r;

  const ADVariableGradient & _grad_potential;
  const ADVariableValue & _em;

  const MaterialProperty<Real> & _massem;
  const MaterialProperty<Real> & _e;

  ADReal _v_thermal;

};
