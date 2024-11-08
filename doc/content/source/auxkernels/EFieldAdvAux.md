# EFieldAdvAux

!syntax description /AuxKernels/EFieldAdvAux

## Overview

`EFieldAdvAux` returns electric field driven advective flux of defined species in logarithmic form.

The advective flux is defined as

\begin{equation}
\Gamma_{\text{Advection}}  = \text{sign}_{j} \mu_{j} \vec{E} n_{j}
\end{equation}

Where $\Gamma_{\text{Advection}}$ is the advective flux, $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species), $\mu_{j}$ is the mobility coefficient, $\vec{E}$ is the electric field, and $n_{j}$ is the density. When converting the density to logarithmic form and applying a scaling factor of the mesh,
`EFieldAdvAux` is defined as

\begin{equation}
\Gamma_{\text{Advection}}  = N_{A} \text{sign}_{j} \mu_{j} \frac{\vec{E}}{l_{c}} \exp(N_{j})
\end{equation}

Where $N_{j}$ is the molar density of the specie in logarithmic form, $N_{A}$ is Avogadro's
number, $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

An example of how to use `EFieldAdvAux` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=AuxKernels/EFieldAdvAux_em

!syntax parameters /AuxKernels/EFieldAdvAux

!syntax inputs /AuxKernels/EFieldAdvAux

!syntax children /AuxKernels/EFieldAdvAux
