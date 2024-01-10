# TM0Cylindrical

!syntax description /Kernels/TM0Cylindrical

## Overview

`TM0Cylindrical` is the wave equation for the magnetizing field, H-field. `TM0Cylindrical` assumes an axisymmetric transverse magnetic (TM) wave and negligible current density compared to the displacement current.

The wave equation for the H-field is defined as

\begin{equation}
  \nabla \times \nabla \times \textbf{H} = \text{-} \epsilon \mu_{0} \omega^{2} \textbf{H}
\end{equation}

Where $\textbf{H}$ is the magnetizing field, $\epsilon$ is the material permittivity, $\mu_{0}$ is the permeability of free space, and $\omega$ is the frequency. By assuming an axisymmetric cylindrical geometry, the wave equation simplifies to

\begin{equation}
  \nabla^2 \text{H}_{\theta} - \frac{\text{H}_{\theta}}{r^2} = \text{-} \epsilon \mu_{0} \omega^{2} \text{H}_{\theta}
\end{equation}

Where $H_{\phi}$ is the azimuthal component of the magnetizing field and $r$ is the radial distance from the axial centerline.

## Example Input File Syntax

An example of how to use `TM0Cylindrical` can be found in the test file `TM_steady_dieletric.i`.

!listing test/tests/TM10_circular_wg/TM_steady_dieletric.i block=Kernels/Hphi_vacuum

!syntax parameters /Kernels/TM0Cylindrical

!syntax inputs /Kernels/TM0Cylindrical

!syntax children /Kernels/TM0Cylindrical
