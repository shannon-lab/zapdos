# DriftDiffusionDoNothingBC

!alert construction title=Undocumented Class
The DriftDiffusionDoNothingBC has not been documented. The content listed below should be used as a starting point for
documenting the class, which includes the typical automatic documentation associated with a
MooseObject; however, what is contained is ultimately determined by what is necessary to make the
documentation clear for users.

!syntax description /BCs/DriftDiffusionDoNothingBC

## Overview

`DriftDiffusionDoNothingBC` is an outflow boundary condition where the outflow at the
boundary is equal to the bulk dift-diffusion equations.
`DriftDiffusionDoNothingBC` assumes the electrostatic approximation for the electric field.

The outflow is defined as

\begin{equation}
\Gamma_{j} \cdot \textbf{n} = \text{sign}_{j} \mu_{j} n_{j} \ \text{-} \nabla (V) \cdot \textbf{n} - D_{j} \nabla (n_{j}) \cdot \textbf{n}
\end{equation}

Where $\Gamma$ is the outflow normal to the boundary, $\textbf{n}$ is the normal vector of the boundary, $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species, $\text{-}1$ for negatively charged species and $\text{0}$ for neutral species), $\mu_{j}$ is the mobility coefficient, $D_{j}$ is the diffusion coefficient, $n_{j}$ is the density, and $V$ is
the potential. When converting the density to logarithmic form and applying a scaling factor of the mesh, the strong form for `DriftDiffusionDoNothingBC` is defined as

\begin{equation}
\Gamma_{j} \cdot \textbf{n} = \text{sign}_{j} \mu_{j} \exp(N_{j}) \ \text{-} \nabla (V / l_{c}) \cdot \textbf{n} - D_{j} \exp(N_{j}) \nabla (N_{j} / l_{c}) \cdot \textbf{n}
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

!! Describe and include an example of how to use the DriftDiffusionDoNothingBC object.

!syntax parameters /BCs/DriftDiffusionDoNothingBC

!syntax inputs /BCs/DriftDiffusionDoNothingBC

!syntax children /BCs/DriftDiffusionDoNothingBC
