import numpy as np
import numpy.matlib

# J_diff = np.mat('1 -1; -1 1')
# J_diff_diri_left = np.mat('1 0; -1 1')

# J_diri_left = J_diff_diri_left - J_diff
# print J_diri_left

# J = np.mat('1 0; 0 1')
# Jinv = np.linalg.inv(J)
# R = np.array([1,0])

# x = np.dot(Jinv,R)
# print x

J_FD_old = np.mat('1 0 0 0; -4 4 0 0; 0 0 2 -2; 0 0 0 1')
J_FD_new = np.mat('1 0 0 0; -2 2 1 -1; -2 2 1 -1; 0 0 0 1')
J_FD_delta = J_FD_new - J_FD_old
print J_FD_delta

J_H_old = np.mat('1 0 0 0; -4 4 0 0; 0 0 2 -2; 0 0 0 1')
J_H_new = np.mat('1 0 0 0; 0 0 2 -2; -2 2 2 -2; 0 0 0 1')
J_H_delta = J_H_new - J_H_old
print J_H_delta

''' Confident Jacobians:
m-DGDiffusionInterface
m-Diffusion
m-DirichletBC
m-MatchedValueBC

InterfaceKernels
z-DGAdvectionInterface
z-DGMatDiffusionLogInt
z-DGMatDiffusionInt
z-DGPenaltyTiedValue
z-InterfaceAdvection (confirmed with interpolated electron transport coefficients)
z-InterfaceLogDiffusionElectrons (confirmed with interpolated electron transport coefficients)

Kernels
z-ElectronTimeDerivative (confirmed with interpolated electron transport coefficients)
z-EFieldAdvection (confirmed with interpolated electron transport coefficients)
z-CoeffDiffusion (confirmed with interpolated electron transport coefficients)
z-ElectronsFromIonizationLFA_KV
z-LogStabilizationMoles (confirmed with interpolated electron transport coefficients)
z-ReactantFirstOrderRxn
z-ReactantAARxn
z-CoeffDiffusionLin (confirmed with interpolated electron transport coefficients)
z-ChargeSourceMoles_KV (confirmed with interpolated electron transport coefficients)
z-IonsFromIonizationLFA_KV
z-EFieldArtDiff
z-ProductFirstOrderRxn
z-ProductAABBRxn
z-NeumannCircuitVoltageMoles_KV
z-EFieldAdvectionElectrons (confirmed with interpolated electron transport coefficients)
z-EFieldAdvectionEnergy (confirmed with interpolated electron transport coefficients)
z-CoeffDiffusionElectrons (confirmed with interpolated electron transport coefficients)
z-CoeffDiffusionEnergy (confirmed with interpolated electron transport coefficients)
z-InterpCoeffDiffusion
z-ElectronsFromIonization (Now confirmed with interpolated electron transport coefficients)
z-JouleHeating (Now confirmed with interpolated electron transport coefficients)
z-IonsFromIonization (Now confirmed with interpolated electron transport coefficients)
z-ElectronEnergyLossFromIonization (Now confirmed with interpolated electron transport coefficients)
z-ElectronEnergyLossFromElastic (Now confirmed with interpolated electron transport coefficients)
z-ElectronEnergyLossFromExcitation (Now confirmed with interpolated electron transport coefficients)

Boundary Conditions
z-DCElectronBC
z-DCIonBC
z-GradMeanEnZeroBC (confirmed with interpolated electron transport coefficients)
z-HagelaarAnodicBC
z-HagelaarIonBC (confirmed with interpolated electron transport coefficients)
z-HagelaarElectronBC (confirmed with interpolated electron transport coefficients)
z-HagelaarEnergyBC (confirmed with interpolated electron transport coefficients)
z-MatchedValueLogBC (confirmed with interpolated electron transport coefficients)

DGKernels
z-DGEFieldAdvection # This will only work as long as the variable and coupled variable have the same number of shape functions in each element
z-DGCoeffDiffusion
'''
