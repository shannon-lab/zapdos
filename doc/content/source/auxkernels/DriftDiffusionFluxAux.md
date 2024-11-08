# DriftDiffusionFluxAux

!syntax description /AuxKernels/DriftDiffusionFluxAux

## Overview

`DriftDiffusionFluxAux` returns the simplified drift-diffusion flux of a species. `DriftDiffusionFluxAux`
assumes a mobility and diffusion coefficient of unity and a non-scaled version of the specie's density.

The flux is defined as

\begin{equation}
\Gamma_{j} =  \text{sign}_{j} \vec{E} n_{j} - \nabla (n_{j})
\end{equation}

Where $\Gamma_{j}$ is the flux assuming drift-diffusion formulation, $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species),
$\vec{E}$ is the electric field, and $n_{j}$ is the density.

!alert note
When calculating the drift-diffusion flux for scaled densities and non-unity coefficients, please refer to [`TotalFlux`](/auxkernels/TotalFlux.md).

!alert warning title=Undocumented Test
The DriftDiffusionFluxAux does not have a formalized test, yet. For this reason,
users should be aware of unforeseen bugs when using DriftDiffusionFluxAux. To
report bugs or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the DriftDiffusionFluxAux object.

```text
[AuxKernels]
  [Electron_Flux]
    type = DriftDiffusionFluxAux
    variable = electron_flux
    u = electrons
    potential =  potential
    positive_charge = false
    component = 0
  []
[]
```

!syntax parameters /AuxKernels/DriftDiffusionFluxAux

!syntax inputs /AuxKernels/DriftDiffusionFluxAux

!syntax children /AuxKernels/DriftDiffusionFluxAux
