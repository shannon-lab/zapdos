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

#include "ADNodalBC.h"

/**
 *  Density Dirichlet boundary condition
 *  (Densities must be in log form and in moles/m^3)
 */
class LogDensityDirichletBC : public ADNodalBC
{
public:
  static InputParameters validParams();

  LogDensityDirichletBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Value of the density on the boundary (in units of #/m^3)
  const Real _value;
};
