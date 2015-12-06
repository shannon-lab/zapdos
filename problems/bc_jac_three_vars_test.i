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
  [./test_u]
    type = Diffusion
    variable = u
  [../]
  [./v]
    type = Diffusion
    variable = v
  [../]
  [./w]
    type = Diffusion
    variable = w
  [../]
[]

# [UserObjects]
#   [./data_provider]
#     type = ProvideMobility
#     # electrode_area = 3.14e-6 # Formerly 3.14e-6
#     electrode_area = 1.1 # Formerly 3.14e-6
#     ballast_resist = 1.1
#     e = 1.1
#     # ballast_resist = 1e6
#   [../]
# []

[BCs]
  [./em_left]
    type = DCElectronBC
    variable = u
    boundary = 'left right'
    potential = w
    ip = v
  [../]
[]

# [Functions]
#   [./potential_bc_func]
#     type = ParsedFunction
#     value = '1.25*tanh(1e6*t)'
#     # value = 1.25e3
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