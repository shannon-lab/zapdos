# JouleHeating

!syntax description /Kernels/JouleHeating

## Overview

`JouleHeating` accounts for the heating of electrons through Joule heating
for electrons and electron mean energy densities in logarithmic form. `JouleHeating` assumes
the electrostatic approximation for the electric field.

The strong form for Joule heating effects for energies in units of eV are
usually defined as

\begin{equation}
p_{\text{Joule}} = \text{-} \nabla (V) \cdot \left[\text{-} \mu_{e} \ \text{-} \nabla (V) n_{e} -
                           D_{e} \nabla (n_{e})\right]
\end{equation}

Where $p_{\text{Joule}}$ is Joule heating in units of eV/m$^{3}$s, $V$ is the potential, $\mu_{e}$ is the mobility of the electrons, $n_{e}$ is
the electron density, and $D_{e}$ is the diffusion coefficient. When converting
the density to logarithmic form and applying scaling factor to the mesh and voltage,
the strong form for `JouleHeating` is defined as

\begin{equation}
p_{\text{Joule}} = \frac{\text{-} \nabla (V) V_{c}}{l_{c}} \cdot [\text{-} \mu_{e} \ \frac{\text{-} \nabla (V)}{l_{c}} \exp(N_{e}) -
                           D_{e} \exp(N_{e}) \frac{\nabla (N_{e})}{l_{c}}]
\end{equation}

Where $N_{e}$ is the molar density of the electrons in logarithmic form, $V_{c}$ is the
scaling factor of the potential , and $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

An example of how to use `JouleHeating` can be found in the
test file `Lymberopoulos_with_argon_metastables.i`.

!listing test/tests/Lymberopoulos_rf_discharge/Lymberopoulos_with_argon_metastables.i block=Kernels/mean_en_joule_heating

!syntax parameters /Kernels/JouleHeating

!syntax inputs /Kernels/JouleHeating

!syntax children /Kernels/JouleHeating
