# AddDriftDiffusionAction

!syntax description /DriftDiffusionAction/AddDriftDiffusionAction

## Overview

The `DriftDiffusionAction` object provides the necessary variables and objects to model the transport of plasma species using the drift-diffusion approximation.

The equation for the species density using the drift-diffusion approximation is:

\begin{equation}
\frac{d n_{j}}{d t} + \nabla \cdot \left( \text{sign}_{j} \mu_{j} \vec{E} n_{j} - D_{j} \nabla n_{j} \right) = S_{j}
\end{equation}

Where:

- the subscript $j$ represents properties of the plasma species,
- $\text{sign}$ indicates the advection behavior ($\text{+}1$ for positively charged species, $\text{-}1$ for negatively charged species, and $0$ for neutral species),
- $\mu$ is the mobility coefficient,
- $D$ is the diffusion coefficient,
- $n$ is the density,
- $\vec{E}$ is the electric field, and
- $S_{j}$ is the source term.

In addition to the species density, Zapdos also tracks the mean energy density of the electrons using the equation:

\begin{equation}
\frac{d n_{\varepsilon}}{d t} + \nabla \cdot \left( - \mu_{\varepsilon} \vec{E} n_{\varepsilon} - D_{\varepsilon} \nabla n_{\varepsilon} \right) - \left( - \mu_{e} \vec{E} n_{e} - D_{e} \nabla n_{e} \right) \cdot \vec{E} = S_{\varepsilon}
\end{equation}

Where:

- the subscript $e$ represents properties of the electrons,
- $n_{\varepsilon}$ is the electron mean energy density (defined as $n_{\varepsilon} = \varepsilon n_{e}$)
- $\varepsilon$ is the electron mean energy in units of eV,
- $\mu_{\varepsilon}$ is the electron mean energy density mobility coefficient (defined as $\mu_{\varepsilon} = \frac{5}{3} \mu_{e}$ by default),
- $D_{\varepsilon}$ is the electron mean energy density diffusion coefficient (defined as $D_{\varepsilon} = \frac{5}{3} D_{e}$ by default), and
- $S_{\varepsilon}$ is the electron mean energy source term.

`DriftDiffusionAction` provides the objects for the right hand side of the above equations, while [CRANE](https://github.com/lcpp-org/crane)'s [AddZapdosReactions.md] action is often used to supply the chemistry network which defines $S_{j}$ and $S_{\varepsilon}$.

If using the electrostatic approximation for the electric field, `DriftDiffusionAction` supplies the Poisson's equation, in the form of:

\begin{equation}
\nabla \cdot \left( - \varepsilon_{0} \nabla V \right) = e \left( \left[\sum{ \text{sign}_{i} n_{i} } \right] - n_{e} \right)
\end{equation}

Where:

- $V$ is the electrostatic potential, and
- $\varepsilon_{0}$ is the permittivity of free space.

`DriftDiffusionAction` can supply additional outputs for electron temperature, current, and electric field by supplying the auxkernels [ElectronTemperature.md], [Current.md], and [Efield.md] respectively.


## Example Input File Syntax

!listing test/tests/DriftDiffusionAction/RF_Plasma_actions.i block=DriftDiffusionAction

!syntax parameters /DriftDiffusionAction/AddDriftDiffusionAction
