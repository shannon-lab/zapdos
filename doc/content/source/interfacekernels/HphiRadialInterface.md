# HphiRadialInterface

!syntax description /InterfaceKernels/HphiRadialInterface

## Overview

`HphiRadialInterface` enforces the axial electric field at an interface to be continuous, assuming an axisymmetric geometry. This is done by using Ampère–Maxwell law to relate the azimuthal magnetic flux to the axial electric field.

Assuming negligible current density when compared to the displacement current, Ampère–Maxwell law in the frequency domain is defined as:

\begin{equation}
  \nabla \times \textbf{H} = \varepsilon \omega \textbf{E}
\end{equation}

Where:

- $\textbf{H}$ is the magnetizing field,
- $\varepsilon$ is the material permittivity,
- $\omega$ is the frequency, and
- $\textbf{E}$ is the electric field.

By assuming an axisymmetric cylindrical geometry, this equation simplifies to:

\begin{equation}
  \frac{\partial H_{\phi}}{\partial r} + \frac{H_{\phi}}{r}  = \varepsilon \omega \text{E}_{z}
\end{equation}

Where:

- $H_{\phi}$ is the azimuthal component of the magnetizing field,
- $\text{E}_{z}$ is the axial component of the electric field, and
- $r$ is the radial distance from the axial centerline.

To enforce that $\text{E}_{z}$ is continuous at an interface, where $\omega$ is the same on both side of the boundary, the following expression can be derived:

\begin{equation}
  \text{E} _{z1} = \text{E} _{z2}
\end{equation}
\begin{equation}
  \frac{1}{\varepsilon_{1}} \left( \frac{\partial H_{\phi 1}}{\partial r} \cdot \textbf{n} + \frac{H_{\phi 1}}{r} \right) = \frac{1}{\varepsilon_{2}} \left( \frac{\partial H_{\phi 2}}{\partial r} \cdot \textbf{n} + \frac{H_{\phi 2}}{r} \right)
\end{equation}
\begin{equation}
  \frac{\partial H_{\phi 1}}{\partial r} \cdot \textbf{n} = \frac{\varepsilon_{1}}{\varepsilon_{2}} \left( \frac{\partial H_{\phi 2}}{\partial r} \cdot \textbf{n} + \frac{H_{\phi 2}}{r} \right) - \frac{H_{\phi 1}}{r}
\end{equation}

Where:

- Subscript $1$ is the the primary side of the interface,
- Subscript $2$ is the the neighboring side of the interface, and
- $\textbf{n}$ is the normal vector of the interface.

The expression is equated to the gradient of $H_{\phi 1}$ because MOOSE's interface kernels provide general flux condition at an interface. For more information, please see the [InterfaceKernels System page](syntax/InterfaceKernels/index.md).

## Example Input File Syntax

!listing test/tests/TM10_circular_wg/TM_steady_dieletric.i block=InterfaceKernels/Ez_continuous

!syntax parameters /InterfaceKernels/HphiRadialInterface

!syntax inputs /InterfaceKernels/HphiRadialInterface

!syntax children /InterfaceKernels/HphiRadialInterface
