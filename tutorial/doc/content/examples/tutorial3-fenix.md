# Tutorial 3 - Kinetic Implementation

!---

# style=margin-top:1em;

# FENIX Intro

# style=margin-top:1em;

In [!cite](lieberman1994principles) this problem is solved with a PIC code. A MOOSE based finite-element PIC code is being developed in collaboration with the Idaho National Laboratory. This capability is going to be a part of the  Fusion ENergy Integrated multiphys-X (FENIX) framework, which will be open-sourced soon.

# style=margin-top:4.5em;

!bibtex bibliography

!---

# PIC Setup

# style=margin-top:2em;

- 100 Macroparticles are placed on a 100 element mesh
- Leap Frog particle stepping is used
- Each particle is initially placed exactly in the center of each cell
- $\Delta t$ = $1\times 10^{-9} [\text{s}]$
- Total simulation time of $2.5\times 10^{-8} [\text{s}]$
- The potential is represented with first order element basis functions

!---

# Results Comparison

All figures show FENIX results super imposed on figures 2.2.a, 2.2.b, and 2.2.c from [!cite](lieberman1994principles). Results from [!cite](lieberman1994principles) are in black and grey while FENIX results are in color.

!row!

!media media/lieberman-particles.png
       style=width:95%;display:block;margin-top:0.5em;margin-left:auto;margin-right:auto;
       caption=Macro Particle Population Evolution

!media media/lieberman-potential.png
       style=width:100%;display:block;margin-top:0.5em;margin-left:auto;margin-right:auto;
       caption=Electrostatic Potential Evolution

!media media/lieberman-vdf.png
       style=width:100%;display:block;margin-top:0.5em;margin-left:auto;margin-right:auto;
       caption=Macro Particle Velocity Distribution Evolution
!row-end!

TODO ASK ABOUT HOW TO CENTER THIS CAPTION
