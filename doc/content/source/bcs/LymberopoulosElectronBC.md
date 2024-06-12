# LymberopoulosElectronBC

!syntax description /BCs/LymberopoulosElectronBC

## Overview

`LymberopoulosElectronBC` is a thermal outflow boundary condition with the addition of ion induced secondary electron energy.

The outflow is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = k_{s} n_{e} - \gamma \left[ \text{sign}_{i} \mu_{i} n_{i} \text{-} \nabla (V) \cdot \textbf{n} \right]
\end{equation}

Where $\Gamma_{e}$ is the outflow of the electrons normal to the boundary, $\textbf{n}$ is the normal of the boundary, $n_{e}$ is the electron density, $n_{i}$ is the ion density, $k_{s}$ is thermal speed of the electrons, $\mu_{i}$ is the oion mobility coefficient, $\text{sign}_{i}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species), $V$ is the potential, and $\gamma$ is the ion induced secondary electron coefficient. When converting the density to log form and applying a scaling
factor of the mesh, the strong form for `LymberopoulosElectronBC` is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = k_{s} \exp(N_{e}) - \gamma \left[ \text{sign}_{i} \mu_{i} \exp(N_{i}) \text{-} \nabla (V / l_{c}) \cdot \textbf{n} \right]
\end{equation}

Where $N_{j}$ is the molar density of the specie in log form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

An example of how to use `LymberopoulosElectronBC` can be found in the
test file `RF_Plasma_actions.i`.

!listing test/tests/DriftDiffusionAction/RF_Plasma_actions.i block=BCs/em_physical_right

!syntax parameters /BCs/LymberopoulosElectronBC

!syntax inputs /BCs/LymberopoulosElectronBC

!syntax children /BCs/LymberopoulosElectronBC
