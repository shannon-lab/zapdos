# DGEFieldAdvection

!syntax description /DGKernels/DGEFieldAdvection

## Overview

`DGEFieldAdvection` is a version of [EFieldAdvection.md] that uses the discontinous Galerkin method.

For more information about the discontinuous Galerkin method within MOOSE, please see [DGKernels syntax page](syntax/DGKernels/index.md).

!alert! warning title=Untested Class
The `DGEFieldAdvection` object does not have a formalized test, yet. For this reason,
users should beware of unforeseen bugs when using `DGEFieldAdvection`. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards on how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).
!alert-end!

## Example Input File Syntax

```text
[DGKernels]
  [em_dg_advection]
    type = DGEFieldAdvection
    variable = em
    field_property_name = efield_plasma
    neighbor_field_property_name = efield_water
  []
[]
```

!syntax parameters /DGKernels/DGEFieldAdvection

!syntax inputs /DGKernels/DGEFieldAdvection

!syntax children /DGKernels/DGEFieldAdvection
