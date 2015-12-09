[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 2
  xmax = 1
[]


[Variables]
  [./u]
    order = FIRST
    family = MONOMIAL
  [../]
  [./v]
  [../]
[]

[Kernels]
  [./test_u]
    type = Diffusion
    variable = u
  [../]
  [./dummy_v]
    type = Diffusion
    variable = v
  [../]
[]

[DGKernels]
  [./dg_advection]
    type = DGEFieldAdvection
    variable = u
    potential = v
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