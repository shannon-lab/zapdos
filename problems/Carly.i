[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 100
  ny = 10
  xmax = 4e-3 # Length of test chamber
  ymax = 4e-4 # Test chamber radius
  uniform_refine = 3
[]

[Variables]
  active = 'OH_conc NO_conc H2O2_conc'
  [./OH_conc]
    #Adds a Linear Lagrange variable by default
    initial_condition = 0 # Start at 0
  [../]
  [./NO_conc]
    initial_condition = 0
  [../]
  [./H2O2_conc]
    initial_condition = 0
  [../]
  [./HNO2_conc]
    initial_condition = 0
  [../]
[]

[Kernels]
  # active = 'diff time_derivative'
  [./diff_OH]
    type = ConstTimesDiffusion
    variable = OH_conc # Operate on the "n_concentration" variable from above
    diffusion_coeff = 2.0e-9
  [../]
  [./time_derivative_OH]
    type = TimeDerivative
    variable = OH_conc
  [../]
  [./reaction_term_OH_NO]
    type = SecondOrderReaction
    variable = OH_conc
    reaction_coeff = 2.0e7
    reactant_two = NO_conc
  [../]
  [./diff_NO]
    type = ConstTimesDiffusion
    variable = NO_conc
    diffusion_coeff = 2.2e-9
  [../]
  [./time_derivative_NO]
    type = TimeDerivative
    variable = NO_conc
  [../]
  [./reaction_term_NO_OH]
    type = SecondOrderReaction
    variable = NO_conc
    reaction_coeff = 2.0e7
    reactant_two = OH_conc
  [../]
  [./reaction_term_OH_OH]
    type = SelfBinaryReaction
    variable = OH_conc
    reaction_coeff = 1.0e7
  [../]
  [./diff_H2O2]
    type = ConstTimesDiffusion
    variable = H2O2_conc
    diffusion_coeff = 1.7e-9
  [../]
  [./time_derivative_H2O2]
    type = TimeDerivative
    variable = H2O2_conc
  [../]
  [./reaction_H2O2_src_from_OH_binary]
    type = SrcSelfBinaryReaction
    variable = H2O2_conc
    reaction_coeff = 1.0e7
    stoich_coeff = -1.0
    sole_reactant = OH_conc
  [../]
[]

[BCs]
  [./inlet_OH]
    type = DirichletBC # Simple u=value BC
    variable = OH_conc
    boundary = left # Name of a sideset in the mesh
    value = 1.15607e-5 # (mol/m^3) Inlet concentration
  [../]
  [./outlet_OH]
    type = NeumannBC
    variable = OH_conc
    boundary = right
    value = 0
  [../]
  [./inlet_NO]
    type = DirichletBC
    variable = NO_conc
    boundary = left
    value = 3.03e-7
  [../]
  [./outlet_NO]
    type = NeumannBC
    variable = NO_conc
    boundary = right
    value = 0
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

[Preconditioning]
  [./SMP_jfnk_full]
    type = SMP
    full = true
    solve_type = 'PJFNK'
    # petsc_options_iname = '-pc_type'
    # petsc_options_value = 'lu'
  [../]
[]

[Executioner]
  type = Transient
  dt = 0.01
  # solve_type = PJFNK
  # petsc_options_iname = '-pc_type -pc_hypre_type'
  # petsc_options_value = 'hypre boomeramg'
  end_time = 1000
  trans_ss_check = true
  ss_check_tol = 1e-8
  nl_rel_tol = 1e-2
  l_tol = 1e-2
  [./TimeStepper]
    type = IterationAdaptiveDT
    linear_iteration_ratio = 25
    cutback_factor = 0.5
    dt = 0.01
    growth_factor = 2
    optimal_iterations = 4
  [../]
[]

[Adaptivity]
  marker = error_frac
  max_h_level = 3
  [./Indicators]
    [./temp_jump]
      type = GradientJumpIndicator
      variable = OH_conc
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
