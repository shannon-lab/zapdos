#include "BovineApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

// Kernels
#include "ConstTimesDiffusion.h"
#include "FirstOrderReaction.h"
#include "SecondOrderReaction.h"
#include "SelfBinaryReaction.h"
#include "SrcSelfBinaryReaction.h"
#include "SrcSecondOrderReaction.h"

// Materials
// #include "DiffusionConst.h"

template<>
InputParameters validParams<BovineApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

BovineApp::BovineApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  BovineApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  BovineApp::associateSyntax(_syntax, _action_factory);
}

BovineApp::~BovineApp()
{
}

extern "C" void BovineApp__registerApps() { BovineApp::registerApps(); }
void
BovineApp::registerApps()
{
  registerApp(BovineApp);
}

void
BovineApp::registerObjects(Factory & factory)
{
  registerKernel(ConstTimesDiffusion);
  registerKernel(FirstOrderReaction);
  registerKernel(SecondOrderReaction);
  registerKernel(SelfBinaryReaction);
  registerKernel(SrcSelfBinaryReaction);
  registerKernel(SrcSecondOrderReaction);
//  registerMaterial(DiffusionConst);
}

void
BovineApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
