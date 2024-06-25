# ElectronTemperatureDirichletBC

!syntax description /BCs/ElectronTemperatureDirichletBC

## Overview

`ElectronTemperatureDirichletBC` is a type of [`PenaltyDirichletBC`](/bcs/ADPenaltyDirichletBC.md) for the electron temperature.

The electron temperature at the boundary is defined as

\begin{equation}
T_{e} = \frac{2}{3} \frac{n_{\varepsilon}}{n_{e}}
\end{equation}

Where $T_{e}$ is the electron temperature, $n_{\varepsilon}$ is the electron mean energy density, and $n_{e}$ is the electron density. When converting the density to logarithmic form,
`ElectronTemperatureDirichletBC` is defined as

\begin{equation}
T_{e} = \frac{2}{3} \exp (N_{\varepsilon} - N_{e})
\end{equation}

Where $N$ is the molar density of the species in logarithmic form.

## Example Input File Syntax

An example of how to use `ElectronTemperatureDirichletBC` can be found in the
test file `2D_RF_Plasma_actions.i`.

!listing test/tests/DriftDiffusionAction/RF_Plasma_actions.i block=BCs/mean_en_physical_right

!syntax parameters /BCs/ElectronTemperatureDirichletBC

!syntax inputs /BCs/ElectronTemperatureDirichletBC

!syntax children /BCs/ElectronTemperatureDirichletBC
