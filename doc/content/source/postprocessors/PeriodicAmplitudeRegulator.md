# PeriodicAmplitudeRegulator

`PeriodicAmplitudeRegulator` periodical updates its value based on the ratio of a coupled Postprocessor value and a reference value. The value of `PeriodicAmplitudeRegulator` is updated with the following scheme

\begin{equation}
  V_n =
  \frac{P_\text{ref}}{P_\text{actual}}
  V_{n-1}
\end{equation}

Where $V_n$ is the new value of the `PeriodicAmplitudeRegulator` Postprocessor, $P_\text{ref}$ is the reference value, $P_\text{actual}$ is the value of the coupled Postprocessor, $V_{n-1}$ is the pervious value of the `PeriodicAmplitudeRegulator` Postprocessor, and the subscript $n$ is some multiplicative integer of the period.


## Example Amplitude Regulation

`PeriodicAmplitudeRegulator` is intended to be used to modify the value of a control parameter to force another Postprocessor value to be equal a refernce value. For the test example [periodic_modifier.i](test/tests/postprocessors/periodic_amplitude_regulator/periodic_modifier.i), the reference value was $10$ and the coupled Postprocessor was [MultiPeriodAverager.md], which takes multiple period averages of a periodic integral that depends on the value of `PeriodicAmplitudeRegulator`. The results in the figure below are from the test example [periodic_modifier.i](test/tests/postprocessors/periodic_amplitude_regulator/periodic_modifier.i) with a more refined time step of `dt = 1e-2`. In this case, the Function Magnitude is the value of `PeriodicAmplitudeRegulator` with an initial value of $-4$ and the Periodic Integral is the value of the coupled Postprocessor, [MultiPeriodAverager.md].

!row!
!col!  small=12 medium=6 large=6
!style halign=center
!media media/periodic_modification.png
       style=width:100%;display:block;margin-top:3em;margin-left:auto;margin-right:auto;
!col-end!

!col! small=12 medium=6 large=6
!style halign=right
!media media/multi_period_mean.png
       style=width:97%;display:block;margin-top:3em;margin-left:auto;margin-right:auto;
!col-end!
!row-end!

## Example Input File Syntax

!listing test/tests/postprocessors/periodic_amplitude_regulator/periodic_modifier.i block=Functions Postprocessors

!syntax parameters /Postprocessors/PeriodicAmplitudeRegulator

!syntax inputs /Postprocessors/PeriodicAmplitudeRegulator

!syntax children /Postprocessors/PeriodicAmplitudeRegulator
