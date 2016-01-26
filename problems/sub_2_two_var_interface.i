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
  [./em]
    block = 0
  [../]
  [./emliq]
    block = 1
  [../]
  [./mean_en]
    block = 0
  [../]
[]

[Kernels]
  [./test_em]
    type = Diffusion
    variable = em
    block = 0
  [../]
  [./dummy_emliq]
    type = Diffusion
    variable = emliq
    block = 1
  [../]
  [./mean_en_diffus]
    type = Diffusion
    variable = mean_en
    block = 0
  [../]
[]

[DGKernels]
  [./test_interface]
    type = InterfaceLogDiffusionElectrons
    variable = emliq
    boundary = master1_interface
    mean_en_neighbor = mean_en
    neighbor_var = em
  [../]
[]

# [BCs]
#   [./left]
#     type = NeumannBC
#     variable = em
#     boundary = 'left'
#     value = 1
#   [../]
#   [./right]
#     type = NeumannBC
#     variable = emliq
#     boundary = 'right'
#     value = 1
#   [../]
# []

[ICs]
  [./em_ic]
    type = RandomIC
    variable = em
    block = 0
  [../]
  [./emliq_ic]
    type = RandomIC
    variable = emliq
    block = 1
  [../]
  [./mean_en_ic]
    type = RandomIC
    variable = mean_en
    block = 0
  [../]
[]

[Materials]
  [./jac_0]
    block = '0 1'
    type = JacMat
    mean_en = mean_en
    em = em
    emliq = emliq
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
  petsc_options = '-snes_converged_reason  -pc_svd_monitor -snes_linesearch_monitor -options_left -snes_test_display'
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