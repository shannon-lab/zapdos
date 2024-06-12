# PenaltyCircuitPotential

!alert construction title=Undocumented Class
The PenaltyCircuitPotential has not been documented. The content listed below should be used as a starting point for
documenting the class, which includes the typical automatic documentation associated with a
MooseObject; however, what is contained is ultimately determined by what is necessary to make the
documentation clear for users.

!syntax description /BCs/PenaltyCircuitPotential

## Overview

`PenaltyCircuitPotential` is a [`PenaltyDirichlBC`](/bcs/ADPenaltyDirichletBC.md) for a potential based on Kirchoff's voltage law.

The formulation of the potential at the wall is:

\begin{equation}
V_{source} + V_{cathode} = J \ A \ R
\end{equation}

Where $V_{source}$ is driven the potential, $V_{cathode}$ is the potential at cathode,
$J$ is the current density, $A$ is the cross-sectional area of the plasma, and
$R$ is the ballast resistance. The current density is supplied through the [`CurrentDensityShapeSideUserObject`](/userobjects/CurrentDensityShapeSideUserObject.md).

## Example Input File Syntax

!! Describe and include an example of how to use the PenaltyCircuitPotential object.

!syntax parameters /BCs/PenaltyCircuitPotential

!syntax inputs /BCs/PenaltyCircuitPotential

!syntax children /BCs/PenaltyCircuitPotential
