[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
  xmax = 1.0
[]

[Variables]
  [./electrons]
  [../]
  [./potential]
  [../]
[]

[/AuxVariables]
  active = 'e_x diffusive_flux advective_flux'
  [./e_x]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./diffusive_flux]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./advective_flux]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Materials]
  [./water]
    block = 0
    type = Water
  [../]
[]

[Kernels]
  active = 'electron_diffusion electrons_time_deriv potential_diffusion electron_advection'
  [./potential_diffusion]
    type = Diffusion
    variable = potential
  [../]
  [./electrons_time_deriv]
    type = TimeDerivative
    variable = electrons
  [../]
  [./electron_advection]
    type = EFieldAdvection
    variable = electrons
    potential = potential
    mobility = munegunity
  [../]
  [./electron_diffusion]
    type = CoeffDiffusion
    variable = electrons
    diffusivity = Dunity
  [../]
[]

[AuxKernels]
#  active = ''
  [./e_x_kernel]
    type = Ex
    variable = e_x
    potential = potential
  [../]
  [./diffusive_flux_kernel]
    type = DiffusiveFlux
    variable = diffusive_flux
    electron_density = electrons
    diffusivity = Dunity
  [../]
  [./advective_flux_kernel]
    type = AdvectiveFlux
    variable = advective_flux
    potential = potential
    electron_density = electrons
    mobility = munegunity
  [../]
[]

[BCs]
  active = 'electrons_flux_left electrons_dirichlet_right potential_left potential_right'
  [./potential_left]
    type = EFieldBC
    variable = potential
    boundary = left
    x_boundary_e_field = -78.8
  [../]
  [./potential_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0.0
  [../]
  [./electrons_flux_left]
    type = SimpleNetFluxBC
    variable = electrons
    boundary = left
    x_boundary_species_current = 1.0
#    species_charge = zem
  [../]
  [./electrons_dirichlet_left]
    type = DirichletBC
    variable = electrons
    boundary = left
    value = 1.0
  [../]
  [./electrons_dirichlet_right]
    type = DirichletBC
    variable = electrons
    boundary = right
    value = 0.0
  [../]
[]

[Problem]
  type = FEProblem
[]

[Executioner]
  type = Transient
  dt = 0.1
  num_steps = 10
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
#  trans_ss_check = true
#  ss_check_tol = 1e-8
  nl_rel_tol = 1e-2
  l_tol = 1e-1
#  nl_abs_tol = 1e-3
  l_max_its = 9
  nl_max_its = 3
[]
  
[Debug]
  show_var_residual_norms = true
[]

[Outputs]
  output_initial = true # Output initial condiiton
  exodus = true # Output Exodus format
  print_perf_log = true # Show performance log information on screen
  print_linear_residuals = true # Display linear residuals on screen
[]
