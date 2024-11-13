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
 *  Boundary condition where the election diffusion flux at the boundary
 *  is equal to the bulk election diffusion equation
 */
class ElectronDiffusionDoNothingBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  ElectronDiffusionDoNothingBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Scaling units for the position
  const Real _r_units;
  /// Diffusion coefficient electrons
  const ADMaterialProperty<Real> & _diffem;
};
