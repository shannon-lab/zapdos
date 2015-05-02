[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10240
#  ny = 50
  xmax = 1024
#  ymax = 16e-3 # Test chamber radius
#  uniform_refine = 1
[]

[Variables]
  active = 'electron_density potential ion_density'
  [./electron_density]
#    Adds a Linear Lagrange variable by default
#    scaling = 1e-14
  [../]
  [./ion_density]
#    scaling = 1e-7
  [../]
  [./potential]
#    scaling = 1e-6
#    initial_condition = 0
  [../]
[]

[AuxVariables]
  active = 'e_field_mag charge_density ion_src_term'
  [./h_size]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./e_field_mag]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./velocity_mag]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./charge_density]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./ion_src_term]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./alpha_times_h]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  active = 'e_field_mag_kernel charge_dens_kernel ion_src_kernel'
  [./e_field_mag_kernel]
    type = EFieldMag
    variable = e_field_mag
    potential = potential
    execute_on = timestep_end
    #component = x
  [../]
  [./velocity_mag_kernel]
    type = VelocityMag
    variable = velocity_mag
    potential = potential
    execute_on = timestep_end
  [../]
  [./charge_dens_kernel]
    type = ChargeDensity
    variable = charge_density
    electron_density = electron_density
    ion_density = ion_density
  [../]
  [./ion_src_kernel]
    type = IonSrcTerm
    variable = ion_src_term
    electron_density = electron_density
    potential = potential
  [../]
  [./alpha_h_kernel]
    type = AlphaTimesHSize
    variable = alpha_times_h
    potential = potential
  [../]
  [./h_kernel]
    type = HSize
    variable = h_size
  [../]
[]

[Materials]
  [./whole_domain]
    block = 0
    type = Air
    delta = 0.0
    potential = potential
  [../]
[]

[Functions]
  [./parsed_function]
    type = ParsedFunction
    value = '.01*exp(-pow(x-993,2))+1.0e-5'
  [../]
  [./linear_function]
    type = ParsedFunction
    value = 'x'
  [../]
  [./null_function]
    type = ParsedFunction
    value = '0.0'
  [../]
  [./unity_function]
    type = ParsedFunction
    value = '1.0'
  [../]
[]

[ICs]
  active = 'electron_density_ic potential_ic ion_density_ic'
  [./electron_density_ic]
    type = FunctionIC
    variable = 'electron_density'
    function = parsed_function
  [../]
  [./ion_density_ic]
    type = FunctionIC
    variable = 'ion_density'
    function = parsed_function
  [../]
  [./potential_ic]
    type = FunctionIC
    variable = 'potential'
    function = linear_function
  [../]
[]

[Kernels]
  active = 'electrons_time_deriv electron_convection electron_diffusion artificial_diff poisson_diffusion poisson_src electron_src ions_src ions_time_deriv'
  [./artificial_diff]
    type = ArtificialDiff
    variable = electron_density
#    potential = potential
  [../]
  [./poisson_diffusion]
    type = Diffusion
    variable = potential
  [../]
  [./poisson_src]
    type = PoissonSource
    variable = potential
    #permittivity = 8.85e-12
    ion_density = ion_density
    electron_density = electron_density
  [../]
  [./electrons_time_deriv]
    type = TimeDerivative
    variable = electron_density
  [../]
  [./electron_convection]
    type = ConstConvection
#    type = DivFreeConvection
    variable = electron_density
    some_variable = potential
  [../]
  [./electron_diffusion]
    type = ConstTimesDiffusion
    variable = electron_density
  [../]
  [./electron_src]
    type = IonizationSource
    variable = electron_density
    potential = potential
  [../]
  [./ions_time_deriv]
    type = TimeDerivative
    variable = ion_density
  [../]
  [./ions_src]
    type = CoupledIonizationSource
    variable = ion_density
    potential = potential
    electron_density = electron_density
    #ionization_coeff = 0.35e-6
  [../]
[]

[BCs] 
  active = 'anode cathode electrons_anode electrons_cathode'
  [./anode]
    type = DirichletBC # Simple u=value BC
    variable = potential
    boundary = right # Name of a sideset in the mesh
    value = 1024
  [../]
  [./cathode]
    type = DirichletBC
    variable = potential
    boundary = left
    value = 0
  [../]
  [./electrons_anode]
    type = DirichletBC
    variable = electron_density
    boundary = right
    value = 0
  [../]
  [./electrons_cathode]
    type = DirichletBC
    variable = electron_density
    value = 0
    boundary = left
  [../]
[]

[Problem]   
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE   
  # coord_type = XYZ # Cartesian   
[]   

#[Preconditioning]
#  [./SMP_jfnk_full]
#    type = SMP
#    full = true
#    solve_type = 'PJFNK'
#    # petsc_options_iname = '-pc_type'
#    # petsc_options_value = 'lu'
#  [../]
#[]

[Executioner]
  type = Transient
  dt = 0.1
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  end_time = 200
#  trans_ss_check = true
#  ss_check_tol = 1e-8
  nl_rel_tol = 1e-2
  l_tol = 1e-1
#  nl_abs_tol = 1e-3
  l_max_its = 9
  nl_max_its = 3
#  scheme = crank-nicolson
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
