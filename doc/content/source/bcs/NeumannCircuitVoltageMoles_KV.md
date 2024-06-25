# NeumannCircuitVoltageMoles_KV

!alert construction title=Undocumented Class
The NeumannCircuitVoltageMoles_KV has not been documented. The content listed below should be used as a starting point for
documenting the class, which includes the typical automatic documentation associated with a
MooseObject; however, what is contained is ultimately determined by what is necessary to make the
documentation clear for users.

!syntax description /BCs/NeumannCircuitVoltageMoles_KV

## Overview

Note: add $n_{\gamma}$

`NeumannCircuitVoltageMoles_KV` is a Neumann boundary condition the equates the plasma and drive potential to the plasma current using Kirchoff’s voltage law for a circuit.

The Kirchoff’s voltage law at the cathode is defined as

\begin{equation}
V_\text{source} + V_\text{cathode} = e\left( \Gamma_{i} - \Gamma_{e}  \right) AR
\end{equation}

Where $V_\text{source}$ is the driven potential, $V_\text{cathode}$ is the potential at cathode,
$e$ is the elemental charge , $\Gamma_i$ and $\Gamma_e$ are fluxes ions and electrons respectively, $A$ is the cross-sectional area of the plasma, and $R$ is the ballast resistance. Within `NeumannCircuitVoltageMoles_KV`, the charged species' flux at the boundary are assumed to be given by:

\begin{equation}
a =
\begin{cases}
1, & \mu_{j} \left( \text{-} \nabla (V) \right) \cdot \textbf{n} > 0\\
0, & \mu_{j} \left( \text{-} \nabla (V) \right)\cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{e} \cdot \textbf{n} = \frac{1-r_{e}}{1+r_{e}} \left[ -(2 a_{e}-1) \ \mu_{e} 
\left(\text{-} \nabla (V) \right)
 \cdot \textbf{n} \ n_{e} + \frac{1}{2}v_{\text{th},e}n_{e} \right] - (1 - a_{e}) \gamma \Gamma_{j} \cdot \textbf{n} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = \frac{1-r_{j}}{1+r_{j}} \left[ (2 a_{j}-1) \ \mu_{j} \left( \text{-} \nabla (V) \right) \cdot \textbf{n} \ n_{j} + \frac{1}{2}v_{\text{th},j}n_{j} \right] \\[10pt]
v_{\text{th},e} = \sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \frac{n_{\varepsilon}}{n_{e}}} \\[10pt]
v_{\text{th},j} = \sqrt{\frac{8k_{B}T}{\pi m_{j}}}
\end{equation}

Where $\textbf{n}$ is the normal vector of the boundary,
$\mu$ is the mobility coefficient, $n$ is the species density, $v_\text{th}$ is the thermal velocity of the species, $n_{\varepsilon}$ is the mean energy density of electrons, $k_{B}$ is the Boltzmann constant, and $T$ is the gas temperature. $a$ is defined such that the outflow is non-zero when the drift velocity is directed towards the wall and zero otherwise. $r$ is defined as the fraction of particles reflected by the surface.

To convert this setup into a Neumann type BC, the set of equations are rearranged, so that this boundary condition solves for the grad potential normal for the boundary, such that:

\begin{equation}
\nabla (V) \cdot \textbf{n} =\frac{\frac{1+r}{1-r}\left( \text{-} V_\text{source}-V_\text{cathode} \right) + \frac{1}{2} e \left[ v_{\text{th},e}n_{e} - \left[(1-a)\gamma - 1\right]v_{\text{th},j}n_{j} \right] \ AR}{e \ \left[ (2a-1)\mu_{e} n_{e} - (2a_{j}-1)\left[(a-1)\gamma - 1\right]\mu_{j}n_{j} \right] AR}
\end{equation}

When converting the density to log form and applying a scaling factor of the mesh and voltage, the strong form for `NeumannCircuitVoltageMoles_KV` is defined as

\begin{equation}
v_{\text{th},e} = \sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \exp (N_{\varepsilon} - N_{e})} \\[10pt]
\nabla (V / l_{c}) \cdot \textbf{n} =\frac{\frac{1+r}{1-r}\left( \text{-} V_{source}-V_{cathode} \right) + \frac{1}{2} \frac{e N_{A}}{V_{c}} \left[ v_{\text{th},e}\exp(N_{e}) - \left[(1-a)\gamma - 1\right]v_{\text{th},j}\exp(N_{j}) \right] \ AR}{\frac{e N_{A}}{V_{c}} \left[ (2a-1)\mu_{e} \exp(N_{e}) - (2a_{j}-1)\left[(a-1)\gamma - 1\right]\mu_{j}\exp(N_{j}) \right] AR}
\end{equation}

Where $N_{j}$ is the molar density of the species in log form, $N_{A}$ is Avogadro's number, $V_{c}$ is the scaling factor of the potential, and $l_{c}$ is the scaling factor of the mesh.


## Example Input File Syntax

An example of how to use `NeumannCircuitVoltageMoles_KV` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=BCs/potential_left

!syntax parameters /BCs/NeumannCircuitVoltageMoles_KV

!syntax inputs /BCs/NeumannCircuitVoltageMoles_KV

!syntax children /BCs/NeumannCircuitVoltageMoles_KV
