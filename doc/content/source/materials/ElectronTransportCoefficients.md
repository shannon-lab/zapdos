# ElectronTransportCoefficients

!syntax description /Materials/ElectronTransportCoefficients

## Overview

`ElectronTransportCoefficients` defines the transport and material properties of electrons and the electron mean energy density. The following are the properties and naming scheme that `ElectronTransportCoefficients` provides:

- electron mass, labeled as "mass + 'electrons variable name'" (e.g., `massem`),
- electron and electron mean energy density charge sign, labeled as "sgn + 'variable name'" (e.g., `sgnem` and `sgnmean_en`),
- electron and electron mean energy density mobility coefficient, labeled as "mu + 'variable name'" (e.g., `muem` and `mumean_en`), and
- electron and electron mean energy density diffusion coefficient, labeled as "diff + 'variable name'" (e.g., `diffem` and `diffmean_en`).

For the electron transport coefficients, they can either be defined as a user-supplied constant or be a function of the mean energy by supplying the output of a Boltzmann solver as a lookup table (such as the outputs from [BOLSIG+](https://www.bolsig.laplace.univ-tlse.fr/)). The electron mean energy density transport coefficients are defined based on the electron coefficients, such that:

\begin{equation}
\mu_{\varepsilon} = \frac{5}{3} \mu_{e} \\[10pt]
D_{\varepsilon} = \frac{5}{3} D_{e}  \\[10pt]
\end{equation}

Where:

- the subscript $\varepsilon$ denotes mean electron energy density properties,
- the subscript $e$ denotes electron properties,
- $\mu$ is the mobility coefficient, and
- $D$ is the diffusion coefficient.

## Example Input File Syntax

!listing test/tests/DriftDiffusionAction/2D_RF_Plasma_actions.i block=Materials/GasBasics

!syntax parameters /Materials/ElectronTransportCoefficients

!syntax inputs /Materials/ElectronTransportCoefficients

!syntax children /Materials/ElectronTransportCoefficients
