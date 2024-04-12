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
    expression = '-4 * x * (x-1)'
  []
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
    cycle_frequency = 0.1
    execute_on = 'initial timestep_end'
  []
[]

[Executioner]
  type = Transient
  end_time = 11
  dt = 0.5
[]

[Outputs]
  exodus = false
  csv = true
[]
