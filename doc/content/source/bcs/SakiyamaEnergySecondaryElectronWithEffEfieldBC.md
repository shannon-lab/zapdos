# SakiyamaEnergySecondaryElectronWithEffEfieldBC

!syntax description /BCs/SakiyamaEnergySecondaryElectronWithEffEfieldBC

## Overview

`SakiyamaEnergySecondaryElectronWithEffEfieldBC` accounts for the mean electron energy density of secondary electrons induced by an ion flux outflow boundary condition. The effective electric field is supplied as scalar componets of the field.

The ion induced secondary electron mean energy density outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{j} \vec{E}_{\text{Eff.}} \cdot \textbf{n} > 0\\
0, & \mu_{j} \vec{E}_{\text{Eff.}} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{\epsilon} \cdot \textbf{n} = \gamma \frac{5}{3} \frac{n_{\epsilon}}{n_{e}} \left[a \ \mu_{j} 
\vec{E}_{\text{Eff.}} 
\cdot \textbf{n} \ n_{j} \right]
\end{equation}

where

- $\Gamma_\epsilon \cdot \textbf{n}$ is the flux normal to the boundary, 
- $\textbf{n}$ is the normal vector of the boundary,
- $\mu_{j}$ is the mobility coefficient, 
- $n_{\epsilon}$ is the mean energy density, 
- $n_{j}$ is the ion density, $\gamma$ is the secondary electron coefficient,
- $\vec{E}$ is the effective electric field (supplied as scalar components), and
- $a$ is defined such that the outflow is only non-zero when the drift velocity is directed towards the wall and zero otherwise. 

When converting the density to log form and applying a scaling factor of the mesh, the strong form for `SakiyamaEnergySecondaryElectronWithEffEfieldBC` is defined as

\begin{equation}
\Gamma_{\epsilon} \cdot \textbf{n} = \gamma \frac{5}{3} \exp(N_{\epsilon}-N_{e}) \left[a \ \mu_{j} 
\left( \vec{E}_{\text{Eff.}} / l_{c} \right) 
\cdot \textbf{n} \ \exp(N_{j}) \right]
\end{equation}

Where $N_{j}$ is the molar density of the species in log form and $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

!listing test/tests/mms/bcs/2D_EnergyBC.i block=BCs/energy_left_second_emissions

!syntax parameters /BCs/SakiyamaEnergySecondaryElectronWithEffEfieldBC

!syntax inputs /BCs/SakiyamaEnergySecondaryElectronWithEffEfieldBC

!syntax children /BCs/SakiyamaEnergySecondaryElectronWithEffEfieldBC
