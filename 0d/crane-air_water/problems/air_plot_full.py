import numpy as np
import matplotlib.pylab as plt
import csv
import pandas as pd

# Output CSV file name
#file = 'air_chemistry_full_out.csv'
#file = 'air_chemistry_full_out_02.csv'
file = 'air_chemistry_full_test.csv'

species = ['N',    'N+',     'N2',    'N2+',     'N2A3',
           'N2B3', 'N2C3',   'N2D',   'N2P',     'N2a_1',
           'N2v1', 'N2v2',   'N2v3',  'N2v4',    'N2v5', 
           'N2v6', 'N2v7',   'N2v8',  'N3+',     'N4+',
           'NO',   'NO+',    'NO-',   'O',       'O+',
           'O-',   'O1D',    'O1S',   'O2',      'O2+',
           'O2-',  'O24_ev', 'O2a1',  'O2b1',    'O2v1',
           'O2v2', 'O2v3',   'O2v4',  'O3',      'O3-',
           'O4+',  'O4-',    'O2pN2', 'N2O',     'NO2',
           'NO3',  'N2O5',   'N2O+',  'NO2+',    'N2O-',
           'NO2-', 'NO3-',   'e']

nn =      [1.,       1.,        2.,       2.,         2.,
           2.,       2.,        1.,       1.,         2.,
           2.,       2.,        2.,       2.,         2.,
           2.,       2.,        2.,       3.,         4.,
           2.,       2.,        2.,       1.,         1.,
           1.,       1.,        1.,       2.,         2.,
           2.,       2.,        2.,       2.,         2.,
           2.,       2.,        2.,       3.,         3.,
           4.,       4.,        4.,       3.,         3.,
           4.,       7.,        3.,       3.,         3.,
           3.,       4.,        1.]
#plot_species = ['O3','O','NO','O2a1','N2A3','N','O2b1','O1S']
#plot_species = ['e', 'N', 'O', 'N+', 'O+']
#plot_species = ['e', 'O3-', 'N+', 'NO-', 'O3']
#plot_species = ['NO', 'NO+', 'NO-', 'O', 'O+', 'O1D']
#plot_species = ['NO-']
#plot_species = np.copy(species)
plot_species = ['N2v1', 'N2v2', 'N2v3', 'N2v4', 'N2v5', 'N2v6', 'N2v7', 'N2v8']
#plot_species = ['Te']
#plot_species = ['reduced_field']
#plot_species = ['voltage']
#plot_species = ['e']
#plot_species = ['N2', 'NEUTRAL']
#plot_species = ['N+']
#plot_species = ['e', 'N2', 'N2v1']
#plot_species = ['N2O', 'NO2', 'NO3', 'N2O5', 'N2O+', 'NO2+', 'N2O-', 'NO2-', 'NO3-', 'e']


#plot_species = ['e', 'N', 'N2', 'N+', 'N2+', 'NO', 'NO+', 'NO-']
#plot_species = ['e']
#plot_species = ['e', 'N4+', 'NO', 'NO+', 'NO-', 'O', 'O+', 'O-', 'O1D']

test = pd.read_csv(file)
#test2 = pd.read_csv(file2)

pos = test['N+'] + test['N2+'] + test['N3+'] + test['N4+'] + test['O+'] + test['O2+'] + test['O4+'] + test['NO+'] + test['O2pN2'] + test['N2O+'] + test['NO2+'] 
neg = test['O-'] + test['O2-'] + test['O3-'] + test['O4-'] + test['NO-'] + test['NO2-'] + test['N2O-'] + test['NO3-'] 
#s = np.zeros(shape=(len(test['time'])))
#for i in range(len(species)-1):
#    s[:] += test[species[i]] * nn[i]
#plt.plot(test['time'], s)
#plt.show()
#exit()

NUM_COLORS = len(plot_species)
#LINE_STYLES = ['solid', 'dashed', 'dashdot', 'dotted']
LINE_STYLES = ['solid', 'dashdot']
LINE_STYLES2 = ['dashed', 'dotted']
NUM_STYLES = len(LINE_STYLES)
cm = plt.get_cmap('brg')
fig = plt.figure(figsize=(12,10))
ax = fig.add_subplot(111)
stoptime = -1
#stoptime = len(test['N+'])/2

