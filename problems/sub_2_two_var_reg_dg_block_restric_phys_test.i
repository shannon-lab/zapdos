[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 100
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
  # [./u]
  #   order = FIRST
  #   family = LAGRANGE
  # [../]
  [./u]
    order = FIRST
    family = MONOMIAL
    block = 0
  [../]
  [./v]
    order = FIRST
    family = MONOMIAL
    block = 1
  [../]
[]

[Kernels]
  [./time]
    type = TimeDerivative
    variable = u
    block = 0
  [../]
  [./test_u]
    type = Diffusion
    variable = u
    block = 0
  [../]
  [./adv_u]
    type = GAdvection
    variable = u
    vx = 1
    vy = 0
    vz = 0
    block = 0
  [../]
  [./time_v]
    type = TimeDerivative
    variable = v
    block = 1
  [../]
  [./test_v]
    type = Diffusion
    variable = v
    block = 1
  [../]
  [./adv_v]
    type = GAdvection
    variable = v
    vx = 1
    vy = 0
    vz = 0
    block = 1
  [../]
[]

[DGKernels]
  [./dg_advection_u]
    type = DGAdvection
    variable = u
    vx = 1
    vy = 0
    vz = 0
    block = 0
  [../]
  [./dg_diffusion_u]
    type = DGDiffusion
    variable = u
    sigma = 0
    epsilon = -1
    block = 0
  [../]
  [./dg_advection_v]
    type = DGAdvection
    variable = v
    vx = 1
    vy = 0
    vz = 0
    block = 1
  [../]
  [./dg_diffusion_v]
    type = DGDiffusion
    variable = v
    sigma = 0
    epsilon = -1
    block = 1
  [../]
[]

[BCs]
  [./left]
    type = InflowBC
    variable = u
    boundary = 'left'
    inlet_conc = 2
    vx = 1
  [../]
  [./master0_inteface]
    type = OutflowBC
    variable = u
    boundary = 'master0_interface'
    vx = 1
  [../]
 [./master1_interface]
   type = InflowBC
   variable = v
   boundary = 'master1_interface'
   inlet_conc = 4
   vx = 1
 [../]
  [./right]
    type = OutflowBC
    variable = v
    boundary = 'right'
    vx = 1
  [../]
[]

[ICs]
  [./u_ic]
    type = ConstantIC
    variable = u
    value = 0
  [../]
  [./v_ic]
    type = ConstantIC
    variable = v
    value = 0
  [../]
[]

[Functions]
  [./init_func]
    type = ParsedFunction
    value = '1*(1-x)'
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
  type = Transient
  dt = 0.1
  end_time = 1
  dtmin = 0.01
  nl_abs_tol = 1e-12
  # scheme = crank-nicolson
  # type = Steady
  solve_type = NEWTON
  petsc_options = '-snes_converged_reason  -pc_svd_monitor -snes_linesearch_monitor -options_left -snes_test_display'
  petsc_options_iname = '-pc_type -ksp_type'
  petsc_options_value = 'lu preonly'
  # petsc_options_iname = '-snes_type'
  # petsc_options_value = 'test'
[]

[Outputs]
  exodus = true
  print_linear_residuals = false
[]

[Debug]
  show_var_residual_norms = true
[]