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
[]

[Kernels]
  [./diff_u]
    type = Diffusion
    variable = u
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = 'left'
    value = 1
  [../]
  [./right]
    type = DirichletBC
    variable = u
    boundary = 'right'
    value = 0
  [../]
[]

[Preconditioning]
  [./fdp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  # petsc_options = '-snes_converged_reason -pc_svd_monitor -snes_linesearch_monitor -ksp_view_mat -pc_svd_monitor -ksp_view_solution -snes_monitor_solution_update'
  # petsc_options_iname = '-pc_type -ksp_view_solution'
  # petsc_options_value = 'svd ascii:solution_unscaled.txt:ascii_matlab:append'
  petsc_options = '-snes_converged_reason  -pc_svd_monitor -snes_linesearch_monitor -options_left -snes_test_display'
  # petsc_options_iname = '-pc_type -snes_type' #  -ksp_view_mat
  # petsc_options_value = 'svd test' #  ascii:sans_dg_kernels.txt
  # line_search = cp
[]

[Outputs]
  exodus = true
  print_linear_residuals = false
[]

[Debug]
  show_var_residual_norms = true
[]