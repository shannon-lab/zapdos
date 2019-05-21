//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef USERFLUX_H
#define USERFLUX_H

#include "AuxKernel.h"

class UserFlux;

template <>
InputParameters validParams<UserFlux>();

class UserFlux : public AuxKernel
{
public:
  UserFlux(const InputParameters & parameters);

  virtual ~UserFlux() {}
  virtual Real computeValue();

protected:
  const VariableValue & _u;
  const VariableGradient & _grad_u;
  Real _mu;
  Real _diff;
  Real _sign;
  Real _EField;
};

#endif // USERFLUX_H
