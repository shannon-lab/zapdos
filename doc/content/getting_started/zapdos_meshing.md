# Meshing with Zapdos

When generating a mesh for a Zapdos input file, the user has several options used
regularly by Zapdos developers:

- The MOOSE [syntax/Mesh/index.md], specifically the [MeshGenerator.md] system.
- [Gmsh](https://gmsh.info/)
- [CUBIT](https://cubit.sandia.gov/), managed by [Sandia National Laboratories](https://www.sandia.gov)
  (requires a US Government contract or affiliation).

  - A commercial/academic version of CUBIT, called [Coreform Cubit](https://www.coreform.com/products/coreform-cubit/)
    is also available for a paid license (Cubit Learn is free for academic use
    for one year, with a 50,000 element export limit in a single mesh).

As CUBIT usage is well-documented elsewhere (and isn't open source software), only
the first two options will be covered here.

## MOOSE MeshGenerator

The MOOSE [MeshGenerator.md] system is designed to build flexible and arbitrary
meshes in stages. See an example of a `MeshGenerator` mesh block below:

!listing moose/test/tests/meshgenerators/sidesets_between_subdomains_generator/sideset_between_subdomains.i block=Mesh

This block first creates a 3D cube in `gmg` using [GeneratedMeshGenerator.md],
then feeds that resulting mesh into `central_block` using the `input` parameter.
[SubdomainBoundingBoxGenerator.md] creates rectangular subdomains defined by their
bottom leftmost point and their top rightmost point and allows the user to define a
`block_id` identifier for the block (in this case, 2). This output is sent to
`central_boundary`, which uses [SideSetsBetweenSubdomainsGenerator.md] to define
an interface between the default block created by `gmg` (block 0), and the new
block created by `central_block` (block 2). The new interface boundary is given
it's own ID, 7.

The [MeshGenerator.md] system generates a mesh "online", meaning at the beginning
of a Zapdos/MOOSE simulation. An "offline" mesh is one that is generated elsewhere
using a tool (or the `--mesh-only` flag when running a Zapdos input file on the
command line) and imported into Zapdos using [FileMeshGenerator.md].

## Gmsh

!style halign=left
[Gmsh](https://gmsh.info) is an open source 3D finite element mesh generator.
Many of the existing input files in the Zapdos `test/tests` directory require a
mesh file of the format `fileName.msh`. An example of this is shown below:

!listing test/tests/Lymberopoulos_rf_discharge/Lymberopoulos_with_argon_metastables.i block=Mesh/file

In order to create the requisite `.msh` file, you must run first download and
install Gmsh on your computer. On the command line (first make sure that gmsh is
in your system `PATH`), run the command `gmsh -d fileName.geo` where `d` is the
dimensionality (1, 2, or 3) of the mesh and `fileName.geo` is the source file
for the mesh. `gmsh` can be downloaded [here](http://gmsh.info/#Download).
Examples of `.msh` and `.geo` files can also be found in the `test/tests`
subdirectories.
