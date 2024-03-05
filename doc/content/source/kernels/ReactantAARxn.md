# ReactantAARxn

!syntax description /Kernels/ReactantAARxn

## Overview

`ReactantAARxn` is a generic second-order reaction source term for the reactant of a reaction in the form of $2A \rightarrow 2B$.

The source term of this reaction for the products can be described as

\begin{equation}
S_{Loss} = \text{-} 2 k n_{A} n_{A}
\end{equation}

Where $S_{Loss}$ is the source term for the reactions, $k$ is the reaction rate coefficient, $n_{A}$ is the reactant specie. When converting
the density to logarithmic form, the strong form for `ReactantAARxn` is defined as

\begin{equation}
S_{Loss} = \text{-} 2 k \exp(N_{A} + N_{A})
\end{equation}

Where $N_{j}$ is the molar density of the specie in logarithmic form.

!alert note
When coupling Zapdos with CRANE, `ReactantAARxn` serves the same function as CRANE's [`ReactionSecondOrderLog`](/kernels/ReactionSecondOrderLog.md).

## Example Input File Syntax

An example of how to use `ReactantAARxn` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=Kernels/emliq_water_bi_sink

!syntax parameters /Kernels/ReactantAARxn

!syntax inputs /Kernels/ReactantAARxn

!syntax children /Kernels/ReactantAARxn
