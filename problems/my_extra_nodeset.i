[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  xmax = 1
  ymax = 1
[]

[MeshModifiers]
  [./middle_nodeset]
    type = AddExtraNodeset
    new_boundary = 'middle_nodes'
    coord = '0.5 0 0.5 0.1 0.5 0.2 0.5 0.3 0.5 0.4 0.5 0.5 0.5 0.6 0.5 0.7 0.5 0.8 0.5 0.9 0.5 1.0'
    # coord = '0.5'
  [../]
  [./subdomain1]
    type = SubdomainBoundingBox
    bottom_left = '0 0 0'
    block_id = 1
    top_right = '0.5 1.0 0'
  [../]
  [./middle_sideset]
    type = SideSetsBetweenSubdomains
    master_block = '0'
    paired_block = '1'
    new_boundary = 'in_between'
  [../]
[]

[Variables]
  [./u]
    block = '0'
  [../]
  [./v]
    block = '1'
  [../]
[]

[Kernels]
  [./diff_u]
    type = Diffusion
    variable = u
    # block = '0'
  [../]
  [./diff_v]
    type = Diffusion
    variable = v
    # block = '1'
  [../]
[]

[BCs]
  [./right]
    type = DirichletBC
    variable = u
    boundary = 'right'
    value = 1
  [../]

  [./left]
    type = DirichletBC
    variable = v
    boundary = 'left'
    value = 0
  [../]

  [./middle]
    type = MultipliedValueBC
    variable = v
    v = u
    mult = 1.0
    boundary = 'middle_nodes'
  [../]
  [./middle2]
    type = NeumannBC
    variable = u
    value = -1.0
    boundary = 'in_between'
  [../]
  # [./middle2]
  #   type = CoupledIntegratedBC
  #   variable = u
  #   coupled_var = v
  #   boundary = 'in_between'
  # [../]
[]

[Executioner]
  type = Steady

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'
[]

[Outputs]
  [./out]
    type = Exodus
  [../]
[]
