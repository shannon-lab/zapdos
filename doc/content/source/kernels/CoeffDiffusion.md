# CoeffDiffusion

!syntax description /Kernels/CoeffDiffusion

## Overview

`CoeffDiffusion` is the diffusion term used for variables in logarithmic form.

The strong form for a diffusion term is usually defined as

\begin{equation}
\nabla \cdot \Gamma_{\text{\text{diff}}} = \nabla \cdot \left[ -D_{j} \nabla (n_{j}) \right]
\end{equation}

Where $\Gamma_{\text{\text{diff}}}$ is the diffusion component of a species' flux, $D_{j}$ is the diffusion coefficient and $n_{j}$ is the density. When
converting the density to logarithmic form and applying a scaling factor of the mesh, the strong form for `CoeffDiffusion` is defined as

\begin{equation}
\nabla \cdot \Gamma_{\text{\text{diff}}} =  \nabla \cdot \left[ -D_{j} \exp(N_{j}) \nabla (N_{j} / l_{c}) \right]
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

An example of how to use `CoeffDiffusion` can be found in the
test file `Lymberopoulos_with_argon_metastables.i`.

!listing test/tests/Lymberopoulos_rf_discharge/Lymberopoulos_with_argon_metastables.i block=Kernels/em_diffusion

!syntax parameters /Kernels/CoeffDiffusion

!syntax inputs /Kernels/CoeffDiffusion

!syntax children /Kernels/CoeffDiffusion
