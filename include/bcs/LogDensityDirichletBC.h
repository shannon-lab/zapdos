//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef LOGDENSITYDIRICHLETBC_H
#define LOGDENSITYDIRICHLETBC_H

#include "NodalBC.h"

// Forward Declarations
class LogDensityDirichletBC;

template <>
InputParameters validParams<LogDensityDirichletBC>();

/**
 * Implements a simple coupled boundary condition where u=v on the boundary.
 */
class LogDensityDirichletBC : public NodalBC
{
public:
  LogDensityDirichletBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  Real _value;
};

#endif // LogDensityDirichletBC_H
