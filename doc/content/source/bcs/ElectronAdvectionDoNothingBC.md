# ElectronAdvectionDoNothingBC

!syntax description /BCs/ElectronAdvectionDoNothingBC

## Overview

`ElectronAdvectionDoNothingBC` is an outflow boundary condition where the outflow at the
boundary is equal to the bulk electron advection equation.

The outflow is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = \text{-} \mu_{e} n_{e} \vec{E} \cdot \textbf{n} 
\end{equation}

Where $\Gamma$ is the outflow normal to the boundary, $\textbf{n}$ is the normal of the boundary, $\mu_{e}$ is the mobility coefficient, $n_{e}$ is the electron density, and $\vec{E}$ is the electric field. When converting the density to logarithmic form and applying a scaling
factor of the mesh, the strong form for `ElectronAdvectionDoNothingBC` is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = \text{-} \mu_{e} \exp(N_{e}) \left(\vec{E} / l_{c} \right) \cdot \textbf{n}
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form and
$l_{c}$ is the scaling factor of the mesh.

!alert warning title=Untested Class
The ElectronAdvectionDoNothingBC does not have a formalized test, yet. For this reason,
users should be aware of unforeseen bugs when using ElectronAdvectionDoNothingBC. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the ElectronAdvectionDoNothingBC object.

```text
[BCs]
  [electron_gap_advection]
    type = ElectronAdvectionDoNothingBC
    variable = electrons
    potential = potential
    position_units = 1.0
    boundary = 'gap'
  []
[]
```

!syntax parameters /BCs/ElectronAdvectionDoNothingBC

!syntax inputs /BCs/ElectronAdvectionDoNothingBC

!syntax children /BCs/ElectronAdvectionDoNothingBC
