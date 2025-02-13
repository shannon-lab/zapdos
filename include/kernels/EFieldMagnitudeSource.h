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
 *  Electric field magnitude source term
 */
class EFieldMagnitudeSource : public ADKernel
{
public:
  static InputParameters validParams();

  EFieldMagnitudeSource(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Gradient of coupled potential
  const ADVariableGradient & _grad_potential;
};
