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
    # order = FIRST
    # family = MONOMIAL
    block = 0
  [../]
  [./emliq]
    # order = FIRST
    # family = MONOMIAL
    block = 1
  [../]
  [./potential]
    # order = FIRST
    # family = MONOMIAL
    block = 0
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
  [./test_potential]
    type = Diffusion
    variable = potential
    block = 0
  [../]
  [./mean_en_diffus]
    type = Diffusion
    variable = mean_en
    block = 0
  [../]
[]

[DGKernels]
  [./interface_advection_em]
    type = InterfaceAdvection
    variable = emliq
    boundary = master1_interface
    mean_en_neighbor = mean_en
    potential_neighbor = potential
    neighbor_var = em
  [../]
[]

[BCs]
  [./left]
    type = NeumannBC
    variable = em
    boundary = 'left'
    value = 1
  [../]
  [./right]
    type = NeumannBC
    variable = emliq
    boundary = 'right'
    value = 1
  [../]
[]

[ICs]
  [./em_ic]
    type = RandomIC
    variable = em
    block = 0
  [../]
  # [./em_ic]
  #   type = ConstantIC
  #   variable = em
  #   block = 0
  #   value = 0
  # [../]
  [./emliq_ic]
    type = RandomIC
    variable = emliq
    block = 1
  [../]
  [./potential_ic]
    type = RandomIC
    variable = potential
    block = 0
  [../]
  [./mean_en_ic]
    type = RandomIC
    variable = mean_en
    block = 0
  [../]
  # [./mean_en_ic]
  #   type = ConstantIC
  #   variable = mean_en
  #   block = 0
  #   value = 2
  # [../]
[]

[Materials]
  [./jac_0]
    block = '0 1'
    type = JacMat
    mean_en = mean_en
    em = em
    emliq = emliq
  [../]
  # [./jac_1]
  #   block = '1'
  #   type = JacMat
  #   # mean_en = mean_en
  #   # em = em
  # [../]
  # [./jac_1]
  #   block = '1'
  #   type = JacMat
  # [../]
  # [./jac_bnd1]
  #   boundary = 'master1_interface'
  #   type = JacMat
  #   mean_en = mean_en
  #   em = em
  # [../]
  # [./jac_bnd0]
  #   boundary = 'master0_interface'
  #   type = JacMat
  #   mean_en = mean_en
  #   em = em
  # [../]
  # [./gas]
  #   block = '1'
  #   type = Gas
  #   potential_units = V
  #   interp_elastic_coeff = true
  #   interp_trans_coeffs = true
  # [../]
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