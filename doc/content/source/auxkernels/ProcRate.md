# ProcRate

!syntax description /AuxKernels/ProcRate

## Overview

`ProcRate` returns the production rate for chemistry reactions determined by Townsend coefficients in units of $\frac{\#}{m^{3}s}$. `ProcRate`
assumes the electrostatic approximation for the current.

The production rate is defined as

\begin{equation}
S_{Townsend} = \alpha_{j} (\mu_{e} \nabla (V) n_{e} - D_{e} \nabla (n_{e}))
\end{equation}

Where $S_{Townsend}$ is the production rate determined by Townsend coefficients, $\alpha_{j}$ is the Townsend coefficient for the reaction, $\mu_{e}$ is the mobility coefficient,
$V$ is the potential, $n_{e}$ is the electron density, and $D_{e}$ is the diffusion coefficient.
When converting the density to logarithmic form and applying a scaling factor of the mesh,
`ProcRate` is defined as

\begin{equation}
S_{Townsend} = \alpha_{j} N_{A} \left(\mu_{e} \frac{\nabla (V)}{l_{c}} \exp(N_{e}) - D_{e} \exp(N_{e}) \frac{\nabla (N_{e})}{l_{c}} \right)
\end{equation}

Where $N_{e}$ is the molar density of the electrons in logarithmic form, $N_{A}$ is Avogadro's
number, $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

An example of how to use `ProcRate` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=AuxKernels/ProcRate_el

!syntax parameters /AuxKernels/ProcRate

!syntax inputs /AuxKernels/ProcRate

!syntax children /AuxKernels/ProcRate
