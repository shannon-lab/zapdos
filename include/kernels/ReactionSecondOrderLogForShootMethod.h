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

class ReactionSecondOrderLogForShootMethod : public ADKernel
{
public:
  static InputParameters validParams();

  ReactionSecondOrderLogForShootMethod(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const ADMaterialProperty<Real> & _reaction_coeff;

  const ADVariableValue & _density;
  unsigned int _density_id;
  const ADVariableValue & _v;
  unsigned int _v_id;

  const Real & _stoichiometric_coeff;
};
