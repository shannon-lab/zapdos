# SideTotFluxIntegral

!syntax description /Postprocessors/SideTotFluxIntegral

## Overview

`SideTotFluxIntegral` computes the surface integrated flux of a species on a boundary.

The surface flux is defined as:

\begin{equation}
a =
\begin{cases}
1, & \text{sign}_{j} \vec{E} \cdot \textbf{n} > 0\\
0, & \text{sign}_{j} \vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
v_{\text{th},j} = \sqrt{\frac{8k_{B}T_{j}}{\pi m_{j}}} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = \frac{1-r}{1+r} \left[ (2 a-1) \ \text{sign}_{j} \mu_{j} \vec{E} \cdot \textbf{n} \ n_{j} + \frac{1}{2}v_{\text{th},j} n_{j} \right] \\[10pt]
\end{equation}

Where:

- the subscripts $j$ represents the properties of chosen species,
- $\Gamma$ is the species flux,
- $\textbf{n}$ is the normal vector of the boundary,
- $\mu$ is the mobility coefficient,
- $n$ is the species density,
- $\vec{E}$ is the electric field,
- $v_\text{th}$ is the thermal velocity of the species,
- $k_{B}$ is the Boltzmann constant,
- $m$ is the species mass,
- $T$ is the species temperature,
- $a$ is defined such that the outflow is non-zero when the drift velocity is directed towards the wall and zero otherwise, and
- $r$ is defined as the fraction of particles reflected by the surface.

When converting the density to molar logarithmic form and applying a scaling factor of the mesh, the following changes are applied to `SideTotFluxIntegral`:

\begin{equation}
\Gamma_{j} \cdot \textbf{n} = \frac{1-r}{1+r} \left[ (2 a-1) \ \text{sign}_{j} \mu_{j} \vec{E} \cdot \textbf{n} \ \exp \left(N_{j}\right) + \frac{1}{2}v_{\text{th},j} \exp \left(N_{j}\right) \right]
\end{equation}

Where:

- $N$ is the molar density of the species in logarithmic form, and
- $l_{c}$ is the scaling factor of the mesh.

!alert! warning title=Untested Class
The `SideTotFluxIntegral` object does not have a formalized test, yet. For this reason,
users should beware of unforeseen bugs when using `SideTotFluxIntegral`. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards on how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).
!alert-end!

## Example Input File Syntax

```text
[Postprocessors]
  [electrode_ion_current]
    type = SideTotFluxIntegral
    variable = ions
    mobility = muions
    r = 0.0
    position_units = 1.0
    field_property_name = electric_field
    boundary = electrode
  []
[]
```

!syntax parameters /Postprocessors/SideTotFluxIntegral

!syntax inputs /Postprocessors/SideTotFluxIntegral

!syntax children /Postprocessors/SideTotFluxIntegral
