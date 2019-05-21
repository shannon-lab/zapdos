//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef USERSOURCE_H
#define USERSOURCE_H

#include "Kernel.h"

class UserSource;

template <>
InputParameters validParams<UserSource>();

class UserSource : public Kernel
{
public:
  UserSource(const InputParameters & parameters);
  virtual ~UserSource();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Real _source;
};

#endif /* USERSOURCE_H */
