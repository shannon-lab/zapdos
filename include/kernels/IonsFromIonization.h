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

class IonsFromIonization : public ADKernel
{
public:
  static InputParameters validParams();

  IonsFromIonization(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const Real _r_units;

  const ADMaterialProperty<Real> & _diffem;
  const ADMaterialProperty<Real> & _muem;
  const ADMaterialProperty<Real> & _alpha_iz;
  const ADMaterialProperty<RealVectorValue> & _electric_field;

  const ADVariableValue & _mean_en;
  const ADVariableValue & _em;
  const ADVariableGradient & _grad_em;
};
