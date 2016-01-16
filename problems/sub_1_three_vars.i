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
[]

[Kernels]
  [./test_kernel]
    type = JouleHeating
    variable = u
    potential = v
    em = w
    potential_units = V
  [../]
  [./diff_v]
    type = Diffusion
    variable = v
  [../]
  [./diff_w]
    type = Diffusion
    variable = w
  [../]
[]

# [BCs]
#   [./both]
#     type = HagelaarAnodicBC
#     variable = u
#     boundary = 'left right'
#     potential = v
#     mean_en = w
#     r = 0.5
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
[]

[Materials]
  [./jac]
    block = '0'
    type = JacMat
    mean_en = u
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