#include "ZapdosApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"
#include "SquirrelApp.h"

template <>
InputParameters
validParams<ZapdosApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_output_syntax") = false;
  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

// When using the new Registry system, this line is required so that
// dependent apps know about the ZapdosApp label.
registerKnownLabel("ZapdosApp");

ZapdosApp::ZapdosApp(InputParameters parameters) : MooseApp(parameters)
{
  ZapdosApp::registerAll(_factory, _action_factory, _syntax);
  SquirrelApp::registerAll(_factory, _action_factory, _syntax);
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
