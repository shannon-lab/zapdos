# HeavySpecies

!syntax description /Materials/HeavySpecies

## Overview

`HeavySpecies` defines the transport and material properties of ions and neutral species. The following are the properties and naming scheme that `HeavySpecies` provides:

- species mass, labeled as "mass + 'variable name'" (e.g., `massargon_ion`),
- species charge, labeled as "sgn + 'variable name'" (e.g., `sgnargon_ion`),
- species mobility coefficient, labeled as "mu + 'variable name'" (e.g., `muargon_ion`), and
- species diffusion coefficient, labeled as "diff + 'variable name'" (e.g., `diffargon_ion`).

To declare species properties as AD materials, please use `type = ADHeavySpecies`.

## Example Input File Syntax

!listing test/tests/DriftDiffusionAction/RF_Plasma_actions.i block=Materials/gas_species_0

!syntax parameters /Materials/HeavySpecies

!syntax inputs /Materials/HeavySpecies

!syntax children /Materials/HeavySpecies
