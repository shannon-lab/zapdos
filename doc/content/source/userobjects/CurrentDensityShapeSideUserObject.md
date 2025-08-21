# CurrentDensityShapeSideUserObject

!syntax description /UserObjects/CurrentDensityShapeSideUserObject

## Overview

`CurrentDensityShapeSideUserObject` calculates the total current density at a boundary for a single ion species plasma, assuming the electrostatic approximation (i.e., $\vec{E} = -\nabla V$). The electrostatic current density is defined as:

\begin{equation}
J_{T} = e \left[ \left( \mu_{i} \left( - \nabla V \right) n_{i} - D_{i} \nabla n_{i} \right) - \left( -\mu_{e} \left( - \nabla V \right) n_{e} - D_{e} \nabla n_{e} \right) \right]
\end{equation}

Where:

- $J_{T}$ is the total current density,
- $e$ is the elemental charge,
- $\mu$ is the mobility coefficient,
- $V$ is the electrostatic potential,
- $n$ is the density, and
- $D$ is the diffusion coefficient,
- Subscript $i$ represents the ions, and
- Subscript $e$ represents the electrons.

When converting the density to molar logarithmic form, `CurrentDensityShapeSideUserObject` is defined as

\begin{equation}
J_{T} = e N_{A} \left[ \left( \mu_{i} \left( - \nabla V \right) \exp(N_{i}) - D_{i} \exp(N_{i}) \nabla N_{i} \right) - \left( -\mu_{e} \left( - \nabla V \right) \exp(N_{e}) - D_{e} \exp(N_{e}) \nabla N_{e} \right) \right]
\end{equation}

Where:

- $N_{i,e}$ is the molar density of the species in logarithmic form, and
- $N_{A}$ is Avogadro's number.


## Example Input File Syntax

!listing test/tests/1d_dc/NonlocalPotentialBCWithSchottky.i block=UserObjects/current_density_user_object

!syntax parameters /UserObjects/CurrentDensityShapeSideUserObject

!syntax inputs /UserObjects/CurrentDensityShapeSideUserObject

!syntax children /UserObjects/CurrentDensityShapeSideUserObject
