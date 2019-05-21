#* This file is part of Zapdos, an open-source
#* application for the simulation of plasmas
#* https://github.com/shannon-lab/zapdos
#*
#* Zapdos is powered by the MOOSE Framework
#* https://www.mooseframework.org
#*
#* Licensed under LGPL 2.1, please see LICENSE for details
#* https://www.gnu.org/licenses/lgpl-2.1.html

import numpy as np
data = np.loadtxt("scaled_coupled_value_matrix.txt")
from numpy import linalg as LA
norm1_data = LA.norm(data,ord=1)
print norm1_data
norm2_data = LA.norm(data,ord=2)
# print LA.norm(data,ord=np.inf)
data_inv = LA.inv(data)
norm1_data_inv = LA.norm(data_inv,ord=1)
norm2_data_inv = LA.norm(data_inv,ord=2)
# print data_inv
print norm1_data_inv
# print LA.norm(data_inv,ord=2)
# print LA.norm(data_inv,ord=np.inf)
cond = norm1_data * norm1_data_inv
cond2 = norm2_data * norm2_data_inv
print cond
print cond2
