# SideCurrent

!syntax description /Postprocessors/SideCurrent

## Overview

`SideCurrent` computes the surface integrated current on a boundary.

The surface current is defined as:

\begin{equation}
a_{e} =
\begin{cases}
1, & - \mu_{e} \vec{E} \cdot \textbf{n} > 0\\
0, & - \mu_{e} \vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
a_{i} =
\begin{cases}
1, & \mu_{i} \vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{i} \vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
v_{\text{th},e} = \sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \frac{n_{\varepsilon}}{n_{e}}} \\[10pt]
v_{\text{th},i} = \sqrt{\frac{8k_{B}T}{\pi m_{i}}} \\[10pt]
\Gamma_{e} \cdot \textbf{n} = \frac{1-r}{1+r} \left[ -(2 a_{e}-1) \ \mu_{e}
\vec{E}
 \cdot \textbf{n} \ n_{e} + \frac{1}{2}v_{\text{th},e} n_{e} \right] \\[10pt]
\Gamma_{i} \cdot \textbf{n} = \frac{1-r}{1+r} \left[ (2 a_{i}-1) \ \mu_{i} \vec{E} \cdot \textbf{n} \ n_{i} + \frac{1}{2}v_{\text{th},i}n_{i} \right] \\[10pt]
I = \int e \left( \Gamma_{i} + \Gamma_{e} \right) \cdot \textbf{n} \ dS \\[10pt]
\end{equation}

Where:

- $I$ is the side current,
- the subscripts $e$ represents properties of electrons,
- the subscripts $i$ represents properties of ions,
- the subscripts $\varepsilon$ represents properties of electron energy,
- $\Gamma$ is the species flux,
- $\textbf{n}$ is the normal vector of the boundary,
- $\mu$ is the mobility coefficient,
- $n$ is the species density,
- $\vec{E}$ is the electric field,
- $v_\text{th}$ is the thermal velocity of the species,
- $k_{B}$ is the Boltzmann constant,
- $e$ is the elemental charge,
- $m$ is the species mass,
- $T$ is the gas temperature,
- $a$ is defined such that the outflow is non-zero when the drift velocity is directed towards the wall and zero otherwise, and
- $r$ is defined as the fraction of particles reflected by the surface.

When converting the density to molar logarithmic form and applying a scaling factor of the mesh, the following changes are applied to `SideCurrent`:

\begin{equation}
v_{\text{th},e} = \sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \exp \left( N_{\varepsilon} - N_{e} \right)} \\[10pt]
\Gamma_{e} \cdot \textbf{n} = \frac{1-r_{e}}{1+r_{e}} \left[ -(2 a_{e}-1) \ \mu_{e}
\frac{\vec{E}}{l_{c}} \cdot \textbf{n} \ \exp \left(N_{e}\right) + \frac{1}{2}v_{\text{th},e} \exp \left(N_{e}\right) \right] \\[10pt]
\Gamma_{i} \cdot \textbf{n} = \frac{1-r_{i}}{1+r_{i}} \left[ (2 a_{i}-1) \ \mu_{i} \frac{\vec{E}}{l_{c}} \cdot \textbf{n} \ \exp \left(N_{i}\right) + \frac{1}{2}v_{\text{th},i}\exp \left(N_{i}\right) \right] \\[10pt]
I = \int N_{A} e \left( \Gamma_{i} + \Gamma_{e} \right) \cdot \textbf{n} \ dS \\[10pt]
\end{equation}

Where:

- $N$ is the molar density of the species in logarithmic form,
- $N_{A}$ is Avogadro's number and
- $l_{c}$ is the scaling factor of the mesh.


!alert! warning title=Untested Class
The `SideCurrent` object does not have a formalized test, yet. For this reason,
users should beware of unforeseen bugs when using `SideCurrent`. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards on how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).
!alert-end!

## Example Input File Syntax

```text
[Postprocessors]
  [electrode_current]
    type = SideCurrent
    variable = electrons
    mean_en = electron_energy
    ions = ions
    field_property_name = electric_field
    r = 0.0
    position_units = 1.0
    mobility = electron_mu
    boundary = electrode
  []
[]
```

!syntax parameters /Postprocessors/SideCurrent

!syntax inputs /Postprocessors/SideCurrent

!syntax children /Postprocessors/SideCurrent
