# PenaltyCircuitPotential

!syntax description /BCs/PenaltyCircuitPotential

## Overview

`PenaltyCircuitPotential` is a [`PenaltyDirichlBC`](/bcs/ADPenaltyDirichletBC.md) for a potential based on Kirchoff's voltage law.

The formulation of the potential at the wall is:

\begin{equation}
V_\text{source} + V_\text{cathode} = J \ A \ R
\end{equation}

Where $V_\text{source}$ is driven the potential, $V_\text{cathode}$ is the potential at cathode,
$J$ is the current density, $A$ is the cross-sectional area of the plasma, and
$R$ is the ballast resistance. The current density is supplied through the [`CurrentDensityShapeSideUserObject`](/userobjects/CurrentDensityShapeSideUserObject.md).

## Example Input File Syntax

!listing test/tests/1d_dc/NonlocalPotentialBCWithSchottky.i block=BCs/potential_left

!syntax parameters /BCs/PenaltyCircuitPotential

!syntax inputs /BCs/PenaltyCircuitPotential

!syntax children /BCs/PenaltyCircuitPotential
