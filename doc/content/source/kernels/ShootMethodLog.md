# ShootMethodLog

!syntax description /Kernels/ShootMethodLog

## Overview

To reduce the run time of simulations of RF discharges involving neutral particles (such as metastable), acceleration by shooting method can be implemented. Zapdos' version of the shooting method scheme is based on work presented by [Lymberopoulos and Economou](https://doi.org/10.1063/1.352926), but a more general description of the method can be found by [Gogolides, Sawin and Brown](https://www.sciencedirect.com/science/article/abs/pii/000925099285133V?via%3Dihub). This scheme takes advantage of the fact that a RF discharge will eventually have a periodic steady-state, in the form of:

\begin{equation}
  N_{j}(0)-N_{j}(T)=0
\end{equation}

Where $N_{j}(0)$ is the density at the beginning of the steady-state cycle and $N_{j}(T)$ is the density end of the same cycle. To obtain a guess for the periodic solution of $N_{j}(0)$, Newton method can be applied and results in:

\begin{equation}
  N_{j}(0)^\text{new}=N_{j}(0)^\text{old}-J^{-1}(N_{j}(0)^\text{old}-N_{j}(T))
\end{equation}
\begin{equation}
  J=I-\left( \frac{\partial N_{j}}{\partial N_{j}(0)} \right)
\end{equation}

Where $I$ is the identity matrix and $\frac{\partial N_{j}}{\partial N_{j}(0)}$ is known as the sensitivity matrix. The sensitivity matrix can be calculated by:

\begin{equation}
  \frac{d}{dt}\left( \frac{\partial N_{j}}{\partial N_{j}(0)} \right) = \frac{\partial F}{\partial N_{j}} \frac{\partial N_{j}}{\partial N_{j}(0)}
\end{equation}

Where $\frac{\partial N_{j}}{\partial N_{j}(0)} = I$ at the beginning of the cycle. With this method, the acceleration scheme is as follows:

- The main simulation runs for X RF cycles.
- After X cycles, a sub-app runs for one RF cycle to calculate $N_{j}(T)$ and the sensitivity matrix.
- The metastable density is then accelerated and sends the new density to the main run.
- The main simulation runs for another X RF cycles and then accelerates again.

## Example Input File Syntax

An example of how to use `ShootMethodLog` can be found in the test file `Acceleration_By_Shooting_Method_Shooting.i`.

!listing test/tests/accelerations/Acceleration_By_Shooting_Method_Shooting.i block=Kernels/Shoot_Method


!syntax parameters /Kernels/ShootMethodLog

!syntax inputs /Kernels/ShootMethodLog

!syntax children /Kernels/ShootMethodLog
