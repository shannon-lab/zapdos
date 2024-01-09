# ElectronTemperature

!syntax description /AuxKernels/ElectronTemperature

## Overview

`ElectronTemperature` returns the electron temperature.

The electron temperature is defined as

\begin{equation}
T_{e} = \frac{2}{3} \frac{n_{\varepsilon}}{n_{e}}
\end{equation}

Where $T_{e}$ is the electron temperature, $n_{\varepsilon}$ is the mean energy density
of the electrons, and $n_{e}$ is the electron density.
When converting the density to logarithmic form,
`ElectronTemperature` is defined as

\begin{equation}
T_{e} = \frac{2}{3} \exp(N_{\varepsilon} - N_{e})
\end{equation}

Where $N_{\varepsilon}$ is the electron mean energy density in logarithmic form
and $N_{e}$ is the electron density in logarithmic form.

## Example Input File Syntax

An example of how to use `ElectronTemperature` can be found in the
test file `Lymberopoulos_with_argon_metastables.i`.

!listing test/tests/Lymberopoulos_rf_discharge/Lymberopoulos_with_argon_metastables.i block=AuxKernels/Te

!syntax parameters /AuxKernels/ElectronTemperature

!syntax inputs /AuxKernels/ElectronTemperature

!syntax children /AuxKernels/ElectronTemperature
