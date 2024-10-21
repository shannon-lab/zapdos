import numpy as np
import matplotlib.pylab as plt

# Output CSV file name
file = 'example1_out.csv'


data = np.genfromtxt(file, dtype=float, delimiter=',', skip_header=1)

plt.plot(data[:,0], data[:,5], 'k-', label='Species x')
plt.plot(data[:,0], data[:,6], 'b-', label='Species y')
plt.xlabel('Time [s]', fontsize=14)
plt.ylabel('`Species` count', fontsize=14)
plt.legend()
plt.show()
