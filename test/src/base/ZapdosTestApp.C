//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ZapdosTestApp.h"
#include "ZapdosApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
ZapdosTestApp::validParams()
{
  InputParameters params = ZapdosApp::validParams();
  return params;
}

ZapdosTestApp::ZapdosTestApp(InputParameters parameters) : MooseApp(parameters)
{
  ZapdosTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

ZapdosTestApp::~ZapdosTestApp() {}

void
ZapdosTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  ZapdosApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"ZapdosTestApp"});
    Registry::registerActionsTo(af, {"ZapdosTestApp"});
  }
}

void
ZapdosTestApp::registerApps()
{
  ZapdosApp::registerApps();
  registerApp(ZapdosTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
ZapdosTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ZapdosTestApp::registerAll(f, af, s);
}
extern "C" void
ZapdosTestApp__registerApps()
{
  ZapdosTestApp::registerApps();
}
