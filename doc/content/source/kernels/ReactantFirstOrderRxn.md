# ReactantFirstOrderRxn

!syntax description /Kernels/ReactantFirstOrderRxn

## Overview

`ReactantFirstOrderRxn` is a generic first reaction source term for the reactants of a reaction in the form of $A \rightarrow B$.

The source term of this reaction for the products can be described as

\begin{equation}
S_{Gain} = \text{-} k n_{A}
\end{equation}

Where $S_{Gain}$ is the source term for the reactant, $k$ is the reaction rate coefficient, $n_{A}$ is the reactant specie.When converting
the density to logarithmic form, the strong form for `ReactantFirstOrderRxn` is defined as

\begin{equation}
S_{Gain} = \text{-} k \exp(N_{A})
\end{equation}

Where $N_{j}$ is the molar density of the specie in logarithmic form.

!alert note
When coupling Zapdos with CRANE, `ReactantFirstOrderRxn` serves the same function as CRANE's [`ReactionFirstOrderLog`](/kernels/ReactionFirstOrderLog.md).

## Example Input File Syntax

An example of how to use `ReactantFirstOrderRxn` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=Kernels/emliq_reactant_first_order_rxn

!syntax parameters /Kernels/ReactantFirstOrderRxn

!syntax inputs /Kernels/ReactantFirstOrderRxn

!syntax children /Kernels/ReactantFirstOrderRxn
