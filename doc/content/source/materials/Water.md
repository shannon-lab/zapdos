# Water

!syntax description /Materials/Water

## Overview

`Water` defines the transport and rate coefficients for solvated electrons in water. `Water` supplies the transport coefficient (i.e., the mobility and diffusion coefficients) for the following species:

- solvated electrons,
- H radical,
- OH$^-$ ion,
- H$_2$O$^+$ ion,
- OH radical,
- H$_2$ molecule,
- O$^-$ ion,
- H$_3$O$^+$ ion,
- H$_2$O$_2$ molecule,
- HO$_2$$^-$ ion,
- O$_2$ molecule,
- O$_2$$^-$ ion,
- O radical,
- HO$_2$ radical,
- O$_3$ molecule, and
- O$_3$$^-$ ion

`Water` supplies the rate coefficients for the following reactions:

- e + H$_2$O $\rightarrow$ H + OH$^-$
- 2e + 2H$_2$O $\rightarrow$ H$_2$ + 2OH$^-$
- e + H + H$_2$O $\rightarrow$ H$_2$ + OH$^-$
- e + OH $\rightarrow$ OH$^-$
- e + O$^-$ + H$_2$O $\rightarrow$ 2OH$^-$
- e + H$_3$O$^+$ $\rightarrow$ H$_2$ + H$_2$O
- e + H$_2$O$_2$ $\rightarrow$ OH + OH$^-$
- e + HO$_2$$^-$ + H$_2$O $\rightarrow$ OH + 2OH$^-$
- e + O$_2$ $\rightarrow$ O$_2$$^-$
- e + O $\rightarrow$ O$^-$
- H + H$_2$O $\rightarrow$ H$_2$ + OH
- 2H $\rightarrow$ H$_2$
- H + OH $\rightarrow$ H$_2$O
- H + OH$^-$ $\rightarrow$ H$_2$O + e
- H + H$_2$O$_2$ $\rightarrow$ OH + H$_2$O
- H$_2$ + H$_2$O$_2$ $\rightarrow$ H + OH + H$_2$O
- H + O$_2$ $\rightarrow$ HO$_2$
- H + HO$_2$ $\rightarrow$ H$_2$O$_2$
- O + H$_2$O $\rightarrow$ 2OH
- O + O$_2$ $\rightarrow$ O$_3$
- 2OH $\rightarrow$ H$_2$O$_2$
- OH + O$^-$ $\rightarrow$ HO$_2$$^-$
- OH + H$_2$ $\rightarrow$ H + H$_2$O
- OH + OH$^-$ $\rightarrow$ O$^-$ + H$_2$O
- OH + HO$_2$ $\rightarrow$ H$_2$O + O$_2$
- OH + O$_2$$^-$ $\rightarrow$ OH$^-$ + O$_2$
- O$^-$ + H$_2$O $\rightarrow$ OH$^-$ + OH
- O$^-$ + H$_2$ $\rightarrow$ OH$^-$ + H
- O$^-$ + H$_2$O$_2$ $\rightarrow$ O$_2$$^-$ + H$_2$O
- O$^-$ + HO$_2$$^-$ $\rightarrow$ O$_2$$^-$ + OH$^-$
- O$^-$ + O$_2$$^-$ $\rightarrow$ O$_3$$^-$
- O$^-$ + O$_2$$^-$ + H$_2$O $\rightarrow$ 2OH$^-$ + O$_2$
- OH + H$_2$O$_2$ $\rightarrow$ H$_2$O + HO$_2$
- OH + HO$_2$$^-$ $\rightarrow$ OH$^-$ + HO$_2$
- H$_2$O$^+$ + H$_2$O $\rightarrow$ H$_3$O$^+$ + OH
- H$_3$O$^+$ + OH$^-$ $\rightarrow$ H + OH + H$_2$O
- HO$_2$ + H$_2$O $\rightarrow$ H$_3$O$^+$ + O$_2$$^-$
- H$_3$O$^+$ + O$_2$$^-$ $\rightarrow$ HO$_2$ + H$_2$O

!alert! note title=Citation
The transport and rate coefficients used in this object can be found in [!cite](tian2014atmospheric).
!alert-end!

## Example Input File Syntax

!listing test/tests/1d_dc/mean_en.i block=Materials/water_block

!syntax parameters /Materials/Water

!syntax inputs /Materials/Water

!syntax children /Materials/Water
