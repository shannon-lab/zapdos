# HagelaarEnergyBC

!syntax description /BCs/HagelaarEnergyBC

## Overview

`HagelaarEnergyBC` is an electric field driven and thermal outflow boundary condition.

The electric field and thermal driven outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{\epsilon} \ -\vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{\epsilon} \ -\vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
v_{\text{th},e} = \sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \frac{n_{\epsilon}}{n_{e}}} \\[10pt]
\Gamma_{\epsilon} \cdot \textbf{n} = \frac{1-r_{\epsilon}}{1+r_{\epsilon}} \left[ -(2 a_{\epsilon}-1) \ \mu_{\epsilon}
\vec{E} 
    \cdot \textbf{n} \ n_{\epsilon} + \frac{5}{6}v_{\text{th},e}n_{\epsilon} \right]
\end{equation}

Where $\Gamma_{\epsilon} \cdot \textbf{n}$ is the outflow normal to the boundary, $\textbf{n}$ is the normal vector of the boundary,
$\mu_{\epsilon}$ is the mobility coefficient, $n_{\epsilon}$ is the mean energy density, $n_{e}$ is the electron density, $\vec{E}$ is
the electric field, $v_{\text{th},e}$ is the thermal velocity of the electrons, and $e$ is the elementary charge. $a$ is defined such that the outflow is only defined when the drift velocity is directed towards the wall and zero otherwise. $r$ is defined as the fraction of particles that are reflected by the surface. When converting the density to log form and applying a scaling
factor of the mesh, the strong form for `HagelaarEnergyBC` is defined as

\begin{equation}
a =
\begin{cases}
1, & \mu_{\epsilon} \ -\vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{\epsilon} \ -\vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
v_{\text{th},e} = \sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \exp (N_{\varepsilon} - N_{e})} \\[10pt]
\Gamma_{\epsilon} \cdot \textbf{n} = \frac{1-r_{\epsilon}}{1+r_{\epsilon}} \left[ -(2 a_{\epsilon}-1) \ \mu_{\epsilon} 
\left( 
\vec{E} / l_{c} 
\right)
\cdot \textbf{n} \ \exp(N_{\epsilon})  + \frac{5}{6}v_{\text{th},e}\exp(N_{\epsilon}) \right]
\end{equation}

Where $N_{\epsilon}$ is the molar energy density of the species in log form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax


!listing test/tests/1d_dc/mean_en.i block=BCs/mean_en_physical_right

!syntax parameters /BCs/HagelaarEnergyBC

!syntax inputs /BCs/HagelaarEnergyBC

!syntax children /BCs/HagelaarEnergyBC
