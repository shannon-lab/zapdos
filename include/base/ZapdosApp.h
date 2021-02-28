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

#include "MooseApp.h"

class ZapdosApp : public MooseApp
{
public:
  ZapdosApp(InputParameters parameters);

  static InputParameters validParams();

  virtual ~ZapdosApp();

  static void registerApps();
  static void registerAll(Factory & f, ActionFactory & af, Syntax & s);
};
