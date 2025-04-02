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

/**
 *  Simpified kinetic ion boundary condition
 */
class LymberopoulosIonBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  LymberopoulosIonBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;

  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;

  /// Mobility coefficient
  const ADMaterialProperty<Real> & _mu;
};
