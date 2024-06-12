# HagelaarIonDiffusionBC

!syntax description /BCs/HagelaarIonDiffusionBC

## Overview

`HagelaarIonDiffusionBC` is a thermal outflow boundary condition.

The thermal driven outflow is defined as

\begin{equation}
v_{th,j} = \sqrt{\frac{8k_{B}T}{\pi m_{j}}} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = \frac{1-r_{j}}{1+r_{j}} \left[ \frac{1}{2}v_{th,j}n_{j} \right]
\end{equation}

Where $\Gamma$ is the outflow normal to the boundary, $\textbf{n}$ is the normal of the boundary, $n_{j}$ is the ion density, $v_{th,j}$ is the thermal velocity of the ions, $k_{B}$ is the Boltzmann constant, and $T$ is the gas temperature. $r$ is defined as the fraction of particles reflected by the surface. When converting the density to log form and applying a scaling
factor of the mesh, the strong form for `HagelaarIonDiffusionBC` is defined as

\begin{equation}
v_{th,j} = \sqrt{\frac{8k_{B}T}{\pi m_{j}}} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = \frac{1-r_{j}}{1+r_{j}} \left[ \frac{1}{2}v_{th,j}\exp(N_{j}) \right]
\end{equation}

Where $N_{j}$ is the molar density of the specie in log form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

An example of how to use `HagelaarIonDiffusionBC` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=BCs/Arp_physical_right_diffusion

!syntax parameters /BCs/HagelaarIonDiffusionBC

!syntax inputs /BCs/HagelaarIonDiffusionBC

!syntax children /BCs/HagelaarIonDiffusionBC
