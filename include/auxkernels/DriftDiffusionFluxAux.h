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

class DriftDiffusionFluxAux : public AuxKernel
{
public:
  DriftDiffusionFluxAux(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeValue() override;

private:
  const Real _sgn;
  const ADMaterialProperty<RealVectorValue> & _electric_field;
  const VariableValue & _u;
  const VariableGradient & _grad_u;
  const int _component;
};
