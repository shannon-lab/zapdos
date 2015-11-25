[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 100
  # ny = 10
  xmax = 1
  # ymax = 1
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
    scaling = .1
  [../]


  [./v]
    order = FIRST
    family = LAGRANGE
    block = '0'
    scaling = 1
  [../]

  # [./w]
  #   block = '0 1'
  # [../]
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
  # [./diff_w]
  #   type = Diffusion
  #   variable = w
  #   block = '0 1'
  # [../]
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
# # I don't know what changed. Perhaps because I'm now based on devel instead of master
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
    value = 1
  [../]
  [./right]
    type = DirichletBC
    variable = v
    boundary = 'right'
    value = 0
  [../]
#  Appears that I can achieve the same functionality as a constraint with this boundary condition
  [./middle]
    type = MatchedValueBC
    variable = v
    boundary = 'master0_interface'
    v = u
  [../]
  # [./middle]
  #   type = MatchedValueBC
  #   variable = v
  #   boundary = 'master0_interface'
  #   v = u
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
  petsc_options = '-snes_converged_reason -pc_svd_monitor'
  # petsc_options = '-pc_svd_monitor -snes_converged_reason -snes_linesearch_monitor -ksp_diagonal_scale -ksp_diagonal_scale_fix'
  petsc_options_iname = '-pc_type'
  petsc_options_value = 'svd'
  # petsc_options_iname = '-pc_type'
  # petsc_options_value = 'ilu'
  # petsc_options_iname = '-pc_type -ksp_type'
  # petsc_options_value = 'lu ksp'
  # line_search = none
[]

[Outputs]
  exodus = true
  print_linear_residuals = false
[]

[Debug]
  show_var_residual_norms = true
[]
