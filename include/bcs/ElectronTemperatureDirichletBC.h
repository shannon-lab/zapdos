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
 *  Electron temperature boundary condition
 */
class ElectronTemperatureDirichletBC : public ADNodalBC
{
public:
  static InputParameters validParams();

  ElectronTemperatureDirichletBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Electron density
  const ADVariableValue & _em;
  /// Value of electron temperature
  const Real _value;
  /// Penalty value
  const Real _penalty_value;
};
