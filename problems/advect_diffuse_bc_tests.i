[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
  xmax = 1
[]

[Variables]
  [./ions]
  [../]
  [./electrons]
  [../]
[]

[Functions]
  [./electron_velocity_function]
    type = ParsedVectorFunction
    value_x = '1.0'
  [../]
  [./ion_velocity_function]
    type = ParsedVectorFunction
    value_x = '-1.0'
  [../]
[]

[ICs]
  [./electron_density_ic]
    type = ConstantIC
    variable = electrons
    value = 1.0
  [../]
  [./ion_density_ic]
    type = ConstantIC
    variable = ions
    value = 1.0
  [../]
[]

[LotsOfTimeDerivatives]
  variables = 'ions electrons'
[]

[LotsOfDiffusion]
  variables = 'ions electrons'
[]

[Kernels]
  [./electron_advection]
    variable = electrons
    type = ConvectionArb
    velocity_function = electron_velocity_function
  [../]
  [./ion_advection]
    variable = ions
    type = ConvectionArb
    velocity_function = ion_velocity_function
  [../]
  [./electron_src]
    variable = electrons
    type = UnitySource
  [../]
  [./ion_src]
    variable = ions
    type = UnitySource
  [../]
[]

[BCs] 
  [./electron_bc]
    variable = electrons
    type = SometimesAdvectionBC
    velocity_function = electron_velocity_function
    boundary = 'left right'
  [../]
  [./ion_bc]
    variable = ions
    type = SometimesAdvectionBC
    velocity_function = ion_velocity_function
    boundary = 'left right'
  [../]
[]

[Problem]   
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE
[]   

[Executioner]
  type = Transient
  dt = 0.1
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  end_time = 1
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
