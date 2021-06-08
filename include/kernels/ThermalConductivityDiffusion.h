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

class ThermalConductivityDiffusion : public ADKernel
{
public:
  static InputParameters validParams();

  ThermalConductivityDiffusion(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

private:
  Real _r_units;
  Real _coeff;

  const ADMaterialProperty<Real> & _diffem;

  const ADVariableValue & _em;
  const ADVariableGradient & _grad_em;
};
