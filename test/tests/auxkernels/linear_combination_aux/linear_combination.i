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
  [v+]
  []

  [lin]
  []
[]

[AuxKernels]
  [func_kernel]
    type = FunctionAux
    variable = v+
    function = ic
  []

  [linear_combo]
    type = LinearCombinationAuxKernel
    variable = lin
    coupled_variables = 'v+ v+'
    weights = '1 3'
    bias = 1
  []
[]

[Functions]
  [ic]
    type = ParsedFunction
    expression = '-4 * x * (x-1)'
  []
[]

[Executioner]
  type = Steady
[]

[Outputs]
  exodus = true
[]
