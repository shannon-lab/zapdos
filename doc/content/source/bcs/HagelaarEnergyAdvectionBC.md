# HagelaarEnergyAdvectionBC

!syntax description /BCs/HagelaarEnergyAdvectionBC

## Overview

`HagelaarEnergyAdvectionBC` is an electric field driven outflow boundary condition with the addition of ion induced secondary electron energy.

The outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{e} \ -\vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{e} \ -\vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{\epsilon} \cdot \textbf{n} = \frac{1-r_{e}}{1+r_{e}} \left[ -(2 a_{e}-1) \frac{5}{3}  \mu_{e} \text{-} \nabla (V) \cdot \textbf{n} \ n_{e} \ \epsilon \right] - \frac{5}{3} \epsilon_{\gamma} (1 - a_{e}) \gamma \left[ \mu_{+} \ 
\vec{E}
\cdot \textbf{n} \ n_{+} \right]
\end{equation}


Where $\Gamma_{\epsilon} \cdot \textbf{n}$ is the outflow of the electron energy density normal to the boundary, $\textbf{n}$ is the normal vector of the boundary, $n_{e}$ is the electron density, $n_{+}$ is the mean energy density, $\mu_{j}$ is the mobility coefficient, $\vec{E}$ is the electric field, $\epsilon_{\gamma}$ is the energy of the secondary electron, and $\gamma$ is the ion induced secondary electron coefficient. $a$ is defined such that the outflow is only defined when the drift velocity is directed towards the wall and zero otherwise. $r$ is defined as the fraction of particles reflected by the surface. When converting the density to log form and applying a scaling
factor of the mesh, the strong form for `HagelaarEnergyAdvectionBC` is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{e} \ \vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{e} \ \vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{\epsilon} \cdot \textbf{n} = \frac{1-r_{e}}{1+r_{e}} \left[ -(2 a_{e}-1) \frac{5}{3}  \mu_{e}
\left( 
\vec{E} / l_{c}
\right) 
  \cdot \textbf{n} \ \exp(N_{e}) \ \epsilon \right] - \frac{5}{3} \epsilon_{\gamma} (1 - a_{e}) \gamma \left[ \mu_{+} \ 
 \left( 
 \vec{E} / l_{c}
 \right)
  \cdot \textbf{n} \ \exp(N_{+}) \right]
\end{equation}

Where $N_{j}$ is the molar density of the species in log form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax


!listing test/tests/reflections/Schottky_300_V_5_um/Input.i block=BCs/mean_en_physical_left

!syntax parameters /BCs/HagelaarEnergyAdvectionBC

!syntax inputs /BCs/HagelaarEnergyAdvectionBC

!syntax children /BCs/HagelaarEnergyAdvectionBC
