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
 *  Joule heating term for electrons (densities must be in logarithmic form)
 */
class JouleHeating : public ADKernel
{
public:
  static InputParameters validParams();

  JouleHeating(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

private:
  /// Position units
  const Real _r_units;
  /// Scaling units for the potential (V or kV)
  const std::string & _potential_units;

  /// Diffusion coefficient
  const ADMaterialProperty<Real> & _diff;
  /// Mobility coefficient
  const ADMaterialProperty<Real> & _mu;
  /// The electric field provided as a material property
  const ADMaterialProperty<RealVectorValue> & _electric_field;
  /// Electron density
  const ADVariableValue & _em;
  /// Gradient of electron density
  const ADVariableGradient & _grad_em;

  /// Scaling value for the potential
  Real _voltage_scaling;
};
