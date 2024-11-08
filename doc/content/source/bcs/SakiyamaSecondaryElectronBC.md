# SakiyamaSecondaryElectronBC

!syntax description /BCs/SakiyamaSecondaryElectronBC

## Overview

`SakiyamaSecondaryElectronBC` accounts for the mean electron energy density of secondary electrons induced by an ion flux outflow boundary condition.

The ion induced secondary electron mean energy density outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{j} \vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{j} \vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{e} \cdot \textbf{n} = \gamma \left[a \ \mu_{j} \vec{E} \cdot \textbf{n} \ n_{j} \right]
\end{equation}

Where $\Gamma_e \cdot \textbf{n}$ is the flux normal to the boundary, $\textbf{n}$ is the normal vector of the boundary,
$\mu_{j}$ is the mobility coefficient, $n_{j}$ is the ion density, $\gamma$ is the secondary electron coefficient, and $\vec{E}$ is the electric field. $a$ is defined such that the outflow is only non-zero when the drift velocity is directed towards the wall and zero otherwise. When converting the density to log form and applying a scaling factor of the mesh, the strong form for `SakiyamaSecondaryElectronBC` is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = \gamma \left[a \ \mu_{j} \left( \vec{E} / l_{c} \right) \cdot \textbf{n} \ \exp(N_{j}) \right]
\end{equation}

Where $N_{j}$ is the molar density of the species in log form and $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax


!listing test/tests/DriftDiffusionAction/2D_RF_Plasma_actions.i block=BCs/em_Ar+_second_emissions

!syntax parameters /BCs/SakiyamaSecondaryElectronBC

!syntax inputs /BCs/SakiyamaSecondaryElectronBC

!syntax children /BCs/SakiyamaSecondaryElectronBC
