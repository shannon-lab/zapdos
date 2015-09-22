[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
  xmax = 1
  ymax = 1
[]

[MeshModifiers]
  [./middle_node]
    type = AddExtraNodeset
    new_boundary = 'middle_nodes'
    coord = '0.5'
  [../]
  [./subdomain1]
    type = SubdomainBoundingBox
    bottom_left = '0.5 0 0'
    block_id = 1
    top_right = '1.0 1.0 0'
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
  [./left]
    type = DirichletBC
    variable = u
    boundary = 'left'
    value = 1
  [../]

  [./right]
    type = DirichletBC
    variable = v
    boundary = 'right'
    value = 0
  [../]

  [./middle]
    type = MatchedValueBC
    variable = v
    v = u
    boundary = 'middle_nodes'
  [../]
  [./middle2]
    type = CoupledIntegratedBC
    variable = u
    coupled_var = v
    boundary = 'middle_nodes'
  [../]
[]

[Executioner]
  type = Steady

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'
  # petsc_options_iname = '-snes_type'
  # petsc_options_value = 'test'
[]

[Outputs]
  [./out]
    type = Exodus
  [../]
[]
