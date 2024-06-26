# Tutorial 3 - Kinetic Implementation using FENIX

!media media/FENIX_logo_blue.png
       style=width:30%;display:block;margin-top:1.5em;margin-left:auto;margin-right:auto;box-shadow:none;

!style fontsize=130% halign=center
[https://mooseframework.inl.gov/fenix/](https://mooseframework.inl.gov/fenix/)

!---

# style=margin-top:1em;

# FENIX Intro

As commercial interest in fusion energy has increased, the need for high-fidelity, multiphysics simulations of fusion devices has also increased. To address this, Idaho National Laboratory, North Carolina State University, the University of Illinois at Urbana-Champaign, and the United Kingdom Atomic Energy Authority are developing an open source application, the Fusion ENergy Integrated multiphys-X (FENIX) framework, for modeling plasma facing components. FENIX is built on the MOOSE framework and couples MOOSE ecosystem capabilities as well as external codes:


- [TMAP8](https://mooseframework.inl.gov/TMAP8/) (Tritium migration)
- [Cardinal](https://cardinal.cels.anl.gov)

  - Monte-Carlo Neutronics via [OpenMC](https://openmc.org)
  - Computational Fluid Dynamics via [NekRS](https://nek5000.mcs.anl.gov)

- [Electromagnetics Module](https://mooseframework.inl.gov/modules/electromagnetics/)
- [Ray Tracing Module](https://mooseframework.inl.gov/modules/ray_tracing/) (Kinetic Plasma Foundation)
- [Heat Transfer](https://mooseframework.inl.gov/modules/heat_transfer/index.html)
- [Solid Mechanics](https://mooseframework.inl.gov/modules/solid_mechanics/index.html)
- [Thermal Hydraulics](https://mooseframework.inl.gov/modules/thermal_hydraulics/index.html)

!---

# style=margin-top:1em;

# PIC in FENIX



In [!cite](lieberman1994principles), this tutorial problem is solved with a PIC code, a core capability of FENIX still in-development. As a very basic benchmarking problem, the PIC example presented in [!cite](lieberman1994principles) has been replicated in FENIX.


- 100 Macroparticles are placed on a 100 element mesh
- Each particle is initially placed exactly in the center of each cell
- Leap Frog particle stepping is used
- $\Delta t$ = $1\times 10^{-9} [\text{s}]$
- Total simulation time of $2.5\times 10^{-8} [\text{s}]$
- The potential is represented with first order nodal basis functions

# style=margin-top:1em;



!---

# Results Comparison

All figures show FENIX results superimposed on figures 2.2.a, 2.2.b, and 2.2.c from [!cite](lieberman1994principles). Results from [!cite](lieberman1994principles) are in black and grey while FENIX results are in color.

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

# Current PIC Status

### Verified Capabilities

- Leap frog and Boris particle stepping
- Electrostatic capabilities using all first order finite elements in libMesh.
- Uniform random particle initialization for all first order finite elements in libMesh.

  - Bounding box particle initialization.

### Under Development

- Particle based current density source calculations.
- Particle collision capabilities.

!---

# Future PIC Work

- Continued verification efforts by replicating Kinetic instabilities

  - Landau Damping
  - Two Stream
  - Dory-Ghast-Haris Instability

- Replicating more complex analytic plasma solutions
- Benchmarking against other codes
- Validation by replicating experimental conditions and data
