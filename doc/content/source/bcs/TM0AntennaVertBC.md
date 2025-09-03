# TM0AntennaVertBC

!syntax description /BCs/TM0AntennaVertBC

## Overview

`TM0AntennaVertBC` is the boundary condition of the azimuthal component of the magnetizing field for a simple vertical antenna. `TM0AntennaVertBC` assumes an axisymmetric transverse magnetic (TM) wave, an incoming electric field of unity, and negligible current density compared to the displacement current.

The boundary condition of the azimuthal component of the magnetizing field normal to the antenna surface is

\begin{equation}
  \textbf{n} \times \left( \nabla \times \textbf{H} \right) = j \omega \varepsilon \textbf{E}
\end{equation}

Where $\textbf{H}$ is the magnetizing field, $\textbf{n}$ is the normal vector of the boundary, $\varepsilon$ is the material permittivity, $\omega$ is the drive frequency of the system, $\textbf{E}$ is the electric field, and $j = \sqrt{-1}$. By assuming the normal of azimuthal component of the magnetizing field to the surface is purely in the axial direction and an incoming electric field of unity (such that $\textbf{E} = (1 - j)$), the integrated boundary condition simplifies to

\begin{equation}
  \nabla \text{H}_{\theta} \cdot \textbf{n} = \frac{\text{-} \text{H}_{\theta}}{r} + \omega \varepsilon
\end{equation}

Where $H_{\phi}$ is the azimuthal component of the magnetizing field and $r$ is the radial distance from the axial centerline.

## Example Input File Syntax

!listing test/tests/TM10_circular_wg/TM_steady_dieletric.i block=BCs/launcher

!syntax parameters /BCs/TM0AntennaVertBC

!syntax inputs /BCs/TM0AntennaVertBC

!syntax children /BCs/TM0AntennaVertBC
