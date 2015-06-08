[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 1000
  xmax = 1.95e-6
#  uniform_refine = 3
#  xmax = 1.0
[]

[Preconditioning]
  [./SMP]
    type = FDP
    full = true
 #Preconditioned JFNK (default)
    solve_type = 'PJFNK'
    petsc_options_iname = '-pc_type -mat_fd_coloring_err -mat_fd_type'
    petsc_options_value = 'lu       1e-6                 ds'
  [../]
[]

[Executioner]
  type = Transient
#  dt = 2.1e-13
  end_time = 2.1e-10
#  solve_type = PJFNK
#  petsc_options_iname = '-pc_type -pc_hypre_type'
#  petsc_options_value = 'hypre boomeramg'
#  trans_ss_check = true
#  ss_check_tol = 1e-7
  nl_rel_tol = 1e-6
#  l_tol = 1e-1
##  nl_abs_tol = 1e-3
  l_max_its = 20
  nl_max_its = 21
  dtmin = 2.1e-16
  line_search = none
  [./TimeStepper]
    type = IterationAdaptiveDT
    linear_iteration_ratio = 5
    cutback_factor = 0.5
    dt = 2.1e-13
    growth_factor = 2.0
    optimal_iterations = 4
  [../]
[]

[Outputs]
#  exodus = true
  print_perf_log = true
  print_linear_residuals = true
  output_initial = true
#  interval = 100
  [./out]
    type = Exodus
    output_material_properties = true
    show_material_properties = 'advection_velocity_em advection_velocity_ip EField gamma_em gamma_ip'
  [../]
[]

[Debug]
  show_var_residual_norms = true
[]

[LotsOfCoeffDiffusion]
  variables = 'em ip'
[]

#[LotsOfVariables]
#  variables = 'em ip potential'
#[]

[LotsOfTimeDerivatives]
  variables = 'em ip'
[]

[LotsOfSources]
  variables = 'em ip potential'
[]

[LotsOfEFieldAdvection]
  variables = 'em ip'
  potential = 'potential'
[]

[Kernels]
  [./potential_diffusion]
    type = Diffusion
    variable = potential
  [../]
[]

[Variables]
  [./potential]
    scaling = 1e9
 [../]
  [./em]
    scaling = 1e23
  [../]
  [./ip]
    scaling = 1e23
  [../]
[]

[Materials]
  [./air]
    block = 0
    type = Air
    em = em
    ip = ip
    potential = potential
#    potential_mult = 35
 [../]
[]

[BCs]
  [./potential_dirichlet_left]
    type = DirichletBC
    variable = potential
    boundary = left
    value = 0.0
  [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 390
  [../]
  [./ip_physical_left]
    type = PhysicalIonBC
    variable = ip
    boundary = left
  [../]
  [./ip_physical_right]
    type = PhysicalIonBC
    variable = ip
    boundary = right
  [../]
  [./em_physical_left]
    type = PhysicalElectronBC
    variable = em
    boundary = left
    ip = ip
    se_coeff = 1.0
  [../]
  [./em_physical_right]
    type = PhysicalElectronBC
    variable = em
    boundary = right
    ip = ip
    se_coeff = 1.0
  [../]
[]

[ICs]
  [./em_ic]
    type = FunctionIC
    variable = em
    function = density_ic_parsed_function
  [../]
  [./ip_ic]
    type = FunctionIC
    variable = ip
    function = density_ic_parsed_function
  [../]
  [./potential_ic]
    type = FunctionIC
    variable = potential
    function = potential_parsed_function
  [../]
[]

[Functions]
  [./density_ic_parsed_function]
    type = ParsedFunction
#    value = '7.81e-6*exp(-pow(x-(7.36e-5),2)/pow(2.30e-6,2))'
    value = '1e-10'
  [../]
  [./potential_parsed_function]
    type = ParsedFunction
    value = '2.0e8*x'
[]

#[Adaptivity]
#  marker = combo
#  max_h_level = 3
#  [./Indicators]
#    active = 'temp_jump_potential temp_jump_edens'
#    [./temp_jump_potential]
#      type = GradientJumpIndicator
#      variable = potential
#      scale_by_flux_faces = true
#    [../]
#    [./temp_jump_edens]
#      type = GradientJumpIndicator
#      variable = em
#      scale_by_flux_faces = true
#    [../]
#    [./analytical]
#      type = AnalyticalIndicator
#      variable = ion_src_term
#      function = null_function
#    [../]
#    [./analytical_diff]
#      type = AnalyticalDiffIndicator
#      variable = alpha_times_h
#      function = unity_function
#    [../]
#  [../]
#  [./Markers]
#    active = 'error_frac_pot error_frac_edens combo'
#    [./error_frac_pot]
#      type = ErrorFractionMarker
#      coarsen = 0.1
#      indicator = temp_jump_potential
#      refine = 0.6
#    [../]
#    [./error_frac_edens]
#      type = ErrorFractionMarker
#      coarsen = 0.1
#      indicator = temp_jump_edens
#      refine = 0.6
#    [../]
#    [./combo]
#      type = ComboMarker
#      markers = 'error_frac_pot error_frac_edens'
#    [../]
#    [./error_tol]
#      type = ErrorToleranceMarker
#      indicator = analytical_diff
#      coarsen = 0
#      refine = 0
#    [../]
#  [../]
#[]
