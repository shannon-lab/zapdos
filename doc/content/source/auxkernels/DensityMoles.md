# DensityMoles

!syntax description /AuxKernels/DensityMoles

## Overview

`DensityMoles` converts the density value of a coupled species from a logarithmic molar density into units of #/m$^{3}$, such that:

\begin{equation}
n_{j} = N_{A} \exp(N_{j})
\end{equation}

Where $n_{j}$ is the density, $N_{j}$ is the molar density of the specie in logarithmic form, and $N_{A}$ is Avogadro's number. This is often needed due to Zapdos solving densities using a logarithmic molar formulation to help avoid negative densities and ill-conditioned matrices.

## Example Input File Syntax

An example of how to use `DensityMoles` can be found in the
test file `Lymberopoulos_with_argon_metastables.i`.

!listing test/tests/Lymberopoulos_rf_discharge/Lymberopoulos_with_argon_metastables.i block=AuxKernels/em_lin

!syntax parameters /AuxKernels/DensityMoles

!syntax inputs /AuxKernels/DensityMoles

!syntax children /AuxKernels/DensityMoles
