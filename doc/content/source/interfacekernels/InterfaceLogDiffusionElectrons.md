# InterfaceLogDiffusionElectrons

!syntax description /InterfaceKernels/InterfaceLogDiffusionElectrons

## Overview

`InterfaceLogDiffusionElectrons` is used to defined the diffusion flux on one side of an interface to the electron diffusion flux on the other side of the interface.

This diffusion term at the interface is defined as

\begin{equation}
\Gamma_{\text{\text{diff}}1} \cdot \textbf{n} = -D_{e2} \nabla (n_{e2}) \cdot \textbf{n}
\end{equation}

Where:

- Subscript $1$ is the the primary side of the interface,
- Subscript $2$ is the the neighboring side of the interface,
- $\textbf{n}$ is the normal vector of the interface,
- $\Gamma_{\text{\text{diff}}}$ is the diffusion component of a species' flux,
- $D_{e}$ is the electron diffusion coefficient, and
- $n_{e}$ is the electron density.

When converting the density to logarithmic form and applying a scaling factor of the mesh, the strong form for `InterfaceLogDiffusionElectrons` is defined as

\begin{equation}
\Gamma_{\text{\text{diff}}1} \cdot \textbf{n} = -D_{e2} \exp(N_{e2}) \nabla (N_{e2} / l_{c}) \cdot \textbf{n}
\end{equation}

Where:

- $N_{e}$ is the molar density of the electrons in logarithmic form, and
- $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

!listing test/tests/1d_dc/mean_en.i block=InterfaceKernels/em_diffusion

!syntax parameters /InterfaceKernels/InterfaceLogDiffusionElectrons

!syntax inputs /InterfaceKernels/InterfaceLogDiffusionElectrons

!syntax children /InterfaceKernels/InterfaceLogDiffusionElectrons
