#include "ZapdosApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
// #include "ModulesApp.h"

// Kernels
#include "TM0CylindricalEz.h"
#include "TM0CylindricalEr.h"
#include "TM0Cylindrical.h"
#include "IonRateIonization.h"
#include "ElectronRateIonization.h"
#include "ElectronEnergyRateIonization.h"
#include "ElectronEnergyRateExcitation.h"
#include "ElectronEnergyRateElastic.h"
#include "EFieldAdvectionEnergy.h"
#include "CoeffDiffusionElectrons.h"
#include "CoeffDiffusionEnergy.h"
#include "EFieldAdvectionElectrons.h"
#include "InterpCoeffDiffusion.h"
#include "ProductAABBRxn.h"
#include "ProductFirstOrderRxn.h"
#include "ElectronsFromIonizationLFA_KV.h"
#include "IonsFromIonizationLFA_KV.h"
#include "LogStabilizationMoles.h"
#include "ChargeSourceMoles.h"
#include "ChargeSourceMoles_KV.h"
#include "CoeffDiffusionLin.h"
#include "ReactantAARxn.h"
#include "ElectronsFromIonizationLFA.h"
#include "IonsFromIonizationLFA.h"
#include "ChargeSource.h"
#include "ElectronEnergyLossFromIonization.h"
#include "ElectronEnergyLossFromExcitation.h"
#include "ElectronEnergyLossFromElastic.h"
#include "IonsFromIonization.h"
#include "EFieldArtDiff.h"
#include "LogStabilization.h"
#include "ElectronsFromIonization.h"
#include "ParamAdvection.h"
#include "CoeffParamDiffusion.h"
#include "IonBolosKernel.h"
#include "ElectronBolosKernel.h"
#include "IonBolosKernelEnergyForm.h"
#include "ElectronBolosKernelEnergyForm.h"
#include "ElectronEnergyBolosKernel.h"
#include "GAdvection.h"
#include "IonKernelEnergyForm.h"
#include "ElectronKernelEnergyForm.h"
#include "ElectronKernelIntTD.h"
#include "IonKernelIntTD.h"
#include "AdvectionDiffusionKernel.h"
#include "ExampleTimeDerivative.h"
#include "CoeffDiffusion.h"
#include "CoupledDiffusion.h"
#include "FirstOrderReaction.h"
#include "ReactantFirstOrderRxn.h"
#include "SecondOrderReaction.h"
#include "SelfBinaryReaction.h"
#include "SrcSelfBinaryReaction.h"
#include "SrcSecondOrderReaction.h"
#include "PoissonSource.h"
#include "MatAdvection.h"
#include "IonizationSource.h"
#include "DivFreeConvection.h"
#include "CoupledIonizationSource.h"
#include "ArtificialDiff.h"
#include "ConstConvection.h"
#include "TimeDerivativeSUPG.h"
#include "ConstConvectionSUPG.h"
#include "ExampleDiffusion.h"
#include "EFieldAdvection.h"
#include "Source.h"
#include "UnitySource.h"
#include "ConvectionArb.h"
#include "PotentialDrivenArtificialDiff.h"
#include "JouleHeating.h"
#include "ElectronDiffusion.h"
#include "ArsSource.h"
#include "ArpSource.h"
#include "ElectronSource.h"
#include "ElectronEnergySource.h"
#include "TimeDerivativeElectronTemp.h"
#include "ElectronEnergyTransport.h"
#include "PotentialDrivenArtificialDiffElectrons.h"
#include "PotentialDrivenArtificialDiffEnergy.h"
#include "CoefTimeDerivative.h"
#include "ElectronKernel.h"
#include "ArpKernel.h"
#include "ElectronEnergyKernel.h"
#include "PoissonKernel.h"
#include "ElectronTimeDerivative.h"

// AuxKernels

