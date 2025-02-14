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
 *  The derivative of an EEDF reaction term used to calculate the
 *  sensitivity variable for the shoothing method
 */
class EEDFReactionLogForShootMethod : public ADKernel
{
public:
  static InputParameters validParams();

  EEDFReactionLogForShootMethod(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Electron density
  const ADVariableValue & _electron;
  /// Density to be accelerated
  const ADVariableValue & _density;

  /// Reaction coefficient
  const ADMaterialProperty<Real> & _reaction_coeff;
  /// Stoichiometric coefficient
  const Real & _stoichiometric_coeff;
};
