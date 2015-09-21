[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 1000
  xmin = .002
  xmax = .05
[]

[Problem]
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE
  coord_type = RZ # Axisymmetric RZ
#  rz_coord_axis = X # Which axis the symmetry is around
[]

[Preconditioning]
  active = 'SMP'
  [./FDP]
    type = FDP
    full = true
 #Preconditioned JFNK (default)
    solve_type = 'NEWTON'
#    petsc_options_iname = '-pc_type -mat_fd_coloring_err -mat_fd_type'
#    petsc_options_value = 'lu       1e-6                 ds'
#    petsc_options_iname = '-pc_type -sub_ksp_type -sub_pc_type'
#    petsc_options_value = 'asm preonly lu'
#    petsc_options_iname = '-ksp_converged_reason -snes_converged_reason -mat_fd_type -snes_monitor -ksp_monitor_true_residual -pc_type -sub_pc_type -sub_pc_factor_shift'
#    petsc_options_value = '1 1 ds 1 1 asm lu NONZERO'  
    petsc_options_iname = '-ksp_converged_reason -snes_converged_reason'
    petsc_options_value = '1 1'  
  [../]
  [./SMP]
    type = SMP
    full = true
 #Preconditioned JFNK (default)
    solve_type = 'PJFNK'
    petsc_options_iname = '-pc_type -pc_hypre_type -ksp_converged_reason -snes_converged_reason'
    petsc_options_value = 'hypre boomeramg 1 1'
#    petsc_options_iname = '-ksp_type -pc_type -sub_pc_type -sub_pc_factor_shift_type -ksp_converged_reason -snes_converged_reason'
#    petsc_options_value = 'gmres asm lu NONZERO 1 1'
#    petsc_options_iname = '-ksp_converged_reason -snes_converged_reason -pc_type' # -sub_pc_type -sub_pc_factor_shift
#    petsc_options_value = '1 1 lu' # lu NONZERO
  [../]
[]

[Executioner]
  type = Transient
  dt = 2e-11
  end_time = .01
#  petsc_options_iname = '-snes_type'
#  petsc_options_value = 'test'
#  solve_type = NEWTON
#  petsc_options_iname = '-pc_type -pc_hypre_type'
#  petsc_options_value = 'hypre boomeramg'
#  trans_ss_check = true
#  ss_check_tol = 1e-7
#  nl_rel_tol = 1e-2
  l_max_its = 50
#  nl_max_its = 75
  dtmin = 2e-11
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
#  exodus = true
#  interval = 100
  [./out]
    type = Exodus
    output_material_properties = true
    show_material_properties = 'advective_ion_flux diffusive_ion_flux total_ion_flux advective_electron_flux diffusive_electron_flux total_electron_flux Electric_Field'
  [../]
[]

[Debug]
  show_var_residual_norms = true
[]

[LotsOfCoeffDiffusion]
  variables = 'Arp'
[]

[LotsOfTimeDerivatives]
  variables = 'em Arp'
[]

[LotsOfEFieldAdvection]
  variables = 'em Arp'
  potential = 'potential'
[]

[LotsOfPotentialDrivenArtificialDiff]
  variables = 'Arp'
  potential = 'potential'
  delta = 5e0
[]

[Kernels]
  [./potential_diffusion]
    type = Diffusion
    variable = potential
  [../]
  [./potential_source]
    type = PoissonSource
    variable = potential
    Arp = Arp
    em = em
  [../]
  [./electron_diffusion]
    type = ElectronDiffusion
    variable = em
    Te = Te
  [../]
  [./electron_artificial_diffusion]
    type = PotentialDrivenArtificialDiffElectrons
    variable = em
    var_name_string = em
    potential = potential
    Te = Te
    delta = 5e0
  [../]
  [./electron_source]
    type = ElectronSource
    variable = em
    Te = Te
  [../]
  [./el_energy_time_deriv]
    type = TimeDerivativeElectronTemp
    variable = Te
    em = em
  [../]
  [./el_energy_transport]
    type = ElectronEnergyTransport
    variable = Te
    potential = potential
    em = em
  [../]
  [./el_energy_source]
    type = ElectronEnergySource
    variable = Te
    em = em
  [../]
  [./el_energy_artificial_diff]
    type = PotentialDrivenArtificialDiffEnergy
    variable = Te
    potential = potential
    em = em
    var_name_string = em
    delta = 5e0
  [../]
#  [./ars_source]
#    type = ArsSource
#    variable = Ars
#    em = em
#    Te = Te
#  [../]
  [./arp_source]
    type = ArpSource
    variable = Arp
    em = em
    Te = Te
  [../]
  [./joule_heating]
    type = JouleHeating
    variable = Te
    potential = potential
    em = em
  [../]
[]

[Variables]
  [./potential]
    scaling = 1e3
 [../]
  [./em]
    scaling = 1e-4
  [../]
  [./Arp]
    scaling = 1e-4
  [../]
#  [./Ars]
#    scaling = 1e-6
#  [../]
  [./Te]
    scaling = 1e-5
  [../]
[]

#[AuxVariables]
#  [./h_size]
#    order = CONSTANT
#    family = MONOMIAL
#  [../]
#[]
#
#[AuxKernels]
#  [./h_kernel]
#    type = HSize
#    variable = h_size
#  [../]
#[]

[Materials]
  [./air]
    block = 0
    type = Argon
    em = em
    potential = potential
    Te = Te
    Arp = Arp
 [../]
[]

[BCs]
#  [./potential_dirichlet_left]
#    type = DirichletBC
#    variable = potential
#    boundary = left
#    value = 1000
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
    var_name = Arp
    potential = potential
    boundary = 'left right'
  [../]
  # Below is the BC that contains a fictional material property _blahzie_ that does not exist in the material file
  [./em_physical_anode]
    type = PhysicalElectronBC
    variable = em
    boundary = 'left'
    ip = Arp
    coupled_ion_name = Arp
    se_coeff = 0.0
    potential = potential
    Te = Te
  [../]
  [./em_physical_cathode]
    type = PhysicalElectronBC
    variable = em
    boundary = 'right'
    ip = Arp
    coupled_ion_name = Arp
    se_coeff = 0.2
    potential = potential
    Te = Te
  [../]
  [./mean_el_en_anode]
    type = PhysicalElectronEnergyBC
    variable = Te
    potential = potential
    em = em
    ip = Arp
    coupled_ion_name = Arp
    se_energy = 0.0
    se_coeff = 0.0
    boundary = 'left'
  [../]
  [./mean_el_en_cathode]
    type = PhysicalElectronEnergyBC
    variable = Te
    potential = potential
    em = em
    ip = Arp
    coupled_ion_name = Arp
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
    value = 1e7
  [../]
  [./ip_ic]
    type = ConstantIC
    variable = Arp
    value = 1e7
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
    value = '1000*tanh(1e6*t)'
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
