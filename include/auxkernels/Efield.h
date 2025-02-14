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

/**
 *  Returns the defined component of the electric field
 */
class Efield : public AuxKernel
{
public:
  Efield(const InputParameters & parameters);

  static InputParameters validParams();

  virtual ~Efield() {}

protected:
  virtual Real computeValue() override;

  /// Component of the electric field
  int _component;
  /// Scaling units for the position
  Real _r_units;
  /// Scaling units for the potential (V or kV)
  std::string _potential_units;
  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;
  /// Scaling value for the potential
  Real _voltage_scaling;
};
