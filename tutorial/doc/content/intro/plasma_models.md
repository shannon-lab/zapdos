# Computational Plasma Models

!---

!style halign=center
!media media/plasma_models.png

!---

# Global Models

!style halign=center fontsize=150%
- Volume Averaged and Simplified Kinetics

- Spatially independent simulations provide:

  - Volume averaged plasma parameters.
  - Energy dependent coefficients.


!---

# Fuild Models (Zapdos)

!style halign=center fontsize=150%
- Local Field Approximation (LFA).
- Local Mean Energy Approximation (LMEA).
- Monte Carlo Fluids (MCF).

- Typically utilize the first two or three moments of the boltzmann equation
- Particle species are represented as continuous fluids.

  - Various assumptions can be used for energy dependent phenomena.


!---

# Higher Order and Hybrid Models


!style halign=center fontsize=150%
- Higher order fluid models.
- Hyprid particle-fluid models.


- Higher order models utilize higher order moments of the boltzmann equation.
- Hybrid models represent a fraction of a species, a single species or multiples species in a fully kinetic manner.

!---

# Kinetic Particle Methods

!style halign=center fontsize=150%
- Direct Kinetic Methods
- Molecular Dynamics (MD).
- Particle In Cell (PIC) with Monte Carlo Collisions (MCC).

- Individual particles or groups of particles are tracked.

  - Direct Kinetic Models explicity solve the Boltzmann equation.
  - In MD models inter-molecular forces between particles are calculated and used to update paricle data.
  - In PIC-MCC models individual particles are traced and are subject to macroscopic fields and particle-particle monte carlo particle-particle collisions.
