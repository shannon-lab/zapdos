# Zapdos Multi-fluid Equations

!---

# Logarithmic and Logarithmic-Molar Form

# style=margin-top:2em;

In Zapdos the Logarithmic form or the Logarithmic-Molar form is used to calculate the species density. This is done for numerical stability and to prevent negative densities. The logarithmic form is given by

\begin{equation}
  \ln \left( n_i \right)
\end{equation}

and the Logarithmic-Molar form is given by

\begin{equation}
  \ln \left(
    \frac{n_i}{N_a}
\right)
\end{equation}

Where $n_i$ is the species density, and $N_a$ is avagadros number

!---

# Drift-Diffusion Approximation

# style=margin-top:2em;

\begin{equation}
  \pf{n_i}{t}
  +
  \nabla \cdot \Gamma_i
  =
  \sum_j
  S_{j,n}
\end{equation}

$i$ and $j$ denote some particle species, $n$ denotes the number of bodies in the source term, and $S_{j}$ denotes sources of species $j$ from chemical reactions.

\begin{equation}
  \Gamma_{\alpha} =
  \mu_{\alpha}
  \nabla \phi\;
  n_\alpha
  -
  D_\alpha
  \nabla n_\alpha
\end{equation}

$\mu_\alpha$ and $D_\alpha$ are the mobility and diffusivity of species $\alpha$ respectively, and $\phi$ is the electric potential.

\begin{equation}
  \Gamma_\beta =
  -
  D_\beta
  \nabla n_\beta
\end{equation}

$\alpha$ denotes charged particles, beta denotes neutral particles.

!---

# Source Terms (Crane)

# style=margin-top:1em;

\begin{equation}
  S_{i,1}
  =
  \nu
  k
  n_1
\end{equation}

\begin{equation}
  S_{i, 2}
  =
  \nu
  k
  n_1 n_2
\end{equation}

\begin{equation}
  S_{i, 3}
  =
  \nu
  k
  n_1 n_2 n_3
\end{equation}

Where $\nu$ is the stoichiometric coefficient of the reaction, $k$ is the reaction rate, and $n_i$ is the density of species $i$

!---

# Electro-Magnetic Field Calculations

When evaluating an electrostatic system Poisson's equation is used to calculate the electric potential.

\begin{equation}
  - \nabla^2 \phi
  =
  \frac{\rho}{\varepsilon_0}
\end{equation}

Where $e$ is the elementary charge, $\varepsilon_0$ is the permitivity of free space, and $\rho$ is the charge density in the system.


In cases where electromagnetic systems are considered MOOSE's [Electromagnetics Module](https://mooseframework.inl.gov/modules/electromagnetics/) is used to perform field calculations

Additionally, Zapdos is capable of calculating an effective electric field using the form

\begin{equation}
  \pf{\vec{E}_\text{eff}}{t}
  =
  \nu_\text{ion}
  \left(
    \vec{E} - \vec{E}_\text{eff}
  \right)
\end{equation}

!---

# Energy Conservation

TODO DEFINE ALLL OF THESE TERMS

\begin{equation}
  \pf{n_e \varepsilon}{t}
  +
  \nabla \cdot \Gamma_\varepsilon
  =
  - e \Gamma_e
  \cdot
  \nabla
  \phi
  -
  3
  \frac{m_e}{m_i}
  n_e n_g
  k_\text{elastic}
  T_e
  -
  \sum_i  E_i K_i
\end{equation}

\begin{equation}
  \Gamma_\epsilon
  =
  \frac{5}{3}
  \left(
  \epsilon
  \Gamma_e
  -
  n_e
  D_e
  \nabla n_e
  \right)
\end{equation}

!---

# Electrostatic Potential Boundary Conditions

\begin{equation}
  \phi =
  \phi_0
  \sin
  \left(
    2 \pi
    f t
  \right)
\end{equation}

\begin{equation}
  \phi = 0
\end{equation}

\begin{equation}
  e \Gamma_i
  -
  e \Gamma_e
  +
  \varepsilon_0
  \pf{\left(\nabla \phi\right)}{t}
  =
  \frac{\varepsilon_i}{d_i}
  \pf{\phi}{t}
\end{equation}

!---

# Flux Boundary Conditions: Type 1

TODO DEFINE ALLL OF THESE TERMS

\begin{equation}
  \Gamma_i
  \cdot
  \hat{n}
  =
  -\mu_i
  n_i
  \nabla \phi
  \cdot
  \hat{n}
\end{equation}

\begin{equation}
  \Gamma_e
  \cdot
  \hat{n}
  =
  k_s n_e
  \cdot
  \hat{n}
  -
  \gamma
  \Gamma_i
\end{equation}

\begin{equation}
  T_e = C_0
\end{equation}


!---

# Flux Boundary Conditions: Type 2

TODO DEFINE ALLL OF THESE TERMS

\begin{equation}
  \Gamma_i
  \cdot
  \hat{n}
  =
  -\mu_i
  n_i
  \nabla \phi_\text{eff}
  \cdot
  \hat{n}
\end{equation}

\begin{equation}
  \Gamma_e
  \cdot
  \hat{n}
  =
  \frac{1}{4}
  \nu_\text{th,e}
  n_e
  \cdot
  \hat{n}
  -
  \gamma
  \Gamma_i
\end{equation}

\begin{equation}
  \Gamma_\varepsilon
  \cdot
  \hat{n}
  =
  \frac{1}{4}
  \nu_\text{th,e}
  \frac{5}{3}
  n_e
  \varepsilon
  \cdot
  \hat{n}
  -
  \frac{5}{3}
  \varepsilon_{se}
  \gamma
  \Gamma_i
\end{equation}

!---

# Flux Boundary Conditions: Type 3

TODO DEFINE ALLL OF THESE TERMS

\begin{equation}
  \Gamma_i \cdot \hat{n}
  =
  \frac{
    1 - r_i
  }{
    1 + r_i
  }
  \left[
    \left(
      2 a_i - 1
    \right)
    \mu_i
    n_i
    \nabla \phi
    \cdot
    \hat{n}
    +
    \frac{1}{2}
    \nu_\text{th, i}
    n_i
  \right]
\end{equation}

\begin{equation}
  \Gamma_e \cdot \hat{n}
  =
  \frac{
    1 - r_\text{dens}
  }{
    1 + r_\text{dens}
  }
  \left[
    -
    \left(
      2 a_e - 1
    \right)
    \mu_e
    \left(
      n_e - n_\gamma
    \right)
    \nabla \phi
    \cdot
    \hat{n}
    +
    \frac{1}{2}
    \nu_\text{th,e}
    \left(
      n_e - n_\gamma
    \right)
  \right]
  -
  \left(
    1 - a_e
  \right)
  \gamma_p
  \Gamma_p
  \cdot
  \hat{n}
\end{equation}

\begin{equation}
  \Gamma_\varepsilon
  \cdot
  \hat{n}
  =
  \frac{
    1 - r_\text{en}
  }{
    1 + r_\text{en}
  }
  \left[
    -
    \left(
      2 a_e - 1
    \right)
    \frac{5}{3}
    \mu_e
     \left(
      \varepsilon n_e -
      \varepsilon_\gamma n_\gamma
    \right)
    \nabla \phi
    +
    \frac{5}{6}
    \nu_\text{th,e}
     \left(
      \varepsilon n_e -
      \varepsilon_\gamma n_\gamma
    \right)
  \right]
  -
  \frac{5}{3}
  \varepsilon_\gamma
  \left(
    1 - a_e
  \right)
  \gamma_p
  \Gamma_p
  \cdot
  \hat{n}
\end{equation}
