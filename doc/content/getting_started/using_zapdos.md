# Using Zapdos

## Running an Input File and Viewing Results

!style halign=left
After Zapdos is installed and tested, you should now be able to run input files
using the `zapdos-opt` executable located at `~/projects/zapdos`. Input files
demonstrating the capabilities of Zapdos can be found in `~/projects/zapdos/tutorial`
and `~/projects/zapdos/tests`. Any input file (say, one called `example_input.i`)
can be run with the following basic syntax:

```bash
~/projects/zapdos/zapdos-opt -i example_input.i
```

Information about the simulation and its progress will then be displayed on the
screen. If a log file of the iterative solution process is also desired, the
console output can be sent to a text file:

```bash
~/projects/zapdos/zapdos-opt -i example_input.i --color off 2>&1 | tee log.txt
```

!alert note
The `--color off` option is to de-clutter the log file from extraneous
mark-up resulting from the displayed console text colors.

For parallelism, users can use the Message Passing Interface protocol (MPI). The 
[MPICH](https://www.mpich.org/) implementation of MPI is provided with the MOOSE 
environment packages. A parallel simulation using 4 processors can be run with the 
following basic syntax:

```bash
mpiexec -n 4 ~/projects/zapdos/zapdos-opt -i example_input.i
```

Many test input files also create an output file with the name format
`example_input_out.e` that contains all the simulation results that have been
selected for output. These results are best viewed using a visualization tool
like [Paraview](http://www.paraview.org/download/).

## Zapdos Tutorial and Tests

!style halign=left
In general the `tutorial` directory is meant to be a showcase of "production"
Zapdos capability. Users are encouraged to start there when learning Zapdos and
setting up new simulations. The `test/tests` directory, on the other hand, holds
*all* Zapdos regression, verification, and validation tests for both complete and
in-progress capability. These files *should not* be modified, so that periodic
tests of Zapdos function can be performed successfully.

As Zapdos is developed (by you hopefully!) and more capabilities are added, the
tests directory will continue to grow. If you feel that you have added important
new functionality, please create a test for it, such that any future changes
will not break that capability.
