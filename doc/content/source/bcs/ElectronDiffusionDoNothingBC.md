# ElectronDiffusionDoNothingBC

!alert construction title=Undocumented Class
The ElectronDiffusionDoNothingBC has not been documented. The content listed below should be used as a starting point for
documenting the class, which includes the typical automatic documentation associated with a
MooseObject; however, what is contained is ultimately determined by what is necessary to make the
documentation clear for users.

!syntax description /BCs/ElectronDiffusionDoNothingBC

## Overview

`ElectronDiffusionDoNothingBC` is an outflow boundary condition where the outflow at the
boundary is equal to the bulk election diffusion equation.

The outflow is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = - D_{e} \nabla (n_{e}) \cdot \textbf{n}
\end{equation}

Where $\Gamma_e \cdot \textbf{n}$ is the outflow normal to the boundary, $\textbf{n}$ is the normal  vector of the boundary, $D_{e}$ is the diffusion coefficient, and $n_{e}$ is the electron density. When converting the density to logarithmic form and applying a scaling
factor of the mesh, the strong form for `ElectronDiffusionDoNothingBC` is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = - D_{e} \exp(N_{e}) \nabla (N_{e} / l_{c}) \cdot \textbf{n}
\end{equation}

Where $N_{e}$ is the molar density of the species in logarithmic form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

!! Describe and include an example of how to use the ElectronDiffusionDoNothingBC object.

!syntax parameters /BCs/ElectronDiffusionDoNothingBC

!syntax inputs /BCs/ElectronDiffusionDoNothingBC

!syntax children /BCs/ElectronDiffusionDoNothingBC
