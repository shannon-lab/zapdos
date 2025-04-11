# ExcitationReaction

!syntax description /Kernels/ExcitationReaction

## Overview

`ExcitationReaction` calculates the metastable excitation production using Townsend coefficients for electrons in logarithmic form.

Electron energy loss from metastable excitation can be described as

\begin{equation}
S_\text{Gain} = \alpha_{ex} \lvert \Gamma_{e} \rvert \\[10pt]
\Gamma_{e} = - \mu_{e} n_{e} \vec{E} - D_{e} \nabla (n_{e})
\end{equation}

Where $S_\text{Gain}$ is the metastable production, $\Gamma_{e}$ is the electron flux, $\alpha_{ex}$ is the Townsend coefficient for metastable excitation, $n_{e}$ is the electron density, $\mu_{e}$ is the mobility coefficient, $D_{e}$ is the diffusion coefficient, and $\vec{E}$ is the electric field. When converting the density to logarithmic form and applying a scaling factor of the mesh, the strong form for `ExcitationReaction` is defined as

\begin{equation}
S_\text{Gain} = \alpha_{ex} \lvert \Gamma_{e} \rvert \\[10pt]
\Gamma_{e} = - \mu_{e} \exp(N_{e}) (\vec{E} / l_{c}) - D_{e} \exp(N_{e}) \nabla (N_{e} / l_{c})
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form and $l_{c}$ is the scaling factor of the mesh.

!alert note
When coupling Zapdos with CRANE, `ExcitationReaction` serves the same function as CRANE's [`ADEEDFReactionTownsend`](/kernels/ADEEDFReactionTownsend.md).

## Example Input File Syntax

An example of how to use `ExcitationReaction` can be found in the
test file `mean_en_multi.i`.

!listing test/tests/1d_dc/mean_en_multi.i block=Kernels/ArEx_excitation

!syntax parameters /Kernels/ExcitationReaction

!syntax inputs /Kernels/ExcitationReaction

!syntax children /Kernels/ExcitationReaction
