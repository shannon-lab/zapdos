#include "ZapdosApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "SquirrelApp.h"
// #include "ModulesApp.h"

// Kernels
#include "UserSource.h"
#include "AxisymmetricCurlZ.h"
#include "TM0CylindricalEz.h"
#include "TM0CylindricalEr.h"
#include "TM0Cylindrical.h"
#include "EFieldAdvectionEnergy.h"
#include "CoeffDiffusionElectrons.h"
#include "CoeffDiffusionEnergy.h"
#include "EFieldAdvectionElectrons.h"
#include "DriftDiffusion.h"
#include "DriftDiffusionUser.h"
#include "DriftDiffusionElectrons.h"
#include "DriftDiffusionEnergy.h"
#include "ProductAABBRxn.h"
#include "ProductFirstOrderRxn.h"
#include "LogStabilizationMoles.h"
#include "ChargeSourceMoles_KV.h"
#include "CoeffDiffusionLin.h"
#include "ReactantAARxn.h"
#include "ElectronEnergyLossFromIonization.h"
#include "ElectronEnergyLossFromExcitation.h"
#include "ElectronEnergyLossFromElastic.h"
#include "IonsFromIonization.h"
#include "EFieldArtDiff.h"
#include "ElectronsFromIonization.h"
#include "ElectronsFromIonizationUser.h"
#include "CoeffDiffusion.h"
#include "ReactantFirstOrderRxn.h"
#include "EFieldAdvection.h"
#include "JouleHeating.h"
#include "ElectronTimeDerivative.h"

// AuxKernels

#include "DriftDiffusionFluxAux.h"
#include "UserFlux.h"
#include "DensityMoles.h"
#include "TM0CylindricalErAux.h"
#include "TM0CylindricalEzAux.h"
#include "AbsValueAux.h"
#include "ProcRate.h"
#include "PowerDep.h"
#include "Current.h"
#include "EFieldAdvAux.h"
#include "TotalFlux.h"
#include "Position.h"
#include "ElectronTemperature.h"
#include "DiffusiveFlux.h"
#include "Efield.h"

// Materials
#include "JacMat.h"
#include "Gas.h"
#include "Water.h"

// Indicators
#include "AnalyticalDiffIndicator.h"

// User Objects
#include "BlockAverageValue.h"
#include "ProvideMobility.h"
#include "CurrentDensityShapeSideUserObject.h"

// Boundary Conditions
#include "DriftDiffusionDoNothingBC.h"
#include "DriftDiffusionUserDoNothingBC.h"
#include "ElectronAdvectionDoNothingBC.h"
#include "ElectronDiffusionDoNothingBC.h"
#include "TM0AntennaVertBC.h"
#include "TM0PECVertBC.h"
#include "PenaltyCircuitPotential.h"
#include "CircuitDirichletPotential.h"
#include "SecondaryElectronBC.h"
#include "FieldEmissionBC.h"
#include "SchottkyEmissionBC.h"
#include "HagelaarIonAdvectionBC.h"
#include "HagelaarIonDiffusionBC.h"
#include "HagelaarElectronBC.h"
#include "HagelaarElectronAdvectionBC.h"
#include "HagelaarEnergyBC.h"
#include "HagelaarEnergyAdvectionBC.h"
#include "MatchedValueLogBC.h"
#include "NeumannCircuitVoltageMoles_KV.h"
#include "NeumannCircuitVoltageNew.h"
#include "DCIonBC.h"

// Actions

#include "AddLotsOfCoeffDiffusion.h"
#include "AddLotsOfVariables.h"
#include "AddLotsOfSources.h"
#include "AddLotsOfTimeDerivatives.h"
#include "AddLotsOfEFieldAdvection.h"
#include "AddLotsOfPotentialDrivenArtificialDiff.h"

// DGKernels
#include "DGCoeffDiffusion.h"
#include "DGEFieldAdvection.h"

// InterfaceKernels
#include "HphiRadialInterface.h"
#include "InterfaceAdvection.h"
#include "InterfaceLogDiffusionElectrons.h"

// Constraints

#include "ArbitrarilyTiedValueConstraint.h"

// Mesh modifiers

#include "NodeAndSidesetBetweenSubdomains.h"

// Postprocessors

#include "SideTotFluxIntegral.h"

template<>
InputParameters validParams<ZapdosApp>()
{
	InputParameters params = validParams<MooseApp>();

	params.set<bool>("use_legacy_output_syntax") = false;
	params.set<bool>("use_legacy_uo_initialization") = false;
	params.set<bool>("use_legacy_uo_aux_computation") = false;
	return params;
}

ZapdosApp::ZapdosApp(InputParameters parameters) :
		MooseApp(parameters)
{

	Moose::registerObjects(_factory);
	SquirrelApp::registerObjects(_factory);
	ZapdosApp::registerObjects(_factory);

	Moose::associateSyntax(_syntax, _action_factory);
	SquirrelApp::associateSyntax(_syntax, _action_factory);
	ZapdosApp::associateSyntax(_syntax, _action_factory);
}

ZapdosApp::~ZapdosApp()
{
}

extern "C" void ZapdosApp__registerApps() { ZapdosApp::registerApps(); }
void
ZapdosApp::registerApps()
{
	registerApp(ZapdosApp);
}

