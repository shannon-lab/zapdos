# PlasmaFrequencyInverse

!syntax description /Postprocessors/PlasmaFrequencyInverse

## Overview

`PlasmaFrequencyInverse` computes the peak value of the inverse plasma frequency. The plasma frequency is defined as:

\begin{equation}
  \omega_{\text{p}} = \sqrt{ \frac{e^{2} n_{e}}{\varepsilon_{0} m_{e}} }
\end{equation}

Where:

- $\omega_{\text{p}}$ is the plasma frequency,
- $n_{e}$ is the electron density,
- $e$ is the elemental charge,
- $\varepsilon_{0}$ is the permittivity of free space, and
- $m_{e}$ is the mass of an electron.

## Example Input File Syntax

!listing test/tests/DriftDiffusionAction/2D_RF_Plasma_actions.i block=Postprocessors/InversePlasmaFreq

!syntax parameters /Postprocessors/PlasmaFrequencyInverse

!syntax inputs /Postprocessors/PlasmaFrequencyInverse

!syntax children /Postprocessors/PlasmaFrequencyInverse
