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
 *  Boundary condition where the election advection flux at the boundary
 *  is equal to the bulk election advection equation
 */
class ElectronAdvectionDoNothingBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  ElectronAdvectionDoNothingBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _position_units;

  /// Mobility coefficient of electrons
  const ADMaterialProperty<Real> & _muem;
  /// Charge sign of electrons
  const MaterialProperty<Real> & _sign;

private:
  // Gradient of the coupled potential
  const ADVariableGradient & _grad_potential;
};
