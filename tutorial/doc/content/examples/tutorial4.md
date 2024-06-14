# Tutorial 4 - Pressure versus Electron Temperature Parametric Study

!---

# Problem Statement

Consider an Argon capacitively coupled plasma (CCP). Utilize the MOOSE Postprocessor system to calculate the volume averaged electron temperature.

!---

### How is the average electron temperature affected as the pressure is varied?

!alert note
The background gas density, pressure in the electron material block, and ion mobility and diffusivity coefficients must all be changed for this study

Background Gas Density

!listing tutorial/tutorial04-PressureVsTe/RF_Plasma_WithOut_Metastables-1Torr.i block=AuxKernels/Ar_val

!---

Pressure in the electron material block, and ion mobility and diffusivity coefficients.

!listing tutorial/tutorial04-PressureVsTe/RF_Plasma_WithOut_Metastables-1Torr.i block=Materials start=[GasBasics] end=[gas_species_2]

!---

# style=margin-top:1em;

# Expected Output

# style=margin-top:1em;

!media media/tutorial4-out.png
       style=width:50%;display:block;margin-top:0.5em;margin-left:auto;margin-right:auto;
