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

// This diffusion kernel should only be used with species whose values are in the logarithmic form.

class DriftDiffusionEnergy : public ADKernel
{
public:
  static InputParameters validParams();

  DriftDiffusionEnergy(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const Real _r_units;

  const ADMaterialProperty<Real> & _muel;
  const MaterialProperty<Real> & _sign;
  const ADMaterialProperty<Real> & _diffel;

  // Coupled variables
  const ADVariableGradient & _grad_potential;
  const ADVariableValue & _em;
};