void
ZapdosApp::registerObjects(Factory & factory)
{
  registerMeshModifier(NodeAndSidesetBetweenSubdomains);
  registerKernel(AxisymmetricCurlZ);
  registerKernel(UserSource);
  registerKernel(TM0CylindricalEz);
  registerKernel(TM0CylindricalEr);
  registerKernel(TM0Cylindrical);
  registerKernel(CoeffDiffusionElectrons);
  registerKernel(CoeffDiffusionEnergy);
  registerKernel(EFieldAdvectionElectrons);
  registerKernel(EFieldAdvectionEnergy);
  registerKernel(DriftDiffusion);
  registerKernel(DriftDiffusionUser);
  registerKernel(DriftDiffusionElectrons);
  registerKernel(DriftDiffusionEnergy);
  registerKernel(ChargeSourceMoles_KV);
  registerKernel(ReactantFirstOrderRxn);
  registerKernel(ReactantAARxn);
  registerKernel(IonsFromIonization);
  registerKernel(EFieldArtDiff);
  registerKernel(ElectronEnergyLossFromIonization);
  registerKernel(ElectronEnergyLossFromExcitation);
  registerKernel(ElectronEnergyLossFromElastic);
  registerKernel(CoeffDiffusion);
  registerKernel(EFieldAdvection);
  registerKernel(JouleHeating);
  registerKernel(ElectronTimeDerivative);
  registerKernel(ElectronsFromIonization);
  registerKernel(ElectronsFromIonizationUser);
  registerKernel(CoeffDiffusionLin);
  registerKernel(LogStabilizationMoles);
  registerKernel(ProductFirstOrderRxn);
  registerKernel(ProductAABBRxn);
  registerAux(DriftDiffusionFluxAux);
  registerAux(AbsValueAux);
  registerAux(DensityMoles);
  registerAux(TM0CylindricalEzAux);
  registerAux(TM0CylindricalErAux);
  registerAux(Current);
  registerAux(PowerDep);
  registerAux(ProcRate);
  registerAux(TotalFlux);
  registerAux(Position);
  registerAux(Efield);
  registerAux(ElectronTemperature);
  registerAux(DiffusiveFlux);
  registerAux(EFieldAdvAux);
  registerAux(UserFlux);
  registerMaterial(JacMat);
  registerMaterial(Gas);
  registerMaterial(Water);
  registerIndicator(AnalyticalDiffIndicator);
  registerUserObject(BlockAverageValue);
  registerUserObject(ProvideMobility);
  registerUserObject(CurrentDensityShapeSideUserObject);
  registerBoundaryCondition(DriftDiffusionDoNothingBC);
  registerBoundaryCondition(DriftDiffusionUserDoNothingBC);
  registerBoundaryCondition(TM0AntennaVertBC);
  registerBoundaryCondition(ElectronAdvectionDoNothingBC);
  registerBoundaryCondition(ElectronDiffusionDoNothingBC);
  registerBoundaryCondition(TM0PECVertBC);
  registerBoundaryCondition(PenaltyCircuitPotential);
  registerBoundaryCondition(CircuitDirichletPotential);
  registerBoundaryCondition(SecondaryElectronBC);
  registerBoundaryCondition(FieldEmissionBC);
  registerBoundaryCondition(SchottkyEmissionBC);
  registerBoundaryCondition(HagelaarIonAdvectionBC);
  registerBoundaryCondition(HagelaarIonDiffusionBC);
  registerBoundaryCondition(HagelaarElectronBC);
  registerBoundaryCondition(HagelaarElectronAdvectionBC);
  registerBoundaryCondition(HagelaarEnergyBC);
  registerBoundaryCondition(HagelaarEnergyAdvectionBC);
  registerBoundaryCondition(NeumannCircuitVoltageMoles_KV);
  registerBoundaryCondition(DCIonBC);
  registerInterfaceKernel(InterfaceAdvection);
  registerInterfaceKernel(HphiRadialInterface);
  registerInterfaceKernel(InterfaceLogDiffusionElectrons);
  registerDGKernel(DGCoeffDiffusion);
  registerDGKernel(DGEFieldAdvection);
  registerConstraint(ArbitrarilyTiedValueConstraint);
  registerPostprocessor(SideTotFluxIntegral);
}

void
ZapdosApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
	// add actions
	registerAction(AddLotsOfCoeffDiffusion, "add_variable");
	registerAction(AddLotsOfCoeffDiffusion, "add_kernel");
	registerAction(AddLotsOfCoeffDiffusion, "add_bc");
	syntax.registerActionSyntax("AddLotsOfCoeffDiffusion", "LotsOfCoeffDiffusion");
	registerAction(AddLotsOfVariables, "add_variable");
	registerAction(AddLotsOfVariables, "add_kernel");
	registerAction(AddLotsOfVariables, "add_bc");
	syntax.registerActionSyntax("AddLotsOfVariables", "LotsOfVariables");
	registerAction(AddLotsOfSources, "add_variable");
	registerAction(AddLotsOfSources, "add_kernel");
	registerAction(AddLotsOfSources, "add_bc");
	syntax.registerActionSyntax("AddLotsOfSources", "LotsOfSources");
	registerAction(AddLotsOfTimeDerivatives, "add_variable");
	registerAction(AddLotsOfTimeDerivatives, "add_kernel");
	registerAction(AddLotsOfTimeDerivatives, "add_bc");
	syntax.registerActionSyntax("AddLotsOfTimeDerivatives", "LotsOfTimeDerivatives");
	registerAction(AddLotsOfEFieldAdvection, "add_variable");
	registerAction(AddLotsOfEFieldAdvection, "add_kernel");
	registerAction(AddLotsOfEFieldAdvection, "add_bc");
	syntax.registerActionSyntax("AddLotsOfEFieldAdvection", "LotsOfEFieldAdvection");
	registerAction(AddLotsOfPotentialDrivenArtificialDiff, "add_variable");
	registerAction(AddLotsOfPotentialDrivenArtificialDiff, "add_kernel");
	registerAction(AddLotsOfPotentialDrivenArtificialDiff, "add_bc");
	syntax.registerActionSyntax("AddLotsOfPotentialDrivenArtificialDiff", "LotsOfPotentialDrivenArtificialDiff");
}