#include "TM0CylindricalErAux.h"
#include "TM0CylindricalEzAux.h"
#include "AbsValueAux.h"
#include "ProcRate.h"
#include "PowerDep.h"
#include "Current.h"
#include "EFieldAdvAux.h"
#include "TotalFlux.h"
#include "ElectronTotalFlux.h"
#include "ElectronTotalFluxMag.h"
#include "AuxSource.h"
#include "Position.h"
#include "ElectronAdvectiveFlux.h"
#include "ElectronDiffusiveFlux.h"
#include "ElectronArtDiffusiveFlux.h"
#include "IonDensity.h"
#include "ElectronTemperature.h"
#include "EFieldMag.h"
#include "VelocityMag.h"
#include "ChargeDensity.h"
#include "IonSrcTerm.h"
#include "AlphaTimesHSize.h"
#include "HSize.h"
#include "Sigma.h"
#include "VelocityH.h"
#include "Velocity.h"
#include "AdvectiveFlux.h"
#include "DiffusiveFlux.h"
#include "Density.h"
#include "Efield.h"

// Materials
#include "JacMat.h"
#include "Test.h"
#include "Test2.h"
#include "Air.h"
#include "AirConstTD.h"
#include "Gas.h"
#include "NoCouplingAir.h"
#include "BlockAverageDiffusionMaterial.h"
#include "WD.h"
#include "Water.h"
#include "Argon.h"
#include "InterpolateTD.h"

// Indicators
#include "AnalyticalDiffIndicator.h"
#include "VariableJumpIndicator.h"

// User Objects
#include "BlockAverageValue.h"
#include "ProvideMobility.h"

// Boundary Conditions
#include "TM0AntennaVertBC.h"
#include "TM0PECVertBC.h"
#include "PenaltyCircuitPotential.h"
#include "CircuitDirichletPotential.h"
#include "VacuumElectricBC.h"
#include "SecondaryElectronBC.h"
#include "HagelaarEnergyBC.h"
#include "HagelaarIonAdvectionBC.h"
#include "HagelaarIonDiffusionBC.h"
#include "HagelaarElectronBC.h"
#include "HagelaarAnodicBC.h"
#include "GradMeanEnZeroBC.h"
#include "RobinBC.h"
#include "OutflowBC.h"
#include "InflowBC.h"
#include "MatchedValueLogBC.h"
#include "MultipliedValueBC.h"
#include "CoupledIntegratedBC.h"
#include "NeumannCircuitVoltage.h"
#include "NeumannCircuitVoltageMoles.h"
#include "NeumannCircuitVoltageMoles_KV.h"
#include "NoDiffusiveFlux.h"
#include "EFieldBC.h"
#include "SpeciesNetFluxBC.h"
#include "SimpleNetFluxBC.h"
#include "RFIonBC.h"
#include "DCIonBC.h"
#include "RFElectronBC.h"
#include "DCElectronBC.h"
#include "AdvectionDoNothingBC.h"
#include "SometimesAdvectionBC.h"
#include "PhysicalElectronEnergyBC.h"
#include "DGFluxBC.h"

// Actions

#include "AddLotsOfDiffusion.h"
#include "AddLotsOfCoeffDiffusion.h"
#include "AddLotsOfVariables.h"
#include "AddLotsOfSources.h"
#include "AddLotsOfTimeDerivatives.h"
#include "AddLotsOfEFieldAdvection.h"
#include "AddLotsOfPotentialDrivenArtificialDiff.h"

// DGKernels
#include "DGCoeffDiffusion.h"
#include "DGEFieldAdvection.h"
#include "DGAdvection.h"

// InterfaceKernels
#include "HphiRadialInterface.h"
#include "InterfaceAdvection.h"
#include "InterfaceLogDiffusionElectrons.h"
#include "DGPenaltyTiedValue.h"
#include "DGDiffusionInt.h"
#include "DGAdvectionInterface.h"
#include "DGMatDiffusionInt.h"
#include "DGMatDiffusionLogInt.h"

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
//  ModulesApp::registerObjects(_factory);
  ZapdosApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
