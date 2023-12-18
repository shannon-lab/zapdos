# ProcRateForRateCoeffThreeBody

!syntax description /AuxKernels/ProcRateForRateCoeffThreeBody

## Overview

`ProcRateForRateCoeffThreeBody` returns the production rate for a three body reactions determined by rate coefficients in units of $\frac{\#}{m^{3}s}$.

The production rate is defined as

\begin{equation}
S_{Rate} =  k n_{i} n_{j} n_{k}
\end{equation}

Where $S_{Rate}$ is the production rate determined by rate coefficients, $k$ is the rate coefficient for the reaction, $n_{j}$ is the density for the first species, $n_{j}$ is the density for the second species, and $n_{k}$ is the density for the third species.
When converting the density to logarithmic form,
`ProcRateForRateCoeffThreeBody` is defined as

\begin{equation}
S_{Rate} = k N_{A}  \exp(N_{i}) \exp(N_{j}) \exp(N_{k})
\end{equation}

Where $N_{k}$, $N_{j}$ and $N_{k}$ is the molar density of the species in logarithmic form, and $N_{A}$ is Avogadro's
number.

!alert note
When coupling Zapdos with CRANE, `ProcRateForRateCoeffThreeBody` serves the same function as CRANE's [`ReactionRateThirdOrderLog`](/auxkernels/ReactionRateThirdOrderLog.md).

## Example Input File Syntax

An example of how to use `ProcRateForRateCoeffThreeBody` can be found in the
test file `Lymberopoulos_with_argon_metastables.i`.

!listing test/tests/Lymberopoulos_rf_discharge/Lymberopoulos_with_argon_metastables.i block=AuxKernels/ThreeBRate

!syntax parameters /AuxKernels/ProcRateForRateCoeffThreeBody

!syntax inputs /AuxKernels/ProcRateForRateCoeffThreeBody

!syntax children /AuxKernels/ProcRateForRateCoeffThreeBody
