# ElectronDiffusionDoNothingBC

!syntax description /BCs/ElectronDiffusionDoNothingBC

## Overview

`ElectronDiffusionDoNothingBC` is an outflow boundary condition where the outflow at the
boundary is equal to the bulk election diffusion equation.

The outflow is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = - D_{e} \nabla (n_{e}) \cdot \textbf{n}
\end{equation}

Where $\Gamma_e \cdot \textbf{n}$ is the outflow normal to the boundary, $\textbf{n}$ is the normal  vector of the boundary, $D_{e}$ is the diffusion coefficient, and $n_{e}$ is the electron density. When converting the density to logarithmic form and applying a scaling
factor of the mesh, the strong form for `ElectronDiffusionDoNothingBC` is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = - D_{e} \exp(N_{e}) \nabla (N_{e} / l_{c}) \cdot \textbf{n}
\end{equation}

Where $N_{e}$ is the molar density of the species in logarithmic form and
$l_{c}$ is the scaling factor of the mesh.

!alert warning title=Untested Class
The ElectronDiffusionDoNothingBC does not have a formalized test, yet. For this reason,
users should be aware of unforeseen bugs when using ElectronDiffusionDoNothingBC. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the ElectronDiffusionDoNothingBC object.

```text
[BCs]
  [electron_gap_diffusion]
    type = ElectronDiffusionDoNothingBC
    variable = electrons
    position_units = 1.0
    boundary = 'gap'
  []
[]
```

!syntax parameters /BCs/ElectronDiffusionDoNothingBC

!syntax inputs /BCs/ElectronDiffusionDoNothingBC

!syntax children /BCs/ElectronDiffusionDoNothingBC
