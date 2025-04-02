# PlasmaDielectricConstant

!syntax description /Materials/PlasmaDielectricConstant

## Overview

`PlasmaDielectricConstant` provides the real and complex components of the plasma dielectric coefficient, along with the spatial gradient and the first time derivative of the plasma dielectric coefficient.

The plasma dielectic coefficient is defined as:

\begin{equation}
\varepsilon_{p} = \varepsilon_{0} \left[ 1 - \frac{\omega_{pe}^{2}}{\omega \left( \omega - j \nu_{m} \right)} \right] \\[10pt]
\omega_{pe} = \sqrt{\frac{e^{2} n_{e}}{\varepsilon_{0} m_{e}}}
\end{equation}

where

- $\varepsilon_{p}$ is the plasma dielectric coefficient,
- $\varepsilon_{0}$ is the permittivity of free space,
- $\omega_{pe}$ is the plasma frequency,
- $\omega$ is the drive frequency of the wave propagation,
- $\nu_{m}$ is the electron-neutral collision frequency,
- $e$ is the elementary charge,
- $n_{e}$ is the electron density, and 
- $m_{e}$ is the electron mass.

## Example Input File Syntax

!listing test/tests/mms/materials/2D_PlasmaDielectricConstant.i block=Materials/Plasma_dielectric

!syntax parameters /Materials/PlasmaDielectricConstant

!syntax inputs /Materials/PlasmaDielectricConstant

!syntax children /Materials/PlasmaDielectricConstant
