# SakiyamaIonAdvectionBC

!syntax description /BCs/SakiyamaIonAdvectionBC

## Overview

`SakiyamaIonAdvectionBC` is an electric field driven outflow boundary condition.
`SakiyamaIonAdvectionBC` assumes the electrostatic approximation for the electric field.

The ion induce secondary electron mean energy density outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{j} \ \text{-} \nabla (V) \cdot \textbf{n} > 0\\
0, & \mu_{j} \ \text{-} \nabla (V) \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = a \ \mu_{j} \ \text{-} \nabla (V) \cdot \textbf{n} \ n_{j}
\end{equation}

Where $\Gamma$ is the outflow normal to the boundary, $\textbf{n}$ is the normal of the boundary,
$\mu_{j}$ is the mobility coefficient, $n_{j}$ is the specie density, and $V$ is the potential. $a$ is defined such that the outflow is only defined when the drift velocity is direct towards the wall and zero otherwise. When converting the density to log form and applying a scaling factor of the mesh, the strong form for `SakiyamaIonAdvectionBC` is defined as

\begin{equation}
\Gamma_{j} \cdot \textbf{n} = a \ \mu_{j} \ \text{-} \nabla (V / l_{c}) \cdot \textbf{n} \ \exp(N_{j})
\end{equation}

Where $N_{j}$ is the molar density of the specie in log form and $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

An example of how to use `SakiyamaIonAdvectionBC` can be found in the
test file `2D_RF_Plasma_actions.i`.

!listing test/tests/DriftDiffusionAction/2D_RF_Plasma_actions.i block=BCs/Ar+_physical_advection

!syntax parameters /BCs/SakiyamaIonAdvectionBC

!syntax inputs /BCs/SakiyamaIonAdvectionBC

!syntax children /BCs/SakiyamaIonAdvectionBC
