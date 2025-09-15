# AverageNodalDifference

!syntax description /Postprocessors/AverageNodalDifference

## Overview

`AverageNodalDifference` computes the nodal differences between two variables. 
`AverageNodalDifference` returns the expression:

\begin{equation}
  \sqrt{ \frac{\sum_{i=1}^{K} \left( u_{i} - v_{i} \right)^{2}}{K^{2}} }
\end{equation}

Where:

- $u$ is the first variable,
- $v$ is the second variable,
- $i$ is the nodal index, and
- $K$ is the total number of nodes.

!alert! note title=Untested Class
While `AverageNodalDifference` object does not have a stand-alone formalized test, yet, this object is called within the [AddPeriodicRelativeNodalDifference.md] action, which has a formalized test.
!alert-end!

## Example Input File Syntax

```text
[Postprocessors]
  [average_difference]
    type = AverageNodalDifference
    variable = electrons
    other_variable = ions
  []
[]
```

!syntax parameters /Postprocessors/AverageNodalDifference

!syntax inputs /Postprocessors/AverageNodalDifference

!syntax children /Postprocessors/AverageNodalDifference
