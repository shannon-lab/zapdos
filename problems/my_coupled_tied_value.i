[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
  # ny = 10
  xmax = 2
  # ymax = 1
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
    family = LAGRANGE
    block = '0'
    # scaling = .1
  [../]


  [./v]
    order = FIRST
    family = LAGRANGE
    block = '1'
    # scaling = 1
  [../]

  # [./w]
  #   block = '0'
  # [../]
  # [./p]
  #   block = '1'
  # [../]
[]

[Kernels]
  [./diff_u]
    type = CoeffParamDiffusion
    variable = u
    D = 4
    block = 0
  [../]
  [./diff_v]
    type = CoeffParamDiffusion
    variable = v
    D = 2
    block = 1
  [../]
  # [./diff_w]
  #   type = Diffusion
  #   variable = w
  #   block = '0'
  # [../]
  # [./diff_p]
  #   type = Diffusion
  #   variable = p
  #   block = '1'
  # [../]
[]

[DGKernels]
  [./dg_interface]
    type = DGDiffusionInterface
    variable = u
    neighbor_var = v
    boundary = master0_interface
    D = 4
    D_neighbor = 2
  [../]
  # [./dg_penalty]
  #   type = DGPenaltyTiedValue
  #   variable = u
  #   neighbor_var = v
  #   boundary = master0_interface
  #   scale_factor = 1
  # [../]
  # [./em_dg_advection_interface]
  #   type = DGAdvectionInterface
  #   variable = u
  #   neighbor_var = v
  #   boundary = master0_interface
  #   potential = w
  #   potential_neighbor = p
  # [../]
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

[Materials]
  [./jac]
    block = '0 1'
    type = JacMat
  [../]
[]

# [ICs]
#   # [./u]
#   #   type = ConstantIC
#   #   variable = u
#   #   value = 1
#   # [../]
#   # [./v]
#   #   type = ConstantIC
#   #   variable = v
#   #   value = 1
#   # [../]
#   # [./u]
#   #   type = RandomIC
#   #   variable = u
#   #   block = 0
#   # [../]
#   # [./v]
#   #   type = RandomIC
#   #   variable = v
#   #   block = 1
#   # [../]
# []


[Preconditioning]
  [./fdp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  # solve_type = PJFNK
  # petsc_options = '-snes_converged_reason -pc_svd_monitor -snes_linesearch_monitor -ksp_view_mat -pc_svd_monitor -ksp_view_solution -snes_monitor_solution_update'
  # petsc_options_iname = '-pc_type -ksp_view_solution'
  # petsc_options_value = 'svd ascii:solution_unscaled.txt:ascii_matlab:append'
  # petsc_options = '-snes_converged_reason  -pc_svd_monitor -snes_linesearch_monitor -options_left -snes_test_display'
  # petsc_options_iname = '-pc_type -snes_type' #  -ksp_view_mat
  # petsc_options_value = 'svd test' #  ascii:sans_dg_kernels.txt
  # line_search = cp
  #  petsc_options_iname = '-pc_type -ksp_type'
  # petsc_options_value = 'lu preonly'
[]

[Outputs]
  exodus = true
  print_linear_residuals = true
[]

[Debug]
  show_var_residual_norms = true
[]