# SakiyamaEnergySecondaryElectronBC

!syntax description /BCs/SakiyamaEnergySecondaryElectronBC

## Overview

`SakiyamaEnergySecondaryElectronBC` accounts for the mean electron energy density of secondary electrons induced by an ion flux outflow boundary condition.

The ion induced secondary electron mean energy density outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{j} \vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{j} \vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{\epsilon} \cdot \textbf{n} = \gamma \frac{5}{3} \frac{n_{\epsilon}}{n_{e}} \left[a \ \mu_{j} 
\vec{E} 
\cdot \textbf{n} \ n_{j} \right]
\end{equation}

Where $\Gamma_\epsilon \cdot \textbf{n}$ is the flux normal to the boundary, $\textbf{n}$ is the normal vector of the boundary,
$\mu_{j}$ is the mobility coefficient, $n_{\epsilon}$ is the mean energy density, $n_{j}$ is the ion density, $\gamma$ is the secondary electron coefficient, and $\vec{E}$ is the electric field. $a$ is defined such that the outflow is only non-zero when the drift velocity is directed towards the wall and zero otherwise. When converting the density to log form and applying a scaling factor of the mesh, the strong form for `SakiyamaEnergySecondaryElectronBC` is defined as

\begin{equation}
\Gamma_{\epsilon} \cdot \textbf{n} = \gamma \frac{5}{3} \exp(N_{\epsilon}-N_{e}) \left[a \ \mu_{j} 
\left( \vec{E} / l_{c} \right) 
\cdot \textbf{n} \ \exp(N_{j}) \right]
\end{equation}

Where $N_{j}$ is the molar density of the species in log form and $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax


!listing test/tests/DriftDiffusionAction/2D_RF_Plasma_actions.i block=BCs/mean_en_Ar+_second_emissions

!syntax parameters /BCs/SakiyamaEnergySecondaryElectronBC

!syntax inputs /BCs/SakiyamaEnergySecondaryElectronBC

!syntax children /BCs/SakiyamaEnergySecondaryElectronBC
