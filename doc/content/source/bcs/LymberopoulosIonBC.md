# LymberopoulosIonBC

!syntax description /BCs/LymberopoulosIonBC

## Overview

`LymberopoulosIonBC` is a thermal outflow boundary condition with the addition of ion induced secondary electron energy.

The outflow is defined as

\begin{equation}
\Gamma_{+} \cdot \textbf{n} = \mu_{+} n_{+} \text{-} \nabla (V) \cdot \textbf{n}
\end{equation}

Where $\Gamma_{+}$ is the outflow of the ions normal to the boundary, $\textbf{n}$ is the normal of the boundary, $n_{+}$ is the ion density, $\mu_{+}$ is the ion mobility coefficient, and $V$ is the potential. When converting the density to log form and applying a scaling factor of the mesh, the strong form for `LymberopoulosIonBC` is defined as

\begin{equation}
\Gamma_{e} \cdot \textbf{n} = \mu_{+} \exp(N_{+}) \text{-} \nabla (V / l_{c}) \cdot \textbf{n}
\end{equation}

Where $N_{j}$ is the molar density of the specie in log form and
$l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

An example of how to use `LymberopoulosIonBC` can be found in the
test file `RF_Plasma_actions.i`.

!listing test/tests/DriftDiffusionAction/RF_Plasma_actions.i block=BCs/Ar+_physical_right_advection

!syntax parameters /BCs/LymberopoulosIonBC

!syntax inputs /BCs/LymberopoulosIonBC

!syntax children /BCs/LymberopoulosIonBC
