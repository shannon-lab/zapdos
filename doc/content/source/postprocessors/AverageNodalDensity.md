# AverageNodalDensity

!syntax description /Postprocessors/AverageNodalDensity

## Overview

Similar to the [AverageNodalVariableValue.md] postprocessor, `AverageNodalDensity` computes the average nodal value of variables in logarithmic form.
This is needed when calculating the nodal average of density values within Zapdos, since densities are in logarithmic form by default.
`AverageNodalDensity` returns the expression:

\begin{equation}
  \frac{\sum_{i=1}^{K} \exp(N_{i})}{K}
\end{equation}

Where:

- $N$ is the density in logarithmic form,
- $i$ is the nodal index, and
- $K$ is the total number of nodes.

!alert! note title=Untested Class
While `AverageNodalDensity` object does not have a stand-alone formalized test, yet, this object is called within the [AddPeriodicRelativeNodalDifference.md] action, which has a formalized test.
!alert-end!

## Example Input File Syntax

```text
[Postprocessors]
  [average_electron_density]
    type = AverageNodalDensity
    variable = electrons
  []
[]
```

!syntax parameters /Postprocessors/AverageNodalDensity

!syntax inputs /Postprocessors/AverageNodalDensity

!syntax children /Postprocessors/AverageNodalDensity
