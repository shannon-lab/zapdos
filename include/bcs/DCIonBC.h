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

class DCIonBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  DCIonBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const Real _r_units;

  const ADMaterialProperty<RealVectorValue> & _electric_field;

  /// Material properties
  const ADMaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _sgn;

  Real _a;
};
