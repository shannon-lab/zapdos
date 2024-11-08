# Current

!syntax description /AuxKernels/Current

## Overview

`Current` returns the electric current density of a species in logarithmic form.

The current density is defined as

\begin{equation}
J_{j} = q_{j} (\text{sign}_{j} \mu_{j} \vec{E} n_{j} - D_{j} \nabla (n_{j}))
\end{equation}

Where $J_{j}$ is the current density, $q_{j}$ is the charge of the species, $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species), $\mu_{j}$ is the mobility coefficient, $\vec{E}$ is the electric field, $n_{j}$ is the density, and $D_{j}$ is the diffusion coefficient. When converting the density to logarithmic form and applying a scaling factor of the mesh, `Current` is defined as

\begin{equation}
J_{j} = q_{j} N_{A} \left(\text{sign}_{j} \mu_{j} \frac{\vec{E}}{l_{c}} \exp(N_{j}) - D_{j} \exp(N_{j}) \frac{\nabla (N_{j})}{l_{c}} \right)
\end{equation}

Where $N_{j}$ is the molar density of the specie in logarithmic form, $N_{A}$ is Avogadro's number, $l_{c}$ is the scaling factor of the mesh.

For the case of the where artificial diffusion is introduced to the charge specie flux, an additional term is included in the current density, such that:

\begin{equation}
J_{j,\text{ Total}} = J_{j} + q_{j} N_{A} \mu_{j} \frac{\text{-}\lVert \vec{E} \rVert_{2}}{l_{c}} \frac{h_\text{max}}{2} \exp(N_{j}) \frac{\nabla (N_{j})}{l_{c}}
\end{equation}

Where $h_\text{max}$ is the max length of the current element.

## Example Input File Syntax

An example of how to use `Current` can be found in the
test file `Lymberopoulos_with_argon_metastables.i`.

!listing test/tests/Lymberopoulos_rf_discharge/Lymberopoulos_with_argon_metastables.i block=AuxKernels/Current_em

!syntax parameters /AuxKernels/Current

!syntax inputs /AuxKernels/Current

!syntax children /AuxKernels/Current
