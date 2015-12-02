import numpy as np
first = np.loadtxt("first_nl_it.txt")
second = np.loadtxt("second_nl_it.txt")
lam1 = 1.0
lam2 = 0.5
final_soln = -lam1 * first - lam2 * second
print final_soln
