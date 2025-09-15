# AddPeriodicRelativeNodalDifference

!syntax description /PeriodicRelativeNodalDifference/AddPeriodicRelativeNodalDifference

## Overview

The `PeriodicRelativeNodalDifference` provides the objects necessary to calculate the relative periodic difference of a variable (either in logarithmic or non-logarithmic form).

The relative periodic difference is defined as:

\begin{equation}
\epsilon = \sqrt{ \frac{\sum_{i=1}^{K}{\left[ \left( \frac{u_{i}}{u_{\text{avg}}} \right)_{P} - \left( \frac{u_{i}}{u_{\text{avg}}} \right)_{P-1} \right]^{2}} }{K^{2}} }
\end{equation}

Where:

- $u$ is the variable of interest,
- $u_{\text{avg}}$ is the spatial average of the variable,
- $P$ is the beginning of the current cycle,
- $P-1$ is the beginning of the previous cycle,
- $i$ is the nodal index, and
- $K$ is the total number of nodes.

## Example Input File Syntax

!listing test/tests/PeriodicRelativeNodalDifference/Sample_Periodic_Diffusion.i block=PeriodicRelativeNodalDifference

!syntax parameters /PeriodicRelativeNodalDifference/AddPeriodicRelativeNodalDifference
