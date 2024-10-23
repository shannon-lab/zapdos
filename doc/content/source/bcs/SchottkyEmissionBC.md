# SchottkyEmissionBC

!syntax description /BCs/SchottkyEmissionBC

## Overview

`SchottkyEmissionBC` is an outflow boundary condition that assumes the electron current density is defined by field ehanced thermionic emission, Schottky emission.

Using a Richardson equation for the field emission, the electron current density is defined as

\begin{equation}
a_{e} =
\begin{cases}
1, & \nabla (V) \cdot \textbf{n} > 0\\
0, & \nabla (V) \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\textbf{J}_{\textbf{e}} \cdot \textbf{n} = A_{G} T^{2} \exp\left( \frac{\text{-} \left( \phi - \Delta \phi \right) }{ k_{B} T} \right) \\[10pt]
F =  \left( 1-a_{e} \right) \gamma \left( \text{-} \nabla V \right) \cdot \textbf{n} \\[10pt]
\Delta \phi = \sqrt{\frac{e^{3} F}{4 \pi \epsilon_{0}}} 
\end{equation}

Where $\textbf{J}_{\textbf{e}}$ is the electron current density, $A_{G}$ is the Richardson coefficient, $T$ is the temperature of the cathode, $k_{B}$ is Boltzmann constant in units of eV/K, $\phi$ is the local work function, $\Delta \phi$ is the difference in the work funtion due to the electric field, $F$ is the local field, $\textbf{n}$ is the normal vector of the boundary, $\gamma$ is the field enhancement factor, and $V$ is the potential. $a_{e}$ is defined such that the outflow is only defined when the drift velocity is direct towards the wall and zero otherwise. With the electron current density, the outward electron flux is defined as

\begin{equation}
\Gamma_{i} \cdot \textbf{n}  = \text{sign}_{i} \mu_{i} \ \text{-} \nabla (V) n_{i} - D_{i} \nabla (n_{i}) \\[10pt]
\Gamma_{e} \cdot \textbf{n}  = \frac{2 (1 - a_{e})}{1 + r} (\text{-} (\textbf{J}_{\textbf{e}} \cdot \textbf{n})/e - \gamma_{se} \Gamma_{i} \cdot \textbf{n})
\end{equation}

Where $\Gamma$ is the outflow normal to the boundary, $\mu_{i}$ is the mobility coefficient of the ions, $\text{sign}_{i}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species), $n_{i}$ is the ion density, $D_{i}$ is the diffusion coefficient of ions, $e$ is the elemental charge, and $\gamma_{se}$ is the ion induced secondary electron emission coefficient. $r$ is defined as the fraction of particles reflected by the surface.

When converting the density to logarithmic form and applying a scaling factor of the mesh and voltage, the strong form is given by

\begin{equation}
F =  \left( 1-a \right) \gamma \left( \text{-} \nabla V / l_{c} \right) \cdot \textbf{n}  \\[10pt]
\Gamma_{i} \cdot \textbf{n}  = \text{sign}_{i} \mu_{i} \ \text{-} \nabla (V / l_{c}) \exp(N_{i}) - D_{i} \exp(N_{i}) \nabla (N_{i} / l_{c}) \\[10pt]
\Gamma_{e} \cdot \textbf{n}  = \frac{2 (1 - a)}{1 + r} (\text{-} (\textbf{J}_{\textbf{e}} \cdot \textbf{n})/ (e / N_{A}) - \gamma_{se} \Gamma_{i} \cdot \textbf{n})
\end{equation}

Where $N_{i}$ is the molar density of the specie in logarithmic form, $N_{A}$ is Avogadro's number, $V_{c}$ is the scaling factor of the potential, and $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

!listing test/tests/1d_dc/NonlocalPotentialBCWithSchottky.i block=BCs/Emission_left

!syntax parameters /BCs/SchottkyEmissionBC

!syntax inputs /BCs/SchottkyEmissionBC

!syntax children /BCs/SchottkyEmissionBC
