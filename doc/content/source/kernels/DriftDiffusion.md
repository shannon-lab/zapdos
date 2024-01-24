# DriftDiffusion

!syntax description /Kernels/DriftDiffusion

## Overview

`DriftDiffusion` is a flux term containing an electric field driven advection and diffusion term used for variables in logarithmic form. `DriftDiffusion` assumes the electrostatic approximation for the electric field in multiple dimensions and can assume a uniform electric field for 1D.

The strong form for an electric field driven advection and diffusion flux is usually defined as

\begin{equation}
\nabla \cdot \Gamma = \nabla \cdot \left[ \text{sign}_{j} \mu_{j} n_{j} \ E - D_{j} \nabla (n_{j}) \right] \\[10pt]
E = \text{-} \nabla (V)
\end{equation}

Where $\Gamma$ is the species' flux, $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species), $\mu_{j}$ is the mobility coefficient, $n_{j}$ is the density, $D_{j}$ is the diffusion coefficient, $E$ is the electric field and $V$ is
the potential. When converting the density to logarithmic form and applying a scaling factor of the mesh, the strong form for `DriftDiffusion` is defined as

\begin{equation}
\nabla \cdot \Gamma = \nabla \cdot \left[ \text{sign}_{j} \mu_{j} \exp(N_{j}) \ \text{-} \nabla (V / l_{c}) - D_{j} \exp(N_{j}) \nabla (N_{j} / l_{c}) \right]
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form and $l_{c}$ is the scaling factor of the mesh.

!alert warning title=Untested Class
The DriftDiffusion does not have a formalized test, yet. For this reason,
users should be aware of unforeseen bugs when using DriftDiffusion. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the DriftDiffusion object.

```text
[Kernels]
  [Electrons_DriftDiffusion]
    type = DriftDiffusion
    variable = electrons
    potential = potential
    position_units = 1.0
  []
[]
```

!syntax parameters /Kernels/DriftDiffusion

!syntax inputs /Kernels/DriftDiffusion

!syntax children /Kernels/DriftDiffusion
