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

template <>
InputParameters
validParams<ZapdosApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_output_syntax") = false;
  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_dirichlet_bc") = false;
  return params;
}

// When using the new Registry system, this line is required so that
// dependent apps know about the ZapdosApp label.
registerKnownLabel("ZapdosApp");

ZapdosApp::ZapdosApp(InputParameters parameters) : MooseApp(parameters)
{
  ZapdosApp::registerAll(_factory, _action_factory, _syntax);
  SquirrelApp::registerAll(_factory, _action_factory, _syntax);
  CraneApp::registerAll(_factory, _action_factory, _syntax);
}

ZapdosApp::~ZapdosApp() {}

void
ZapdosApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAll(f, af, s);
  Registry::registerObjectsTo(f, {"ZapdosApp"});
  Registry::registerActionsTo(af, {"ZapdosApp"});

  /* register custom execute flags, action syntax, etc. here */
  s.registerActionSyntax("AddLotsOfCoeffDiffusion", "LotsOfCoeffDiffusion");
  s.registerActionSyntax("AddLotsOfVariables", "LotsOfVariables");
  s.registerActionSyntax("AddLotsOfSources", "LotsOfSources");
  s.registerActionSyntax("AddLotsOfTimeDerivatives", "LotsOfTimeDerivatives");
  s.registerActionSyntax("AddLotsOfEFieldAdvection", "LotsOfEFieldAdvection");
  s.registerActionSyntax("AddLotsOfPotentialDrivenArtificialDiff",
                         "LotsOfPotentialDrivenArtificialDiff");
  s.registerActionSyntax("AddPeriodicControllers", "PeriodicControllers/*");
  s.registerActionSyntax("AddDriftDiffusionAction", "DriftDiffusionAction/*");
  s.registerActionSyntax("AddDriftDiffusionActionAD", "DriftDiffusionActionAD/*");
  s.registerActionSyntax("AddPeriodicRelativeNodalDifference", "PeriodicRelativeNodalDifference/*");
  s.registerActionSyntax("AddElectronAction", "ElectronAction");
  s.registerActionSyntax("AddHeavySpeciesTransportAction", "HeavySpeciesTransport/*");
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
