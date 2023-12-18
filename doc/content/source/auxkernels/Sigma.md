# Sigma

!alert construction title=Undocumented Class
The Sigma has not been documented. The content listed below should be used as a starting point for
documenting the class, which includes the typical automatic documentation associated with a
MooseObject; however, what is contained is ultimately determined by what is necessary to make the
documentation clear for users.

!syntax description /AuxKernels/Sigma

## Overview

`Sigma` calculates a simplifed version of the surface charge on a boundary due to the advection flux of an ion species. `Sigma` assumes a mobility coefficient of unity, the electrostatic approximation for the electric field, and a non-scaled version of the specie's density.

The surface charge is defined as

\begin{equation}
\sigma = \int \Gamma_{i} \cdot \textbf{n} \ \text{d}t \\[10pt]
\Gamma_{i} = \text{-} \nabla (V) n_{i}
\end{equation}

Where $\sigma$ is the surface charge, $\Gamma_{i}$ is the advective flux of the ions, $\textbf{n}$ is the outward pointing unit normal on the boundary, $V$ is the potential, and $n_{i}$ is the ion density.

Using the midpoint method for integration, the surface charge calculation becomes

\begin{equation}
\sigma_{t} = \sigma_{t-1} + \text{-} \nabla (V) n_{i}  \cdot \textbf{n} \ \text{d}t
\end{equation}

Where $\sigma_{t}$ is the surface charge of the current time step, $\sigma_{t-1}$ is the surface of the previous time step, and $\text{d}t$ is the difference between time steps.

!alert note
When calculating the surface charge for scaled densities, non-unity coefficients, and includes contribution due to electron flux, please refer to [`ADSurfaceCharge`](/materials/ADSurfaceCharge.md).

## Example Input File Syntax

!! Describe and include an example of how to use the Sigma object.

!syntax parameters /AuxKernels/Sigma

!syntax inputs /AuxKernels/Sigma

!syntax children /AuxKernels/Sigma
