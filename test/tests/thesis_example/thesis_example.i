[Mesh]
  type = GeneratedMesh
  nx = 50
  xmin = -.25
  xmax = .25
  ny = 50
  ymin = -.25
  ymax = .25
  dim = 2
[]

[Problem]
  type = FEProblem
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Executioner]
  type = Transient
  dt = .0001
  end_time = .005
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -ksp_type'
  petsc_options_value = 'lu preonly'
[]

[Outputs]
  perf_graph = true
  [out]
    type = Exodus
  []
[]

[Variables]
  [coffee_creamer]
  []
[]

[Kernels]
  [time]
    type = TimeDerivative
    variable = coffee_creamer
  []
  [diffusion]
    type = Diffusion
    variable = coffee_creamer
  []
[]

[ICs]
  [func_ic]
    type = FunctionIC
    variable = coffee_creamer
    function = gauss
  []
[]

[Functions]
  [gauss]
    type = ParsedFunction
    value = 'exp(-x^2 / 0.2^2) * exp(-y^2 / 0.2^2)'
  []
[]
