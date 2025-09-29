# DielectricBCWithEffEfield

!syntax description /BCs/DielectricBCWithEffEfield

## Overview

`DielectricBCWithEffEfield` is a type of [`NeumannBC`](/bcs/NeumannBC.md) for the potential on the boundary of a grounded ideal dielectric. The advection term for the ion is determined by an effective electric field.

The potential at the boundary of a grounded ideal dielectric is defined as

\begin{equation}
\varepsilon_{p}\frac{\partial (E \cdot \textbf{n}) }{\partial t} - \frac{\varepsilon_{i}}{d_{i}}\frac{\partial V_{i}}{\partial t} = - e \left( \Gamma_{+} \cdot \textbf{n} -\Gamma_{e} \cdot \textbf{n} \right) \\[10pt]
\Gamma_{e} \cdot \textbf{n}  = \frac{1}{4}\sqrt{\frac{8 k T_{e}}{\pi m_{e}}} \ n_e - \gamma \Gamma_{+} \cdot \textbf{n} \\[10pt]
\Gamma_{+} \cdot \textbf{n}  = a \ \mu_{+} \ \vec{E}_{\text{Eff.}} \cdot \textbf{n} \ n_{+} \\[10pt]
a =
\begin{cases}
1, & \mu_{+} \ \vec{E}_{\text{Eff.}} \cdot \textbf{n} > 0\\
0, & \mu_{+} \ \vec{E}_{\text{Eff.}} \cdot \textbf{n} \leq 0\\
\end{cases}
\end{equation}

where

- $\varepsilon_{i}$ is the permittivity of the dielectric,
- $d_{i}$ is the thickness of the dielectric,
- $V_{i}$ is the voltage on the dielectric,
- $\textbf{n}$ is the normal to the boundary,
- $e$ is the elemental charge,
- $\varepsilon_{p}$ is the permittivity of the plasma (defaulted to the permittivity of free space),
- $\vec{E} \cdot \textbf{n}$ is the electric field normal to the dielectric,
- $\Gamma_{e}$ is the electron outflow flux, and
- $\Gamma_{+}$ is the ion outflow flux.

!alert note title=Flux Information
$\Gamma_{e}$ and $\Gamma_{+}$ are defined with the [`SakiyamaElectronDiffusionBC`](/bcs/SakiyamaElectronDiffusionBC.md), [`SakiyamaSecondaryElectronWithEffEfieldBC`](/bcs/SakiyamaSecondaryElectronWithEffEfieldBC.md) and [`SakiyamaIonAdvectionWithEffEfieldBC`](/bcs/SakiyamaIonAdvectionWithEffEfieldBC.md) (please refer to those BC's for more information on the fluxes).

To convert the above equation into the form of a NeumannBC, the time integral is taken such that:

\begin{equation}
\int{ \varepsilon_{p}\frac{\partial (E \cdot \textbf{n}) }{\partial t} } dt - \int{ \frac{\varepsilon_{i}}{d_{i}}\frac{\partial V_{i}}{\partial t} } dt = \int{ - e \left( \Gamma_{+} \cdot \textbf{n} -\Gamma_{e} \cdot \textbf{n} \right) } dt
\end{equation}

Using the trapezoidal rule for the definite integral and rearranging the equation such that the electric field term is on one side results in:

\begin{equation}
\varepsilon_{p} \left( E \cdot \textbf{n} \right) = \varepsilon_{p} \left( E_{\text{old}} \cdot \textbf{n} \right) + \frac{\varepsilon_{i}}{d_{i}} \left( V - V_
{old} \right) - 0.5 \left( e \left( \Gamma_{+} \cdot \textbf{n} - \Gamma_{e} \cdot \textbf{n} \right) + e \left( \Gamma_{+} \cdot \textbf{n} - \Gamma_{e} \cdot \textbf{n} \right)_{old} \right) dt
\end{equation}

where

- The subscript $\text{old}$ is the value of the variable during the previous time step, and
- $dt$ is the current time step size.

Lastly, the electrostatic approximation is applied to the electric field normal to the dielectric, which results in a NeumannBC for the potential defined as:

\begin{equation}
\varepsilon_{p} \left( -\nabla V \cdot \textbf{n} \right) = \varepsilon_{p} \left( -\nabla V_{\text{old}} \cdot \textbf{n} \right) + \frac{\varepsilon_{i}}{d_{i}} \left( V - V_
{old} \right) - 0.5 \left( e \left( \Gamma_{+} \cdot \textbf{n} - \Gamma_{e} \cdot \textbf{n} \right) + e \left( \Gamma_{+} \cdot \textbf{n} - \Gamma_{e} \cdot \textbf{n} \right)_{old} \right) dt
\end{equation}

## Example Input File Syntax

!listing test/tests/mms/bcs/2D_DielectricBCWithEffEfield.i block=BCs/potential_left_BC

!syntax parameters /BCs/DielectricBCWithEffEfield

!syntax inputs /BCs/DielectricBCWithEffEfield

!syntax children /BCs/DielectricBCWithEffEfield
