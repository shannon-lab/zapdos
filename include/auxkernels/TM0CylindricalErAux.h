//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef TM0CYLINDRICALERAUX_H
#define TM0CYLINDRICALERAUX_H

#include "AuxKernel.h"

class TM0CylindricalErAux;

template <>
InputParameters validParams<TM0CylindricalErAux>();

class TM0CylindricalErAux : public AuxKernel
{
public:
  TM0CylindricalErAux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _grad_Hphi;

  Real _omega;
  Real _eps_r;
  Real _eps0;
};

#endif // TM0CYLINDRICALERAUX_H
