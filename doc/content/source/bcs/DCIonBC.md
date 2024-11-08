# DCIonBC

!syntax description /BCs/DCIonBC

## Overview

`DCIonBC` is an electric field driven outflow boundary condition.

The electric field driven outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \text{sign}_{j} \mu_{j} \ \vec{E} \cdot \textbf{n} > 0\\
0, & \text{sign}_{j} \mu_{j} \ \vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = a \ \text{sign}_{j} \mu_{j} \ \vec{E} \cdot \textbf{n} \ n_{j}
\end{equation}

Where $\Gamma$ is the outflow normal to the boundary, $\textbf{n}$ is the normal vector of the boundary, $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species), $\mu_{j}$ is the mobility coefficient, $n_{j}$ is the density, and $\vec{E}$ is
the electric field. $a$ is defined such that the outflow is only defined when the drift velocity is direct towards the wall and zero otherwise. When converting the density to logarithmic form and applying a scaling
factor of the mesh, the strong form for `DCIonBC` is defined as

\begin{equation}
a =
\begin{cases}
1, & \text{sign}_{j} \mu_{j} \ \vec{E} \cdot \textbf{n} > 0\\
0, & \text{sign}_{j} \mu_{j} \ \vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = a \ \text{sign}_{j} \mu_{j} \ \left(\vec{E} / l_{c} \right) \cdot \textbf{n} \ \exp(N_{j})
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form and
$l_{c}$ is the scaling factor of the mesh.


## Example Input File Syntax

!listing test/tests/1d_dc/mean_en.i block=BCs/OHm_physical

!syntax parameters /BCs/DCIonBC

!syntax inputs /BCs/DCIonBC

!syntax children /BCs/DCIonBC
