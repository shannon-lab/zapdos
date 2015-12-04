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

''' Gold Jacobians:
DGDiffusionInterface
Diffusion
DirichletBC
MatchedValueBC
'''
