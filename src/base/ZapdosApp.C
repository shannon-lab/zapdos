#include "ZapdosApp.h"
#include "Moose.h"
#include "AppFactory.h"
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

  Moose::registerObjects(_factory);
  SquirrelApp::registerObjects(_factory);
  ZapdosApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  SquirrelApp::associateSyntax(_syntax, _action_factory);
  ZapdosApp::associateSyntax(_syntax, _action_factory);
}

ZapdosApp::~ZapdosApp() {}

extern "C" void
ZapdosApp__registerApps()
{
  ZapdosApp::registerApps();
}
void
ZapdosApp::registerApps()
{
  registerApp(ZapdosApp);
}

void
ZapdosApp::registerObjects(Factory & factory)
{
  Registry::registerObjectsTo(factory, {"ZapdosApp"});
}

void
ZapdosApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  // add actions
  Registry::registerActionsTo(action_factory, {"ZapdosApp"});
  syntax.registerActionSyntax("AddLotsOfCoeffDiffusion", "LotsOfCoeffDiffusion");
  syntax.registerActionSyntax("AddLotsOfVariables", "LotsOfVariables");
  syntax.registerActionSyntax("AddLotsOfSources", "LotsOfSources");
  syntax.registerActionSyntax("AddLotsOfTimeDerivatives", "LotsOfTimeDerivatives");
  syntax.registerActionSyntax("AddLotsOfEFieldAdvection", "LotsOfEFieldAdvection");
  syntax.registerActionSyntax("AddLotsOfPotentialDrivenArtificialDiff",
                              "LotsOfPotentialDrivenArtificialDiff");
}
