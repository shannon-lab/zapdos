# ElectronEnergyTermElasticRate

!syntax description /Kernels/ElectronEnergyTermElasticRate

## Overview

`ElectronEnergyTermElasticRate` is calculates the electron energy loss from elastic collisions using reaction rate coefficients for electrons in logarithmic form.

Electron energy loss from elastic collisions can be described as

\begin{equation}
S_{Loss} =  -3 \frac{m_{e}}{m_{g}} \frac{2n_{\epsilon}}{3n_{e}} k_{el} n_{e} n_{g}
\end{equation}

Where $S_{Loss}$ is the loss term of the electron mean energy density, $k_{el}$ is the reaction rate coefficient for elastic electron-neutral collisions, $m_{e}$ is the mass of the electrons, $m_{g}$ is the mass of the neutral specie, $n_{e}$ is the electron density, $n_{g}$ is the neutral specie density, and $n_{\epsilon}$ is the electron mean energy density. When converting the density to logarithmic form and applying a scaling factor of the mesh, the strong form for `ElectronEnergyTermElasticRate` is defined as

\begin{equation}
S_{Loss} =  -3 \frac{m_{e}}{m_{g}} \frac{2}{3} \exp(N_{\varepsilon} - N_{e}) k_{el} \exp(N_{e}) \exp(N_{g})
\end{equation}

Where $N_{j}$ is the molar density of the specie in logarithmic form and $l_{c}$ is the scaling factor of the mesh.

!alert note
When coupling Zapdos with CRANE, `ElectronEnergyTermElasticRate` serves the same function as CRANE's [`ADEEDFElasticLog`](/kernels/ADEEDFElasticLog.md).

!alert warning title=Untested Class
The ElectronEnergyTermElasticRate does not have a formalized test, yet. For this reason,
users should be aware of unforeseen bugs when using ElectronEnergyTermElasticRate. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the ElectronEnergyTermElasticRate object.

```text
[Kernels]
  [mean_en_elastic]
    type = ElectronEnergyTermElasticRate
    variable = mean_en
    electron_species = electrons
    target_species = Ar
    reaction = elastic
    position_units = 1
  []
[]
```

!syntax parameters /Kernels/ElectronEnergyTermElasticRate

!syntax inputs /Kernels/ElectronEnergyTermElasticRate

!syntax children /Kernels/ElectronEnergyTermElasticRate
