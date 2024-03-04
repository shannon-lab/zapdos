# PeriodicTimeIntegratedPostprocessor

`PeriodicTimeIntegratedPostprocessor` provides the same functionationlity as [MultipliedTimeIntegratedPostprocessor.md] except this integrals value will periodically be set to 0 in order to integrate values over a single period.

\begin{equation}
  I \approx
  C
  \int_0^t
  f(t) dt
  \:\:
  \text{mod}
  \left(
    \text{T}
  \right)
\end{equation}

Where $f(t)$ is a time dependent function and $\text{T}$ is the period of the cycle.




!alert note title=Proper Usage Hint
[MultipliedTimeIntegratedPostprocessor.md] uses the trapezoid rule for time integration and since this object inherits from the [MultipliedTimeIntegratedPostprocessor.md] this integration is also performed by trapezoid rule. The integration is also reset after the next time which is appoximately greater than or equal to the next period start. Users should also take care to ensure that the period they want to integrate over is sufficiently resolved. Additionally, if users would like to ensure that the time time steps hit the start of each period the [AddPeriodicControllers.md] action can be used in the following manner. The parameter `num_contoller_set` should be set to a number of periods that is greater than or equal to the number of periods you are simulating.

```
[PeriodicControllers]
  [enforcer]
    name = enforcer
    starting_cycle = 0
    cycles_between_controls = 0
    num_controller_set = 2000
  []
[]
```


## Example Input File Syntax
In this example, the variable `v` is integrated over the spatial domain using [ElementIntegralVariablePostprocessor.md], resulting in the variable `a`, and then periodically integrated over time using `PeriodicTimeIntegratedPostprocessor`.

!listing test/tests/postprocessors/periodic_integration/periodic_integral.i block=Postprocessors


!syntax parameters /Postprocessors/PeriodicTimeIntegratedPostprocessor

!syntax inputs /Postprocessors/PeriodicTimeIntegratedPostprocessor

!syntax children /Postprocessors/PeriodicTimeIntegratedPostprocessor
