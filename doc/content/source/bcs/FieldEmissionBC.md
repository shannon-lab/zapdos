# FieldEmissionBC

!syntax description /BCs/FieldEmissionBC

## Overview

`FieldEmissionBC` is an outflow boundary condition that assumes the electron current density is defined by field emission.

Using a Fowler-Nordheim calculation for the field emission, the electron current density is defined as

\begin{equation}
a_{e} =
\begin{cases}
1, & \nabla (V) \cdot \textbf{n} > 0\\
0, & \nabla (V) \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\textbf{J}_{\textbf{e}} \cdot \textbf{n} = a \ \phi^{-1} \ F^{2} \exp \left[\text{-}v(f) \ b \ \phi^{3/2} / F \right] \\[10pt]
F =  \left( 1-a_{e} \right) \gamma \left( \text{-} \nabla V \right) \cdot \textbf{n}  \\[10pt]
a = 1.541434e\text{-}6 : \text{units of} \ A \ eV \ V^{-2} \\[10pt]
b = 6.830890e9 : \text{units of}  \ V \ m^{-1} \ eV^{-3/2} \\[10pt]
v(f) = 1 - f + \frac{1}{6}f\ln f \\[10pt]
f = c \frac{F}{\phi^{2}} \\[10pt]
c = 1.439964e\text{-}9 : \text{units of} \ eV^{2} \ V^{-1} \ m
\end{equation}

Where $\textbf{J}_{\textbf{e}}$ is the electron current density, $a$ is the first Fowler–Nordheim constant, $\phi$ is the local work function, $F$ is the local field, $b$ is the second Fowler–Nordheim constant, $v(f)$ is a correction factor that depends on the scaled barrier field ($f$), $\textbf{n}$ is the normal vector of the boundary, $\gamma$ is the field enhancement factor, and $V$ is the potential. $a_{e}$ is defined such that the outflow is only defined when the drift velocity is direct towards the wall and zero otherwise. With the electron current density, the outward electron flux is defined as

\begin{equation}
\Gamma_{i} \cdot \textbf{n}  = \text{sign}_{i} \mu_{i} \left(- \nabla V\right) n_{i} - D_{i} \nabla (n_{i}) \\[10pt]
\Gamma_{e} \cdot \textbf{n}  = \frac{2 (1 - a_{e})}{1 + r} (\text{-} (\textbf{J}_{\textbf{e}} \cdot \textbf{n})/e - \gamma_{se} \Gamma_{i} \cdot \textbf{n})
\end{equation}

Where $\Gamma$ is the outflow normal to the boundary, $\mu_{i}$ is the mobility coefficient of the ions, $\text{sign}_{i}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species), $n_{i}$ is the ion density, $D_{i}$ is the diffusion coefficient of ions, $e$ is the elemental charge, and $\gamma_{se}$ is the ion induced secondary electron emission coefficient. $r$ is defined as the fraction of particles reflected by the surface.

When converting the density to log form and applying a scaling factor of the mesh and voltage, the strong form is given by


\begin{equation}
F =  \left( 1-a \right) \gamma \left( \text{-} \nabla V / l_{c} \right) \cdot \textbf{n}  \\[10pt]
a = 1.541434e\text{-}6 * V_{c}^{2} \\[10pt]
b = 6.830890e9 / V_{c} \\[10pt]
c = 1.439964e\text{-}9 * V_{c}\\[10pt]
\Gamma_{i} \cdot \textbf{n}  = \text{sign}_{i} \mu_{i} \left( - \nabla V / l_{c}\right) \exp(N_{i}) - D_{i} \exp(N_{i}) \nabla (N_{i} / l_{c}) \\[10pt]
\Gamma_{e} \cdot \textbf{n}  = \frac{2 (1 - a)}{1 + r} (\text{-} (\textbf{J}_{\textbf{e}} \cdot \textbf{n})/ (e / N_{A}) - \gamma_{se} \Gamma_{i} \cdot \textbf{n})
\end{equation}

Where $N_{i}$ is the molar density of the species in log form, $N_{A}$ is Avogadro's number, $V_{c}$ is the scaling factor of the potential, and $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax


!listing test/tests/field_emission/field_emission.i block=BCs/FieldEmission_left


!syntax parameters /BCs/FieldEmissionBC

!syntax inputs /BCs/FieldEmissionBC

!syntax children /BCs/FieldEmissionBC
