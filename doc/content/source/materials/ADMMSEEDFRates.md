# ADMMSEEDFRates

!syntax description /Materials/ADMMSEEDFRates

## Overview

`ADMMSEEDFRates` supplies the electron mean energy dependent coefficients for a user-specifed function for the purposes of methods of manufactured solutions (MMS) verification. This object also calculates the derivative of the electron mean energy dependent coefficients with respect to the electron density and the electron energy density.

## Example Input File Syntax

!listing test/tests/mms/continuity_equations/2D_Coupling_Electons_Potential_Ions_MeanEnergy.i block=Materials/Material_Coeff_Set2

!syntax parameters /Materials/ADMMSEEDFRates

!syntax inputs /Materials/ADMMSEEDFRates

!syntax children /Materials/ADMMSEEDFRates
