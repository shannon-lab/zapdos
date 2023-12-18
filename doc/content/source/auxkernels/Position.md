# Position

!syntax description /AuxKernels/Position

## Overview

`Position` returns the characteristic scaling length for a given direction. Zapdos
users can uniformly scale the position units for a given set of equations. This means
a user can construct a normalized mesh of some factor and scale all equations to
that same factor. `Position` is then used to plot against any spatial results.

## Example Input File Syntax

An example of how to use `Position` can be found in the
test file `Lymberopoulos_with_argon_metastables.i`.

!listing test/tests/Lymberopoulos_rf_discharge/Lymberopoulos_with_argon_metastables.i block=AuxKernels/x_g

!syntax parameters /AuxKernels/Position

!syntax inputs /AuxKernels/Position

!syntax children /AuxKernels/Position
