# Drift-Diffusion Model

The drift-diffusion model is the primary model used in Zadpos for industrial applications of plasmas. Instead of solving for the species velocity directly, the drift-diffusion model redefines the species density flux into a diffusion and an electric field driven advection term. From the $1^{\text{th}}$ moment of the Boltzmann equation, the momentum equation, the following assumptions are applied:

- acceleration, inertial forces, and the magnetic fields are neglectable,
- the momentum source term is dominated by collisions with neutrals, and
- the pressure is isotropic, which converts the pressure tensor into a scalar value.

This leads to a momentum equation of:

\begin{equation}
Z e n \vec{E} - \nabla p - m n \nu_{m} \vec{u} = 0
\end{equation}

where:

- $Z$ is the charge of the species,
- $e$ is the elemental charge,
- $n$ is the species density,
- $\vec{E}$ is the electric field,
- $p$ is the pressure scalar,
- $m$ is the mass of the species,
- $\nu_{m}$ is the species collision frequency with neutrals, and
- $\vec{u}$ is the velocity.

With the addition of assuming the ideal gas law for the pressure, the species velocity is redefined as:

\begin{equation}
\vec{u} = \frac{Z e}{m \nu_{m}} \vec{E} - \frac{k_{\text{B}} T}{m \nu_{m}} \frac{\nabla n}{n}
\end{equation}

where:

- $k_{\text{B}}$ is the Boltzmann constant, and
- $T$ is the species temperature.

From this definition of velocity, two new transport coefficients can be defined: the mobility, $\mu$, and diffusivity, $D$.

\begin{equation}
\mu = \frac{Z e}{m \nu_{m}} \\[10pt]
D = \frac{k_{\text{B} T}}{m \nu_{m}}
\end{equation}

In combination with the $0^{\text{th}}$ moment of the Boltzmann equation, the continuity equation, the drift-diffusion model is:

\begin{equation}
\frac{d n}{d t} + \nabla \cdot \vec{\Gamma} = S_{n} \\[10pt]
\vec{\Gamma} = \text{sign} \mu \vec{E} n - D \nabla n
\end{equation}

Where:

- $\text{sign}$ indicates the advection behavior ($\text{+}1$ for positively charged species, $\text{-}1$ for negatively charged species, and $0$ for neutral species),
- $\Gamma$ is the species flux, and
- $S_{n}$ is the source term.

A similar approach is taken with the electron energy flux in the $2^{\text{th}}$ moment of the Boltzmann, the energy equation, where:

\begin{equation}
\frac{\partial n_{\epsilon}}{\partial t} + \nabla \cdot \vec{\Gamma_{\epsilon}} - \vec{E} \cdot \vec{\Gamma_{e}} = S_{\epsilon} \\[10pt]
\vec{\Gamma}_{\epsilon} = - \mu_{\epsilon} \vec{E} n_{\epsilon} - D_{\epsilon} \nabla n_{\epsilon}
\end{equation}

Where:

- the subscript $e$ represents properties of the electrons,
- $n_{\epsilon}$ is the electron mean energy density (defined as $n_{\epsilon} = \epsilon n_{e}$)
- $\epsilon$ is the electron mean energy in units of eV,
- $\mu_{\epsilon}$ is the electron mean energy density mobility coefficient,
- $D_{\epsilon}$ is the electron mean energy density diffusion coefficient, and
- $S_{\epsilon}$ is the electron mean energy source term.

## Transport Coefficients

!style halign=left
The transport coefficients used in the drift-diffusion model need to be determine, either through experiments or a simplified Boltzmann solver. The Boltzmann solver of choice that has been used in several Zapdos simulations is [BOLSIG+](https://www.bolsig.laplace.univ-tlse.fr/). More on how these transport coefficients are calculated, please refer to [!cite](hagelaar2005solving).

## Source Terms

!style halign=left
The source terms depend on the chemistry reaction network of interest. This often require networks that are defined using rate coefficients or Townsend coefficients. The general form of the source terms defined by rate coefficients are:

\begin{equation}
S_{n} = \sum_{i}{\left( \nu_{i} k_{i} \prod_{j}{n_{j}} \right)} \\[10pt]
S_{\epsilon} = \sum_{i}{\left( E_{i} \nu_{i} k_{i} \prod_{j}{n_{j}} \right)}
\end{equation}

where:

- subscript $i$ represents a reaction within the reaction network,
- subscript $j$ represents the reactants within a reaction,
- $\nu$ is the stoichiometric coefficient,
- $k$ is the rate coefficient, and
- $E$ is the energy threshold of the reaction.

The general form of the source terms defined by Townsend coefficients are:

\begin{equation}
S_{n} = \lvert \Gamma_{e} \rvert \sum_{i}{\alpha_{i}} \\[10pt]
S_{\epsilon} = \lvert \Gamma_{e} \rvert \sum_{i}{\left( E_{i} \alpha_{i} \right)}
\end{equation}

where:

- $\alpha$ is the Townsend coefficient.

The rate and Townsend can also be provide from a simplified Boltzmann solver, such as [BOLSIG+](https://www.bolsig.laplace.univ-tlse.fr/).
