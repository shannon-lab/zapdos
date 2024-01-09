# TM0CylindricalErAux

!syntax description /AuxKernels/TM0CylindricalErAux

## Overview

`TM0CylindricalErAux` calculates the radial component of the E-field based on the azimuthal component of the magnetic field. `TM0CylindricalErAux` assumes an axisymmetric transverse magnetic (TM) wave and negligible current density compared to the displacement current.

The radial component of the displacement E-field for a TM$_{0}$ wave is defined as

\begin{equation}
E_{r} = \frac{\text{-} 1}{\omega \varepsilon_{0} \varepsilon_{r}} \frac{dH_{\phi}}{dz}
\end{equation}

Where $E_{r}$ is the radial component of the E-field, $H_{\phi}$ is the azimuthal component of the magnetic field, $\omega$ is the drive frequency, $\varepsilon_{0}$ is the permittivity of free space, and $\varepsilon_{r}$ is the relative permittivity of the medium.

## Example Input File Syntax

An example of how to use `TM0CylindricalErAux` can be found in the
test file `TM_steady.i`.

!listing test/tests/TM10_circular_wg/TM_steady.i block=AuxKernels/Er

!syntax parameters /AuxKernels/TM0CylindricalErAux

!syntax inputs /AuxKernels/TM0CylindricalErAux

!syntax children /AuxKernels/TM0CylindricalErAux
