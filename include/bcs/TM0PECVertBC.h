//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef TM0PECVERTBC_H
#define TM0PECVERTBC_H

#include "IntegratedBC.h"

class TM0PECVertBC;

template <>
InputParameters validParams<TM0PECVertBC>();

class TM0PECVertBC : public IntegratedBC
{
public:
  TM0PECVertBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
};

#endif // TM0PECVERTBC_H
