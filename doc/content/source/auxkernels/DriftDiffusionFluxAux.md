# DriftDiffusionFluxAux

!alert construction title=Undocumented Class
The DriftDiffusionFluxAux has not been documented. The content listed below should be used as a starting point for
documenting the class, which includes the typical automatic documentation associated with a
MooseObject; however, what is contained is ultimately determined by what is necessary to make the
documentation clear for users.

!syntax description /AuxKernels/DriftDiffusionFluxAux

## Overview

`DriftDiffusionFluxAux` returns the simplified drift-diffusion flux of a species. `DriftDiffusionFluxAux`
assumes a mobility and diffusion coefficient of unity, the electrostatic approximation for the electric field, and a non-scaled version of the specie's density.

The electrostatic flux is defined as

\begin{equation}
\Gamma_{j} = \text{sign}_{j} \ \text{-} \nabla (V) n_{j} - \nabla (n_{j})
\end{equation}

Where $\Gamma_{j}$ is the flux assuming drift-diffusion formulation, $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species),
$V$ is the potential, and $n_{j}$ is the density.

!alert note
When calculating the drift-diffusion flux for scaled densities and non-unity coefficients, please refer to [`TotalFlux`](/auxkernels/TotalFlux.md).

## Example Input File Syntax

!! Describe and include an example of how to use the DriftDiffusionFluxAux object.

!syntax parameters /AuxKernels/DriftDiffusionFluxAux

!syntax inputs /AuxKernels/DriftDiffusionFluxAux

!syntax children /AuxKernels/DriftDiffusionFluxAux
