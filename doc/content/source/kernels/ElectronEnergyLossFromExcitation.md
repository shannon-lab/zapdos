# ElectronEnergyLossFromExcitation


!syntax description /Kernels/ElectronEnergyLossFromExcitation

## Overview

`ElectronEnergyLossFromExcitation` calculates the electron energy loss from metastable excitation using Townsend coefficients for electrons in logarithmic form.

Electron energy loss from metastable excitation can be described as

\begin{equation}
S_\text{Loss} = \text{-} \alpha_{ex} \epsilon_{ex} \lvert \Gamma_{e} \rvert \\[10pt]
\Gamma_{e} = - \mu_{e} n_{e} \vec{E} - D_{e} \nabla (n_{e})
\end{equation}

Where $S_\text{Loss}$ is the loss term of the electron mean energy density, $\Gamma_{e}$ is the electron flux, $\alpha_{ex}$ is the Townsend coefficient for metastable excitation, $\epsilon_{ex}$ the electron energy lost in an excitation collision, $n_{e}$ is the electron density, $\mu_{e}$ is the mobility coefficient, $D_{e}$ is the diffusion coefficient, and $\vec{E}$ is
the electric field. When converting the density to logarithmic form and applying a scaling factor of the mesh, the strong form for `ElectronEnergyLossFromExcitation` is defined as

\begin{equation}
S_\text{Loss} = \text{-} \alpha_{ex} \epsilon_{ex} \lvert \Gamma_{e} \rvert \\[10pt]
\Gamma_{e} = - \mu_{e} \exp(N_{e}) (\vec{E} / l_{c}) - D_{e} \exp(N_{e}) \nabla (N_{e} / l_{c})
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form and $l_{c}$ is the scaling factor of the mesh.

!alert note
When coupling Zapdos with CRANE, `ElectronEnergyLossFromExcitation` serves the same function as CRANE's [`ADEEDFEnergyTownsendLog`](/kernels/ADEEDFEnergyTownsendLog.md).

## Example Input File Syntax

An example of how to use `ElectronEnergyLossFromExcitation` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=Kernels/mean_en_excitation

!syntax parameters /Kernels/ElectronEnergyLossFromExcitation

!syntax inputs /Kernels/ElectronEnergyLossFromExcitation

!syntax children /Kernels/ElectronEnergyLossFromExcitation
