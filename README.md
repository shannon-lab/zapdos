[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.801834.svg)](https://doi.org/10.5281/zenodo.801834)

# Zapdos

Free (in all senses of the word) and open source software for modeling plasmas using finite elements. This application is built on top of [the MOOSE Framework](https://mooseframework.inl.gov).

## Documentation

There are three main pieces of file-based documentation for Zapdos, all located in the `doc` directory:

- `Zapdos_Tutorial.pdf` - A general tutorial of Zapdos capabilities, with explanations of the finite element method, code and input file structure, the Peacock GUI (from MOOSE), and examples of usage.
- `Chemical_Reactions.ipynb` - A Jupiter notebook containing notes on understanding existing chemistry kernels and/or implementing new ones in Zapdos/MOOSE.
- `Lindsay_thesis_coupling_of_plasmas_and_liquids.pdf` - Chapter 3 of the original PhD dissertation introducing Zapdos ("Coupling of Plasmas and Liquids" by Alex Lindsay).

Alternatively, there are two websites available:

- [https://mooseframework.inl.gov](https://mooseframework.inl.gov) - for information on the underpinnings of Zapdos and other available resources from MOOSE.
- [https://shannon-lab.github.io/zapdos](https://shannon-lab.github.io/zapdos) - for source code documentation and general info (UNDER CONSTRUCTION, last updated: Oct 2019)

## Step-by-step instructions for installing Zapdos

1. Follow the [MOOSE getting started instructions](https://mooseframework.inl.gov/getting_started/installation/index.html) for setting up the MOOSE environment.
3. Choose a directory (we recommend creating one named `projects` in the user home directory) to hold Zapdos and clone this repository by running the command:
   * `git clone https://github.com/shannon-lab/zapdos`
4. Download CRANE, MOOSE, and squirrel. These dependencies are contained with Zapdos as submodules, set to a particular version (git commit hash) that has been tested successfully on Linux and Mac against the current version of Zapdos. To download, navigate to the `zapdos` directory and run the following commands in the terminal:
   * `git submodule init`
   * `git submodule update`
5. Build and test MOOSE. To do this, run the following commands in the `zapdos` directory:
   * `cd moose/test`
   * `make -j4` where `4` could be changed to represent the number of logical processors on your computer
   * `./run_tests -j4`
   * If any tests fail, check [the MOOSE troubleshooting page for failing test issues](https://mooseframework.inl.gov/help/troubleshooting.html#failingtests).
6. Build and test Zapdos. To do this, run the following commands in the `zapdos` directory:
   * `make -j4`
   * `./run_tests -j4`

If all tests pass, you should now be able to run input files using the `zapdos-opt` executable found in the `zapdos` directory. Input files demonstrating the capabilities of zapdos can be found in the `tests` directory. If you want to start modifying an input file, it is recommended that you first copy this file to a "workspace" directory so that the original test is not modified unintentionally.

Again, the `tests` directory is meant to be a showcase and provide examples of the capabilities already established in Zapdos. As Zapdos is developed (by you hopefully!) and more capabilities are added, the tests directory will continue to grow. If you feel that you have added important new functionality, please create a test for it, such that any future changes will not break that capability.

## Example of running a Zapdos input file

A good input file to start with is located at `zapdos/tests/1d_dc/mean_en.i`. An input file like `mean_en.i` can be run using the following commands. **Note:** It is assumed here that Zapdos has been placed within the `~/projects` directory and that `mean_en.i` and `liquidNew.msh` (the mesh file required to run `mean_en.i`) has been copied to a user-created workspace directory located at `~/projects/zapdos/workspace`.
 * `cd ~/projects/zapdos/workspace`
 * `../zapdos-opt -i mean_en.i --color off 2>&1 | tee log.txt`
   * The above command will parse information of the iterative solution process to both the console and to the log file `log.txt`
   * The above command will also create an output file named `mean_en_out.e` containing all the solution variable values. These results are best viewed using a visualization tool like **Paraview**, downloadable [here](http://www.paraview.org/download/).

## Meshing

Meshing in Zapdos can be performed using the internal MOOSE [Mesh system](https://mooseframework.inl.gov/syntax/Mesh/index.html) or through external tools, such as [gmsh](http://gmsh.info). Many of the existing input files in the `tests` subdirectories use gmsh and require a `.msh` file to operate (example: `liquidNew.msh` for `mean_en.i`). These should exist alongside the gmsh program file that created them (`.geo` files).

In order to create the requisite `.msh` file yourself, you must run the command `gmsh -d fileName.geo` where `d` is the dimension of the mesh and `fileName.geo` is the source file for the mesh. gmsh can be installed for Linux and Mac via download [here](http://gmsh.info/#Download).

## Questions? Issues? Want to Contribute?

Please do not hesitate to contact the [Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions) if you have any questions about using or contributing to this software.
