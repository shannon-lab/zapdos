import numpy as np
import matplotlib.pylab as plt

file = 'helium_oxygen_out.csv'

# time,He,He*,He+,He2*,He2+,M,O,O2,O2+,O2-,O3,O4+,T0,Teg,e
data = np.genfromtxt(file, dtype=float, delimiter=',', skip_header=1)

time = data[:,0]
N_He = data[:,1]
N_HeEx = data[:,2]
N_Hep = data[:,3]
N_He2Ex = data[:,4]
N_He2p = data[:,6]
N_M = data[:,7]
N_O = data[:,8]
N_O2p = data[:,9]
N_O2n = data[:,10]
N_O3 = data[:,11]
N_O4p = data[:,12]
N_e = data[:,15]

plot11, = plt.loglog(time, N_e, label='$e^-$')
# plot12, = plt.loglog(time, N_O, label='$O$')
# plot13, = plt.loglog(time, N_O2p, label='$O_2^+$')
# plot14, = plt.loglog(time, N_O2n, label='$O_2^-$')
# plot15, = plt.loglog(time, N_O3, label='$e^-$')
# plot16, = plt.loglog(time, N_O4p, label='$O_4^+$')
plot17, = plt.loglog(time, N_He, label='$He$')
plot18, = plt.loglog(time, N_HeEx, label='$He^*$')
plot19, = plt.loglog(time, N_Hep, label='$He^+$')
plot20, = plt.loglog(time, N_He2Ex, label='$He_2^*$')
plot21, = plt.loglog(time, N_He2p, label='$He_2^+$')
plt.xlabel('Time [s]', fontsize=14)
plt.ylabel('Density [$cm^{-3}$]', fontsize=14)
plt.legend()


plt.show()
