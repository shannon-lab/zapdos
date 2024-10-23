# LymberopoulosElectronBC

!syntax description /BCs/LymberopoulosElectronBC

## Overview

`LymberopoulosElectronBC` is a thermal outflow boundary condition with the addition of ion induced secondary electron energy.

The outflow is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = k_{s} n_{e} - \gamma \left[ \text{sign}_{i} \mu_{i} n_{i}
\left( 
 \text{-} \nabla (V) 
\right) 
\cdot \textbf{n} \right]
\end{equation}

Where $\Gamma_{e} \cdot \textbf{n}$ is the flux of the electrons normal to the boundary, $\textbf{n}$ is the normal of the boundary, $n_{e}$ is the electron density, $n_{i}$ is the ion density, $\mu_{i}$ is the ion mobility coefficient, $\text{sign}_{i}$ indicates the advection behavior ($\text{+}1$ for positively charged species and $\text{-}1$ for negatively charged species), $V$ is the electric potential, $\gamma$ is the ion induced secondary electron coefficient, and $k_{s}$ is electron surface recombination coefficient. For an electron sticking coefficient of unity, $k_{s}$ is equal to the thermal speed of the electrons. When converting the density to log form and applying a scaling factor of the mesh, the strong form for `LymberopoulosElectronBC` is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = k_{s} \exp(N_{e}) - \gamma \left[ \text{sign}_{i} \mu_{i} \exp(N_{i})
\left( 
 \text{-} \nabla (V / l_{c})
 \right) 
  \cdot \textbf{n} \right]
\end{equation}

Where $N_{j}$ is the molar density of the species in log form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

An example of how to use `LymberopoulosElectronBC` can be found in the
test file `RF_Plasma_actions.i`.

!listing test/tests/DriftDiffusionAction/RF_Plasma_actions.i block=BCs/em_physical_right

!syntax parameters /BCs/LymberopoulosElectronBC

!syntax inputs /BCs/LymberopoulosElectronBC

!syntax children /BCs/LymberopoulosElectronBC
