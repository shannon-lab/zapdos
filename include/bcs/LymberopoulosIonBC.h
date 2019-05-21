//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef LYMBEROPOULOSIONBC_H
#define LYMBEROPOULOSIONBC_H

#include "IntegratedBC.h"

class LymberopoulosIonBC;

template <>
InputParameters validParams<LymberopoulosIonBC>();

class LymberopoulosIonBC : public IntegratedBC
{
public:
  LymberopoulosIonBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  Real _r_units;

  // Coupled variables

  const VariableGradient & _grad_potential;
  unsigned int _potential_id;

  const MaterialProperty<Real> & _mu;
};

#endif // LymberopoulosIonBC_H
