import numpy as np
import numpy.matlib

h = 0.5
D_u = 1
D_v = 3

Juu_diff = h * D_u * np.mat('1 -1; -1 1')
Jvv_diff = h * D_v * np.mat('1 -1; -1 1')

Juu_diri = np.mat('1 0; 0 0')
Jvv_diri = np.mat('0 0; 0 1')

Juu_matched = np.mat('0 0; 0 1')
Juv_matched = np.mat('0 0; -1 0')

Juu = Juu_diff + Juu_diri + Juu_matched
Juv = Juv_matched
Jvu = np.matlib.zeros((2,2))
Jvv = Jvv_diff + Jvv_diri

J = np.bmat([[Juu, Juv], [Jvu, Jvv]])
print J
