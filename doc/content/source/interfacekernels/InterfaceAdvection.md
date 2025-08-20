# InterfaceAdvection

!syntax description /InterfaceKernels/InterfaceAdvection

## Overview

`InterfaceAdvection` is used to defined the advection flux on one side of an interface to a species' electric field driven advective flux on the other side of the interface.

This advection term at the interface is defined as

\begin{equation}
\Gamma_{\text{adv}1} \cdot \textbf{n} = \text{sign}_{j2} \mu_{j2} n_{j2} \ \vec{E}_{2} \cdot \textbf{n}
\end{equation}

Where:

- Subscript $1$ is the the primary side of the interface,
- Subscript $2$ is the the neighboring side of the interface,
- $\textbf{n}$ is the normal vector of the interface,
- $\Gamma_{\text{adv}}$ is the advection component of a species' flux,
- $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species),
- $\mu_{j}$ is the mobility coefficient,
- $n_{j}$ is the density, and
- $\vec{E}$ is the electric field.

When converting the density to logarithmic form and applying a scaling
factor of the mesh, `InterfaceAdvection` is defined as

\begin{equation}
\Gamma_{\text{adv1}} \cdot \textbf{n} = \text{sign}_{j2} \mu_{j2} \exp(N_{j2}) \ (\vec{E}_{2} / l_{c}) \cdot \textbf{n}
\end{equation}

Where:

- $N_{j}$ is the molar density of the species in logarithmic form and
- $l_{c}$ is the scaling factor of the mesh.


## Example Input File Syntax

!listing test/tests/1d_dc/mean_en.i block=InterfaceKernels/em_advection

!syntax parameters /InterfaceKernels/InterfaceAdvection

!syntax inputs /InterfaceKernels/InterfaceAdvection

!syntax children /InterfaceKernels/InterfaceAdvection
