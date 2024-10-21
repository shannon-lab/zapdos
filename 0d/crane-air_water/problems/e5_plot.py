import numpy as np
import matplotlib.pylab as plt

# Output CSV file name
# file = 'example5_scale_out.csv'
file = 'e5_out.csv'
file2 = 'e5_track_out.csv'
file3 = 'e4_out.csv'

data = np.genfromtxt(file, dtype=float, delimiter=',', skip_header=1)
data2 = np.genfromtxt(file2, dtype=float, delimiter=',', skip_header=1)
data3 = np.genfromtxt(file3, dtype=float, delimiter=',', skip_header=1)
names =['Ar','Ar+','Production2','Production0','Production3','e'] 
names2 =['Ar','Ar+','e','Ar+ and e Production rate','Ar+ + e Recombination rate','test 1-Body Production rate'] 
names3 =['N','N+','N2','N2+','N2A','N2B','N2C','N2a1','N3+','N4+','Te','Teff','e','rate0','rate1','rate10','rate11','rate12','rate13','rate14','rate15','rate16','rate17','rate18','rate19','rate2','rate20','rate21','rate22','rate23','rate24','rate25','rate26','rate27','rate28','rate29','rate3','rate30','rate31','rate32','rate33','rate4','rate5','rate6','rate7','rate8','rate9']
print(data3)

for i in range(len(names)):
    plt.semilogy(data[:,0], data[:,i+1],label='%s'%names[i])
plt.gca().set_prop_cycle(None)

plt.xlabel('Time [s]', fontsize=14)
plt.ylabel('Number Density, [$cm^{-3}$]', fontsize=14)
plt.legend()
plt.figure(2)
for i in range(len(names2)):
    plt.semilogy(data2[:,0], data2[:,i+1],'--',label='%s'%names2[i])
plt.legend()

plt.xlabel('Time [s]', fontsize=14)
plt.ylabel('Number Density, [$cm^{-3}$]', fontsize=14)
j = names3.index('rate0')
plt.figure(3)
for i in range(j):
    plt.semilogy(data3[:,0], data3[:,i+1],label='%s'%names3[i])

plt.xlabel('Time [s]', fontsize=14)
plt.ylabel('Number Density, [$cm^{-3}$]', fontsize=14)
plt.legend()

plt.figure(4)
for i in range(j,len(names3)):
    plt.semilogy(data3[:,0], data3[:,i+1],'--',label='%s'%names3[i])
plt.title('Rates')
plt.xlabel('Time [s]', fontsize=14)
plt.ylabel('Number Density, [$cm^{-3}$]', fontsize=14)


plt.legend()
plt.show()
