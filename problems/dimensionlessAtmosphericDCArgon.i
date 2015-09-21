[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 2000
  xmin = 0
  xmax = 5
[]

[Problem]
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE
  # coord_type = RZ # Axisymmetric RZ
#  rz_coord_axis = X # Which axis the symmetry is around
[]

# [Preconditioning]
#   [./FDP]
#     type = FDP
#     full = true
#  #Preconditioned JFNK (default)
#     solve_type = 'NEWTON'
# #    petsc_options_iname = '-pc_type -mat_fd_coloring_err -mat_fd_type'
# #    petsc_options_value = 'lu       1e-6                 ds'
# #    petsc_options_iname = '-pc_type -sub_ksp_type -sub_pc_type'
# #    petsc_options_value = 'asm preonly lu'
# #    petsc_options_iname = '-ksp_converged_reason -snes_converged_reason -mat_fd_type -snes_monitor -ksp_monitor_true_residual -pc_type -sub_pc_type -sub_pc_factor_shift'
# #    petsc_options_value = '1 1 ds 1 1 asm lu NONZERO'  
#     petsc_options_iname = '-ksp_converged_reason -snes_converged_reason'
#     petsc_options_value = '1 1'  
#   [../]
# []

[Executioner]
  type = Transient
  dt = 1e-6
  end_time = 10
#  petsc_options_iname = '-snes_type'
#  petsc_options_value = 'test'
 solve_type = PJFNK
 petsc_options_iname = '-pc_type -pc_hypre_type'
 petsc_options_value = 'hypre boomeramg'
#  trans_ss_check = true
#  ss_check_tol = 1e-7
 nl_rel_tol = 1e-4
  l_max_its = 15
 nl_max_its = 6
  dtmin = 1e-12
#  line_search = none
  [./TimeStepper]
    type = IterationAdaptiveDT
#    linear_iteration_ratio = 5
    cutback_factor = 0.5
    dt = 2e-11
    growth_factor = 2.0
#    optimal_iterations = 4
  [../]
[]

[Outputs]
  exodus = true
#  execute_on = 'nonlinear'
#  interval = 100
#  [./out]
#    type = Exodus
#    output_material_properties = true
#    show_material_properties = 'advective_ion_flux diffusive_ion_flux total_ion_flux advective_electron_flux diffusive_electron_flux total_electron_flux Electric_Field'
#  [../]
[]

[Debug]
  show_var_residual_norms = true
[]

[LotsOfTimeDerivatives]
  variables = 'em Arp'
[]


[Kernels]
  [./el_energy_time_deriv]
    type = TimeDerivativeElectronTemp
    variable = Te
    em = em
  [../]
  [./electrons]
    type = ElectronKernel
    variable = em
    Te = Te
    potential = potential
  [../]
  [./argon_ions]
    type = ArpKernel
    variable = Arp
    em = em
    potential = potential
    Te = Te
  [../]
  [./potential]
    type = PoissonKernel
    variable = potential
    em = em
    Arp = Arp
  [../]
  [./el_energy]
    type = ElectronEnergyKernel
    variable = Te
    em = em
    potential = potential
  [../]

[Variables]
  [./potential]
  [../]
  [./em]
  [../]
  [./Arp]
  [../]
  [./Te]
  [../]
[]

[Materials]
  [./air]
    block = 0
    type = Argon
 [../]
[]

[BCs]
#  [./potential_dirichlet_left]
#    type = DirichletBC
#    variable = potential
#    boundary = left
#    value = 1
#  [../]
  [./potential_dirichlet_func_left]
    type = FunctionDirichletBC
    variable = potential
    boundary = left
    function = potential_bc_func
  [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  [../]
  [./ip_physical]
    type = PhysicalIonBC
    variable = Arp
    potential = potential
    boundary = 'left right'
  [../]
  [./em_physical_anode]
    type = PhysicalElectronBC
    variable = em
    boundary = 'left'
    Arp = Arp
    se_coeff = 0.0
    potential = potential
    Te = Te
  [../]
  [./em_physical_cathode]
    type = PhysicalElectronBC
    variable = em
    boundary = 'right'
    Arp = Arp
    se_coeff = 0.2
    potential = potential
    Te = Te
  [../]
  [./mean_el_en_anode]
    type = PhysicalElectronEnergyBC
    variable = Te
    potential = potential
    em = em
    Arp = Arp
    se_energy = 0.0
    se_coeff = 0.0
    boundary = 'left'
  [../]
  [./mean_el_en_cathode]
    type = PhysicalElectronEnergyBC
    variable = Te
    potential = potential
    em = em
    Arp = Arp
    se_energy = 4.0
    se_coeff = 0.2
    boundary = 'right'
  [../]
[]

[ICs]
#  [./em_ic]
#    type = FunctionIC
#    variable = em
#    function = density_ic_parsed_function
#  [../]
#  [./ip_ic]
#    type = FunctionIC
#    variable = Arp
#    function = density_ic_parsed_function
#  [../]
  [./em_ic]
    type = ConstantIC
    variable = em
    value = 1e-6
  [../]
  [./ip_ic]
    type = ConstantIC
    variable = Arp
    value = 1e-6
  [../]
  [./mean_el_energy_ic]
    type = ConstantIC
    variable = Te
    value = 4.0
  [../]
#  [./potential_ic]
#    type = FunctionIC
#    variable = potential
#    function = potential_parsed_function
#  [../]
[]

[Functions]
  [./density_ic_parsed_function]
    type = ParsedFunction
    value = '1e13'
  [../]
  [./potential_ic_function]
    type = ParsedFunction
    value = '2.0e4*(x-.055)'
  [../]
  [./potential_bc_func]
    type = ParsedFunction
    value = '1.0*tanh(1e4*t)'
  [../]
[]

#[Adaptivity]
#  marker = error_frac_edens
#  max_h_level = 3
#  [./Indicators]
##    [./temp_jump_potential]
##      type = GradientJumpIndicator
##      variable = potential
##      scale_by_flux_faces = true
##    [../]
#    [./temp_jump_edens]
#      type = GradientJumpIndicator
#      variable = em
#      scale_by_flux_faces = true
#    [../]
##    [./temp_jump_idens]
##      type = GradientJumpIndicator
##      variable = ip
##      scale_by_flux_faces = true
##    [../]
###    [./analytical]
###      type = AnalyticalIndicator
###      variable = ion_src_term
###      function = null_function
###    [../]
###    [./analytical_diff]
###      type = AnalyticalDiffIndicator
###      variable = alpha_times_h
###      function = unity_function
###    [../]
#  [../]
#  [./Markers]
##    [./error_frac_pot]
##      type = ErrorFractionMarker
##      coarsen = 0.1
##      indicator = temp_jump_potential
##      refine = 0.6
##    [../]
#    [./error_frac_edens]
#      type = ErrorFractionMarker
#      coarsen = 0.1
#      indicator = temp_jump_edens
#      refine = 0.6
#    [../]
##    [./error_frac_idens]
##      type = ErrorFractionMarker
##      coarsen = 0.1
##      indicator = temp_jump_idens
##      refine = 0.6
##    [../]
##    [./combo]
##      type = ComboMarker
##      markers = 'error_frac_pot error_frac_edens error_frac_idens'
##    [../]
###    [./error_tol]
###      type = ErrorToleranceMarker
###      indicator = analytical_diff
###      coarsen = 0
###      refine = 0
###    [../]
#  [../]
#[]
