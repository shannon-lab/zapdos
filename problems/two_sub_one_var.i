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
    order = FIRST
    family = LAGRANGE
  [../]

[]

[Kernels]
  [./diff_u1]
    type = Diffusion
    variable = u1
  [../]
  [./diff_u2]
    type = Diffusion
    variable = u2
  [../]
[]

[DGKernels]
  [./em_dg_diffusion_interface]
    type = DGMatDiffusionInt
    variable = u1
    neighbor_var = u2
    boundary = master0_interface
  [../]
[]

[ICs]
  [./u1_ic]
    type = RandomIC
    variable = u1
  [../]
  [./u2_ic]
    type = RandomIC
    variable = u2
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
  type = Steady
  solve_type = NEWTON
  petsc_options = '-snes_test_display'
  petsc_options_iname = '-snes_type'
  petsc_options_value = 'test'
[]