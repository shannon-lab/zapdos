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
 solve_type = NEWTON
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor -ksp_monitor_true_residual -ksp_converged_reason -pc_svd_monitor'
  petsc_options_iname = '-pc_type'
  petsc_options_value = 'svd'
  dt = .1
  end_time = .3
[]

[Outputs]
  exodus = true
  print_linear_residuals = false
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
    scaling = 1e-1
  [../]
[]

[BCs]
  [./u_left]
    type = DirichletBC
    variable = u
    boundary = left
    value = 1
  [../]
  [./u_right]
    type = DirichletBC
    variable = u
    boundary = right
    value = 0
  [../]
[]

# [Materials]
#   [./dummy]
#     type = ArgonConstTD
#     block = 0
#     mean_en = u
#     interp_trans_coeffs = true
#   [../]
# []

[ICs]
  [./u_begin]
    type = ConstantIC
    variable = u
    value = 1000
  [../]
[]
