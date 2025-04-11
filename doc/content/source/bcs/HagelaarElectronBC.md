# HagelaarElectronBC

!syntax description /BCs/HagelaarElectronBC

## Overview

`HagelaarElectronBC` is an electric field driven and thermal outflow boundary condition.

The electric field and thermal driven outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{e} \ -\vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{e} \ -\vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
v_{\text{th},e} = \sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \frac{n_{\varepsilon}}{n_{e}}} \\[10pt]
\Gamma_{e} \cdot \textbf{n} = \frac{1-r_{e}}{1+r_{e}} \left[ -(2 a_{e}-1) \ \mu_{e} 
\vec{E} 
\cdot \textbf{n} \ n_{e} + \frac{1}{2}v_{\text{th},e}n_{e} \right]
\end{equation}

Where $\Gamma_e \cdot \textbf{n}$ is the outflow normal to the boundary, $\textbf{n}$ is the normal of the boundary,
$\mu_{e}$ is the mobility coefficient, $n_{e}$ is the electron density, $\vec{E}$ is
the electric field, $v_{\text{th},e}$ is the thermal velocity of the electrons, $e$ is the elementary charge, and $n_{\varepsilon}$ is the mean energy density. $a$ is defined such that the outflow is only defined when the drift velocity is directed towards the wall and zero otherwise. $r_e$ is defined as the fraction of particles reflected by the surface. When converting the density to log form and applying a scaling
factor of the mesh, the strong form for `HagelaarElectronBC` is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{e} \ -\vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{e} \ -\vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
v_{\text{th},e} = \sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \exp (N_{\varepsilon} - N_{e})} \\[10pt]
\Gamma_{e} \cdot \textbf{n} = \frac{1-r_{e}}{1+r_{e}} \left[ -(2 a_{e}-1) \ \mu_{e}
\left( \vec{E} / l_{c} \right)
\cdot \textbf{n} \ \exp(N_{e})  + \frac{1}{2}
v_{\text{th},e}
\exp(N_{e}) \right]
\end{equation}

Where $N_{j}$ is the molar density of the species in log form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax


!listing test/tests/1d_dc/mean_en.i block=BCs/em_physical_right

!syntax parameters /BCs/HagelaarElectronBC

!syntax inputs /BCs/HagelaarElectronBC

!syntax children /BCs/HagelaarElectronBC
