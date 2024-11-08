# PotentialDriftOutflowBC

!syntax description /BCs/PotentialDriftOutflowBC

## Overview

`PotentialDriftOutflowBC` is an electric field driven outflow boundary condition.
`PotentialDriftOutflowBC` assumes a mobility coefficient of unity and a non-scaled version of the species' density.

The electric field driven outflow is defined as

\begin{equation}
a =
\begin{cases}
1, & \text{sign}_{j} \vec{E} \cdot \textbf{n} > 0\\
0, & \text{sign}_{j} \vec{E} \cdot \textbf{n} \leq 0\\
\end{cases} \\[10pt]
\Gamma_{j} \cdot \textbf{n} = a \ \text{sign}_{j} \vec{E} \cdot \textbf{n} \ n_{j}
\end{equation}

Where $\Gamma_{j}$ is the flux assuming drift-diffusion formulation, $\textbf{n}$ is the normal vector of the boundary, $\text{sign}_{j}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species),
$\vec{E}$ is the electric field, and $n_{j}$ is the density.

When calculating with scaled densities and non-unity coefficients, please refer to [`HagelaarIonAdvectionBC`](/bcs/HagelaarIonAdvectionBC.md), [`DCIonBC`](/bcs/DCIonBC.md), or [`SakiyamaIonAdvectionBC`](/bcs/SakiyamaIonAdvectionBC.md).

!alert warning title=Untested Class
The PotentialDriftOutflowBC does not have a formalized test, yet. For this reason,
users should be aware of unforeseen bugs when using PotentialDriftOutflowBC. To
report a bug or discuss future contributions to Zapdos, please refer to the
[Zapdos GitHub Discussions page](https://github.com/shannon-lab/zapdos/discussions).
For standards of how to contribute to Zapdos and the MOOSE framework,
please refer to the [MOOSE Contributing page](framework/contributing.md).

## Example Input File Syntax

!! Describe and include an example of how to use the PotentialDriftOutflowBC object.

```text
[BCs]
  [Ion_electrode]
    type = PotentialDriftOutflowBC
    variable = ions
    potential = potential
    boundary = 'electrode'
  []
[]
```

!syntax parameters /BCs/PotentialDriftOutflowBC

!syntax inputs /BCs/PotentialDriftOutflowBC

!syntax children /BCs/PotentialDriftOutflowBC
