# TM0CylindricalEr

!syntax description /Kernels/TM0CylindricalEr

## Overview

`TM0CylindricalEr` is the wave equation for the radial component of the electric field. `TM0CylindricalEr` assumes an axisymmetric transverse magnetic (TM) wave and negligible current density compared to the displacement current.

The wave equation for the electric field is defined as

\begin{equation}
  \nabla \times \textbf{H} = \epsilon \omega \textbf{E}
\end{equation}

Where $\textbf{H}$ is the magnetizing field, $\epsilon$ is the material permittivity, $\textbf{E}$ is the electric field, and $\omega$ is the frequency. By assuming an axisymmetric cylindrical geometry, the wave equation simplifies to

\begin{equation}
  \text{-} \frac{\partial H_{\phi}}{\partial z} = \epsilon \omega \text{E}_{r}
\end{equation}

Where $H_{\phi}$ is the azimuthal component of the magnetizing field and $\text{E}_{r}$ is the radial component of the electric field.

## Example Input File Syntax

An example of how to use `TM0CylindricalEr` can be found in the test file `TM_steady_dieletric.i`.

!listing test/tests/TM10_circular_wg/TM_steady_dieletric.i block=Kernels/Er_vacuum

!syntax parameters /Kernels/TM0CylindricalEr

!syntax inputs /Kernels/TM0CylindricalEr

!syntax children /Kernels/TM0CylindricalEr
