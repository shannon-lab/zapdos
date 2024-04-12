# MultipliedTimeIntegratedPostprocessor

`MultipliedTimeIntegratedPostprocessor` provides the same functionationlity as [TimeIntegratedPostprocessor.md] except you can multiply the time integral by a constant coefficient.

If the value of [TimeIntegratedPostprocessor.md] is given by

\begin{equation}
  I = \int_0^t
  f(t) dt
\end{equation}

The value returned by `MultipliedTimeIntegratedPostprocessor` will be given by


\begin{equation}
  I =
  C
  \int_0^t
  f(t) dt
\end{equation}

Where $C$ is the constant factor to scale the time integration.

## Example Input File Syntax

In this example, the variable `v` is integrated over the spatial domain using [ElementIntegralVariablePostprocessor.md], resulting in the variable `a`, and then integrated over time by a factor of $2$ using `MultipliedTimeIntegratedPostprocessor`. For reference, `a` was also integrated over time using [TimeIntegratedPostprocessor.md].

!listing test/tests/postprocessors/multiplied_time_integration/multiplied_integral.i block=Postprocessors


!syntax parameters /Postprocessors/MultipliedTimeIntegratedPostprocessor

!syntax inputs /Postprocessors/MultipliedTimeIntegratedPostprocessor

!syntax children /Postprocessors/MultipliedTimeIntegratedPostprocessor
