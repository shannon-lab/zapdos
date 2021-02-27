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

#include "ADKernelGrad.h"

class EFieldAdvectionEnergy : public ADKernelGrad
{
public:
  static InputParameters validParams();

  EFieldAdvectionEnergy(const InputParameters & parameters);

protected:
  ADRealVectorValue precomputeQpResidual() override;

  const Real _r_units;

  /// Material properties
  const ADMaterialProperty<Real> & _muel;
  const MaterialProperty<Real> & _sign;

  /// Coupled variables
  const ADVariableGradient & _grad_potential;
};
