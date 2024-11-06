# TM0PECVertBC

!syntax description /BCs/TM0PECVertBC

## Overview

`TM0PECVertBC` is a perfect electric conductor boundary condition of the azimuthal component of the magnetizing field. `TM0PECVertBC` assumes an axisymmetric transverse magnetic (TM) wave.

The perfect electric conductor boundary condition of the azimuthal component of the magnetizing field normal to the antenna surface is

\begin{equation}
  \textbf{n} \times \left( \nabla \times \textbf{H} \right) = 0
\end{equation}

Where $\textbf{H}$ is the magnetizing field and $\textbf{n}$ is the normal vector of the boundary. By assuming the normal of azimuthal component of the magnetizing field to the surface is purely in the axial direction, the integrated boundary condition simplifies to

\begin{equation}
  \nabla \text{H}_{\theta} \cdot \textbf{n} = \frac{\text{-} \text{H}_{\theta}}{r}
\end{equation}

Where $H_{\phi}$ is the azimuthal component of the magnetizing field and $r$ is the radial distance from the axial centerline.

## Example Input File Syntax

!listing test/tests/TM10_circular_wg/TM_steady_dieletric.i block=BCs/vert_wall

!syntax parameters /BCs/TM0PECVertBC

!syntax inputs /BCs/TM0PECVertBC

!syntax children /BCs/TM0PECVertBC
