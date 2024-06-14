# Tutorial 5 - Plasma-Water Interface

!---

# Problem Statement

Consider an argon DC discharge over water. Within Zapdos, users can model material surface interfaces of plasma processes (in this case, electrons diffusing into a water’s surface). This is done using what is called the Interface System within Zapdos/MOOSE.

!---

# style=margin-top:1.5em;

!style fontsize=120%
The current input file assumes that all of the electrons enter the water What will happen if we change the reflection coefficients at the boundary of the water for the electrons and electrons mean energy?

!listing tutorial/tutorial05-PlasmaWaterInterface/DC_argon-With-Water.i block=BCs start=[em_physical_right] end=[mean_en_physical_right]


!---

# Expected Output

!media media/tutorial5-out.png
       style=width:30%;display:block;margin-top:0.5em;margin-left:auto;margin-right:auto;
