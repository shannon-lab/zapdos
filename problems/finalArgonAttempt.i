[Mesh]
  # type = FileMesh
  # file = argon_mesh.unv
  # boundary_id = '3 4'
  # boundary_name = 'left right'
  type = GeneratedMesh
  dim = 1
  nx = 4000
  xmin = 0.002
  xmax = .05
[]

[Problem]
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE
  coord_type = RZ
[]

# [Preconditioning]
#   [./SMP]
#     type = SMP
#     # full = true
#     off_diag_row = 'em'
#     off_diag_column = 'potential'
#   [../]
# []

[Executioner]
  type = Transient
 end_time = 1e-1
 solve_type = PJFNK
 petsc_options_iname = '-petsc_type -petsc_hypre_type -ksp_converged_reason -snes_converged_reason -snes_stol'
 petsc_options_value = 'hypre boomeramg true true 0'
 nl_rel_tol = 1e-2
 # l_tol = 1e-3
 # trans_ss_check = true
 # ss_check_tol = 1e-7
 # nl_abs_tol = 1e3
  l_max_its = 15
 nl_max_its = 13
  dtmin = 0.9e-10
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.5
    dt = 1e-10
    growth_factor = 2.0
   optimal_iterations = 10
  [../]
[]

[Outputs]
  exodus = true
  print_perf_log = true
  print_linear_residuals = true
  output_initial = true
[]

[Debug]
  show_var_residual_norms = true
[]

# [LotsOfTimeDerivatives]
#   variables = 'em'
# []


[Kernels]
  [./el_energy_time_deriv]
    type = TimeDerivativeElectronTemp
    variable = mean_en
  [../]
  [./em_time_deriv]
    type = ElectronTimeDerivative
    variable = em
  [../]
  [./Arp_time_deriv]
    type = ElectronTimeDerivative
    variable = Arp
  [../]
  [./electrons]
    type = ElectronKernel
    variable = em
    mean_en = mean_en
    potential = potential
  [../]
  [./argon_ions]
    type = ArpKernel
    variable = Arp
    em = em
    mean_en = mean_en
    potential = potential
  [../]
  [./potential]
    type = PoissonKernel
    variable = potential
    em = em
    Arp = Arp
  [../]
  [./el_energy]
    type = ElectronEnergyKernel
    variable = mean_en
    em = em
    potential = potential
  [../]
[]

[Variables]
  [./potential]
    # scaling = 1e12
  [../]
  [./em]
    # scaling = 1e-6
  [../]
  [./Arp]
    # scaling = 1e-6
  [../]
  [./mean_en]
    # scaling = 1e-11
  [../]
[]

[AuxVariables]
  [./em_lin]
  [../]
  [./Arp_lin]
  [../]
  [./energy_lin]
  [../]
  [./e_temp]
  [../]
[]

[AuxKernels]
  [./em_lin]
    type = ElectronDensity
    variable = em_lin
    electron_density = em
  [../]
  [./Arp_lin]
    type = IonDensity
    variable = Arp_lin
    ion_density = Arp
  [../]
  [./energy_lin]
    type = ElectronDensity
    variable = energy_lin
    electron_density = mean_en
  [../]  
  [./e_temp]
    type = ElectronTemperature
    variable = e_temp
    electron_density = em
    mean_en = mean_en
  [../]
[]

[BCs]
  [./potential_dirichlet_left]
    type = DirichletBC
    variable = potential
    boundary = left
    value = -1000
  [../]
  # [./potential_dirichlet_left]
  #   type = FunctionDirichletBC
  #   variable = potential
  #   boundary = left
  #   function = potential_bc_func
  # [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  [../]
  [./em_physical]
    type = PhysicalElectronBC
    variable = em
    boundary = 'left right'
    potential = potential
    mean_en = mean_en
  [../]
  [./Arp_physical]
    type = PhysicalIonBC
    variable = Arp
    boundary = 'left right'
    potential = potential
  [../]
  [./mean_el_en]
    type = PhysicalElectronEnergyBC
    variable = mean_en
    potential = potential
    # em = em
    boundary = 'left right'
  [../]
[]

[ICs]
  # [./em_ic]
  #   type = FunctionIC
  #   variable = em
  #   function = density_ic_parsed_function
  # [../]
  [./em_ic]
    type = ConstantIC
    variable = em
    value = 29.934
  [../]
  [./ip_ic]
    type = ConstantIC
    variable = Arp
    value = 29.934
  [../]
  [./mean_el_energy_ic]
    type = ConstantIC
    variable = mean_en
    value = 31.3199
   [../]
  # [./mean_el_energy_ic]
  #   type = FunctionIC
  #   variable = mean_en
  #   function = en_ic_parsed_function
  #  [../]
 [./potential_ic]
   type = FunctionIC
   variable = potential
   function = potential_ic_function
 [../]
  # [./potential_ic]
  #   type = ConstantIC
  #   variable = potential
  #   value = 0
  # [../]
[]

[Functions]
  [./density_ic_parsed_function]
    type = ParsedFunction
    value = '30*(x/.05)^2'
  [../]
  [./en_ic_parsed_function]
    type = ParsedFunction
    value = '30*(x/.05)^2'
  [../]
  [./potential_ic_function]
    type = ParsedFunction
    value = '310.67*log(x)+930.68'
  [../]
  [./potential_bc_func]
    type = ParsedFunction
    value = '-1000.0*tanh(1e6*t)'
  [../]
[]

# [Adaptivity]
#   marker = error_frac_edens
#   max_h_level = 3
#   [./Indicators]
#     [./temp_jump_edens]
#       type = GradientJumpIndicator
#       variable = em
#       scale_by_flux_faces = true
#     [../]
#   [../] 
#   [./Markers]
#     [./error_frac_edens]
#       type = ErrorFractionMarker
#       coarsen = 0.1
#       indicator = temp_jump_edens
#       refine = 0.6
#     [../]
#   [../]
# []
