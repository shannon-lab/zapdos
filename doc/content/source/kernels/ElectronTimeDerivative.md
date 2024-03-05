# ElectronTimeDerivative

!syntax description /Kernels/ElectronTimeDerivative

## Overview

`ElectronTimeDerivative` is the time derivative term used for variables in logarithmic form.
Despite the name, `ElectronTimeDerivative` can be applied to any logarithmic form variable,
not just electrons.

The strong form for a time derivative term is usually defined as

\begin{equation}
\frac{\partial n_{j}}{\partial t}
\end{equation}

Where $n_{j}$ is the density. When converting the density to logarithmic form, the
strong form for `ElectronTimeDerivative` is defined as

\begin{equation}
\frac{\partial N_{j}}{\partial t} \exp(N_{j})
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form.

## Example Input File Syntax

An example of how to use `ElectronTimeDerivative` can be found in the
test file `Lymberopoulos_with_argon_metastables.i`.

!listing test/tests/Lymberopoulos_rf_discharge/Lymberopoulos_with_argon_metastables.i block=Kernels/em_time_deriv

!syntax parameters /Kernels/ElectronTimeDerivative

!syntax inputs /Kernels/ElectronTimeDerivative

!syntax children /Kernels/ElectronTimeDerivative
