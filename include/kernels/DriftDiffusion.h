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

class DriftDiffusion : public ADKernel
{
public:
  static InputParameters validParams();

  DriftDiffusion(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const Real _r_units;

  const ADMaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _sign;
  ADMaterialProperty<Real> _user_mu;
  MaterialProperty<Real> _user_sign;

  const ADMaterialProperty<Real> & _diffusivity;
  ADMaterialProperty<Real> _user_diff;

  const ADMaterialProperty<RealVectorValue> & _electric_field;
};
