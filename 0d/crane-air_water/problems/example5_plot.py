import numpy as np
import matplotlib.pylab as plt

# Output CSV file name
# file = 'example5_scale_out.csv'
file = 'example5_out.csv'

data = np.genfromtxt(file, dtype=float, delimiter=',', skip_header=1)

plt.semilogy(data[:,0], data[:,3], 'ko-')
plt.xlabel('Time [s]', fontsize=14)
plt.ylabel('Electron Density, [$cm^{-3}$]', fontsize=14)
plt.show()