//  ModulesApp::associateSyntax(_syntax, _action_factory);
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
  registerKernel(TM0CylindricalEz);
  registerKernel(TM0CylindricalEr);
  registerKernel(TM0Cylindrical);
  registerKernel(IonRateIonization);
  registerKernel(ElectronRateIonization);
  registerKernel(ElectronEnergyRateIonization);
  registerKernel(ElectronEnergyRateExcitation);
  registerKernel(ElectronEnergyRateElastic);
  registerKernel(CoeffDiffusionElectrons);
  registerKernel(CoeffDiffusionEnergy);
  registerKernel(InterpCoeffDiffusion);
  registerKernel(EFieldAdvectionElectrons);
  registerKernel(EFieldAdvectionEnergy);
  registerKernel(ChargeSourceMoles);
  registerKernel(ChargeSourceMoles_KV);
  registerKernel(IonsFromIonizationLFA_KV);
  registerKernel(ElectronsFromIonizationLFA_KV);
  registerKernel(ReactantFirstOrderRxn);
  registerKernel(ReactantAARxn);
  registerKernel(IonsFromIonization);
  registerKernel(IonsFromIonizationLFA);
  registerKernel(ElectronsFromIonizationLFA);
  registerKernel(EFieldArtDiff);
  registerKernel(ElectronEnergyLossFromIonization);
  registerKernel(ElectronEnergyLossFromExcitation);
  registerKernel(ElectronEnergyLossFromElastic);
  registerKernel(ChargeSource);
  registerKernel(LogStabilization);
  registerKernel(IonBolosKernel);
  registerKernel(ElectronBolosKernel);
  registerKernel(IonBolosKernelEnergyForm);
  registerKernel(ElectronBolosKernelEnergyForm);
  registerKernel(ElectronEnergyBolosKernel);
  registerKernel(CoefTimeDerivative);
  registerKernel(GAdvection);
  registerKernel(ElectronKernelEnergyForm);
  registerKernel(IonKernelEnergyForm);
  registerKernel(IonKernelIntTD);
  registerKernel(AdvectionDiffusionKernel);
  registerKernel(CoeffDiffusion);
  registerKernel(CoupledDiffusion);
  registerKernel(FirstOrderReaction);
  registerKernel(SecondOrderReaction);
  registerKernel(SelfBinaryReaction);
  registerKernel(SrcSelfBinaryReaction);
  registerKernel(SrcSecondOrderReaction);
  registerKernel(PoissonSource);
  registerKernel(MatAdvection);
  registerKernel(CoeffParamDiffusion);
  registerKernel(IonizationSource);
  registerKernel(DivFreeConvection);
  registerKernel(CoupledIonizationSource);
  registerKernel(ArtificialDiff);
  registerKernel(ConstConvection);
  registerKernel(TimeDerivativeSUPG);
  registerKernel(ConstConvectionSUPG);
  registerKernel(ExampleDiffusion);
  registerKernel(EFieldAdvection);
  registerKernel(Source);
  registerKernel(UnitySource);
  registerKernel(ConvectionArb);
  registerKernel(PotentialDrivenArtificialDiff);
  registerKernel(JouleHeating);
  registerKernel(ElectronDiffusion);
  registerKernel(ArsSource);
  registerKernel(ArpSource);
  registerKernel(ElectronSource);
  registerKernel(ElectronEnergySource);
  registerKernel(TimeDerivativeElectronTemp);
  registerKernel(ElectronEnergyTransport);
  registerKernel(PotentialDrivenArtificialDiffElectrons);
  registerKernel(PotentialDrivenArtificialDiffEnergy);
  registerKernel(ElectronKernel);
  registerKernel(ArpKernel);
  registerKernel(ElectronEnergyKernel);
  registerKernel(PoissonKernel);
  registerKernel(ExampleTimeDerivative);
  registerKernel(ElectronTimeDerivative);
  registerKernel(ElectronKernelIntTD);
  registerKernel(ParamAdvection);
  registerKernel(ElectronsFromIonization);
  registerKernel(CoeffDiffusionLin);
  registerKernel(LogStabilizationMoles);
  registerKernel(ProductFirstOrderRxn);
  registerKernel(ProductAABBRxn);
  registerAux(AbsValueAux);
  registerAux(TM0CylindricalEzAux);
  registerAux(TM0CylindricalErAux);
  registerAux(Current);
  registerAux(PowerDep);
  registerAux(ProcRate);
  registerAux(TotalFlux);
  registerAux(Position);
  registerAux(Efield);
  registerAux(AuxSource);
  registerAux(ElectronTotalFlux);
  registerAux(ElectronTotalFluxMag);
  registerAux(ElectronAdvectiveFlux);
  registerAux(ElectronDiffusiveFlux);
  registerAux(ElectronArtDiffusiveFlux);
  registerAux(IonDensity);
  registerAux(ElectronTemperature);
  registerAux(Density);
  registerAux(EFieldMag);
  registerAux(VelocityMag);
  registerAux(ChargeDensity);
  registerAux(IonSrcTerm);
  registerAux(AlphaTimesHSize);
  registerAux(HSize);
  registerAux(Sigma);
  registerAux(VelocityH);
  registerAux(Velocity);
  registerAux(AdvectiveFlux);
  registerAux(DiffusiveFlux);
  registerAux(EFieldAdvAux);
  registerMaterial(JacMat);
  registerMaterial(Air);
  registerMaterial(Test);
  registerMaterial(Test2);
  registerMaterial(AirConstTD);
  registerMaterial(Gas);
  registerMaterial(NoCouplingAir);
  registerMaterial(BlockAverageDiffusionMaterial);
  registerMaterial(WD);
  registerMaterial(Water);
  registerMaterial(Argon);
  registerMaterial(InterpolateTD);
  registerIndicator(AnalyticalDiffIndicator);
  registerIndicator(VariableJumpIndicator);
  registerUserObject(BlockAverageValue);
  registerUserObject(ProvideMobility);
  registerBoundaryCondition(TM0AntennaVertBC);
  registerBoundaryCondition(TM0PECVertBC);
  registerBoundaryCondition(PenaltyCircuitPotential);
  registerBoundaryCondition(CircuitDirichletPotential);
  registerBoundaryCondition(VacuumElectricBC);
  registerBoundaryCondition(DGFluxBC);
  registerBoundaryCondition(SecondaryElectronBC);
  registerBoundaryCondition(HagelaarAnodicBC);
  registerBoundaryCondition(HagelaarIonAdvectionBC);
  registerBoundaryCondition(HagelaarIonDiffusionBC);
  registerBoundaryCondition(HagelaarElectronBC);
  registerBoundaryCondition(HagelaarEnergyBC);
  registerBoundaryCondition(GradMeanEnZeroBC);
  registerBoundaryCondition(InflowBC);
  registerBoundaryCondition(MultipliedValueBC);
  registerBoundaryCondition(NeumannCircuitVoltage);
  registerBoundaryCondition(NeumannCircuitVoltageMoles);
  registerBoundaryCondition(NeumannCircuitVoltageMoles_KV);
  registerBoundaryCondition(CoupledIntegratedBC);
  registerBoundaryCondition(NoDiffusiveFlux);
  registerBoundaryCondition(EFieldBC);
  registerBoundaryCondition(SpeciesNetFluxBC);
  registerBoundaryCondition(MatchedValueLogBC);
  registerBoundaryCondition(SimpleNetFluxBC);
  registerBoundaryCondition(RFIonBC);
  registerBoundaryCondition(DCIonBC);
  registerBoundaryCondition(RFElectronBC);
  registerBoundaryCondition(DCElectronBC);
  registerBoundaryCondition(AdvectionDoNothingBC);
  registerBoundaryCondition(SometimesAdvectionBC);
  registerBoundaryCondition(PhysicalElectronEnergyBC);
  registerBoundaryCondition(OutflowBC);
  registerBoundaryCondition(RobinBC);
  registerInterfaceKernel(InterfaceAdvection);
  registerInterfaceKernel(HphiRadialInterface);
  registerInterfaceKernel(InterfaceLogDiffusionElectrons);
  registerInterfaceKernel(DGPenaltyTiedValue);
  registerInterfaceKernel(DGDiffusionInt);
  registerInterfaceKernel(DGAdvectionInterface);
  registerInterfaceKernel(DGMatDiffusionInt);
  registerInterfaceKernel(DGMatDiffusionLogInt);
  registerDGKernel(DGAdvection);
  registerDGKernel(DGCoeffDiffusion);
  registerDGKernel(DGEFieldAdvection);
  registerConstraint(ArbitrarilyTiedValueConstraint);
  registerPostprocessor(SideTotFluxIntegral);
}

void
ZapdosApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  // add actions
  registerAction(AddLotsOfDiffusion, "add_variable");
  registerAction(AddLotsOfDiffusion, "add_kernel");
  registerAction(AddLotsOfDiffusion, "add_bc");
  syntax.registerActionSyntax("AddLotsOfDiffusion", "LotsOfDiffusion");
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
