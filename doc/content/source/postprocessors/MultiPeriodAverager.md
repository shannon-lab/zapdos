# MultiPeriodAverager

`MultiPeriodAverager` calculates the the period average of values of periodic fuctions at the end of each period, such that:
\begin{equation}
P = \frac{\sum_i^{N_\text{T}} f(\text{T})_i }{N_\text{T}}
\end{equation}
Where $P$ is the value of `MultiPeriodAverager`, $N_\text{T}$ is the number of periods to average over, and $f(\text{T})_i$ is the value of the periodic value at the end of a period.  Until the number of periods over which you are averaging has passed the value of the Postprocessor will reflect the previously calculated average.

!alert warning
Before the first average is calculated the value of this post processor will be 0.


!alert note title=Proper Usage Hint
`MultiPeriodAverager` is intended to be used with the [PeriodicTimeIntegratedPostprocessor.md].

## Example Input File Syntax

!listing test/tests/postprocessors/multi_period_averaging/multi_period_averager.i block=Postprocessors


!syntax parameters /Postprocessors/MultiPeriodAverager

!syntax inputs /Postprocessors/MultiPeriodAverager

!syntax children /Postprocessors/MultiPeriodAverager
