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
first = np.loadtxt("first_nl_it.txt")
second = np.loadtxt("second_nl_it.txt")
lam1 = 1.0
lam2 = 0.5
final_soln = -lam1 * first - lam2 * second
print final_soln
