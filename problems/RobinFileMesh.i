[Mesh]
  file = t1.unv
[]

[Variables]
  [./n_concentration]
    #Adds a Linear Lagrange variable by default
    initial_condition = 0 # Start at 0
  [../]
[]

[Kernels]
  # active = 'diff time_derivative'
  [./diff]
    type = ConstTimesDiffusion
    variable = n_concentration # Operate on the "n_concentration" variable from above
    diffusion_coeff = 3.16e-8
  [../]
  [./time_derivative]
    type = TimeDerivative
    variable = n_concentration
  [../]
  [./reaction_term]
    type = FirstOrderReaction
    variable = n_concentration
    reaction_coeff = 51.2
  [../]
[]

[BCs]
  [./inlet]
    type = DirichletBC # Simple u=value BC
    variable = n_concentration
    boundary = left # Name of a sideset in the mesh
    value = 2.05 # (uM) Inlet concentration
  [../]
  [./outlet]
    type = VacuumBC
    variable = n_concentration
    alpha = 0.001048 # 1/m 
    boundary = right
    # value = 0 # Outlet concentration
  [../]
[]

# [Materials]
#   [./hoof]
#     type = DiffusionConst
#     block = 0
#   [../]
# []

[Problem]
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE
  # coord_type = XYZ # Cartesian
[]

[Executioner]
  # active = 'Transient'
  type = Transient
  num_steps = 100
  dt = .01
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  trans_ss_check = true
  ss_check_tol = 1e-4
[]

# [Executioner]
#  type = Transient # Transient solver
#  dt = 7.91e-5
#  solve_type = PJFNK #Preconditioned Jacobian Free Newton Krylov
#  petsc_options_iname = '-pc_type -pc_hypre_type' #Matches with the values below
#  petsc_options_value = 'hypre boomeramg'
#  end_time = 0.5
#   nl_rel_tol = 1e-02
#   l_tol = 1e-02
#  [./TimeStepper]
#    type = IterationAdaptiveDT
#    linear_iteration_ratio = 5
#    cutback_factor = 0.5
#    dt = 7.91e-5
#    growth_factor = 2
#    optimal_iterations = 4
#  [../]
# []

# [Adaptivity]
#  marker = error_frac
#  max_h_level = 5
#  [./Indicators]
#    [./temp_jump]
#      type = GradientJumpIndicator
#      variable = n_concentration
#      scale_by_flux_faces = true
#    [../]
#  [../]
#  [./Markers]
#    [./error_frac]
#      type = ErrorFractionMarker
#      coarsen = 0.1
#      indicator = temp_jump
#      refine = 0.6
#    [../]
#  [../]
# []

[Outputs]
  output_initial = true # Output initial condiiton
  exodus = true # Output Exodus format
  print_perf_log = true # Show performance log information on screen
  print_linear_residuals = true # Display linear residuals on screen
[]
