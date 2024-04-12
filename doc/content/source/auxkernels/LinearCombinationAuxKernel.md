# LinearCombinationAuxKernel

`LinearCombinationAuxKernel` allows you to calculate the linear combination of several coupled variables.

\begin{equation}
  f = \sum_{i=1}^n w_i x_i + b
\end{equation}

Where $w$ is the weighting factor per coupled variable, $x$ is an array of coupled variables to be summed, the subscript $i$ is the ith component of the weighted summands, and b is the linear shift of the weighted sum.



## Example Input File Syntax

!listing test/tests/auxkernels/linear_combination_aux/linear_combination.i block=AuxKernels

!syntax parameters /AuxKernels/LinearCombinationAuxKernel

!syntax inputs /AuxKernels/LinearCombinationAuxKernel

!syntax children /AuxKernels/LinearCombinationAuxKernel
