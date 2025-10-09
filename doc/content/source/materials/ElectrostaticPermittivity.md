# ElectrostaticPermittivity

!syntax description /Materials/ElectrostaticPermittivity

## Overview

`ElectrostaticPermittivity` declares the permittivity for the electrostatic potential as a material property. By default, `ElectrostaticPermittivity` defines this values using the permittivity of free space, but custom material and plasma dielectric coefficients can be supplied.

The naming scheme of the electrostatic permittivity that `ElectrostaticPermittivity` provides is:

- "diff'electrostatic potential variable name'" (e.g., `diffpotential`)

This nomenclature is to reflect that the Poisson's equation is a diffusion-type problem, where the permittivity acts as the diffusion coefficient of the potential (i.e., $\nabla \cdot \left( -\varepsilon \nabla V \right) = \rho$).

## Example Input File Syntax

!listing test/tests/DriftDiffusionAction/2D_RF_Plasma_actions.i block=Materials/gas_permittivity

!syntax parameters /Materials/ElectrostaticPermittivity

!syntax inputs /Materials/ElectrostaticPermittivity

!syntax children /Materials/ElectrostaticPermittivity
