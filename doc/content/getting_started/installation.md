# Getting Started

## Step One: Install Conda MOOSE Environment

!style halign=left
In order to install Zapdos, the MOOSE developer environment must be installed. The
installation procedure depends on your operating system, so click on the MOOSE
website link below that corresponds to your operation system/platform and follow
the instructions to the conda installation step named "Cloning MOOSE". Then,
return to this page and continue with Step Two.

- [Linux and MacOS](https://mooseframework.inl.gov/getting_started/installation/conda.html)
- [Windows 10 (experimental)](https://mooseframework.inl.gov/getting_started/installation/windows10.html)

Advanced manual installation instructions for this environment are available
[via the MOOSE website](https://mooseframework.inl.gov/getting_started/installation/index.html).

If an error or other issue is experienced while using the conda environment,
please see [the MOOSE troubleshooting guide for Conda](https://mooseframework.inl.gov/help/troubleshooting.html#condaissues)

## Step Two: Clone Zapdos

!style halign=left
Zapdos is hosted on [GitHub](https://github.com/shannon-lab/zapdos), and should
be cloned directly from there using [git](https://git-scm.com/). As in the MOOSE
directions, it is recommended that users create a directory named "projects" to
put all of your MOOSE-related work.

To clone Zapdos, run the following commands in Terminal:

```bash
mkdir ~/projects
cd ~/projects
git clone https://github.com/shannon-lab/zapdos.git
cd zapdos
git checkout master
```

## Step Three: Build and Test Zapdos

!style halign=left
To compile Zapdos, first make sure that the conda MOOSE environment is activated
(*and be sure to do this any time that a new Terminal window is opened*):

```bash
conda activate moose
```

Then navigate to the Zapdos clone directory and download the MOOSE submodule:

```bash
cd ~/projects/zapdos
git submodule update --init squirrel crane moose
```

!alert note
The copy of MOOSE provided with Zapdos has been fully tested against the current
Zapdos version, and is guaranteed to work with all current Zapdos tests.

Once all dependencies have been downloaded, Zapdos can be compiled and tested:

```bash
make -j8
./run_tests -j8
```

If Zapdos is working correctly, all active tests will pass. This indicates that
Zapdos is ready to be used and further developed.

## Running an Input File and Viewing Results

!style halign=left
After testng is complete, you should now be able to run input files using the
`zapdos-opt` executable located at `~/projects/zapdos`. Input files demonstrating
the capabilities of Zapdos can be found in `~/projects/zapdos/examples` and
`~/projects/zapdos/tests`. Any input file (say, one called `example_input.i`)
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

Many test input files also create an output file with the format
`example_input_out.e` that contains all the simulation results that have been
selected for output. These results are best viewed using a visualization tool
like [Paraview](http://www.paraview.org/download/).

## Zapdos Examples and Tests

!style halign=left
In general the `examples` directory is meant to be a showcase of "production"
Zapdos capability. Users are encouraged to start there when learning Zapdos and
setting up new simulations. The `test/tests` directory, on the other hand, holds
*all* Zapdos regression, verification, and validation tests for both complete and
in-progress capability. These files *should not* be modified, so that periodic
tests of Zapdos function can be performed successfully.

As Zapdos is developed (by you hopefully!) and more capabilities are added, the
tests directory will continue to grow. If you feel that you have added important
new functionality, please create a test for it, such that any future changes
will not break that capability.

## Troubleshooting

!style halign=left
If issues are experienced in installation, testing, and usage, several resources
are available:

- [Zapdos Discussion Forum](https://github.com/shannon-lab/zapdos/discussions)
- [MOOSE FAQ page for common MOOSE issues](https://mooseframework.inl.gov/help/faq/index.html)
- [MOOSE Discussion Forum](https://github.com/idaholab/moose/discussions)
