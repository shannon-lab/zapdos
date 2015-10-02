[Mesh]
  file = conforming_two_var_meshing_only_in.e

  [./MortarInterfaces]
    [./middle]
      master = 'right_sideset'
      slave = 'left_sideset'
      subdomain = 1000
    [../]
  [../]
[]

# [MeshModifiers]
#   [./middle_nodeset]
#     type = AddExtraNodeset
#     new_boundary = 'middle_nodes'
#     coord = '0.5 0 0.5 0.2 0.5 0.4 0.5 0.6 0.5 0.8 0.5 1.0 0.5 1.2 0.5 1.4 0.5 1.6 0.5 1.8 0.5 2.0'
#     # coord = '0.5'
#   [../]
#   [./subdomain1]
#     type = SubdomainBoundingBox
#     bottom_left = '0 0 0'
#     block_id = 1
#     top_right = '0.5 2.0 0'
#   [../]
#   [./right_sideset]
#     type = SideSetsBetweenSubdomains
#     master_block = '0'
#     paired_block = '1'
#     new_boundary = 'right_sideset'
#   [../]
#   [./left_sideset]
#     type = SideSetsBetweenSubdomains
#     master_block = '1'
#     paired_block = '0'
#     new_boundary = 'left_sideset'
#   [../]
# []

[Functions]
  [./exact_sln]
    type = ParsedFunction
    value = y
  [../]
  [./ffn]
    type = ParsedFunction
    value = 0
  [../]
[]

[Variables]
  [./u]
    order = FIRST
    family = LAGRANGE
    block = '0 1'
  [../]

  [./lm_u]
    order = FIRST
    family = LAGRANGE
    block = middle
  [../]

  [./v]
    order = FIRST
    family = LAGRANGE
    block = '0 1'
  [../]

  [./lm_v]
    order = FIRST
    family = LAGRANGE
    block = middle
  [../]

[]

[Kernels]
  [./diff_u]
    type = Diffusion
    variable = u
  [../]
  [./ffn]
    type = UserForcingFunction
    variable = u
    function = ffn
  [../]
  [./diff_v]
    type = Diffusion
    variable = v
  [../]
  [./coupled_u]
    type = CoupledForce
    variable = v
    v = u
  [../]
[]

[Constraints]
  [./ced_u]
    type = EqualValueConstraint
    variable = lm_u
    interface = middle
    master_variable = u
  [../]
  [./ced_v]
    type = EqualValueConstraint
    variable = lm_v
    interface = middle
    master_variable = v
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = u
    boundary = 'left right top bottom'
    function = exact_sln
  [../]
  [./allv]
    type = DirichletBC
    variable = v
    boundary = 'left right top bottom'
    value = 0
  [../]
[]

[Postprocessors]
  [./l2_error]
    type = ElementL2Error
    variable = u
    function = exact_sln
    block = '0 1'
    execute_on = 'initial timestep_end'
  [../]
  [./l2_v]
    type = ElementL2Norm
    variable = v
    block = '0 1'
    execute_on = 'initial timestep_end'
  [../]
[]

[Preconditioning]
  [./fmp]
    type = SMP
    full = true
    solve_type = 'NEWTON'
  [../]
[]

[Executioner]
  type = Steady
  nl_rel_tol = 1e-12
  l_tol = 1e-12
[]

[Outputs]
  exodus = true
[]
