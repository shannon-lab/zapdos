# SakiyamaIonAdvectionWithEffEfieldBC

!syntax description /BCs/SakiyamaIonAdvectionWithEffEfieldBC

## Overview

`SakiyamaIonAdvectionWithEffEfieldBC` is an electric field driven outflow boundary condition. The effective electric field is supplied as scalar componets of the field.

The ion outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{j} \vec{E}_{\text{Eff.}} \cdot \textbf{n} > 0\\
0, & \mu_{j} \vec{E}_{\text{Eff.}} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = a \ \mu_{j} \vec{E}_{\text{Eff.}} \cdot \textbf{n} \ n_{j}
\end{equation}

Where 

- $\Gamma$ is the outflow normal to the boundary, 
- $\textbf{n}$ is the normal of the boundary,
- $\mu_{j}$ is the mobility coefficient, 
- $n_{j}$ is the species density, 
- $\vec{E}_{\text{Eff.}}$ is the electric field (supplied as scalar components), and
- $a$ is defined such that the outflow is only non-zero when the drift velocity is directed towards the wall and zero otherwise. 

When converting the density to log form and applying a scaling factor of the mesh, the strong form for `SakiyamaIonAdvectionWithEffEfieldBC` is defined as

\begin{equation}
\Gamma_{j} \cdot \textbf{n} = a \ \mu_{j} \left( \vec{E}_{\text{Eff.}} / l_{c} \right) \cdot \textbf{n} \ \exp(N_{j})
\end{equation}

Where $N_{j}$ is the molar density of the species in log form and $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

!listing test/tests/mms/bcs/2D_IonBC.i block=BCs/ion_left_physical_advection

!syntax parameters /BCs/SakiyamaIonAdvectionWithEffEfieldBC

!syntax inputs /BCs/SakiyamaIonAdvectionWithEffEfieldBC

!syntax children /BCs/SakiyamaIonAdvectionWithEffEfieldBC
