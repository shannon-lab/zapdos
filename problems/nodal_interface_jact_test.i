[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 2
  xmax = 2
[]

[MeshModifiers]
  [./subdomain1]
    type = SubdomainBoundingBox
    bottom_left = '1.0 0 0'
    block_id = 1
    top_right = '2.0 1.0 0'
  [../]
  [./interface]
    type = SideSetsBetweenSubdomains
    depends_on = subdomain1
    master_block = '0'
    paired_block = '1'
    new_boundary = 'master0_interface'
  [../]
  [./interface_again]
    type = SideSetsBetweenSubdomains
    depends_on = subdomain1
    master_block = '1'
    paired_block = '0'
    new_boundary = 'master1_interface'
  [../]
[]


[Variables]
  [./u1]
    order = FIRST
    family = LAGRANGE
  [../]
  [./u2]
  [../]
  # [./w]
  # [../]
[]

[Kernels]
  [./test_u]
    type = Diffusion
    variable = u1
  [../]
  [./v]
    type = Diffusion
    variable = u2
  [../]
  # [./w]
  #   type = Diffusion
  #   variable = w
  # [../]
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
    type = MatchedValueLogBC
    variable = u2
    boundary = 'master0_interface'
    v  = u1
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
    variable = u1
  [../]
  [./v_ic]
    type = RandomIC
    variable = u2
  [../]
  # [./w_ic]
  #   type = RandomIC
  #   variable = w
  # [../]
[]

# [Materials]
#   [./jac]
#     block = '0'
#     type = JacMat
#   [../]
# []

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