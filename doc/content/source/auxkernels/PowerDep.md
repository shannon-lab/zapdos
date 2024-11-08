# PowerDep

!syntax description /AuxKernels/PowerDep

## Overview

`PowerDep` returns the amount of power deposited into a user specified specie by
Joule Heating.

The power deposited by Joule Heating is defined as

\begin{equation}
P_{\text{Joule Heating}} = \Gamma_{j} \cdot \vec{E} \\
\\[10pt]
\Gamma_{j} = q_{j} (\text{sign}_{j} \mu_{j} \vec{E} n_{j} - D_{j} \nabla (n_{j}))
\end{equation}

Where $P_{\text{Joule Heating}}$ is the power deposited by Joule heating, $q_{j}$ is the charge of the species, $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species), $\mu_{j}$ is the mobility coefficient,
$\vec{E}$ is the electric field, $n_{j}$ is the density, and $D_{j}$ is the diffusion coefficient.
When converting the density to log form and applying a scaling factor of the mesh / voltage,
`PowerDep` is defined as

\begin{equation}
P_{\text{Joule Heating}} = \Gamma_{j}  \cdot \frac{\vec{E} V_{c}}{l_{c}} \\
\\[10pt]
\Gamma_{j} = q_{j} N_{A} \left( \text{sign}_{j} \mu_{j} \frac{\vec{E}}{l_{c}} \exp(N_{j}) - D_{j} \exp(N_{j}) \frac{\nabla (N_{j})}{l_{c}} \right)
\end{equation}

Where $N_{j}$ is the molar density of the specie in log form, $N_{A}$ is Avogadro's
number, $l_{c}$ is the scaling factor of the mesh, and $V_{c}$ is the scaling factor
of the potential.

For the case where artificial diffusion is introduced to the charge specie flux, an additional term is included, such that:

\begin{equation}
\Gamma_{j\text{, Total}} = \Gamma_{j} + q_{j} N_{A} \mu_{j} \frac{\text{-}\lVert \vec{E} \rVert_{2}}{l_{c}} \frac{h_\text{max}}{2} \exp(N_{j}) \frac{\nabla (N_{j})}{l_{c}}
\end{equation}

Where $h_\text{max}$ is the max length of the current element.

## Example Input File Syntax

An example of how to use `PowerDep` can be found in the
test file `mean_en.i`.

!listing test/tests/1d_dc/mean_en.i block=AuxKernels/PowerDep_em

!syntax parameters /AuxKernels/PowerDep

!syntax inputs /AuxKernels/PowerDep

!syntax children /AuxKernels/PowerDep
