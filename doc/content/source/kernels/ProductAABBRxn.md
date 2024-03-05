# ProductAABBRxn

!syntax description /Kernels/ProductAABBRxn

## Overview

`ProductAABBRxn` is a generic second-order reaction source term for the products of a reaction in the form of $2A \rightarrow 2B$.

The source term of this reaction for the products can be described as

\begin{equation}
S_\text{Gain} = 2 k n_{A} n_{A}
\end{equation}

Where $S_\text{Gain}$ is the source term for the products, $k$ is the reaction rate coefficient, $n_{A}$ is the reactant specie. When converting
the density to logarithmic form, the strong form for `ProductAABBRxn` is defined as

\begin{equation}
S_\text{Gain} = 2 k \exp(N_{A} + N_{A})
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form.

!alert note
When coupling Zapdos with CRANE, `ProductAABBRxn` serves the same function as CRANE's [`ReactionSecondOrderLog`](/kernels/ReactionSecondOrderLog.md).

## Example Input File Syntax

An example of how to use `ProductAABBRxn` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=Kernels/OHm_product_aabb_rxn

!syntax parameters /Kernels/ProductAABBRxn

!syntax inputs /Kernels/ProductAABBRxn

!syntax children /Kernels/ProductAABBRxn
