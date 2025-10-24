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

#include "ADMaterial.h"

/*
 *  Material properties representing electrostatic permittivity
 */
class ElectrostaticPermittivity : public ADMaterial
{
public:
  ElectrostaticPermittivity(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void computeQpProperties() override;

  /// Set to true when a plasma/material permittivity value is provided
  const bool _supplied_permittivity;

  /// Coupled plasma/material permittivity
  const ADMaterialProperty<Real> & _permittivity;

  /// Potential diffusion coefficient (material permittivity)
  ADMaterialProperty<Real> & _diffpotential;
};
