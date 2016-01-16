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
[]

[Kernels]
  [./test_u]
    type = CoeffDiffusionEnergy
    variable = u
    em = v
  [../]
  [./diff_v]
    type = Diffusion
    variable = v
  [../]
[]

# [BCs]
#   [./left]
#     type = HagelaarIonBC
#     variable = u
#     boundary = 'left'
#     potential = v
#     r = 0
#   [../]
#   [./right]
#     type = HagelaarIonBC
#     variable = u
#     boundary = 'right'
#     potential = v
#     r = 0
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
    em = v
    mean_en = u
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
[]

[Debug]
  show_var_residual_norms = true
[]