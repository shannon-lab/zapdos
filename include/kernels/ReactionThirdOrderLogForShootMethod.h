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

#include "Kernel.h"

// Forward Declaration
class ReactionThirdOrderLogForShootMethod;

template <>
InputParameters validParams<ReactionThirdOrderLogForShootMethod>();

class ReactionThirdOrderLogForShootMethod : public Kernel
{
public:
  ReactionThirdOrderLogForShootMethod(const InputParameters & parameters);

protected:
  Real computeQpResidual() override;
  Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const MaterialProperty<Real> & _reaction_coeff;

  const VariableValue & _density;
  unsigned int _density_id;
  const VariableValue & _v;
  unsigned int _v_id;
  const VariableValue & _w;
  unsigned int _w_id;

  Real _stoichiometric_coeff;
};
