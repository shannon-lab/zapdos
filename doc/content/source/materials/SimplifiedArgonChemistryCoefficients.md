# SimplifiedArgonChemistryCoefficients

!syntax description /Materials/SimplifiedArgonChemistryCoefficients

## Overview

`SimplifiedArgonChemistryCoefficients` defines the coefficients for a simplified argon chemistry network. This includes both rate and Townsend coefficients, and threshold energies. The following are the properties and naming scheme that `SimplifiedArgonChemistryCoefficients` provides:

- rate coefficients for elastic collision, ionization, and excitation, labeled as `kel`, `kiz`, and `kex`,
- Townsend coefficients for elastic collision, ionization, and excitation, labeled as `alpha_el`, `alpha_iz`, and `alpha_ex`, and
- threshold energy for ionization and excitation, labeled as `Eiz` and `Eex`,

In addition to the argon chemistry, `SimplifiedArgonChemistryCoefficients` also defines the following:

- argon mass, labeled as `massGas`, and
- neutral argon gas density, labeled as `n_gas`.

## Example Input File Syntax

!listing test/tests/1d_dc/mean_en_multi.i block=Materials/gas_block

!syntax parameters /Materials/SimplifiedArgonChemistryCoefficients

!syntax inputs /Materials/SimplifiedArgonChemistryCoefficients

!syntax children /Materials/SimplifiedArgonChemistryCoefficients
