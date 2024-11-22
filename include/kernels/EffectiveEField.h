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

/**
 *  Supplies the source term of the time derivative calculation of the effective electric field for ions
 */
class EffectiveEField : public ADKernel
{
public:
  static InputParameters validParams();

  EffectiveEField(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual();

private:
  /// Position units
  const Real _r_units;
  /// Momentum-transfer frequency of ions
  const Real _nu;
  /// Component of the electric field
  unsigned _component;
  /// Electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;
};
