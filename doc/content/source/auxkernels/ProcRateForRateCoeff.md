# ProcRateForRateCoeff

!syntax description /AuxKernels/ProcRateForRateCoeff

## Overview

`ProcRateForRateCoeff` returns the production rate for a two body reactions determined by rate coefficients in units of #/m$^{3}$s.

The production rate is defined as

\begin{equation}
S_{\text{Rate}} = k n_{i} n_{j}
\end{equation}

Where $S_{\text{Rate}}$ is the production rate determined by rate coefficients, $k$ is the rate coefficient for the reaction, $n_{j}$ is the density for the first species, and $n_{j}$ is the density for the second species.
When converting the density to logarithmic form,
`ProcRateForRateCoeff` is defined as

\begin{equation}
S_{\text{Rate}} = k N_{A}  \exp(N_{i}) \exp(N_{j})
\end{equation}

Where $N_{i}$ and $N_{j}$ is the molar density of the species in logarithmic form, and $N_{A}$ is Avogadro's
number.

!alert note
When coupling Zapdos with CRANE, `ProcRateForRateCoeff` serves the same function as CRANE's [`ReactionRateSecondOrderLog`](/auxkernels/ReactionRateSecondOrderLog.md).

## Example Input File Syntax

An example of how to use `ProcRateForRateCoeff` can be found in the
test file `Lymberopoulos_with_argon_metastables.i`.

!listing test/tests/Lymberopoulos_rf_discharge/Lymberopoulos_with_argon_metastables.i block=AuxKernels/emRate

!syntax parameters /AuxKernels/ProcRateForRateCoeff

!syntax inputs /AuxKernels/ProcRateForRateCoeff

!syntax children /AuxKernels/ProcRateForRateCoeff
