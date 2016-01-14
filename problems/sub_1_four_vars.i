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
    type = Diffusion
    variable = u
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

[BCs]
  [./both]
    type = HagelaarElectronBC
    variable = u
    boundary = 'left right'
    potential = v
    mean_en = w
    ip = p
    r = 0.5
  [../]
[]

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
  [./jac_block]
    block = '0'
    type = JacMat
  [../]
  [./jac_boundary]
    boundary = 'left right'
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
  type = Steady
  solve_type = NEWTON
  petsc_options = '-options_left -snes_test_display'
  petsc_options_iname = '-snes_type'
  petsc_options_value = 'test'
[]

[Outputs]
  exodus = true
  print_linear_residuals = false
  [./DOFMap]
    type = DOFMap
  [../]
[]

[Debug]
  show_var_residual_norms = true
[]