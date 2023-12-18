# TM0CylindricalEzAux

!syntax description /AuxKernels/TM0CylindricalEzAux

## Overview

`TM0CylindricalEzAux` calculates the axial component of the E-field based on the azimuthal component of the magnetic field. `TM0CylindricalEzAux` assumes an axisymmetric transverse magnetic (TM) wave and negligible current density compared to the displacement current.

The axial component of the displacement E-field for a TM$_{0}$ wave is defined as

\begin{equation}
E_{z} = \frac{1}{\omega \varepsilon_{0} \varepsilon_{r}} \left( \frac{H_{\phi}}{r} + \frac{dH_{\phi}}{dr} \right)
\end{equation}

Where $E_{z}$ is the axial component of the E-field, $H_{\phi}$ is the azimuthal component of the magnetic field, $\omega$ is the drive frequency, $r$ is the radial distance from the axial centerline, $\varepsilon_{0}$ is the permittivity of free space, and $\varepsilon_{r}$ is the relative permittivity of the medium.

## Example Input File Syntax

An example of how to use `TM0CylindricalEzAux` can be found in the
test file `TM_steady.i`.

!listing test/tests/TM10_circular_wg/TM_steady.i block=AuxKernels/Electric_z

!syntax parameters /AuxKernels/TM0CylindricalEzAux

!syntax inputs /AuxKernels/TM0CylindricalEzAux

!syntax children /AuxKernels/TM0CylindricalEzAux
