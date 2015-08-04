[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 1
  xmin = 0
  xmax = 1
[]

[Problem]
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE
[]

[Executioner]
  type = Transient
  dt = 0.01
 end_time = 0.5
 solve_type = NEWTON
 scheme = 'crank-nicolson'
 petsc_options_iname = '-ksp_converged_reason -snes_converged_reason -snes_stol -snes_type'
 petsc_options_value = 'true true 0 test'
[]

[Outputs]
  exodus = true
  print_perf_log = true
  print_linear_residuals = true
  output_initial = true
[]

[Debug]
  show_var_residual_norms = true
[]

[Kernels]
  [./time_deriv]
    type = TimeDerivative
    variable = u
  [../]
  [./transport]
    type = Diffusion
    variable = u
  [../]
[]

[Variables]
  [./u]
  [../]
[]

[BCs]
  [./u_left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 1
  [../]
[]

[ICs]
  [./u_begin]
    type = ConstantIC
    variable = u
    value = 0
  [../]
[]
