# PotentialGradientSource

!syntax description /Kernels/PotentialGradientSource

## Overview

`PotentialGradientSource` is a duplicate kernel of [`EFieldMagnitudeSource`](/EFieldMagnitudeSource.md).

!alert warning title=Untested Class
The PotentialGradientSource does not have a formalized test, yet. For this reason,
users should be aware of unforeseen bugs when using PotentialGradientSource. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the PotentialGradientSource object.

```text
[Kernels]
  [Source]
    type = PotentialGradientSource
    variable = source
    potential = potential
  []
[]
```

!syntax parameters /Kernels/PotentialGradientSource

!syntax inputs /Kernels/PotentialGradientSource

!syntax children /Kernels/PotentialGradientSource
