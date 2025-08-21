# NeumannCircuitVoltageMoles_KV

!syntax description /BCs/NeumannCircuitVoltageMoles_KV

## Overview

`NeumannCircuitVoltageMoles_KV` is a Neumann boundary condition that equates the plasma and drive potential to the plasma current using Kirchoff’s voltage law for a circuit.

The Kirchoff’s voltage law at the cathode is defined as

\begin{equation}
V_\text{source} + V_\text{cathode} = e\left( \Gamma_{i} - \Gamma_{e}  \right) AR
\end{equation}

Where $V_\text{source}$ is the driven potential, $V_\text{cathode}$ is the potential at cathode,
$e$ is the elemental charge , $\Gamma_i$ and $\Gamma_e$ are the ion and and electron particle fluxes, respectively, $A$ is the cross-sectional area of the plasma, and $R$ is the ballast resistance. $A$ and $R$ are provided by the user object [ProvideMobility.md].

Within `NeumannCircuitVoltageMoles_KV`, the charged species' flux at the boundary is assumed to be given by:

\begin{equation}
a_{e} =
\begin{cases}
1, & \mu_{e} \left( \nabla (V) \right) \cdot \textbf{n} > 0\\
0, & \mu_{e} \left( \nabla (V) \right)\cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
a_{i} =
\begin{cases}
1, & \mu_{i} \left( - \nabla (V) \right) \cdot \textbf{n} > 0\\
0, & \mu_{i} \left( - \nabla (V) \right)\cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{e} \cdot \textbf{n} = \frac{1-r_{e}}{1+r_{e}} \left[ -(2 a_{e}-1) \ \mu_{e}
\left(\text{-} \nabla (V) \right)
 \cdot \textbf{n} \ \left( n_{e} - n_{\gamma} \right) + \frac{1}{2}v_{\text{th},e} \left( n_{e} - n_{\gamma} \right) \right] - (1 - a_{e}) \gamma \Gamma_{i} \cdot \textbf{n} \\[10pt]
\Gamma_{i} \cdot \textbf{n} = \frac{1-r_{i}}{1+r_{i}} \left[ (2 a_{i}-1) \ \mu_{i} \left( \text{-} \nabla (V) \right) \cdot \textbf{n} \ n_{i} + \frac{1}{2}v_{\text{th},i}n_{i} \right] \\[10pt]
v_{\text{th},e} = \sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \frac{n_{\varepsilon}}{n_{e}}} \\[10pt]
v_{\text{th},i} = \sqrt{\frac{8k_{B}T}{\pi m_{i}}} \\[10pt]
n_{\gamma} = (1 - a_{e}) \frac{\gamma \Gamma_{i} \cdot \textbf{n}}{\mu_{e} (\text{-}\nabla V) \cdot \textbf{n}}
\end{equation}

Where the subscripts $e$, $j$ and $\varepsilon$ represents properties of electrons, ions and electron energy respectively, $\textbf{n}$ is the normal vector of the boundary,
$\mu$ is the mobility coefficient, $n$ is the species density, $v_\text{th}$ is the thermal velocity of the species, $n_{\varepsilon}$ is the mean energy density of electrons, $k_{B}$ is the Boltzmann constant, $T$ is the gas temperature, and $n_{\gamma}$ is electron density emitted by the surface. $a$ is defined such that the outflow is non-zero when the drift velocity is directed towards the wall and zero otherwise. $r$ is defined as the fraction of particles reflected by the surface.

To convert Kirchoff’s voltage law into a Neumann type BC, the set of equations are rearranged, so that this boundary condition solves for the potential flux normal for the boundary, such that:

\begin{equation}
\nabla (V) \cdot \textbf{n} =\frac{\frac{1+r}{1-r}\left( \text{-} V_\text{source}-V_\text{cathode} \right) + \frac{1}{2} e \left[ v_{\text{th},e}\left( n_{e} - n_{\gamma} \right) - \left[(1-a)\gamma - 1\right]v_{\text{th},i}n_{i} \right] \ AR}{e \ \left[ (2a-1)\mu_{e} \left( n_{e} - n_{\gamma} \right) - (2a_{i}-1)\left[(a-1)\gamma - 1\right]\mu_{i}n_{i} \right] AR}
\end{equation}

When converting the density to logarithmic-molar form and applying a scaling factor of the mesh and voltage, the strong form for `NeumannCircuitVoltageMoles_KV` is defined as

\begin{equation}
v_{\text{th},e} = \sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \exp (N_{\varepsilon} - N_{e})} \\[10pt]
\nabla (V / l_{c}) \cdot \textbf{n} =\frac{\frac{1+r}{1-r}\left( \text{-} V_{source}-V_{cathode} \right) + \frac{1}{2} \frac{e N_{A}}{V_{c}} \left[ v_{\text{th},e}\left( \exp(N_{e}) - n_{\gamma} \right) - \left[(1-a)\gamma - 1\right]v_{\text{th},i}\exp(N_{i}) \right] \ AR}{\frac{e N_{A}}{V_{c}} \left[ (2a-1)\mu_{e} \left( \exp(N_{e}) - n_{\gamma} \right) - (2a_{i}-1)\left[(a-1)\gamma - 1\right]\mu_{i}\exp(N_{i}) \right] AR}
\end{equation}

Where $N_{e}$, $N_{i}$ and $N_{\varepsilon}$ is the molar density of the electrons, ions and electron energy in logarithmic form, $N_{A}$ is Avogadro's number, $V_{c}$ is the scaling factor of the potential, and $l_{c}$ is the scaling factor of the mesh.


## Example Input File Syntax


!listing test/tests/1d_dc/mean_en.i block=BCs/potential_left

!syntax parameters /BCs/NeumannCircuitVoltageMoles_KV

!syntax inputs /BCs/NeumannCircuitVoltageMoles_KV

!syntax children /BCs/NeumannCircuitVoltageMoles_KV
