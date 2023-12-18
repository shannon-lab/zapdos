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
    function = func
  []
[]

[Functions]
  [func]
    type = ParsedFunction
    symbol_names = 'mag'
    symbol_values = 'mag'
    expression = 'mag * x * (x-1)'
  []
[]

[Postprocessors]
  [a]
    type = ElementIntegralVariablePostprocessor
    variable = v
    execute_on = 'initial timestep_end'
  []

  [periodic_a]
    type = PeriodicTimeIntegratedPostprocessor
    value = a
    cycle_frequency = 0.1
    coefficient = 0.1
    execute_on = 'initial timestep_end'
  []

  [multi_period]
    type = MultiPeriodAverager
    value = periodic_a
    cycle_frequency = 0.1
    number_of_periods = 2
    execute_on = 'initial timestep_begin'
  []

  [mag]
    type = PeriodicAmplitudeRegulator
    value = multi_period
    cycle_frequency = 0.1
    initial_value = -4
    reference_value = 10
    start_cycle = 2
    cycles_between_modification = 2
    execute_on = 'initial timestep_end'
  []

[]

[Executioner]
  type = Transient
  end_time = 200
  dt = 0.5
[]

[Outputs]
  csv = true
[]
