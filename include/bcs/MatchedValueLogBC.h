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
 *  Henry’s Law like thermodynamic boundary condition for specifying a specie
 *  concentration ratio at the gas-liquid interface
 */
class MatchedValueLogBC : public ADNodalBC
{
public:
  static InputParameters validParams();

  MatchedValueLogBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Couple variable to match at the boundary
  const ADVariableValue & _v;
  /// Ratio of liquid phase density to gas phase density
  const Real _H;
};
