# Getting Started

## Install and Test MOOSE

First you will need to install the MOOSE Environment. To do this, proceed to the
[MOOSE Getting Started pages](https://mooseframework.inl.gov/getting_started/index.html). After
successfully obtaining a working MOOSE Environment, return to this page
to continue.

!alert note
These instructions will assume that you are working in the `~/projects` directory, which is
consistent with the MOOSE installation instructions.

## Build and Test Zapdos

To download Zapdos, do the following:

```bash
cd ~/projects
git clone https://github.com/shannon-lab/zapdos
```

Note that Zapdos can be used with MOOSE installed in its own directory, or as a submodule within
Zapdos. The latter option allows for a version of MOOSE that is guaranteed to work with the current
version of Zapdos. Instructions for each option is provided below.

### Using MOOSE as a Zapdos submodule

To use MOOSE as a Zapdos submodule, do the following:

```bash
cd zapdos
git submodule init
git submodule update
cd moose
scripts/update_and_rebuild_libmesh.sh
cd test
make -j4
./run_tests -j4
```

!alert note
You can replace `-j4` with `-j` plus the number of cores your computer has available for faster
build performance.

Make sure all active MOOSE submodule tests pass. To build and test Zapdos:

```bash
cd ~/projects/zapdos
make -j4
./run_tests -j4
```

If Zapdos is working correctly, all active tests will pass. This indicates that Zapdos is ready to
be used and further developed.

### Using MOOSE in its own directory

To use MOOSE in its own directory:

```bash
cd ~/projects
git clone https://github.com/idaholab/moose
cd moose
scripts/update_and_rebuild_libmesh.sh
cd test
make -j4
./run_tests -j4
```

After all active MOOSE tests pass, you can proceed to build and test Zapdos:

```bash
cd zapdos
git submodule init squirrel crane
git submodule update squirrel crane
make -j4
./run_tests -j4
```

If Zapdos is working correctly, all active tests will pass. This indicates that Zapdos is ready to
be used and further developed.

## How to Proceed

After testng is complete, you should now be able to run input files using the `zapdos-opt`
executable in the `~/projects/zapdos` directory. Input files demonstrating the capabilities of
Zapdos can be found in the sub-directories of `~/projects/zapdos/tests`. If you want to start
modifying an input file, a good one to choose is `mean_en.i` in `~/projects/zapdos/problems`. A
typical command to run a Zapdos input file is as follows:

```bash
cd ~/projects/zapdos/problems
../zapdos-opt -i mean_en.i --color off 2>&1 | tee log.txt
```

The above command will parse information of the iterative solution process to both the console and
to the log file `log.txt`. It will also create an output file named `mean_en_out.e` containing all
the solution variable values. These results are best viewed using a visualization tool like
*Paraview*, downloadable [here](http://www.paraview.org/download/).

!alert note
Many of the existing input files in the `problems` directory require `fileName.msh`. In order to
create the requisite `.msh` file, you must run the command `gmsh -d fileName.geo` where `d` is the
dimensionality (1, 2, or 3) of the mesh and `fileName.geo` is the source file for the mesh. `gmsh`
can be downloaded [here](http://gmsh.info/#Download). Some of the `*.msh` files can also be found
in the `tests` directory.

In general the `problems` directory is meant to be the user work-space. S/he should feel welcome to
modify any files in that directory. The `tests` directory, on the other hand, is meant to be a
showcase and provide examples of the capabilities already established in Zapdos. As Zapdos is
developed (by you hopefully!) and more capabilities are added, the tests directory will continue to
grow. If you feel that you have added important new functionality, please create a test for it, such
that any future changes will not break that capability.

## Troubleshooting

Please see the [MOOSE FAQ page](https://www.mooseframework.org/help/faq.html) for general
troubleshooting information for the framework. If your issue is not listed among the FAQs, please
refer to the [Zapdos Mailing List](https://groups.google.com/forum/#!forum/zapdos-users) or the
[MOOSE Mailing List](https://groups.google.com/forum/#!forum/moose-users).
