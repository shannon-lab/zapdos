# Tutorial 1 - Diffusion + Constant Source

!---

# Problem Statement

Consider a one dimensional single species, $i$, plasma on the domain $x\in\left[-\frac{l}{2}, \frac{l}{2}\right]$. Additionally, consider that this is a purely diffusive system with a constant source term due to a constant background gas density $n_g$. This system takes the following form

\begin{equation}
  -
  \nabla
  \cdot
  \left(
    D \nabla n_i
  \right)
  =
  k
  n_g
\end{equation}


Where $D$ is a constant diffusion coefficient, $n_i$ is the species density, $k$ is a constant first order constant reaction rate. Additionally, a zero density boundary condition will be imposed

\begin{equation}
  n_i
  \left(
    \pm \frac{l}{2}
  \right)
  =
  0
\end{equation}

!---

# style=margin-top:1em;

### Explore what happens as the diffusion coefficient is varried.

!listing tutorial/tutorial01-Diffusion/diffusion-only.i block=Materials/gas_species_0

### Explore what happens as the reaction rate is varied.

!listing tutorial/tutorial01-Diffusion/diffusion-only.i block=Materials/FirstOrder_Reaction

!---

# Analytic Solution

!media media/tutorial1.png
       style=width:300px;padding-left:20px;float:right;clear:right;
       caption=Diffusive Species Solution.

# style=margin-top:3em;

\begin{equation}
  n_i(x)
  =
  \frac{
    k n_g l^2
   }{
    8 D
   }
   \left[
    1  -
    \left(
    \frac{2x}{l}
    \right)^2
   \right]
\end{equation}
