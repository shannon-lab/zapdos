import matplotlib.pylab as plt
from matplotlib.patches import Rectangle
import numpy as np
import csv

file = 'example4_out.csv'
file2 = '/Users/keniley/Documents/LCPP_Atmos/example3/out.dat'

data = np.genfromtxt(file, dtype=float, delimiter=',', skip_header=1)
data2 = np.genfromtxt(file2, dtype=float, delimiter='   ', skip_header=1)
# time,N,N+,N2,N2+,N2A,N2B,N2C,N3+,N4+,e,reduced_field
time = data[:,0]
N_N = data[:,1]
N_Ni = data[:,2]
N_N2 = data[:,3]
N_N2i = data[:,4]
N_N2A = data[:,5]
N_N2B = data[:,6]
N_N2C = data[:,7]
N_N3i = data[:,8]
N_N4i = data[:,10]
N_e = data[:,10]
EN = data[:,11]

# ZDPlasKin Data
time_2 = data2[:,0]
N_N_2 = data2[:,3]
N_Ni_2 = data2[:,9]
N_N2_2 = data2[:,4]
N_N2i_2 = data2[:,10]
N_N2A_2 = data2[:,5]
N_N2B_2 = data2[:,6]
N_N2C_2 = data2[:,8]
N_N3i_2 = data2[:,11]
N_N4i_2 = data2[:,12]

fig = plt.figure(figsize=(8,8))
ax = plt.subplot(111)
# ax.semilogy(time, N_N, 'g', label='$N$', alpha=0.7)
# ax.semilogy(time_2, N_N_2, 'g--', label='$N$', alpha=0.7)
#
# ax.semilogy(time, N_N2A, 'b', label='$N2(A)$', alpha=0.7)
# ax.semilogy(time_2, N_N2A_2, 'b--', label='$N2(A)$', alpha=0.7)
#
# ax.semilogy(time, N_N2C, 'r', label='$N2(C)$', alpha=0.7)
# ax.semilogy(time_2, N_N2C_2, 'r--', label='$N2(C)$', alpha=0.7)
#
# ax.semilogy(time, N_N2i, 'c', label='$N_2^+$', alpha=0.7)
# ax.semilogy(time_2, N_N2i_2, 'c--', label='$N_2^+$', alpha=0.7)
#
# ax.semilogy(time, N_N4i, 'k', label='$N_4^+$', alpha=0.7)
# ax.semilogy(time_2, N_N4i_2, 'k--', label='$N_4^+$', alpha=0.7)
plot11, = ax.semilogy(time, N_N, 'g-', label='N', alpha=0.7)
plot12, = ax.semilogy(time, N_N2A, 'b-', label='N$_2$(A)', alpha=0.7)
plot13, = ax.semilogy(time, N_N2C, 'r-', label='N$_2$(C)', alpha=0.7)
plot14, = ax.semilogy(time, N_N2i, 'c-', label='N$_2^+$', alpha=0.7)
plot15, = ax.semilogy(time, N_N4i, 'k-', label='N$_4^+$', alpha=0.7)
# plot21, = ax.semilogy(time_2, N_N_2, 'g--', label='N', alpha=0.7)
# plot22, = ax.semilogy(time_2, N_N2A_2, 'b--', label='N$_2$(A)', alpha=0.7)
# plot23, = ax.semilogy(time_2, N_N2C_2, 'r--', label='N$_2$(C)', alpha=0.7)
# plot24, = ax.semilogy(time_2, N_N2i_2, 'c--', label='N$_2^+$', alpha=0.7)
# plot25, = ax.semilogy(time_2, N_N4i_2, 'k--', label='N$_4^+$', alpha=0.7)
handles, labels = ax.get_legend_handles_labels()
# plot11, = ax.plot(time_2[2::], (N_N[3::] - N_N_2[2::])/N_N_2[2::], 'g', label='$N$', alpha=0.7)
# plot12, = ax.plot(time_2[2::], (N_N2A[3::] - N_N2A_2[2::])/N_N2A_2[2::], 'b', label='$N2(A)$', alpha=0.7)
# plot13, = ax.plot(time_2[2::], (N_N2C[3::] - N_N2C_2[2::])/N_N2C_2[2::], 'r', label='$N2(C)$', alpha=0.7)
# plot14, = ax.plot(time_2[2::], (N_N2i[3::] - N_N2i_2[2::])/N_N2i_2[2::], 'c', label='$N_2^+$', alpha=0.7)
# plot15, = ax.plot(time_2[2::], (N_N4i[3::] - N_N4i_2[2::])/N_N4i_2[2::], 'k', label='$N_4^+$', alpha=0.7)
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.1,
                 box.width, box.height * 0.9])
# plt.legend()
plt.legend(loc='upper center', bbox_to_anchor=(0.5, 1.0), shadow=True, ncol=5)
# extra = Rectangle((0,0), 1,1, fc="w", fill=False, edgecolor='none', linewidth=0)
# extra2 = Rectangle((0,0), 1,1, fc="w", fill=False, edgecolor='none', linewidth=0)
# plt.legend([extra, extra2, plot11, plot21, plot12, plot22, plot13, plot23, plot14, plot24, plot15, plot25], ("CRANE:", "ZDPlasKin:", labels[0], labels[5], labels[1], labels[6], labels[2], labels[7], labels[3], labels[8], labels[4], labels[9]), ncol=6)
plt.axis([0, 2.5e-3, 10**4, 10**15])
# plt.axis([0, 2.5e-3, 0, 0.4*10**14])
# plt.axis([-1.5e-5, 2.2e-4, -1.44e10, 1.5e11])
plt.xlabel('Time [s]', fontsize=14)
plt.ylabel('Density [cm$^{-3}$]', fontsize=14)
plt.tick_params(axis='both', labelsize=11)
# plt.savefig('cpc_files/zdplaskin_comp_ex3.pdf', dpi=300, bbox_inches='tight')
# plt.close()
plt.show()
