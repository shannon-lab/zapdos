[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 100
  ny = 1
  xmax = 1
  ymax = 1
[]

[MeshModifiers]
  [./subdomain1]
    type = SubdomainBoundingBox
    bottom_left = '0 0 0'
    block_id = 1
    top_right = '0.5 1.0 0'
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
    family = LAGRANGE
    block = '1'
  [../]


  [./v]
    order = FIRST
    family = LAGRANGE
    block = '0'
  [../]

[]

[Kernels]
  [./diff_u]
    type = CoeffParamDiffusion
    variable = u
    D = 1
    block = 1
  [../]
  [./diff_v]
    type = CoeffParamDiffusion
    variable = v
    D = 3
    block = 0
  [../]
[]

[DGKernels]
  [./dg_interface]
    type = DGDiffusionInterface
    variable = u
    neighbor_var = v
    boundary = master1_interface
    D = 1
    D_neighbor = 3
  [../]
[]

# u is block 1, v is block 0
# At the interface, u has a lower element ID (because it's on the LHS of the domain) than v

# # For reasons unknown to me, this block currently produces a seg fault. It used to work.
# # I don't know what changed.
# [Constraints]
#   [./value]
#     type = CoupledTiedValueConstraint
#     variable = v
#     slave = master0_interface
#     master = master1_interface
#     master_variable = u
#   [../]
# []

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = 'left'
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = v
    boundary = 'right'
    value = 1
  [../]
  # Appears that I can achieve the same functionality as a constraint with this boundary condition
  [./middle]
    type = MatchedValueBC
    variable = v
    boundary = 'master0_interface'
    v = u
  [../]
[]



[Executioner]
  type = Steady
  # nl_rel_tol = 1e-12
  # l_tol = 1e-12
[]

[Outputs]
  exodus = true
[]
