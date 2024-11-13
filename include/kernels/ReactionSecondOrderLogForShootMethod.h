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
 *  The derivative of a second order reaction term used to calculate
 *  the sensitivity variable for the shoothing method.
 */
class ReactionSecondOrderLogForShootMethod : public ADKernel
{
public:
  static InputParameters validParams();

  ReactionSecondOrderLogForShootMethod(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Reaction coefficient
  const ADMaterialProperty<Real> & _reaction_coeff;

  /// Accelerated density value
  const ADVariableValue & _density;
  /// Accelerated density variable 
  unsigned int _density_id;
  /// Coupled density value
  const ADVariableValue & _v;
  /// Coupled density variable 
  unsigned int _v_id;
  /// Stoichiometric coefficient
  const Real & _stoichiometric_coeff;
};
