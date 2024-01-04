# DensityNormalization

!syntax description /AuxKernels/DensityNormalization

## Overview

`DensityNormalization` is similar to [`NormalizationAux`](/auxkernels/NormalizationAux.md), except it normalizes a variable in logarithmic form based on a Postprocessor value.

The formulation of `DensityNormalization` is defined as

\begin{equation}
\frac{\exp(\text{variable})*\text{normal factor}}{\text{normalization}} - \text{shift}
\end{equation}

!alert warning title=Undocumented Test
The DensityNormalization does not have a formulized test, yet. For this reason,
users should be aware of unforseen debugs when using DensityNormalization. To
report debug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of have to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the DensityNormalization object.

```text
[AuxKernels]
  [Normalized_Electrons]
    type = DensityNormalization
    variable = norm_electrons
    Density = electrons
    normalization = max_electron
  []
[]
```

!syntax parameters /AuxKernels/DensityNormalization

!syntax inputs /AuxKernels/DensityNormalization

!syntax children /AuxKernels/DensityNormalization
