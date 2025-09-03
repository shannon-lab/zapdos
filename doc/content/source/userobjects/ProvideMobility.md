# ProvideMobility

!syntax description /UserObjects/ProvideMobility

## Overview

`ProvideMobility` provides a user defined electrode area, ballast resistance, and custom Coulomb charge for other Zapdos objects. Most commonly used with the boundary condition objects [NeumannCircuitVoltageMoles_KV.md] and [PenaltyCircuitPotential.md].

## Example Input File Syntax

!listing test/tests/1d_dc/mean_en.i block=UserObjects/data_provider

!syntax parameters /UserObjects/ProvideMobility

!syntax inputs /UserObjects/ProvideMobility

!syntax children /UserObjects/ProvideMobility
