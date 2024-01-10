# ProductFirstOrderRxn

!syntax description /Kernels/ProductFirstOrderRxn

## Overview

`ProductFirstOrderRxn` is a generic first reaction source term for the products of a reaction in the form of $A \rightarrow B$.

The source term of this reaction for the products can be described as

\begin{equation}
S_{Gain} = k n_{A}
\end{equation}

Where $S_{Gain}$ is the source term for the products, $k$ is the reaction rate coefficient, $n_{A}$ is the reactant specie.When converting
the density to logarithmic form, the strong form for `ProductFirstOrderRxn` is defined as

\begin{equation}
S_{Gain} = k \exp(N_{A})
\end{equation}

Where $N_{j}$ is the molar density of the specie in logarithmic form.

!alert note
When coupling Zapdos with CRANE, `ProductFirstOrderRxn` serves the same function as CRANE's [`ReactionFirstOrderLog`](/kernels/ReactionFirstOrderLog.md).

## Example Input File Syntax

An example of how to use `ProductFirstOrderRxn` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=Kernels/OHm_product_first_order_rxn

!syntax parameters /Kernels/ProductFirstOrderRxn

!syntax inputs /Kernels/ProductFirstOrderRxn

!syntax children /Kernels/ProductFirstOrderRxn
