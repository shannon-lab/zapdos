[Mesh]
  type = GeneratedMesh # Can generate simple lines, rectangles and rectangular prisms
  dim = 1 # Dimension of the mesh
  nx = 30 # Number of elements in the x direction
  # ny = 3 # Number of elements in the y direction
  xmax = 50e-6  # Length of reactor
  # ymax = 50e-7 # Width of reactor
  uniform_refine = 3
[]

[Variables]
  [./n_concentration]
    #Adds a Linear Lagrange variable by default
    initial_condition = 0 # Start at 0
  [../]
[]

[Kernels]
  [./diff]
    type = ConstTimesDiffusion # A Laplacian operator
    variable = n_concentration # Operate on the "n_concentration" variable from above
    diffusion_coeff = 3.16e-8
  [../]
  [./time_derivative]
    type = TimeDerivative
    variable = n_concentration
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
    alpha = 3.3e4 # 1/m 
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
  coord_type = XYZ # Cartesian
[]

[Executioner]
  type = Transient # Transient solver
  dt = 7.91e-5
  solve_type = PJFNK #Preconditioned Jacobian Free Newton Krylov
  petsc_options_iname = '-pc_type -pc_hypre_type' #Matches with the values below
  petsc_options_value = 'hypre boomeramg'
  end_time = 0.5
   nl_rel_tol = 1e-02
   l_tol = 1e-02
  [./TimeStepper]
    type = IterationAdaptiveDT
    linear_iteration_ratio = 5
    cutback_factor = 0.5
    dt = 7.91e-5
    growth_factor = 2
    optimal_iterations = 4
  [../]
[]

[Adaptivity]
  marker = error_frac
  max_h_level = 5
  [./Indicators]
    [./temp_jump]
      type = GradientJumpIndicator
      variable = n_concentration
      scale_by_flux_faces = true
    [../]
  [../]
  [./Markers]
    [./error_frac]
      type = ErrorFractionMarker
      coarsen = 0.1
      indicator = temp_jump
      refine = 0.6
    [../]
  [../]
[]

[Outputs]
  output_initial = true # Output initial condiiton
  exodus = true # Output Exodus format
  print_perf_log = true # Show performance log information on screen
  print_linear_residuals = true # Display linear residuals on screen
[]
