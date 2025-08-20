# DGCoeffDiffusion

!syntax description /DGKernels/DGCoeffDiffusion

## Overview

`DGCoeffDiffusion` is a version of [CoeffDiffusion.md] that uses the discontinous Galerkin method.

For more information about the discontinuous Galerkin method within MOOSE, please see [DGKernels syntax page](syntax/DGKernels/index.md).

!alert! warning title=Untested Class
The `DGCoeffDiffusion` object does not have a formalized test, yet. For this reason,
users should beware of unforeseen bugs when using `DGCoeffDiffusion`. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards on how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).
!alert-end!

## Example Input File Syntax

```text
[DGKernels]
  [em_dg_diffusion]
    type = DGCoeffDiffusion
    variable = em
    epsilon = -1
    sigma = 6
  []
[]
```

!syntax parameters /DGKernels/DGCoeffDiffusion

!syntax inputs /DGKernels/DGCoeffDiffusion

!syntax children /DGKernels/DGCoeffDiffusion
