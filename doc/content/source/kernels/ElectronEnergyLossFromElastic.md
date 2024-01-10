# ElectronEnergyLossFromElastic

!syntax description /Kernels/ElectronEnergyLossFromElastic

## Overview

`ElectronEnergyLossFromElastic` calculates the electron energy loss from elastic collisions using Townsend coefficients for electrons in logarithmic form. For Townsend discharge, `ElectronEnergyLossFromElastic` assumes the electrostatic approximation for the electric field.

Electron energy loss from elastic collisions can be described as

\begin{equation}
S_{Loss} = \text{-} \lvert \Gamma_{e} \rvert \left[ 3 \alpha_{el} \frac{m_{e}}{m_{g}} \frac{2n_{\epsilon}}{3n_{e}}  \right] \\[10pt]
\Gamma_{e} = \mu_{e} n_{e} \nabla (V) - D_{e} \nabla (n_{e})
\end{equation}

Where $S_{Loss}$ is the loss term of the electron mean energy density, $\Gamma_{e}$ is the electron flux, $\alpha_{el}$ is the Townsend coefficient for elastic electron-neutral collisions, $m_{e}$ is the mass of the electrons, $m_{g}$ is the mass of the neutral specie, $n_{e}$ is the electron density, $n_{\epsilon}$ is the electron mean energy density, $\mu_{e}$ is the mobility coefficient, $D_{e}$ is the diffusion coefficient, and $V$ is
the potential. When converting the density to logarithmic form and applying a scaling factor of the mesh, the strong form for `ElectronEnergyLossFromElastic` is defined as

\begin{equation}
S_{Loss} = \text{-} \lvert \Gamma_{e} \rvert \left[ 3 \alpha_{el} \frac{m_{e}}{m_{g}} \frac{2}{3} \exp(N_{\varepsilon} - N_{e}) \right] \\[10pt]
\Gamma_{e} = \mu_{e} \exp(N_{e}) \nabla (V / l_{c}) - D_{e} \exp(N_{e}) \nabla (N_{e} / l_{c})
\end{equation}

Where $N_{j}$ is the molar density of the specie in logarithmic form and $l_{c}$ is the scaling factor of the mesh.

!alert note
When coupling Zapdos with CRANE, `ElectronEnergyLossFromElastic` serves the same function as CRANE's [`ADEEDFElasticTownsendLog`](/kernels/ADEEDFElasticTownsendLog.md).

## Example Input File Syntax

An example of how to use `ElectronEnergyLossFromElastic` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=Kernels/mean_en_elastic

!syntax parameters /Kernels/ElectronEnergyLossFromElastic

!syntax inputs /Kernels/ElectronEnergyLossFromElastic

!syntax children /Kernels/ElectronEnergyLossFromElastic
