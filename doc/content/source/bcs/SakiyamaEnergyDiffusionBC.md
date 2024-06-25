# SakiyamaEnergyDiffusionBC

!syntax description /BCs/SakiyamaEnergyDiffusionBC

## Overview

`SakiyamaEnergyDiffusionBC` is a thermal outflow boundary condition.

The thermal driven outflow is defined as

\begin{equation}
\Gamma_{\epsilon} \cdot \textbf{n} = \frac{1}{4}\sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \frac{n_{\epsilon}}{n_{e}}}\frac{5}{3}n_{\epsilon}
\end{equation}

Where $\Gamma_\varepsilon \cdot \textbf{n}$ is the flux normal to the boundary, $\textbf{n}$ is the normal vector of the boundary, $n_{e}$ is the electron density, $e$ is the elementary charge, and $n_{\epsilon}$ is the mean energy density. When converting the density to log form and applying a scaling factor of the mesh, the strong form for `SakiyamaEnergyDiffusionBC` is defined as

\begin{equation}
\Gamma_{\epsilon} \cdot \textbf{n} = \frac{1}{4}\sqrt{\frac{8e}{\pi m_{e}} \frac{2}{3} \exp (N_{\epsilon} - N_{e})}\frac{5}{3}\exp (N_{\epsilon})
\end{equation}

Where $N_{j}$ is the molar density of the species in log form.

## Example Input File Syntax

An example of how to use `SakiyamaEnergyDiffusionBC` can be found in the
test file `2D_RF_Plasma_actions.i`.

!listing test/tests/DriftDiffusionAction/2D_RF_Plasma_actions.i block=BCs/mean_en_physical_diffusion

!syntax parameters /BCs/SakiyamaEnergyDiffusionBC

!syntax inputs /BCs/SakiyamaEnergyDiffusionBC

!syntax children /BCs/SakiyamaEnergyDiffusionBC
