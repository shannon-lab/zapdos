[Mesh]
  [generator]
    type = GeneratedMeshGenerator
    dim = 1
    xmax = 1
    nx = 100
  []
[]

[Problem]
  type = FEProblem
[]

[Variables]
  [u]
  []
[]

[Kernels]
  [null_kernel]
    type = NullKernel
    variable = u
  []
[]

[AuxVariables]
  [v]
  []
[]

[AuxKernels]
  [func_kernel]
    type = FunctionAux
    variable = v
    function = ic
  []
[]

[Functions]
  [ic]
    type = ParsedFunction
    expression = '-4 * x * (x-1) * t'
  []
[]

[GlobalParams]
  cycle_frequency = 0.1
[]
[Postprocessors]
  [a]
    type = ElementIntegralVariablePostprocessor
    variable = v
    execute_on = 'initial timestep_end'
  []

  [periodic]
    type = PeriodicTimeIntegratedPostprocessor
    value = a
    execute_on =  'initial timestep_end'
  []

  [multi_period]
    type = MultiPeriodAverager
    value = periodic
    number_of_periods = 2
  []
[]


[Executioner]
  type = Transient
  end_time = 41
  dt = 0.5
[]

[Outputs]
  exodus = false
  csv = true
[]
