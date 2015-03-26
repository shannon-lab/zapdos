[Mesh]
  type = GeneratedMesh # Can generate simple lines, rectangles and rectangular prisms
  dim = 2 # Dimension of the mesh
  nx = 30 # Number of elements in the x direction
  ny = 3 # Number of elements in the y direction
  xmax = 1  # Length of reactor
  ymax = .1 # Width of reactor
  # uniform_refine = 3
[]

[Variables]
  [./n_concentration]
    #Adds a Linear Lagrange variable by default
    initial_condition = 0 # Start at 0
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion # A Laplacian operator
    variable = n_concentration # Operate on the "n_concentration" variable from above
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
    boundary = right
    # value = 0 # Outlet concentration
  [../]
[]

[Problem]
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE
  coord_type = XYZ # Cartesian
[]

[Executioner]
  type = Transient # Transient solver
  num_steps = 100
  dt = 0.01
  solve_type = PJFNK #Preconditioned Jacobian Free Newton Krylov
  petsc_options_iname = '-pc_type -pc_hypre_type' #Matches with the values below
  petsc_options_value = 'hypre boomeramg'
[]

[Adaptivity]
  marker = error_frac
  max_h_level = 3
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
      coarsen = 0.5
      indicator = temp_jump
      refine = 0.5
    [../]
  [../]
[]

[Outputs]
  output_initial = true # Output initial condiiton
  exodus = true # Output Exodus format
  print_perf_log = true # Show performance log information on screen
  print_linear_residuals = true # Display linear residuals on screen
[]
