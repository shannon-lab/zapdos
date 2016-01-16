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
z-DGAdvectionInterface
z-ElectronTimeDerivative
z-EFieldAdvection
z-CoeffDiffusion
z-ElectronsFromIonizationLFA_KV Woooo!!!
z-LogStabilizationMoles
z-ReactantFirstOrderRxn
z-ReactantAARxn
z-CoeffDiffusionLin
z-ChargeSourceMoles_KV
z-IonsFromIonizationLFA_KV
z-EFieldArtDiff
z-ProductFirstOrderRxn
z-ProductAABBRxn
z-DGMatDiffusionLogInt
z-DGMatDiffusionInt
z-NeumannCircuitVoltageMoles_KV
z-EFieldAdvectionElectrons
z-EFieldAdvectionEnergy
z-CoeffDiffusionElectrons
z-CoeffDiffusionEnergy
z-DCElectronBC # Matched perfectly in user state. Discrepancy in 1.0 and -1.0 variable vectors. However, if if statements are removed from the src file, then discrepancies disappear.
z-DCIonBC # Matched perfectly in user state. Discrepancy in 1.0 and -1.0 variable vectors. However, if if statements are removed from the src file, then discrepancies disappear.
z-GradMeanEnZeroBC # Matched perfectly in user state. Discrepancy in 1.0 and -1.0 variable vectors. However, if if statements are removed from the src file, then discrepancies disappear.
z-HagelaarAnodicBC # Matched perfectly in user state. Discrepancy in 1.0 and -1.0 variable vectors. However, if if statements are removed from the src file, then discrepancies disappear.
z-HagelaarIonBC # Matched perfectly in user state. Discrepancy in 1.0 and -1.0 variable vectors. However, if if statements are removed from the src file, then discrepancies disappear.
z-HagelaarElectronBC # Matched perfectly in user state. Discrepancy in 1.0 and -1.0 variable vectors. However, if if statements are removed from the src file, then discrepancies disappear.
z-HagelaarEnergyBC # Matched perfectly in user state. Discrepancy in 1.0 and -1.0 variable vectors. However, if if statements are removed from the src file, then discrepancies disappear.
z-MatchedValueLogBC
z-DGPenaltyTiedValue
z-DGEFieldAdvection # This will only work as long as the variable and coupled variable have the same number of shape functions in each element
z-DGCoeffDiffusion
z-InterpCoeffDiffusion
z-ElectronsFromIonization (Now confirmed with interpolated transport coefficients)
z-JouleHeating (Now confirmed with interpolated transport coefficients)
z-IonsFromIonization (Now confirmed with interpolated transport coefficients)
#z-ElectronEnergyLossFromIonization
#z-ElectronEnergyLossFromElastic
#z-ElectronEnergyLossFromExcitation
'''
