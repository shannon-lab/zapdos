import numpy as np
import matplotlib.pylab as plt
import csv
import pandas as pd


file = 'air_water_chemistry_vib_test.csv'

test = pd.read_csv(file)

nitrogen = ['N',    'N+',     'N2',    'N2+',     'N2A3',
           'N2B3', 'N2C3',   'N2D',   'N2P',     'N2a_1',
           'N2v1', 'N2v2',   'N2v3',  'N2v4',    'N2v5', 
           'N2v6', 'N2v7',   'N2v8',  'N3+',     'N4+', 'e']
oxygen = ['O',       'O+',
           'O-',   'O1D',    'O1S',   'O2',      'O2+',
           'O2-',  'O24_ev', 'O2a1',  'O2b1',    'O2v1',
           'O2v2', 'O2v3',   'O2v4',  'O3',      'O3-',
           'O4+',  'O4-', 'e']
nxoy = ['NO',   'NO+',    'NO-', 'O2pN2', 'N2O',     'NO2',
           'NO3',  'N2O5',   'N2O+',  'NO2+',    'N2O-',
           'NO2-', 'NO3-', 'e']
hydrogen = ['H+',      'H2+',
           'H3+',  'OH+',    'H2O+',  'H3O+',    'H-',
           'OH-',  'H',      'H2',    'OH',      'HO2',
           'H2O2', 'HNO',    'HNO2',  'HNO3',    'H2O', 'e']

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
           'NO2-', 'NO3-',   'e',     'H+',      'H2+',
           'H3+',  'OH+',    'H2O+',  'H3O+',    'H-',
           'OH-',  'H',      'H2',    'OH',      'HO2',
           'H2O2', 'HNO',    'HNO2',  'HNO3',    'H2O']

#NUM_COLORS = len(plot_species)
#LINE_STYLES = ['solid', 'dashed', 'dashdot', 'dotted']

#LINE_STYLES = ['solid', 'dashdot']
#LINE_STYLES2 = ['dashed', 'dotted']
#NUM_STYLES = len(LINE_STYLES)
cm = plt.get_cmap('brg')
#fig = plt.figure(figsize=(12,10))
#ax = fig.add_subplot(221)
fig, axs = plt.subplots(2, 2, figsize=(18,15))
stoptime = -1
#stoptime = len(test['N+'])/2

def find_times(t,recurrence_time):
    for i in range(len(t)):
        if (t[i]>=recurrence_time):
            break
    return(i)

def define_colors(names):
    NUM_COLORS = len(names)
    #LINE_STYLES = ['solid', 'dashed', 'dashdot', 'dotted']
    LINE_STYLES = ['solid', 'dashdot']
    #LINE_STYLES2 = ['dashed', 'dotted']
    NUM_STYLES = len(LINE_STYLES)
    return(LINE_STYLES,NUM_STYLES,NUM_COLORS)


def species_plot(data, species, ax, plot_type):
    line_types, styles, colors = define_colors(species)
    for i in range(len(species)):
        if (plot_type == 'semilogy'):
            lines = ax.semilogy(data['time'], data[species[i]] , label=species[i])

        elif (plot_type == 'plot'):
            lines = ax.plot(data['time'], data[species[i]] , label=species[i])
        elif (plot_type == 'loglog'):
            lines = ax.loglog(data['time'], data[species[i]] , label=species[i])

        lines[0].set_color(cm(i//styles*float(styles)/colors))
        lines[0].set_linestyle(line_types[i%styles])
    ax.legend(loc='best', ncol=4)

plot_type = 'semilogy'
#plot_type = 'plot'
#plot_type= 'loglog'

species_plot(test, nitrogen, axs[0, 0], plot_type)
species_plot(test, oxygen, axs[0, 1], plot_type)
species_plot(test, nxoy, axs[1, 0], plot_type)
species_plot(test, hydrogen, axs[1, 1], plot_type)

#plt.legend(ncol=4)
axis = plt.gca()
#axis.set_ylim([-1e-4, 1e-4])
plt.xlabel('Time [s]', fontsize=14)
#plt.ylabel('kV', fontsize=14)
#plt.ylabel('Density [cm$^{-3}$]')
plt.savefig('subplot_test.png', dpi=300, bbox_inches='tight')
plt.close()
#plt.show()
exit()
