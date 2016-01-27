[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 1
  xmax = 1
[]


[Variables]
  [./em]
    order = FIRST
    family = LAGRANGE
  [../]
  [./potential]
  [../]
  [./mean_en]
  [../]
[]

[Kernels]
  [./test_kernel]
    type = Diffusion
    variable = em
  [../]
  [./diff_potential]
    type = Diffusion
    variable = potential
  [../]
  [./diff_mean_en]
    type = Diffusion
    variable = mean_en
  [../]
[]

[BCs]
  [./both]
    type = GradMeanEnZeroBC
    variable = mean_en
    boundary = 'left right'
    potential = potential
    em = em
  [../]
[]

[ICs]
  [./em_ic]
    type = RandomIC
    variable = em
  [../]
  [./potential_ic]
    type = RandomIC
    variable = potential
  [../]
  [./mean_en_ic]
    type = RandomIC
    variable = mean_en
  [../]
[]

[Materials]
  [./jac]
    block = '0'
    type = JacMat
    mean_en = mean_en
    em = em
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
  # [./DOFMap]
  #   type = DOFMap
  # [../]
[]

[Debug]
  show_var_residual_norms = true
[]