[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 40
  xmax = 2
[]

[Variables]
  [./concentration]
  [../]
[]

#[AuxVariables]
#  [./sigma]
#    order = CONSTANT
#    family = MONOMIAL
#  [../]
#  [./velocity_h]
#    order = CONSTANT
#    family = MONOMIAL
#  [../]
#  [./velocity]
#    order = CONSTANT
#    family = MONOMIAL
#  [../]
#[]

[Functions]
  [./velocity_function]
    type = ParsedVectorFunction
    value_x = '1.0'
  [../]
  [./parsed_function]
    type = ParsedFunction
    value = '10.0*exp(-pow(x-.3,2)/pow(.03,2))'
  [../]
[]

[ICs]
  active = 'null_ic'
  [./null_ic]
    type = ConstantIC
    variable = 'concentration'
    value = 0.0
  [../]
  [./concentration_ic]
    type = FunctionIC
    variable = 'concentration'
    function = parsed_function
  [../]
[]

[Kernels]
  active = 'advection time_derivative diffusion' # SUPG_convection SUPG_time_deriv
  [./SUPG_time_deriv]
    type = TimeDerivativeSUPG
    variable = concentration
    crosswind = true
  [../]
  [./advection]
    type = BovineConvection
    variable = concentration
  [../]
  [./time_derivative]
    type = TimeDerivative
    variable = concentration
  [../]
  [./diffusion]
    type = ConstTimesDiffusion
    variable = concentration
  [../]
  [./SUPG_convection]
    type = ArtificialDiff
    variable = concentration
    crosswind = true
  [../]
[]

#[AuxKernels]
#  [./sigma_aux_kernel]
#    type = Sigma
#    variable = sigma
#    some_var = concentration
#    execute_on = timestep_end
#  [../]
#  [./velocity_h_kernel]
#    type = VelocityH
#    variable = velocity_h
#    some_var = concentration
#    execute_on = timestep_end
#  [../]
#  [./velocity_kernel]
#    type = Velocity
#    variable = velocity
#    some_var = concentration
#    execute_on = timestep_end
#  [../]
#[]

[BCs] 
  active = 'left_wall right_wall'
  [./left_wall]
    type = DirichletBC # Simple u=value BC
    variable = concentration
    boundary = left
    value = 1
  [../]
  [./right_wall]
    type = NoDiffusiveFlux
    variable = concentration
    boundary = right
#    value = 0
  [../]
[]

[Materials]
  [./whole_domain]
    block = 0
    type = NoCouplingAir
    user_diffusivity = 1.0
    velocity_function = velocity_function
    consistent = true
    potential = potential
  [../]
[]

[Problem]   
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE   
  # coord_type = XYZ # Cartesian   
[]   

[Executioner]
  type = Transient
  dt = 0.05
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  end_time = 2
#  trans_ss_check = true
#  ss_check_tol = 1e-8
  nl_rel_tol = 1e-2
  l_tol = 1e-1
#  nl_abs_tol = 1e-3
  l_max_its = 9
  nl_max_its = 3
  scheme = crank-nicolson
#  [./TimeStepper]
#    type = IterationAdaptiveDT
#    linear_iteration_ratio = 5
#    cutback_factor = 0.4
#    dt = 5.0e-12
#    growth_factor = 1.2
#    optimal_iterations = 4
#  [../]
[]

# [Adaptivity]
#   marker = combo
#   max_h_level = 10
#   [./Indicators]
#     active = 'temp_jump_potential temp_jump_edens'
#     [./temp_jump_potential]
#       type = GradientJumpIndicator
#       variable = potential
#       scale_by_flux_faces = true
#     [../]
#     [./temp_jump_edens]
#       type = GradientJumpIndicator
#       variable = electron_density
#       scale_by_flux_faces = true
#     [../]
#     [./analytical]
#       type = AnalyticalIndicator
#       variable = ion_src_term
#       function = null_function
#     [../]
#     [./analytical_diff]
#       type = AnalyticalDiffIndicator
#       variable = alpha_times_h
#       function = unity_function
#     [../]
#   [../]
#   [./Markers]
#     active = 'error_frac_pot error_frac_edens combo'
#     [./error_frac_pot]
#       type = ErrorFractionMarker
#       coarsen = 0.1
#       indicator = temp_jump_potential
#       refine = 0.6
#     [../]
#     [./error_frac_edens]
#       type = ErrorFractionMarker
#       coarsen = 0.1
#       indicator = temp_jump_edens
#       refine = 0.6
#     [../]
#     [./combo]
#       type = ComboMarker
#       markers = 'error_frac_pot error_frac_edens'
#     [../]
#     [./error_tol]
#       type = ErrorToleranceMarker
#       indicator = analytical_diff
#       coarsen = 0
#       refine = 0
#     [../]
#   [../]
# []

[Debug]
  show_var_residual_norms = true
[]

[Outputs]
  output_initial = true # Output initial condiiton
  exodus = true # Output Exodus format
  print_perf_log = true # Show performance log information on screen
  print_linear_residuals = true # Display linear residuals on screen
[]
