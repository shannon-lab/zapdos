# PotentialDriftOutflowBC

!alert construction title=Undocumented Class
The PotentialDriftOutflowBC has not been documented. The content listed below should be used as a starting point for
documenting the class, which includes the typical automatic documentation associated with a
MooseObject; however, what is contained is ultimately determined by what is necessary to make the
documentation clear for users.

!syntax description /BCs/PotentialDriftOutflowBC

## Overview

`PotentialDriftOutflowBC` is an electric field driven outflow boundary condition.
`PotentialDriftOutflowBC` assumes a mobility coefficient of unity, the electrostatic approximation for the electric field, and a non-scaled version of the species' density.

The electrostatic electric field driven outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \text{sign}_{j} \ \text{-} \nabla (V) \cdot \textbf{n} > 0\\
0, & \text{sign}_{j} \ \text{-} \nabla (V) \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = a \ \text{sign}_{j} \ \text{-} \nabla (V) \cdot \textbf{n} \ n_{j}
\end{equation}

When calculating with scaled densities and non-unity coefficients, please refer to [`HagelaarIonAdvectionBC`](/bcs/HagelaarIonAdvectionBC.md), [`DCIonBC`](/bcs/DCIonBC.md), or [`SakiyamaIonAdvectionBC`](/bcs/SakiyamaIonAdvectionBC.md).

## Example Input File Syntax

!! Describe and include an example of how to use the PotentialDriftOutflowBC object.

!syntax parameters /BCs/PotentialDriftOutflowBC

!syntax inputs /BCs/PotentialDriftOutflowBC

!syntax children /BCs/PotentialDriftOutflowBC
