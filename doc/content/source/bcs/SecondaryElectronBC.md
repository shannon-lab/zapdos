# SecondaryElectronBC

!syntax description /BCs/SecondaryElectronBC

## Overview

`SecondaryElectronBC` is an electron mean energy density of secondary electrons induced by ion flux outflow boundary condition.

\begin{equation}
a_{e} =
\begin{cases}
1, & \mu_{e} \left( -\vec{E} \right) \cdot \textbf{n} > 0\\
0, & \mu_{e} \left( -\vec{E} \right)\cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
a_{i} =
\begin{cases}
1, & \mu_{i} \vec{E} \cdot \textbf{n} > 0\\
0, & \mu_{i} \vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{e} \cdot \textbf{n} = \frac{1 - r_{e}}{1 + r_{e}} \frac{\text{-}1}{2} v_{\text{th},e} n_{\gamma} - \frac{2}{1+r} (1 - a_{e}) \gamma \Gamma_{j} \cdot \textbf{n} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = \frac{1-r_{j}}{1+r_{j}} \left[ (2 a_{j}-1) \ \mu_{j}
\vec{E}
 \cdot \textbf{n} \ n_{j} + \frac{1}{2}v_{\text{th},j}n_{j} \right] \\[10pt]
v_{\text{th},e} = \sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \frac{n_{\varepsilon}}{n_{e}}} \\[10pt]
v_{\text{th},j} = \sqrt{\frac{8k_{B}T}{\pi m_{j}}} \\[10pt]
n_{\gamma} = (1 - a_{e}) \frac{\gamma \Gamma_{i} \cdot \textbf{n}}{\mu_{e} \vec{E} \cdot \textbf{n}}
\end{equation}

Where the subscripts $e$, $j$ and $\varepsilon$ represents properties of electrons, ions and electron energy respectively, $\Gamma$ is the flux of the electron or ions, $\textbf{n}$ is the normal vector of the boundary,
$\mu$ is the mobility coefficient, $n$ is the species density, $v_\text{th}$ is the thermal velocity of the species, $k_{B}$ is the Boltzmann constant, $T$ is the gas temperature, $\vec{E}$ is the electric field, and $n_{\gamma}$ is electron density emitted by the surface. $a$ is defined such that the outflow is non-zero when the drift velocity is directed towards the wall and zero otherwise. $r$ is defined as the fraction of particles reflected by the surface. When converting the density to log form and applying a scaling factor of the mesh, the strong form for `SecondaryElectronBC` is defined as

\begin{equation}
v_{\text{th},e} = \sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \exp (N_{\varepsilon} - N_{e})} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = \frac{1-r_{j}}{1+r_{j}} \left[ (2 a_{j}-1) \ \mu_{j} \left( \vec{E} / l_{c} \right) \cdot \textbf{n} \ \exp(N_{j}) + \frac{1}{2}v_{\text{th},j}\exp(N_{j}) \right]
\end{equation}

Where $N_{e}$, $N_{i}$ and $N_{\varepsilon}$ is the molar density of the electrons, ions and electron energy in logarithmic form and $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax


!listing test/tests/1d_dc/mean_en.i block=BCs/sec_electrons_left

!syntax parameters /BCs/SecondaryElectronBC

!syntax inputs /BCs/SecondaryElectronBC

!syntax children /BCs/SecondaryElectronBC
