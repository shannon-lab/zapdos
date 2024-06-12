# HagelaarElectronAdvectionBC

!syntax description /BCs/HagelaarElectronAdvectionBC

## Overview

`HagelaarElectronAdvectionBC` is an electric field driven outflow boundary condition.
`HagelaarElectronAdvectionBC` assumes the electrostatic approximation for the electric field.

The electrostatic electric field driven outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{e} \ \nabla (V) \cdot \textbf{n} > 0\\
0, & \mu_{e} \ \nabla (V) \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{e} \cdot \textbf{n} = \frac{1-r_{e}}{1+r_{e}} \left[ -(2 a_{e}-1) \ \mu_{e} \text{-} \nabla (V) \cdot \textbf{n} \ n_{e} \right]
\end{equation}

Where $\Gamma$ is the outflow normal to the boundary, $n$ is the normal of the boundary,
$\mu_{e}$ is the mobility coefficient, $n_{e}$ is the electron density, and $V$ is
the potential. $a$ is defined such that the outflow is only defined when the drift velocity is direct towards the wall and zero otherwise. $r$ is defined as the fraction of particles reflected by the surface. When converting the density to log form and applying a scaling
factor of the mesh, the strong form for `HagelaarElectronAdvectionBC` is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{e} \ \nabla (V) \cdot \textbf{n} > 0\\
0, & \mu_{e} \ \nabla (V) \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{e} \cdot \textbf{n} = \frac{1-r_{e}}{1+r_{e}} \left[ -(2 a_{e}-1) \ \mu_{e} \text{-} \nabla (V / l_{c}) \cdot \textbf{n} \ \exp(N_{e}) \right]
\end{equation}

Where $N_{e}$ is the molar density of the specie in log form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

An example of how to use `HagelaarElectronAdvectionBC` can be found in the
test file `NonlocalPotentialBCWithSchottky.i`.

!listing test/tests/1d_dc/NonlocalPotentialBCWithSchottky.i block=BCs/em_physical_right

!syntax parameters /BCs/HagelaarElectronAdvectionBC

!syntax inputs /BCs/HagelaarElectronAdvectionBC

!syntax children /BCs/HagelaarElectronAdvectionBC
