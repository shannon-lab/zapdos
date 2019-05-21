//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef ABSVALUEAUX_H
#define ABSVALUEAUX_H

#include "AuxKernel.h"

class AbsValueAux;

template <>
InputParameters validParams<AbsValueAux>();

class AbsValueAux : public AuxKernel
{
public:
  AbsValueAux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

private:
  const VariableValue & _u;
};

#endif // ABSVALUEAUX_H
