# DriftDiffusionDoNothingBC

!syntax description /BCs/DriftDiffusionDoNothingBC

## Overview

`DriftDiffusionDoNothingBC` is an outflow boundary condition where the outflow at the
boundary is equal to the bulk dift-diffusion equations.

The outflow is defined as

\begin{equation}
\Gamma_{j} \cdot \textbf{n} = \text{sign}_{j} \mu_{j} n_{j} \vec{E} \cdot \textbf{n} - D_{j} \nabla (n_{j}) \cdot \textbf{n}
\end{equation}

Where $\Gamma$ is the outflow normal to the boundary, $\textbf{n}$ is the normal vector of the boundary, $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species, $\text{-}1$ for negatively charged species and $\text{0}$ for neutral species), $\mu_{j}$ is the mobility coefficient, $D_{j}$ is the diffusion coefficient, $n_{j}$ is the density, and $\vec{E}$ is the electric field. When converting the density to logarithmic form and applying a scaling factor of the mesh, the strong form for `DriftDiffusionDoNothingBC` is defined as

\begin{equation}
\Gamma_{j} \cdot \textbf{n} = \text{sign}_{j} \mu_{j} \exp(N_{j}) \left(\vec{E} / l_{c} \right) \cdot \textbf{n} - D_{j} \exp(N_{j}) \nabla (N_{j} / l_{c}) \cdot \textbf{n}
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form and
$l_{c}$ is the scaling factor of the mesh.

!alert warning title=Untested Class
The DriftDiffusionDoNothingBC does not have a formalized test, yet. For this reason,
users should be aware of unforeseen bugs when using DriftDiffusionDoNothingBC. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the DriftDiffusionDoNothingBC object.

```text
[BCs]
  [electron_gap_drift_diffusion]
    type = DriftDiffusionDoNothingBC
    variable = electrons
    position_units = 1.0
    boundary = 'gap'
  []
[]
```

!syntax parameters /BCs/DriftDiffusionDoNothingBC

!syntax inputs /BCs/DriftDiffusionDoNothingBC

!syntax children /BCs/DriftDiffusionDoNothingBC
