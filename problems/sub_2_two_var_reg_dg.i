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
  [./u]
    order = FIRST
    family = MONOMIAL
    block = 0
  [../]
  [./v]
    order = FIRST
    family = MONOMIAL
    block = 1
  [../]
[]

[Kernels]
  [./test_u]
    type = Diffusion
    variable = u
    block = 0
  [../]
  [./dummy_v]
    type = Diffusion
    variable = v
    block = 1
  [../]
[]

[DGKernels]
  [./dg_diffus_u]
    type = DGDiffusion
    variable = u
    sigma = 6
    epsilon = -1
    block = 0
  [../]
  [./dg_diffus_v]
    type = DGDiffusion
    variable = v
    sigma = 6
    epsilon = -1
    block = 1
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
    block = 0
  [../]
  [./v_ic]
    type = RandomIC
    variable = v
    block = 1
  [../]
[]

[Materials]
  [./jac]
    block = '0 1'
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