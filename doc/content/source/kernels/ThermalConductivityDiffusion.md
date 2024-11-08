# ThermalConductivityDiffusion

!syntax description /Kernels/ThermalConductivityDiffusion

## Overview

`ThermalConductivityDiffusion` supplies a electron energy diffusion term that assumes an electron thermal conductivity for the electron energy flux.

The thermal conductivity formulation of the electron energy flux in terms of electron temperature is defined as:

\begin{equation}
  \vec{q}_{e} = -K_{e} \nabla T_{e} + \frac{5}{2}T_{e} \vec{\Gamma}_{e} \\[10pt]
  K_{e} = \frac{3}{2} D_{e} n_{e} \\[10pt]
  \vec{\Gamma}_{e} = -D_{e} \nabla n_{e} - \mu_{e} n_{e} \vec{E}
\end{equation}

where

- $\vec{q}_{e}$ is the electron energy flux,
- $K_{e}$ is the electron thermal conductivity,
- $T_{e}$ is the electron temperature (in units of eV),
- $\vec{\Gamma}_{e}$ is the electron flux,
- $n_{e}$ is the electron density,
- $D_{e}$ is the electron diffusion coefficient,
- $\mu_{e}$ is the electron mobility coefficient, and 
- $\vec{E}$ is the electric field.

Instead of the electron temperature, Zapdos solves for the electron energy density ($n_{\varepsilon}$), such that:

\begin{equation}
  T_{e} = \frac{2}{3} \frac{n_{\varepsilon}}{n_{e}}
\end{equation}

Using the electron energy density, the thermal conductivity formulation of the electron energy flux becames:

\begin{equation}
  \vec{q}_{e} = -\mu_{\varepsilon} n_{e} \vec{E} - D_{\varepsilon} \nabla n_{\varepsilon} + \frac{2}{3} D_{e} \left( \nabla n_{\varepsilon} - \frac{n_{\varepsilon}}{n_{e}} \nabla n_{e} \right)
\end{equation}

where

- $D_{\varepsilon}$ is the electron energy diffusion coefficient (assuming $D_{\varepsilon} = \frac{5}{3} D_{e}$), and
- $\mu_{e}$ is the electron energy mobility coefficient (assuming $\mu_{\varepsilon} = \frac{5}{3} \mu_{e}$).

The first term is supplied by [EFieldAdvection.md], the second term is suppled by [CoeffDiffusion.md] and the remaining terms are supplied by `ThermalConductivityDiffusion`.

When converting the density to logarithmic form and applying a scaling factor of the mesh, `ThermalConductivityDiffusion` is defined as

\begin{equation}
\frac{2}{3} D_{e} \left( \exp(N_{\varepsilon}) \left( \nabla N_{\varepsilon} / l_{c} \right) - \exp(n_{\varepsilon}-n_{e}) \exp(N_{e}) \left( \nabla N_{e} / l_{c} \right) \right)
\end{equation}

Where $N$ is the molar density of the species in logarithmic form and
$l_{c}$ is the scaling factor of the mesh.



## Example Input File Syntax

!listing test/tests/mms/continuity_equations/2D_Coupling_Electons_Potential_Ions_MeanEnergy_Einstein_Relation.i block=Kernels/mean_en_diffusion_correction

!syntax parameters /Kernels/ThermalConductivityDiffusion

!syntax inputs /Kernels/ThermalConductivityDiffusion

!syntax children /Kernels/ThermalConductivityDiffusion
