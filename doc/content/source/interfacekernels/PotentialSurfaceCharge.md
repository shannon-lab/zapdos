# PotentialSurfaceCharge

!syntax description /InterfaceKernels/PotentialSurfaceCharge

## Overview

`PotentialSurfaceCharge` enforces the dielectric boundary condition at an interface by equating the difference in the electric field at an interface to a surface charge. To supply the surface charge, the [ADSurfaceCharge.md] object is often used.

The dielectric boundary condition is defined as

\begin{equation}
\left( \varepsilon_{1} \vec{E}_{1} - \varepsilon_{2} \vec{E}_{2} \right) \cdot \textbf{n} = \sigma
\end{equation}

Where:

- Subscript $1$ is the the primary side of the interface,
- Subscript $2$ is the the neighboring side of the interface,
- $\textbf{n}$ is the normal vector of the interface,
- $\vec{E}$ is the electric field, and
- $\sigma$ is the surface charge.

`PotentialSurfaceCharge` assumes the electrostatic approximation (i.e., $\vec{E} = -\nabla V$). When converting to the electrostatic potential and applying a scaling factor of the mesh, `PotentialSurfaceCharge` is defined as

\begin{equation}
\left( \varepsilon_{2} \left( \nabla V_{2} / l_{c,2} \right) -  \varepsilon_{1} \nabla \left( V_{1} / l_{c,1} \right) \right) \cdot \textbf{n} = \sigma
\end{equation}

Where:

- $V$ is the electrostatic potential, and
- $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

!listing test/tests/surface_charge/dbd_test.i block=InterfaceKernels/potential_right

!syntax parameters /InterfaceKernels/PotentialSurfaceCharge

!syntax inputs /InterfaceKernels/PotentialSurfaceCharge

!syntax children /InterfaceKernels/PotentialSurfaceCharge
