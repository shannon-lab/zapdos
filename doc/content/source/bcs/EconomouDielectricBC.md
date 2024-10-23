# EconomouDielectricBC

!syntax description /BCs/EconomouDielectricBC

## Overview

`EconomouDielectricBC` is a type of [`PenaltyDirichletBC`](/bcs/ADPenaltyDirichletBC.md) for the potential on the boundary of a grounded ideal dielectric.

The potential at the boundary of a grounded ideal dielectric is defined as

\begin{equation}
\frac{\epsilon_{i}}{d_{i}}\frac{\partial V_{i}}{\partial t} = e(\Gamma_{+} \cdot \textbf{n} -\Gamma_{e} \cdot \textbf{n})+\epsilon_{0}\frac{\partial (E \cdot \textbf{n}) }{\partial t} \\[10pt]
E = \text{-} \nabla (V)\\[10pt]
\Gamma_{e} \cdot \textbf{n}  = \frac{1}{4}\sqrt{\frac{8 k T_{e}}{\pi m_{e}}} \ n_e - \gamma \Gamma_{+} \cdot \textbf{n} \\[10pt]
\Gamma_{+} \cdot \textbf{n}  = a \ \mu_{+} \ \text{-} \nabla (V) \cdot \textbf{n} \ n_{+} \\[10pt]
a =
\begin{cases}
1, & \mu_{j} \ \text{-} \nabla (V) \cdot \textbf{n} > 0\\
0, & \mu_{j} \ \text{-} \nabla (V) \cdot \textbf{n} \leq 0\\
\end{cases}
\end{equation}

Where $\epsilon_{i}$ is the permittivity of the dielectric, $d_{i}$ is the thickness of the dielectric, $V_{i}$ is the voltage on the dielectric, $\textbf{n}$ is the normal to the boundary, $e$ is the elemental charge, $\epsilon_{0}$ is the permittivity of free space, and $E$ is the E-field normal to the dielectric. $\Gamma_{e}$ and $\Gamma_{+}$ are the electron and ion outflow flux and are defined with the [`SakiyamaElectronDiffusionBC`](/bcs/SakiyamaElectronDiffusionBC.md), [`SakiyamaSecondaryElectronBC`](/bcs/SakiyamaSecondaryElectronBC.md) and [`SakiyamaIonAdvectionBC`](/bcs/SakiyamaIonAdvectionBC.md) (please refer to those BC's for more information on the fluxes).

## Example Input File Syntax


!listing test/tests/DriftDiffusionAction/2D_RF_Plasma_actions.i block=BCs/potential_Dielectric

!syntax parameters /BCs/EconomouDielectricBC

!syntax inputs /BCs/EconomouDielectricBC

!syntax children /BCs/EconomouDielectricBC
