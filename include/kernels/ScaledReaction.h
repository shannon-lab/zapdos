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
 *  The multiple of a given variable
 *  (Used for calculating the effective ion potential for a given collision frequency)
 */
class ScaledReaction : public ADKernel
{
public:
  static InputParameters validParams();

  ScaledReaction(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Momentum-transfer frequency of ions
  const Real & _nu;
};
