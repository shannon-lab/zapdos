# HagelaarElectronAdvectionBC

!syntax description /BCs/HagelaarElectronAdvectionBC

## Overview

`HagelaarElectronAdvectionBC` is an electric field driven outflow boundary condition.

The electric field driven outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{e} \ -\vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{e} \ -\vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{e} \cdot \textbf{n} = \frac{1-r_{e}}{1+r_{e}} \left[ -(2 a_{e}-1) \ \mu_{e}
\vec{E}
 \cdot \textbf{n} \ n_{e} \right]
\end{equation}

Where $\Gamma_e \cdot \textbf{n}$ is the outflow normal to the boundary, $n$ is the normal vector of the boundary,
$\mu_{e}$ is the mobility coefficient, $n_{e}$ is the electron density, and $\vec{E}$ is
the electric field. $a$ is defined such that the outflow is only defined when the drift velocity is directed towards the wall and zero otherwise. $r$ is defined as the fraction of particles reflected by the surface. When converting the density to log form and applying a scaling
factor of the mesh, the strong form for `HagelaarElectronAdvectionBC` is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{e} \ -\vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{e} \ -\vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{e} \cdot \textbf{n} = \frac{1-r_{e}}{1+r_{e}} \left[ -(2 a_{e}-1) \ \mu_{e}
 \left( 
 \vec{E} / l_{c}
\right)
  \cdot \textbf{n} \ \exp(N_{e}) \right]
\end{equation}

Where $N_{e}$ is the molar density of the species in log form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax


!listing test/tests/1d_dc/NonlocalPotentialBCWithSchottky.i block=BCs/em_physical_right

!syntax parameters /BCs/HagelaarElectronAdvectionBC

!syntax inputs /BCs/HagelaarElectronAdvectionBC

!syntax children /BCs/HagelaarElectronAdvectionBC
