# ElectronAdvectionDoNothingBC

!alert construction title=Undocumented Class
The ElectronAdvectionDoNothingBC has not been documented. The content listed below should be used as a starting point for
documenting the class, which includes the typical automatic documentation associated with a
MooseObject; however, what is contained is ultimately determined by what is necessary to make the
documentation clear for users.

!syntax description /BCs/ElectronAdvectionDoNothingBC

## Overview

`ElectronAdvectionDoNothingBC` is an outflow boundary condition where the outflow at the
boundary is equal to the bulk election advection equation.
`ElectronAdvectionDoNothingBC` assumes the electrostatic approximation for the electric field.

The outflow is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = \text{-} \mu_{e} n_{e} \left( \text{-} \nabla (V)\right) \cdot \textbf{n} 
\end{equation}

Where $\Gamma$ is the outflow normal to the boundary, $\textbf{n}$ is the normal of the boundary, $\mu_{e}$ is the mobility coefficient, $n_{e}$ is the electron density, and $V$ is the electric potential. When converting the density to logarithmic form and applying a scaling
factor of the mesh, the strong form for `ElectronAdvectionDoNothingBC` is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = \text{-} \mu_{e} \exp(N_{e}) \left(  \text{-} \nabla (V / l_{c}) \right) \cdot \textbf{n}
\end{equation}

Where $N_{j}$ is the molar density of the specie in logarithmic form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

!! Describe and include an example of how to use the ElectronAdvectionDoNothingBC object.

!syntax parameters /BCs/ElectronAdvectionDoNothingBC

!syntax inputs /BCs/ElectronAdvectionDoNothingBC

!syntax children /BCs/ElectronAdvectionDoNothingBC
