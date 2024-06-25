# CircuitDirichletPotential

!alert construction title=Undocumented Class
The CircuitDirichletPotential has not been documented. The content listed below should be used as a starting point for
documenting the class, which includes the typical automatic documentation associated with a
MooseObject; however, what is contained is ultimately determined by what is necessary to make the
documentation clear for users.

!syntax description /BCs/CircuitDirichletPotential

## Overview

`CircuitDirichletPotential` is a Dirichlet boundary condition for a potential based on Kirchoff's voltage law.

The formulation of the potential at the wall is:

\begin{equation}
V_\text{source} + V_\text{cathode} = e \Gamma A R
\end{equation}

Where $V_\text{source}$ is driven the potential, $V_\text{cathode}$ is the potential at cathode,
$\Gamma$ is the charged flux to the boundary, $e$ is the elemental charge, $A$ is the cross-sectional area of the plasma, and
$R$ is the ballast resistance. When converting the density to log form and applying a scaling factor for both the mesh and voltage,
`CircuitDirichletPotential` is defined as

\begin{equation}
V_\text{source} + V_\text{cathode} = e N_{A} \Gamma \frac{A}{l_{c}^2} \frac{R}{V_{c}}
\end{equation}

Where $N_{A}$ is Avogadro's number, $l_{c}$ is the scaling factor of the mesh, and $V_{c}$ is the scaling factor of the potential.


The charged flux is supplied as a [Postprocessor](syntax/Postprocessors/index.md) (usually the [`SideCurrent`](/postprocessors/SideCurrent.md) Postprocessor).

## Example Input File Syntax

!! Describe and include an example of how to use the CircuitDirichletPotential object.

!syntax parameters /BCs/CircuitDirichletPotential

!syntax inputs /BCs/CircuitDirichletPotential

!syntax children /BCs/CircuitDirichletPotential
