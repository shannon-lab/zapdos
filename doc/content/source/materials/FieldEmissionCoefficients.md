# FieldEmissionCoefficients

!syntax description /Materials/FieldEmissionCoefficients

## Overview

`FieldEmissionCoefficients` defines the coefficients needed for the field emission boundary conditions (i.e., [FieldEmissionBC.md] and [SchottkyEmissionBC.md]). The following are the properties and naming scheme that `FieldEmissionCoefficients` provides:

- the work function, labeled as `work_function`,
- the field enhancement factor, labeled as `field_enhancement`, and
- the Richardson coefficient, labeled as `Richardson_coefficient`.


## Example Input File Syntax

!listing test/tests/1d_dc/NonlocalPotentialBCWithSchottky.i block=Materials/gas_block_field_emission

!syntax parameters /Materials/FieldEmissionCoefficients

!syntax inputs /Materials/FieldEmissionCoefficients

!syntax children /Materials/FieldEmissionCoefficients
