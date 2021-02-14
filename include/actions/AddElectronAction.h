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

class AddElectronAction;

template <>
InputParameters validParams<AddElectronAction>();

class AddElectronAction : public Action
{
public:
  AddElectronAction(InputParameters params);

  virtual void act(); //does this need override?
protected:
  virtual void addElectronKernels(const std::string & em_name,
                                  const std::string & potential_name,
                                  const std::string & mean_en_name,
                                  const bool & Using_offset);

};
