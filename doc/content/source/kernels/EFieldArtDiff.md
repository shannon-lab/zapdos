# EFieldArtDiff

!syntax description /Kernels/EFieldArtDiff

## Overview

`EFieldArtDiff` adds an artificial diffusion term that is proportional to the magnitude of the electric field driven advection.
`EFieldArtDiff` assumes the electrostatic approximation for the electric field.

The strong form for the artificial diffusion flux is usually defined as

\begin{equation}
\nabla \cdot \Gamma_{\text{art}} = \nabla \cdot \left[ \mu_{j} \text{-} \nabla (V) \frac{h_\text{max}}{2} \nabla (n_{j})  \text{Scale} \right]
\end{equation}

Where $\Gamma_{\text{art}}$ is the advection component of a species' flux, $\mu_{j}$ is the mobility coefficient, $V$ is the potential, $n_{j}$ is the density, $h_\text{max}$ is the max length of the current element, and Scale is a user defined scaling factor.
When converting the density to logarithmic form and applying a scaling factor of the mesh,
`EFieldArtDiff` is defined as

\begin{equation}
\nabla \cdot \Gamma_{\text{art}} = \nabla \cdot \left[ \mu_{j} \frac{\text{-}\lVert \nabla (V) \rVert_{2}}{l_{c}} \frac{h_{max} l_{c}}{2} \exp(N_{j}) \frac{\nabla (N_{j})}{l_{c}}  * Scale \right]
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form, $N_{A}$ is Avogadro's
number, $l_{c}$ is the scaling factor of the mesh.

!alert warning title=Untested Class
The EFieldArtDiff does not have a formalized test, yet. For this reason,
users should be aware of unforeseen bugs when using EFieldArtDiff. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the EFieldArtDiff object.

```text
[Kernels]
  [em_advection_stabilization]
    type = EFieldArtDiff
    variable = em
    potential = potential
  []
[]
```

!syntax parameters /Kernels/EFieldArtDiff

!syntax inputs /Kernels/EFieldArtDiff

!syntax children /Kernels/EFieldArtDiff
