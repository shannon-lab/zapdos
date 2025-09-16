# ADSurfaceCharge

!syntax description /Materials/ADSurfaceCharge

## Overview

`ADSurfaceCharge` calculates the surface charge at a boundary. The surface charge material property is labeled `surface_charge`.

The surface charge is defined as

\begin{equation}
\sigma = \int \vec{J} \ \text{d}t \\[10pt]
\vec{J} \cdot \textbf{n} = \sum{\left( q_{j} \vec{\Gamma}_{j} \cdot \textbf{n} \right)}  \\[10pt]
\vec{\Gamma}_{j} = \text{sign}_{j} \mu_{j} \vec{E} n_{j} - D_{j} \nabla (n_{j}) \\[10pt]
\end{equation}

Where:

- $\sigma$ is the surface charge,
- $\vec{J}$ is the total current density,
- the subscript $j$ represents properties of a plasma species,
- $q_{j}$ is the charge of the species,
- $\vec{\Gamma}$ is the drift-diffusion flux,
- $\textbf{n}$ is the outward pointing unit normal on the boundary,
- $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species),
- $\mu_{j}$ is the mobility coefficient,
- $D_{j}$ is the diffusion coefficient,
- $\vec{E}$ is the electric field, and
- $n_{j}$ is the species density.

Using the midpoint method for integration, the surface charge calculation becomes

\begin{equation}
\sigma_{t} = \sigma_{t-1} + \vec{J} \cdot \textbf{n} \ \text{d}t
\end{equation}

Where:

- $\sigma_{t}$ is the surface charge of the current time step,
- $\sigma_{t-1}$ is the surface of the previous time step, and
- $\text{d}t$ is the difference between time steps.

When converting the density to logarithmic form and applying a scaling factor of the mesh, the drift-diffusion flux of `ADSurfaceCharge` is redefined as

\begin{equation}
\vec{\Gamma}_{j} = N_{A} \left(\text{sign}_{j} \mu_{j} \frac{\vec{E}}{l_{c}} \exp(N_{j}) - D_{j} \exp(N_{j}) \frac{\nabla (N_{j})}{l_{c}} \right)
\end{equation}

Where:

- $N_{j}$ is the molar density of the species in logarithmic form,
- $N_{A}$ is Avogadro's number, and
- $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

!listing test/tests/surface_charge/dbd_test.i block=Materials/surface_charge_material

!syntax parameters /Materials/ADSurfaceCharge

!syntax inputs /Materials/ADSurfaceCharge

!syntax children /Materials/ADSurfaceCharge
