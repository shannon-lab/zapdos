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
class EEDFReactionLogForShootMethod;

template <>
InputParameters validParams<EEDFReactionLogForShootMethod>();

class EEDFReactionLogForShootMethod : public Kernel
{
public:
  EEDFReactionLogForShootMethod(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const VariableValue & _electron;
  const VariableValue & _density;
  const VariableValue & _energy;
  unsigned int _electron_id;
  unsigned int _density_id;
  unsigned int _energy_id;

  const MaterialProperty<Real> & _reaction_coeff;
  const MaterialProperty<Real> & _d_k_d_en;
  Real _stoichiometric_coeff;
};
