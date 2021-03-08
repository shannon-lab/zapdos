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

#include "AddVariableAction.h"
#include "Action.h"

class AddHeavySpeciesTransportAction;

template <>
InputParameters validParams<AddHeavySpeciesTransportAction>();

class AddHeavySpeciesTransportAction : public Action
{
public:
  AddHeavySpeciesTransportAction(InputParameters params);

  virtual void act(); //does this need override?

protected:
  virtual void addADHeavySpeciesMaterial(const std::string & name,
                                         const Real & mass,
                                         const Real & charge);
  virtual void addADHeavySpeciesChargedKernels(const std::string & name,
                                               const std::string & potential_name);
  virtual void addADHeavySpeciesNeutralKernels(const std::string & name);


};
