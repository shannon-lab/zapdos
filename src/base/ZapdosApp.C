//* This file is part of Zapdos, an open-source
//* application for the simulation of plasmas
//* https://github.com/shannon-lab/zapdos
//*
//* Zapdos is powered by the MOOSE Framework
//* https://www.mooseframework.org
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ZapdosApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"
#include "SquirrelApp.h"
#include "CraneApp.h"

InputParameters
ZapdosApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  params.set<bool>("use_legacy_material_output") = false;
  return params;
}

// When using the new Registry system, this line is required so that
// dependent apps know about the ZapdosApp label.
registerKnownLabel("ZapdosApp");

ZapdosApp::ZapdosApp(InputParameters parameters) : MooseApp(parameters)
{
  ZapdosApp::registerAll(_factory, _action_factory, _syntax);
}

ZapdosApp::~ZapdosApp() {}

void
ZapdosApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAllObjects<ZapdosApp>(f, af, s);
  Registry::registerObjectsTo(f, {"ZapdosApp"});
  Registry::registerActionsTo(af, {"ZapdosApp"});

  /* register objects from dependent applications */
  SquirrelApp::registerAll(f, af, s);
  CraneApp::registerAll(f, af, s);

  /* register custom execute flags, action syntax, etc. here */
  s.registerActionSyntax("AddPeriodicControllers", "PeriodicControllers/*");
  s.registerActionSyntax("AddDriftDiffusionAction", "DriftDiffusionAction/*");
  s.registerActionSyntax("AddPeriodicRelativeNodalDifference", "PeriodicRelativeNodalDifference/*");
}

void
ZapdosApp::registerApps()
{
  registerApp(ZapdosApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
ZapdosApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ZapdosApp::registerAll(f, af, s);
}

extern "C" void
ZapdosApp__registerApps()
{
  ZapdosApp::registerApps();
}
