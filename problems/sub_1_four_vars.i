[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 1
  xmax = 1
[]


[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
  [./v]
  [../]
  [./w]
  [../]
  [./p]
  [../]
[]

[Kernels]
  [./test_u]
    type = IonsFromIonization
    variable = u
    potential = v
    em = w
    mean_en = p
  [../]
  [./diff_v]
    type = Diffusion
    variable = v
  [../]
  [./diff_w]
    type = Diffusion
    variable = w
  [../]
  [./diff_p]
    type = Diffusion
    variable = p
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
  [./w_ic]
    type = RandomIC
    variable = w
  [../]
  [./p_ic]
    type = RandomIC
    variable = p
  [../]
  # [./u_ic]
  #   type = ConstantIC
  #   variable = u
  #   value = 0.5
  # [../]
  # [./v_ic]
  #   type = ConstantIC
  #   variable = v
  #   value = 0.5
  # [../]
  # # [./w_ic]
  # #   type = ConstantIC
  # #   variable = w
  # #   value = 0.5
  # # [../]
  # [./p_ic]
  #   type = ConstantIC
  #   variable = p
  #   value = 0.5
  # [../]
[]

[Materials]
  [./jac]
    block = '0'
    type = JacMat
    mean_en = p
    em = w
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