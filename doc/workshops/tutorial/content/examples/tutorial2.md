# Tutorial 2 - Reaction Network

!---

# Problem Statement

Consider a system of 3 species, $A, B, C$.

- $A$ decays at a rate of $k_a$ into species $B$
- $B$ decays at a rate of $k_b$ into species $C$
- Species $C$ is a stable species

The initial condition for this system is given by

\begin{equation}
  n_A(0) = n_{A_0}
\end{equation}

\begin{equation}
  n_B(0) = n_C(0) = 0
\end{equation}

!---

# System of Equations

\begin{equation}
  \pf{n_A}{t}
  =
  - k_A
  n_A
\end{equation}

\begin{equation}
  \pf{n_B}{t}
  =
  k_A n_A
  -
  k_B n_B
\end{equation}

\begin{equation}
  \pf{n_C}{t}
  =
  k_B n_B
\end{equation}

!---

### How would the reaction rates need to change to decrease the decay of $A$ and increase the growth of $B$?

!listing tutorial/tutorial02-ReactionNetwork/transient-kinetics.i block=Reactions/Gas


!---

# Analytic Solution

!media media/tutorial2.png
       style=width:300px;padding-left:20px;float:right;clear:right;
       caption=Species evolution over time.


# style=margin-top:2.5em;

\begin{equation}
  n_A(t) =
  n_{A_0}
  e^{-k_A t}
\end{equation}

\begin{equation}
  n_B(t) =
  n_{A_0}
  \frac{
    k_A
  }{
    k_B - k_A
  }
  \left(
    e^{-k_A t}
    -
    e^{-k_B t}
  \right)
\end{equation}


\begin{equation}
  n_C(t)
  =
  n_{A_0}
  \left[
    1 +
    \frac{1}{
      k_A - k_B
    }
    \left(
      k_B
      e^{-k_A t}
      -
      k_A e^{-k_B t}
    \right)
  \right]
\end{equation}




