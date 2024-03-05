# ElectronsFromIonization

!syntax description /Kernels/ElectronsFromIonization

## Overview

`ElectronsFromIonization` is calculates the electron production from ionization using Townsend coefficients for electrons in logarithmic form. `ElectronsFromIonization` assumes the electrostatic approximation for the electric field.

Electron production from ionization can be described as

\begin{equation}
S_\text{gain} = \alpha_{iz} \lvert \Gamma_{e} \rvert \\[10pt]
\Gamma_{e} = \mu_{e} n_{e} \nabla (V) - D_{e} \nabla (n_{e})
\end{equation}

Where $S_\text{gain}$ is the electron production from ionization, $\Gamma_{e}$ is the electron flux, $\alpha_{iz}$ is the Townsend coefficient for ionization, $n_{e}$ is the electron density, $\mu_{e}$ is the mobility coefficient, $D_{e}$ is the diffusion coefficient, and $V$ is
the potential. When converting the density to logarithmic form and applying a scaling factor of the mesh, the strong form for `ElectronsFromIonization` is defined as

\begin{equation}
S_\text{Gain} = \alpha_{iz} \lvert \Gamma_{e} \rvert \\[10pt]
\Gamma_{e} = \mu_{e} \exp(N_{e}) \nabla (V / l_{c}) - D_{e} \exp(N_{e}) \nabla (N_{e} / l_{c})
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form and $l_{c}$ is the scaling factor of the mesh.

!alert note
When coupling Zapdos with CRANE, `ElectronsFromIonization` serves the same function as CRANE's [`ADEEDFReactionTownsend`](/kernels/ADEEDFReactionTownsend.md).

## Example Input File Syntax

An example of how to use `ElectronsFromIonization` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=Kernels/em_ionization

!syntax parameters /Kernels/ElectronsFromIonization

!syntax inputs /Kernels/ElectronsFromIonization

!syntax children /Kernels/ElectronsFromIonization
