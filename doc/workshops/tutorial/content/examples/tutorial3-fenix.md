# Tutorial 3 - Kinetic Implementation

!---

# style=margin-top:1em;

# FENIX Intro

As commercial interested in fusion energy has increased the need for high-fidelity multi-physics simulations of fusion devices has also increased. To address this the Idaho National Laboratory, North Carolina State University, and the University of Illinois Urbana-Champaign are developing the Fusion ENergy Integrated multiphys-X (FENIX) framework for modeling plasma facing components. FENIX is built on the MOOSE framework and couples: MOOSE modules, applications and several existing codes:

# style=margin-top:1em;

- TMAP8 (Tritium migration)
- Cardinal

  - Monte-Carlo Neutronics vi OpenMC
  - Computational Fluid Dynamics via NekRS

- Electromagnetics Module
- Ray Tracing Module (Kinetic Plasma Foundation)

!---

# PIC in FENIX

# style=margin-top:1.5em;

In [!cite](lieberman1994principles) this tutorial problem is solved with a PIC code. A core part of the FENIX framework is the PIC capabilities that are being developed. As a very basic benchmarking problem the PIC example presented in [!cite](lieberman1994principles) has been replicated in FENIX


- 100 Macroparticles are placed on a 100 element mesh
- Each particle is initially placed exactly in the center of each cell
- Leap Frog particle stepping is used
- $\Delta t$ = $1\times 10^{-9} [\text{s}]$
- Total simulation time of $2.5\times 10^{-8} [\text{s}]$
- The potential is represented with first order nodal basis functions

# style=margin-top:1em;

!bibtex bibliography


!---

# Results Comparison

All figures show FENIX results super imposed on figures 2.2.a, 2.2.b, and 2.2.c from [!cite](lieberman1994principles). Results from [!cite](lieberman1994principles) are in black and grey while FENIX results are in color.

!row!

!media media/lieberman-particles.png
       style=width:93%;display:block;margin-top:0.5em;margin-left:auto;margin-right:auto;
       caption=Particle Population Evolution

!media media/lieberman-potential.png
       style=width:100%;display:block;margin-top:0.5em;margin-left:auto;margin-right:auto;
       caption=Electrostatic Potential Evolution

!media media/lieberman-vdf.png
       style=width:100%;display:block;margin-top:0.5em;margin-left:auto;margin-right:auto;
       caption=Particle Phase Space Evolution
!row-end!

!---

# FENIX Current Status

- Leap frog and Boris particle stepping have been implemented and verified.
- Electrostatic capabilities have been verified for all first order finite elements in libMesh.
- Uniform random particle initialization for all first order finite elements in libMesh has been verified.

  - Bounding box particle initialization has also been verified.

- Particle based current density source calculations is near completion and will be verified.
- Particle collision capabilities are the next to be developed.

!---

# FENIX Future Work

- Continued verification efforts by replicating Kinetic instabilities

  - Landau Damping
  - Two Stream
  - Dory-Ghast-Haris Instability

- Replicating more complex analytic plasma solutions
- Benchmarking against other codes
- Validation by replicating experimental data