#ax.plot(test['time'], pos, label='positive')
#ax.plot(test['time'], neg + test['e'], '--', label='negative')
#plt.legend()
#plt.show()
#exit()

def find_times(t,recurrence_time):
    for i in range(len(t)):
        if (t[i]>=recurrence_time):
            break
    return(i)


#cycle_index = find_times(test['time'], 1e-4)
#num_cycles = 6
##df = test['e'].rename_axis('ID').values
#df = test['reduced_field'].rename_axis('ID').values
#for i in range(num_cycles-1):
#    t1 = cycle_index*i
#    t2 = cycle_index*(i+1)
#    t3 = cycle_index*(i+2)
#    cycle1 = df[t1:t2]
#    cycle2 = df[t2:t3]
#    #plt.semilogy(test['time'][t1:t2],cycle1, '.')
#    #plt.semilogy(test['time'][t1:t2],cycle2, '.--')
#    lines = plt.semilogy(abs(cycle2-cycle1), label=str(i))
#    lines[0].set_color(cm(i//NUM_STYLES*float(NUM_STYLES)/6))
#    lines[0].set_linestyle(LINE_STYLES[i%NUM_STYLES])
#plt.legend()
#plt.show()
#exit()

#ax.plot(test['time'], test['e']/np.linalg.norm(test['e']), 'o', label='e')
#ax.plot(test['time'], test['voltage']/np.linalg.norm(test['voltage']), label='V')
#ax.plot(test['time'], test['reduced_field']/np.linalg.norm(test['reduced_field']), 'o', label='V')
#plt.legend()
#plt.show()
#exit()
for i in range(len(plot_species)):
    #loc = np.where(test[plot_species[i]] <= 0)[0]
    #print(test[plot_species[i]][loc]) 

    #ax.semilogy(test['time'], pos, label='positive')
    #ax.semilogy(test['time'], neg + test['e'], label='negative')
    #lines = ax.plot(test['time'], test['ION'] + test['NEUTRAL'] + test['e'], label='all')
    #lines = ax.plot(test['time'], pos - (neg + test['e']), label='all')
    #lines = ax.plot(test['time'][1:stoptime], test[plot_species[i]][1:stoptime]/np.linalg.norm(test[plot_species[i]][1:stoptime]), label=plot_species[i])

    lines = ax.semilogy(test['time'][1:stoptime], test[plot_species[i]][1:stoptime], label=plot_species[i])
    #lines = ax.semilogy(test['time'][1:stoptime], np.exp(test[plot_species[i]][1:stoptime]), label=plot_species[i])
    #lines = ax.semilogy(np.exp(test[plot_species[i]][1:stoptime]), label=plot_species[i])

    #lines = ax.plot(test['time'][1:stoptime], test[plot_species[i]][1:stoptime], label=plot_species[i])
    lines[0].set_color(cm(i//NUM_STYLES*float(NUM_STYLES)/NUM_COLORS))
    lines[0].set_linestyle(LINE_STYLES[i%NUM_STYLES])

    #lines2 = ax.semilogy(test2['time'][1:stoptime2], test2[plot_species[i]][1:stoptime2]) 
    #lines2[0].set_color(cm(i//NUM_STYLES*float(NUM_STYLES)/NUM_COLORS))
    #lines2[0].set_linestyle(LINE_STYLES2[i%NUM_STYLES])
plt.legend(ncol=4)
#plt.axis([1e-9, 1e4, 1e8, 1e19])
axis = plt.gca()
#axis.set_ylim([-1e-4, 1e-4])
plt.show()
plt.xlabel('Time [s]', fontsize=14)
#plt.ylabel('kV', fontsize=14)
#plt.ylabel('Density [cm$^{-3}$]')
#plt.savefig('air_voltage_plot.png', dpi=200, bbox_inches='tight')
#plt.close()

exit()
