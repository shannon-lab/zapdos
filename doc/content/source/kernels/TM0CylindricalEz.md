# TM0CylindricalEz

!syntax description /Kernels/TM0CylindricalEz

## Overview

`TM0CylindricalEz` is the wave equation for the axial component of the electric field. `TM0CylindricalEz` assumes an axisymmetric transverse magnetic (TM) wave and negligible current density compared to the displacement current.

The wave equation for the electric field is defined as

\begin{equation}
  \nabla \times \textbf{H} = \epsilon \omega \textbf{E}
\end{equation}

Where $\textbf{H}$ is the magnetizing field, $\epsilon$ is the material permittivity, $\textbf{E}$ is the electric field, and $\omega$ is the frequency. By assuming an axisymmetric cylindrical geometry, the wave equation simplifies to

\begin{equation}
  \frac{\partial H_{\phi}}{\partial r} -\frac{H_{\phi}}{r}  = \epsilon \omega \text{E}_{z}
\end{equation}

Where $H_{\phi}$ is the azimuthal component of the magnetizing field, $\text{E}_{z}$ is the axial component of the electric field, and $r$ is the radial distance from the axial centerline.

## Example Input File Syntax

An example of how to use `TM0CylindricalEz` can be found in the test file `TM_steady_dieletric.i`.

!listing test/tests/TM10_circular_wg/TM_steady_dieletric.i block=Kernels/Ez_vacuum_kern

!syntax parameters /Kernels/TM0CylindricalEz

!syntax inputs /Kernels/TM0CylindricalEz

!syntax children /Kernels/TM0CylindricalEz
