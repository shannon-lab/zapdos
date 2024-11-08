# ProcRate

!syntax description /AuxKernels/ProcRate

## Overview

`ProcRate` returns the production rate for chemistry reactions determined by Townsend coefficients in units of #/m$^{3}$s.

The production rate is defined as

\begin{equation}
S_{\text{Townsend}} = \alpha_{j} (\mu_{e} \vec{E} n_{e} - D_{e} \nabla (n_{e}))
\end{equation}

Where $S_{\text{Townsend}}$ is the production rate determined by Townsend coefficients, $\alpha_{j}$ is the Townsend coefficient for the reaction, $\mu_{e}$ is the mobility coefficient,
$\vec{E}$ is the electric field, $n_{e}$ is the electron density, and $D_{e}$ is the diffusion coefficient.
When converting the density to logarithmic form and applying a scaling factor of the mesh,
`ProcRate` is defined as

\begin{equation}
S_{\text{Townsend}} = \alpha_{j} N_{A} \left(\mu_{e} \frac{\vec{E}}{l_{c}} \exp(N_{e}) - D_{e} \exp(N_{e}) \frac{\nabla (N_{e})}{l_{c}} \right)
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
