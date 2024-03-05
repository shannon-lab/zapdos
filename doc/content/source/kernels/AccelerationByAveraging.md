# AccelerationByAveraging

!syntax description /Kernels/AccelerationByAveraging

## Overview

`AccelerationByAveraging` is an acceleration method that makes a growth prediction for a species based on the average rate of change for a given time period.

The growth of a species for a constant rate of change for a given time period is:

\begin{equation}
n_{T} - n_{0} = \frac{\text{d}n}{\text{d}t} \ T
\end{equation}

where $n_{0}$ is the species' density at the start of the acceleration, $n_{T}$ is the density at the end of the acceleration, and $T$ is the time period of the acceleration.

If the rate of change is assumed to linear, then $\frac{\text{d}n}{\text{d}t}$ an be estimated by:

\begin{equation}
\frac{\text{d}n}{\text{d}t} = \frac{n_{Ts} - n_{0s}}{t_{s}}
\end{equation}

where $t_{s}$ is some sample period of time less than $T$. The subscripts $0s$ and $Ts$ denote the beginning and end of the sample period of time, $t_{s}$ , respectively. When converting the density to logarithmic form,
`AccelerationByAveraging` is defined as

\begin{equation}
\exp(N_{j, T}) - \exp(N_{j, 0}) = \frac{\text{d}n}{\text{d}t} \ T  \\[10pt]
\frac{\text{d}n}{\text{d}t} = \frac{\exp(N_{j, Ts}) - \exp(N_{j, 0s})}{t_{s}}
\end{equation}

Where $N_{j}$ is the molar density of the species in logarithmic form.

## Example Input File Syntax

An example of how to use `AccelerationByAveraging` can be found in the
test file `Acceleration_By_Averaging_acceleration.i`.

!listing test/tests/accelerations/Acceleration_By_Averaging_acceleration.i block=Kernels/Ar*_AcclerationByAveraging

!syntax parameters /Kernels/AccelerationByAveraging

!syntax inputs /Kernels/AccelerationByAveraging

!syntax children /Kernels/AccelerationByAveraging
