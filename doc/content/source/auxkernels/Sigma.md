# Sigma

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
\sigma_{t} = \sigma_{t-1} - \nabla (V) n_{i}  \cdot \textbf{n} \ \text{d}t
\end{equation}

Where $\sigma_{t}$ is the surface charge of the current time step, $\sigma_{t-1}$ is the surface of the previous time step, and $\text{d}t$ is the difference between time steps.

!alert note
When calculating the surface charge for scaled densities, non-unity coefficients, and includes contribution due to electron flux, please refer to [`ADSurfaceCharge`](/materials/ADSurfaceCharge.md).

!alert warning title=Untested Class
The Sigma does not have a formulized test, yet. For this reason,
users should be aware of unforseen debugs when using Sigma. To
report debug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of have to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the Sigma object.

```text
[AuxKernels]
  [Surface_Charge]
    type = Sigma
    variable = charge
    n = ions
    potential =  potential
  []
[]
```

!syntax parameters /AuxKernels/Sigma

!syntax inputs /AuxKernels/Sigma

!syntax children /AuxKernels/Sigma
