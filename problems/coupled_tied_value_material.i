[Mesh]
  type = GeneratedMesh
  dim = 2
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
  # [./interface]
  #   type = SideSetsBetweenSubdomains
  #   depends_on = subdomain1
  #   master_block = '0'
  #   paired_block = '1'
  #   new_boundary = 'master0_interface'
  # [../]
  # [./interface_again]
  #   type = SideSetsBetweenSubdomains
  #   depends_on = subdomain1
  #   master_block = '1'
  #   paired_block = '0'
  #   new_boundary = 'master1_interface'
  # [../]
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
    block = '1 0'
  [../]


  # [./v]
  #   order = FIRST
  #   family = LAGRANGE
  #   block = '0'
  # [../]

[]

[Kernels]
  [./diff_u]
    type = CoeffDiffusion
    variable = u
    block = '0 1'
  [../]
  # [./diff_u]
  #   type = CoeffParamDiffusion
  #   variable = u
  #   D = 1
  #   block = 1
  # [../]
  # [./diff_v]
  #   type = CoeffParamDiffusion
  #   variable = v
  #   D = 3
  #   block = 0
  # [../]
[]

# [DGKernels]
#   [./dg_interface]
#     type = DGDiffusionInterface
#     epsilon = 0
#     sigma = 0
#     variable = u
#     neighbor_var = v
#     boundary = master1_interface
#     D = 1
#     D_neighbor = 3
#   [../]
# []

# [Constraints]
#   [./value]
#     type = CoupledTiedValueConstraint
#     variable = u
#     slave = master1_interface
#     master = master0_interface
#     master_variable = v
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
    variable = u
    boundary = 'right'
    value = 1
  [../]
[]

[Materials]
  [./test]
    type = Test
    block = '0'
  [../]
  [./test2]
    type = Test2
    block = '1'
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
