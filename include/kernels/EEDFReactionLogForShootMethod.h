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

class EEDFReactionLogForShootMethod : public ADKernel
{
public:
  static InputParameters validParams();

  EEDFReactionLogForShootMethod(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const ADVariableValue & _electron;
  const ADVariableValue & _density;

  const ADMaterialProperty<Real> & _reaction_coeff;
  const Real & _stoichiometric_coeff;
};
