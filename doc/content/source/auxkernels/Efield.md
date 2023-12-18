# Efield

!syntax description /AuxKernels/Efield

## Overview

`Efield` returns a component of the electrostatic electric field.

The formulation of `Efield` is defined as

\begin{equation}
E_{\text{comp.}} = \frac{\text{-} \nabla_{\text{comp.}} (V) \ V_{c}}{l_{c}}
\end{equation}

Where $E_{\text{comp.}}$ is a component of the electric field, $V$ is the potential, $V_{c}$ is the
scaling factor of the potential , and $l_{c}$ is the scaling factor of the mesh.

## Example Input File Syntax

An example of how to use `Efield` can be found in the
test file `Lymberopoulos_with_argon_metastables.i`.

!listing test/tests/Lymberopoulos_rf_discharge/Lymberopoulos_with_argon_metastables.i block=AuxKernels/Efield_calc

!syntax parameters /AuxKernels/Efield

!syntax inputs /AuxKernels/Efield

!syntax children /AuxKernels/Efield
