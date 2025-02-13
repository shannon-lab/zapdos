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
 *  Electron energy loss term for elastic collisions using reaction rate coefficients
 *  (Densities must be in logarithmic form)
 */
class ElectronEnergyTermElasticRate : public ADKernel
{
public:
  static InputParameters validParams();

  ElectronEnergyTermElasticRate(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Position units
  const Real _r_units;
  /// Reaction coefficient
  const ADMaterialProperty<Real> & _rate_coefficient;
  /// Electron density
  const ADVariableValue & _electron;
  /// Density of colliding species
  const ADVariableValue & _target;
  /// Mass of electrons
  const ADMaterialProperty<Real> & _massIncident;
  /// Mass of colliding species
  const ADMaterialProperty<Real> & _massTarget;
};
