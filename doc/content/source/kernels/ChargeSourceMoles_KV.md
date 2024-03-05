# ChargeSourceMoles_KV

!syntax description /Kernels/ChargeSourceMoles_KV

## Overview

`ChargeSourceMoles_KV` adds the charge contribution of a single species to Poisson's equation, describing the
relationship between total charge density and electrostatic potential.

The strong form for `ChargeSourceMoles_KV` is defined as right side of

\begin{equation}
-\varepsilon_{0} \nabla^{2} V = \sum_{j} \left[ q_{j} n_{j} \right]
\end{equation}

where $V$ is the electrostatic potential, $q_{j}$ is the charge of the species, $n_{j}$ is the density of the charged species, and $\varepsilon_{0}$ is the permittivity of free space. When converting the density to logarithmic form and applying a scaling factor of the mesh and voltage, the strong form for `NeumannCircuitVoltageMoles_KV` is defined as

\begin{equation}
-\varepsilon_{0}\nabla^{2} V = \frac{\sum_{j} \left[ q_{j} \exp(N_{j}) N_{A} \right]}{V_{c}}
\end{equation}


where $N_{j}$ is the molar density of the species in logarithmic form, $N_{A}$ is Avogadro's number, and $V_{c}$ is the scaling factor of the potential.

## Example Input File Syntax

An example of how to use `ChargeSourceMoles_KV` can be found in the
test file `Lymberopoulos_with_argon_metastables.i`.

!listing test/tests/Lymberopoulos_rf_discharge/Lymberopoulos_with_argon_metastables.i block=Kernels/Ar+_charge_source

!listing test/tests/Lymberopoulos_rf_discharge/Lymberopoulos_with_argon_metastables.i block=Kernels/em_charge_source


!syntax parameters /Kernels/ChargeSourceMoles_KV

!syntax inputs /Kernels/ChargeSourceMoles_KV

!syntax children /Kernels/ChargeSourceMoles_KV
