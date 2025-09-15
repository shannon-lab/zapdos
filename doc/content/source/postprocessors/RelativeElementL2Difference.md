# RelativeElementL2Difference

!syntax description /Postprocessors/RelativeElementL2Difference

## Overview

`RelativeElementL2Difference` computes the relative L$_{2}$ difference between two variables. The relative L$_{2}$ difference is defined as:

\begin{equation}
  \frac{|| u - v ||_{L_2}}{|| u ||}
\end{equation}

Where:

- $u$ is the primary variable, and
- $v$ is the secondary variable.

## Example Input File Syntax

!listing test/tests/accelerations/Acceleration_By_Shooting_Method_Shooting.i block=Postprocessors/Meta_Relative_Diff

!syntax parameters /Postprocessors/RelativeElementL2Difference

!syntax inputs /Postprocessors/RelativeElementL2Difference

!syntax children /Postprocessors/RelativeElementL2Difference
