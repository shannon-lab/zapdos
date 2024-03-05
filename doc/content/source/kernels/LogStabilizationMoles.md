# LogStabilizationMoles


!syntax description /Kernels/LogStabilizationMoles

## Overview

`LogStabilizationMoles` adds an offset to the applied variable in logarithmic form. In Zapdos,
densities and energy densities are treated in logarithmic form to avoid negative values. This is
represented as

\begin{equation}
N_{j} = \log(n_{j} / N_{A}) \\
N_{\varepsilon} = \log(\varepsilon n_{j} / N_{A})
\end{equation}

Where $N_{j}$ and $N_{\varepsilon}$ are the logarithmic forms of the density and energy
density, $n_{j}$ and $n_{\varepsilon}$ is the density and energy density, $N_{A}$ is Avogadro's number, and $\varepsilon$ is the energy. When $n_{j}$ or
$n_{\varepsilon}$ approach zero, numerical instabilities can occur. To avoid this,
an artificial source term is added in the form of:

\begin{equation}
F_{j} = S_{j} + \exp(-(b+u))
\end{equation}

Where $F_{j}$ are the main physics terms, $S_{j}$ are the source terms, and $b$
is the offset.

## Example Input File Syntax

!listing test/tests/1d_dc/mean_en.i block=Kernels/em_log_stabilization

!syntax parameters /Kernels/LogStabilizationMoles

!syntax inputs /Kernels/LogStabilizationMoles

!syntax children /Kernels/LogStabilizationMoles
