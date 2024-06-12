# SecondaryElectronBC

!syntax description /BCs/SecondaryElectronBC

## Overview

Note: add $n_{\gamma}$

`SecondaryElectronBC` is an electron mean energy density of secondary electrons induced by ion flux outflow boundary condition.
`SecondaryElectronBC` assumes the electrostatic approximation for the electric field.

\begin{equation}
a =
\begin{cases}
1, & \mu_{j} \ \text{-} \nabla (V) \cdot \textbf{n} > 0\\
0, & \mu_{j} \ \text{-} \nabla (V) \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{e} \cdot \textbf{n} = \frac{-2}{1+r} (1 - a_{e}) \gamma \Gamma_{j} \cdot \textbf{n} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = \frac{1-r_{j}}{1+r_{j}} \left[ (2 a_{j}-1) \ \mu_{j} \text{-} \nabla (V) \cdot \textbf{n} \ n_{j} + \frac{1}{2}v_{th,j}n_{j} \right] \\[10pt]
v_{th,j} = \sqrt{\frac{8k_{B}T}{\pi m_{j}}}
\end{equation}

Where $\Gamma$ is the flux of the electron or ions, $\textbf{n}$ is the normal of the boundary,
$\mu$ is the mobility coefficient, $n$ is the specie density, $v_{th}$ is the thermal velocity of the species, $k_{B}$ is the Boltzmann constant, and $T$ is the gas temperature. $a$ is defined such that the outflow is only defined when the drift velocity is direct towards the wall and zero otherwise. $r$ is defined as the fraction of particles reflected by the surface. When converting the density to log form and applying a scaling factor of the mesh, the strong form for `SecondaryElectronBC` is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = \frac{-2}{1+r} (1 - a_{e}) \gamma \Gamma_{j} \cdot \textbf{n} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = \frac{1-r_{j}}{1+r_{j}} \left[ (2 a_{j}-1) \ \mu_{j} \text{-} \nabla (V / l_{c}) \cdot \textbf{n} \ \exp(N_{j}) + \frac{1}{2}v_{th,j}\exp(N_{j}) \right]
\end{equation}

Where $N_{j}$ is the molar density of the specie in log form and $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

An example of how to use `SecondaryElectronBC` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=BCs/sec_electrons_left

!syntax parameters /BCs/SecondaryElectronBC

!syntax inputs /BCs/SecondaryElectronBC

!syntax children /BCs/SecondaryElectronBC
