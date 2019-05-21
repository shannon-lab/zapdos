//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef ADDLOTSOFPOTENTIALDRIVENARTIFICIALDIFF_H
#define ADDLOTSOFPOTENTIALDRIVENARTIFICIALDIFF_H

#include "AddVariableAction.h"
#include "Action.h"

class AddLotsOfPotentialDrivenArtificialDiff;

template <>
InputParameters validParams<AddLotsOfPotentialDrivenArtificialDiff>();

class AddLotsOfPotentialDrivenArtificialDiff : public AddVariableAction
{
public:
  AddLotsOfPotentialDrivenArtificialDiff(InputParameters params);

  virtual void act();
};

#endif // ADDLOTSOFPOTENTIALDRIVENARTIFICIALDIFF_H
