# LogDensityDirichletBC

!syntax description /BCs/LogDensityDirichletBC

## Overview

`LogDensityDirichletBC` is a Dirichlet boundary condition for molar density of the species in logarithmic form.

The formulation of the density at the wall is:

\begin{equation}
n_{j} = N_{A} \exp(N_{j})
\end{equation}

Where $n_{j}$ is the density, $N_{j}$ is the molar density of the specie in logarithmic form, and $N_{A}$ is Avogadro's
number.

## Example Input File Syntax

An example of how to use `LogDensityDirichletBC` can be found in the
test file `RF_Plasma_actions.i`.

!listing test/tests/DriftDiffusionAction/RF_Plasma_actions.i block=BCs/Ar*_physical_right_diffusion

!syntax parameters /BCs/LogDensityDirichletBC

!syntax inputs /BCs/LogDensityDirichletBC

!syntax children /BCs/LogDensityDirichletBC
