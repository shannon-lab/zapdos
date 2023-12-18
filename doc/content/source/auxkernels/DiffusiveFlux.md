# DiffusiveFlux

!syntax description /AuxKernels/DiffusiveFlux

## Overview

`DiffusiveFlux` returns the diffusive flux of a species in logarithmic form.

The diffusive flux is defined as

\begin{equation}
\Gamma_{Diffusion}  = \text{-}D_{j} \nabla (n_{j})
\end{equation}

Where $\Gamma$ is the diffusive flux, $D_{j}$ is the diffusion coefficient and $n_{j}$ is the density.
When converting the density to logarithmic form and applying a scaling factor of the mesh,
`DiffusiveFlux` is defined as

\begin{equation}
\Gamma_{Diffusion} = \text{-}D_{j} N_{A} \exp(N_{j}) \frac{\nabla (N_{j})}{l_{c}}
\end{equation}

Where $N_{j}$ is the molar density of the specie in logarithmic form, $N_{A}$ is Avogadro's
number, $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

An example of how to use `DiffusiveFlux` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=AuxKernels/DiffusiveFlux_em

!syntax parameters /AuxKernels/DiffusiveFlux

!syntax inputs /AuxKernels/DiffusiveFlux

!syntax children /AuxKernels/DiffusiveFlux
