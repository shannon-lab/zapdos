[Mesh]
  type = GeneratedMesh
  dim = 1
  ny = 1000
  ymin = .002
  ymax = .05
[]

[Problem]
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE
  coord_type = RZ # Axisymmetric RZ
  rz_coord_axis = X # Which axis the symmetry is around
[]

[Preconditioning]
#  [./FDP]
#    type = FDP
#    full = true
# #Preconditioned JFNK (default)
#    solve_type = 'PJFNK'
#    petsc_options_iname = '-pc_type -mat_fd_coloring_err -mat_fd_type'
#    petsc_options_value = 'lu       1e-6                 ds'
#  [../]
  [./SMP]
    type = SMP
    full = true
 #Preconditioned JFNK (default)
    solve_type = 'PJFNK'
    petsc_options_iname = '-pc_type -pc_hypre_type'
    petsc_options_value = 'hypre boomeramg'
  [../]
[]

[Executioner]
  type = Transient
#  dt = 2.1e-13
  end_time = 0.1
#  solve_type = PJFNK
#  petsc_options_iname = '-pc_type -pc_hypre_type'
#  petsc_options_value = 'hypre boomeramg'
#  trans_ss_check = true
#  ss_check_tol = 1e-7
#  nl_rel_tol = 1e-6
#  l_tol = 1e-1
##  nl_abs_tol = 1e-3
  l_max_its = 10
  nl_max_its = 5
#  dtmin = 2.1e-16
#  line_search = none
  [./TimeStepper]
    type = IterationAdaptiveDT
    linear_iteration_ratio = 5
    cutback_factor = 0.5
    dt = 1e-6
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
  variables = 'Ars Arp'
[]

[LotsOfTimeDerivatives]
  variables = 'em mean_electron_energy Ars Arp'
[]

[LotsOfEFieldAdvection]
  variables = 'em mean_electron_energy Arp'
  potential = 'potential'
[]

#[LotsOfPotentialDrivenArtificialDiff]
#  variables = 'em'
#  potential = 'potential'
#[]

[Kernels]
  [./potential_diffusion]
    type = Diffusion
    variable = potential
  [../]
  [./potential_source]
    type = PoissonSource
    variable = potential
    ion_density = Arp
    electron_density = em
  [../]
  [./electron_diffusion]
    type = ElectronDiffusion
    variable = em
    mean_electron_energy = mean_electron_energy
  [../]
  [./electron_source]
    type = ElectronSource
    variable = em
    Ars = Ars
    mean_electron_energy = mean_electron_energy
  [../]
  [./el_energy_diffusion]
    type = ElectronEnergyDiffusion
    variable = mean_electron_energy
    em = em
  [../]
  [./el_energy_source]
    type = ElectronEnergySource
    variable = mean_electron_energy
    Ars = Ars
    em = em
  [../]
  [./ars_source]
    type = ArsSource
    variable = Ars
    em = em
    mean_electron_energy = mean_electron_energy
  [../]
  [./arp_source]
    type = ArpSource
    variable = Arp
    em = em
    mean_electron_energy = mean_electron_energy
    Ars = Ars
  [../]
  [./joule_heating]
    type = JouleHeating
    variable = mean_electron_energy
    potential = potential
    em = em
  [../]
[]

[Variables]
  [./potential]
    scaling = 1e9
 [../]
  [./em]
    scaling = 1e-7
  [../]
  [./Arp]
    scaling = 1e-5
  [../]
  [./Ars]
    scaling = 1
  [../]
  [./mean_electron_energy]
    scaling = 1
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
    mean_electron_energy = mean_electron_energy
 [../]
[]

[BCs]
  [./potential_dirichlet_left]
    type = DirichletBC
    variable = potential
    boundary = left
    value = -1000
  [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  [../]
  [./ip_physical_left]
    type = PhysicalIonBC
    variable = Arp
    boundary = left
  [../]
  [./ip_physical_right]
    type = PhysicalIonBC
    variable = Arp
    boundary = right
  [../]
  [./em_physical_left]
    type = PhysicalElectronBC
    variable = em
    boundary = left
    ip = Arp
    se_coeff = 0.1
  [../]
  [./em_physical_right]
    type = PhysicalElectronBC
    variable = em
    boundary = right
    ip = Arp
    se_coeff = 0.1
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
    variable = Arp
    function = density_ic_parsed_function
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
  [./potential_parsed_function]
    type = ParsedFunction
    value = '2.0e7*x'
[]

#[Adaptivity]
#  marker = combo
#  max_h_level = 3
#  [./Indicators]
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
#    [./temp_jump_idens]
#      type = GradientJumpIndicator
#      variable = ip
#      scale_by_flux_faces = true
#    [../]
##    [./analytical]
##      type = AnalyticalIndicator
##      variable = ion_src_term
##      function = null_function
##    [../]
##    [./analytical_diff]
##      type = AnalyticalDiffIndicator
##      variable = alpha_times_h
##      function = unity_function
##    [../]
#  [../]
#  [./Markers]
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
#    [./error_frac_idens]
#      type = ErrorFractionMarker
#      coarsen = 0.1
#      indicator = temp_jump_idens
#      refine = 0.6
#    [../]
#    [./combo]
#      type = ComboMarker
#      markers = 'error_frac_pot error_frac_edens error_frac_idens'
#    [../]
##    [./error_tol]
##      type = ErrorToleranceMarker
##      indicator = analytical_diff
##      coarsen = 0
##      refine = 0
##    [../]
#  [../]
#[]
