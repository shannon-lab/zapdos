# Multi-fluid Description of Plasma

The foundational form of the multi-fluid description is derived by taking the moments of the Boltzmann equation. The Boltzmann equation describes the change in the distribution function for a set of particles in position and velocity space (i.e., $\vec{r}$ and $\vec{v}$). The Boltzmann equation can be represented as:


\begin{equation}
\frac{\partial}{\partial t} f \left( \vec{r},\vec{v},t \right) +  \vec{v} \cdot \nabla _{\vec{r}} f \left( \vec{r},\vec{v},t \right) +  \vec{A}  \cdot \nabla _{\vec{v}} f \left( \vec{r},\vec{v},t \right) = \left( \frac{\partial f}{\partial t} \right) _{\text{coll.}}
\end{equation}

Where:

- $f \left( \vec{r},\vec{v},t \right)$ is the particle distribution function,
- $\nabla _{\vec{r}}$ is the gradient operator in position space,
- $\nabla _{\vec{v}}$ is the gradient operator in velocity space,
- $\vec{A}$ is an acceleration acting on the particles, and
- $\left( \frac{\partial f}{\partial t} \right) _{\text{coll.}}$ is the collision effects acting on the particles.

Obtaining the moments of the Boltzmann equation requires taking the integral over velocity space. This allows for the tracking of number densities and group velocities ($n$ and $\vec{u}$), instead of particle tracking. The number density and group velocity are defined as:

\begin{equation}
n \left( \vec{r},t \right) = \int{ f \left( \vec{r},\vec{v},t \right) d \vec{v} }
\end{equation}

And,

\begin{equation}
\vec{u} \left( \vec{r},t \right) = \frac{1}{n \left( \vec{r},t \right)} \int{ \vec{v} \ f \left( \vec{r},\vec{v},t \right) d \vec{v} }
\end{equation}

## Moments of the Boltzmann Equations

!style halign=left
Most models in Zapdos utilize the first three moments of the Boltzmann equation (commonly referred to as the $0^{\text{th}}$ - $2^{\text{nd}}$ moments). This page summarizes the foundational form of these moments, but does not go throught the derivation. If the reader would like an explanation of the derivations, please refer to [!cite](inan2010principles). The first three moments are:


$\textbf{0}^{\textbf{th}}$ $\textbf{Moment - Continuity}$

\begin{equation}
\frac{\partial n}{\partial t} + \nabla \cdot \left( n \vec{u} \right) = S_{n}
\end{equation}

Where:

- $S_{n}$ is the source term for the species.

$\textbf{1}^{\textbf{th}}$ $\textbf{Moment - Momentum}$

\begin{equation}
\frac{\partial}{\partial t} \left( mn\vec{v} \right) + \nabla \cdot \left( mn\vec{v} \otimes \vec{v} \right) + \nabla \cdot \Psi - Zen\left( \vec{E} + \vec{v} \times \vec{B} \right) = \vec{S}_{m\vec{v}}
\end{equation}

Where:

- $m$ is the mass of the species,
- $\Psi$ is the pressure tensor,
- $Z$ is the charge of the species,
- $e$ is the elemental charge,
- $\vec{E}$ is the electric field,
- $\vec{B}$ is the magnetic field, and
- $\vec{S}_{m\vec{v}}$ is the momentum source term.

$\textbf{2}^{\textbf{th}}$ $\textbf{Moment - Energy}$

\begin{equation}
\frac{\partial \epsilon n}{\partial t} + \nabla \cdot \vec{Q} - Zen\vec{E} \cdot \vec{u} = S_{\epsilon}
\end{equation}

Where:

- $\epsilon$ is the mean energy,
- $Q$ is the energy flux, and
- $S_{\epsilon}$ is the energy source term.

All fluid can be derived from those moments, and any additional higher moments, but the exact definitions for several of the variable listed (such as $\vec{Q}$, $S_{n}$, $\vec{S}_{m\vec{v}}$, and $S_{\epsilon}$) depend on the fluid model of choice and closure method. For additional information about the particular models used in Zapdos, follow the links below:

$\textbf{Models:}$

- [Drift-Diffusion Model](drift_diffusion_model.md)
