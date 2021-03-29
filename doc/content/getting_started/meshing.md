# Meshing with Zapdos

Many of the existing input files in the `problems` directory require `fileName.msh`. In order to
create the requisite `.msh` file, you must run the command `gmsh -d fileName.geo` where `d` is the
dimensionality (1, 2, or 3) of the mesh and `fileName.geo` is the source file for the mesh. `gmsh`
can be downloaded [here](http://gmsh.info/#Download). Some of the `*.msh` files can also be found
in the `tests` directory.
