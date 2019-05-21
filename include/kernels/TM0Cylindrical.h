//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef TM0CYLINDRICAL_H
#define TM0CYLINDRICAL_H

#include "Kernel.h"

class TM0Cylindrical;

template <>
InputParameters validParams<TM0Cylindrical>();

class TM0Cylindrical : public Kernel
{
public:
  TM0Cylindrical(const InputParameters & parameters);
  virtual ~TM0Cylindrical();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  /* Real _r_units; */
  Real _omega;
  const MaterialProperty<Real> & _eps_r;
  Real _mu0;
  Real _eps0;
};

#endif /* TM0CYLINDRICAL_H */
