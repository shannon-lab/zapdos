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

#include "AuxKernel.h"

class TM0CylindricalEzAux;

template <>
InputParameters validParams<TM0CylindricalEzAux>();

class TM0CylindricalEzAux : public AuxKernel
{
public:
  TM0CylindricalEzAux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _grad_Hphi;
  const VariableValue & _Hphi;

  Real _omega;
  Real _eps_r;
  Real _eps0;
};
