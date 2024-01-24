# ElectronEnergyTermRate

!syntax description /Kernels/ElectronEnergyTermRate

## Overview

`ElectronEnergyTermRate` calculates the electron energy loss from elastic collisions using reaction rate coefficients for electrons in logarithmic form.

Electron energy loss from elastic collisions can be described as

\begin{equation}
S_\text{Loss} =  k \epsilon n_{e} n_{j}
\end{equation}

Where $S_\text{Loss}$ is the loss term of the electron mean energy density, $k$ is the reaction rate coefficient, $n_{e}$ is the electron density, $n_{j}$ is the colliding species density, and $\epsilon$ the electron energy lost in the collision. When converting the density to logarithmic form and applying a scaling factor of the mesh, the strong form for `ElectronEnergyTermRate` is defined as

\begin{equation}
S_\text{Loss} =  k \epsilon \exp(N_{e}) \exp(N_{j})
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form and $l_{c}$ is the scaling factor of the mesh.

!alert note
When coupling Zapdos with CRANE, `ElectronEnergyTermRate` serves the same function as CRANE's [`ADEEDFEnergyLog`](/kernels/ADEEDFEnergyLog.md).

!alert warning title=Untested Class
The ElectronEnergyTermRate does not have a formalized test, yet. For this reason,
users should be aware of unforeseen bugs when using ElectronEnergyTermRate. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the ElectronEnergyTermRate object.

```text
[Kernels]
  [mean_en_ionization]
    type = ElectronEnergyTermRate
    variable = mean_en
    em = electrons
    v = Ar
    reaction = ionization
    threshold_energy = -15.7
    position_units = 1
  []
[]
```

!syntax parameters /Kernels/ElectronEnergyTermRate

!syntax inputs /Kernels/ElectronEnergyTermRate

!syntax children /Kernels/ElectronEnergyTermRate
