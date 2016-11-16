#!/bin/bash
#$ -V
#-pe mpi-8 8
#$ -N ZapdosInstall
#$ -M jhaase1@nd.edu
#$ -m ae
#$ -r y

if [ -r /opt/crc/Modules/current/init/bash ]
	then
	    source /opt/crc/Modules/current/init/bash
fi

module unload intel gcc git matlab ompi allinea
module load cmake git gcc/4.9.2 ompi/1.10.2-gcc-4.9.2 boost/1.61

source /afs/crc.nd.edu/user/j/jhaase1/Moose-dir/moose.bash

export CC=mpicc
export CXX=mpicxx
export F90=mpif90
export F77=mpif77
export FC=mpif90

make -j8

make METHOD=dbg -j8
