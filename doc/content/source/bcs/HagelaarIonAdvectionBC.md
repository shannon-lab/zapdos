# HagelaarIonAdvectionBC

!syntax description /BCs/HagelaarIonAdvectionBC

## Overview

`HagelaarIonAdvectionBC` is an electric field driven outflow boundary condition.

The electric field driven outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{j} \vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{j} \vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = \frac{1-r_{j}}{1+r_{j}} \left[ (2 a_{j}-1) \ \mu_{j}
\vec{E}
\cdot \textbf{n} \ n_{j} \right]
\end{equation}

Where $\Gamma_j \cdot \textbf{n}$ is the flux normal to the boundary, $n$ is the normal vector of the boundary,
$\mu_{j}$ is the mobility coefficient, $n_{j}$ is the ion density, and $\vec{E}$ is
the electric field. $a$ is defined such that the outflow is only non-zero when the drift velocity is directed towards the wall and zero otherwise. $r$ is defined as the fraction of particles reflected by the surface. When converting the density to log form and applying a scaling factor of the mesh, the strong form for `HagelaarIonAdvectionBC` is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{j} \vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{j} \vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = \frac{1-r_{j}}{1+r_{j}} \left[ (2 a_{j}-1) \ \mu_{j} 
\left( 
\vec{E}V / l_{c}
\right)
 \cdot \textbf{n} \ \exp(N_{j}) \right]
\end{equation}

Where $N_{j}$ is the molar density of the species in log form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

!listing test/tests/1d_dc/mean_en.i block=BCs/Arp_physical_right_advection

!syntax parameters /BCs/HagelaarIonAdvectionBC

!syntax inputs /BCs/HagelaarIonAdvectionBC

!syntax children /BCs/HagelaarIonAdvectionBC
