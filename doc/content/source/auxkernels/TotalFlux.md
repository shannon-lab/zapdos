# TotalFlux

!syntax description /AuxKernels/TotalFlux

## Overview

`TotalFlux` returns the total flux of a species in logarithmic form. `TotalFlux`
assumes the electrostatic approximation for the electric field.

The electrostatic flux is usually defined as

\begin{equation}
\Gamma_{j} = \text{sign}_{j} \mu_{j} \left( \text{-} \nabla V \right) n_{j} - D_{j} \nabla (n_{j})
\end{equation}

Where $\Gamma_{j}$ is the flux assuming drift-diffusion formulation, $\mu_{j}$ is the mobility coefficient, $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species, $\text{-}1$ for negatively charged species and $\text{0}$ for neutral species), $V$ is the potential, $n_{j}$ is the density, and $D_{j}$ is the diffusion coefficient. When converting the density to logarithmic form, `TotalFlux` is defined as

\begin{equation}
\Gamma_{j} = \text{sign}_{j} \mu_{j} \left(\text{-} \nabla V\right) \exp(N_{j}) - D_{j} \exp(N_{j}) \nabla (N_{j})
\end{equation}

Where $N_{j}$ is the molar density of the specie in logarithmic form.

## Example Input File Syntax

An example of how to use `TotalFlux` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=AuxKernels/tot_flux_OHm

!syntax parameters /AuxKernels/TotalFlux

!syntax inputs /AuxKernels/TotalFlux

!syntax children /AuxKernels/TotalFlux
