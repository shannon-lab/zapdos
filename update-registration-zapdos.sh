#!/bin/bash
# run this script with one or more arguments that are the directories that hold the code files for
# the objects you want to update.

dirs=$@

appname='ZapdosApp'

objs='
NodeAndSidesetBetweenSubdomains
PotentialGradientSource
EFieldMagnitudeSource
AxisymmetricCurlZ
UserSource
TM0CylindricalEz
TM0CylindricalEr
TM0Cylindrical
CoeffDiffusionElectrons
CoeffDiffusionEnergy
EFieldAdvectionElectrons
EFieldAdvectionEnergy
DriftDiffusion
DriftDiffusionUser
DriftDiffusionElectrons
DriftDiffusionEnergy
ChargeSourceMoles_KV
ReactantFirstOrderRxn
ReactantAARxn
IonsFromIonization
EFieldArtDiff
ElectronEnergyLossFromIonization
ElectronEnergyLossFromExcitation
ElectronEnergyLossFromElastic
CoeffDiffusion
EFieldAdvection
JouleHeating
ElectronTimeDerivative
ElectronsFromIonization
ElectronsFromIonizationUser
CoeffDiffusionLin
LogStabilizationMoles
ProductFirstOrderRxn
ProductAABBRxn
Sigma
DriftDiffusionFluxAux
AbsValueAux
DensityMoles
TM0CylindricalEzAux
TM0CylindricalErAux
Current
PowerDep
ProcRate
TotalFlux
Position
Efield
ElectronTemperature
DiffusiveFlux
EFieldAdvAux
UserFlux
SigmaMat
JacMat
Gas
Water
AnalyticalDiffIndicator
BlockAverageValue
ProvideMobility
CurrentDensityShapeSideUserObject
PotentialDriftOutflowBC
DriftDiffusionDoNothingBC
DriftDiffusionUserDoNothingBC
TM0AntennaVertBC
ElectronAdvectionDoNothingBC
ElectronDiffusionDoNothingBC
TM0PECVertBC
PenaltyCircuitPotential
CircuitDirichletPotential
SecondaryElectronBC
FieldEmissionBC
SchottkyEmissionBC
HagelaarIonAdvectionBC
HagelaarIonDiffusionBC
HagelaarElectronBC
HagelaarElectronAdvectionBC
HagelaarEnergyBC
HagelaarEnergyAdvectionBC
NeumannCircuitVoltageMoles_KV
DCIonBC
InterfaceAdvection
HphiRadialInterface
InterfaceLogDiffusionElectrons
DGCoeffDiffusion
DGEFieldAdvection
ArbitrarilyTiedValueConstraint
SideTotFluxIntegral
'

actions='
AddLotsOfCoeffDiffusion add_variable
AddLotsOfCoeffDiffusion add_kernel
AddLotsOfCoeffDiffusion add_bc
AddLotsOfVariables add_variable
AddLotsOfVariables add_kernel
AddLotsOfVariables add_bc
AddLotsOfSources add_variable
AddLotsOfSources add_kernel
AddLotsOfSources add_bc
AddLotsOfTimeDerivatives add_variable
AddLotsOfTimeDerivatives add_kernel
AddLotsOfTimeDerivatives add_bc
AddLotsOfEFieldAdvection add_variable
AddLotsOfEFieldAdvection add_kernel
AddLotsOfEFieldAdvection add_bc
AddLotsOfPotentialDrivenArtificialDiff add_variable
AddLotsOfPotentialDrivenArtificialDiff add_kernel
AddLotsOfPotentialDrivenArtificialDiff add_bc
'

for obj in $objs; do
    find $dirs | grep "/${obj}\.C$" | xargs perl -0777 -i'' -pe 's/(template ?<>\nInputParameters\n? ?validParams<(\w*)>\(\))/registerMooseObject\("'"$appname"'", \2\);\n\n\1/igs'
done

while read action task; do
    find $dirs | grep "/${action}\.C$" | xargs perl -0777 -i'' -pe 's/(template ?<>\nInputParameters\n? ?validParams<(\w*)>\(\))/registerMooseAction\("'"$appname"'", \2, "'"$task"'"\);\n\n\1/igs'
done <<< "$actions"
