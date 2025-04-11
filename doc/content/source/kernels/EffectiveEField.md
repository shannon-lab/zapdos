# EffectiveEField

!syntax description /Kernels/EffectiveEField

## Overview

`EffectiveEField` supplies the source term of the time derivative calculation of an
effective electric field for ions.

This object supplies the right hand term of the following equation:
\begin{equation}
\frac{\vec{E}_{\text{Eff.}}}{\partial t} = \nu_{i} \left( \vec{E} - \vec{E}_{\text{Eff.}} \right)
\end{equation}

where

- $\vec{E}_{\text{Eff.}}$ is the effective electric field acting on the ions,
- $\vec{E}$ is the electric field, and
- $\nu_{i}$ is the ion-collision frequency.

## Example Input File Syntax

!listing test/tests/mms/continuity_equations/2D_Coupling_Electons_Potential_Ions_MeanEnergy_Einstein_Relation_EffEfield.i block=Kernels/EffEfield_X_ForceBody

!syntax parameters /Kernels/EffectiveEField

!syntax inputs /Kernels/EffectiveEField

!syntax children /Kernels/EffectiveEField
