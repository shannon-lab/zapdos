[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 3
  xmax = 1
[]


[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
  [./v]
  [../]
[]

[Kernels]
  [./test_u]
    type = InterpCoeffDiffusion
    variable = u
    v = v
  [../]
  [./diff_v]
    type = Diffusion
    variable = v
  [../]
[]

# [BCs]
#   [./left]
#     type = DirichletBC
#     variable = u
#     boundary = 'left'
#     value = 1
#   [../]
#   [./right]
#     type = DirichletBC
#     variable = u
#     boundary = 'right'
#     value = 0
#   [../]
#   [./left_v]
#     type = DirichletBC
#     variable = v
#     boundary = 'left'
#     value = 0
#   [../]
#   [./right_v]
#     type = DirichletBC
#     variable = v
#     boundary = 'right'
#     value = 1
#   [../]
# []

[ICs]
  [./u_ic]
    type = RandomIC
    variable = u
  [../]
  [./v_ic]
    type = RandomIC
    variable = v
  [../]
[]

[Materials]
  [./jac]
    block = '0'
    type = JacMat
    v = v
  [../]
[]

[Preconditioning]
  [./fdp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  # type = Transient
  # dt = 0.1
  # end_time = 1
  type = Steady
  solve_type = NEWTON
  petsc_options = '-snes_converged_reason  -pc_svd_monitor -snes_linesearch_monitor -options_left -snes_test_display'
  petsc_options_iname = '-snes_type'
  petsc_options_value = 'test'
[]

[Outputs]
  exodus = true
  print_linear_residuals = false
[]

[Debug]
  show_var_residual_norms = true
[]