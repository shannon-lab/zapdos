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
import netCDF4

nc = netCDF4.Dataset('LFA_different_scaling_in.e')
all_ns = nc.variables['ns_names']
# print "The nodeset names are "
# print all_ns[:,:]
all_ss = nc.variables['ss_names']
# print "The sideset names are "
# print all_ss[:,:]
a,b = all_ns.shape
for i in range(1,a+1):
    ns = nc.variables['node_ns' + str(i)]
    ss = nc.variables['elem_ss' + str(i)]
    print "The nodeset with name %s has node number equal to %d." % (ns.name, ns[0])
    print "The sideset with name %s has node number equal to %d." % (ss.name, ss[0])
    # print ns.name
    # print ss[0]
    # print ss.name

