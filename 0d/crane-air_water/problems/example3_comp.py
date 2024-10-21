import numpy as np
import matplotlib.pylab as plt

# Output CSV file name
file = 'zdplaskin_ex3_out.csv'
file2 = 'example3_log_out.csv'
# zdplaskin_file = '/Users/keniley/Documents/LCPP_Atmos/example1/out.txt'

# zdplaskin_data = pd.read_csv(zdplaskin_file, sep="  ", header=0)
# zd_data = np.genfromtxt(zdplaskin_file, dtype=float, delimiter="  ", skip_header=14, skip_footer=2)
# test = zdplaskin_data.values

data = np.genfromtxt(file, dtype=float, delimiter=',', skip_header=1)
data2 = np.genfromtxt(file2, dtype=float, delimiter=',', skip_header=1)

plt.semilogy(data[:,0], data[:,7], 'g--', label='$N_2(A)$')
plt.semilogy(data[:,0], data[:,4], 'r--', label='$Ar^{2+}$')
plt.semilogy(data[:,0], data[:,2], 'c--', label='$Ar^*$')
plt.semilogy(data[:,0], data[:,13], 'k--', label='$e^-$')
plt.semilogy(data2[:,0], np.exp(data2[:,7]), 'g', alpha=0.5, label='$N_2(A)$')
plt.semilogy(data2[:,0], np.exp(data2[:,4]), 'r', alpha=0.5, label='$Ar^{2+}$')
plt.semilogy(data2[:,0], np.exp(data2[:,2]), 'c', alpha=0.5, label='$Ar^*$')
plt.semilogy(data2[:,0], np.exp(data2[:,13]), 'k', alpha=0.5, label='$e^-$')
plt.xlabel('Time [s]', fontsize=14)
plt.ylabel('Electron Density, [$cm^{-3}$]', fontsize=14)
plt.legend()
plt.show()
