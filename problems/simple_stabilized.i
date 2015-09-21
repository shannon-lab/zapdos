[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
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
 solve_type = PJFNK
 scheme = 'crank-nicolson'
 petsc_options_iname = '-petsc_type -petsc_hypre_type -ksp_converged_reason -snes_converged_reason -snes_stol'
 petsc_options_value = 'hypre boomeramg true true 0'
[]

[Outputs]
  exodus = true
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
    type = AdvectionDiffusionKernel
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
