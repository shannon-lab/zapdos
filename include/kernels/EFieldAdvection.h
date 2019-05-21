//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef EFIELDADVECTION_H
#define EFIELDADVECTION_H

#include "Kernel.h"

class EFieldAdvection;

template <>
InputParameters validParams<EFieldAdvection>();

class EFieldAdvection : public Kernel
{
public:
  EFieldAdvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  // Material properties

  Real _r_units;

  const MaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _sign;

private:
  // Coupled variables
  unsigned int _potential_id;
  const VariableGradient & _grad_potential;
};

#endif // EFIELDADVECTION_H
