[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 50
  xmin = 0
  xmax = .05
[]

[Problem]
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE
[]

[Executioner]
  type = Transient
 end_time = 1
 solve_type = PJFNK
 petsc_options_iname = '-pc_type -pc_hypre_type -ksp_converged_reason -snes_converged_reason -snes_stol'
 petsc_options_value = 'hypre boomeramg true true 0'
 # nl_rel_tol = 1e-4
 # trans_ss_check = true
 # ss_check_tol = 1e-7
 # nl_abs_tol = 1e-10
  l_max_its = 15
 nl_max_its = 6
  dtmin = 1e-12
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.5
    dt = 1e-7
    growth_factor = 2.0
   optimal_iterations = 4
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
    em = em
  [../]
  [./em_time_deriv]
    type = ElectronTimeDerivative
    variable = em
  [../]
  [./electrons]
    type = ElectronKernel
    variable = em
    mean_en = mean_en
    potential = potential
  [../]
  # [./argon_ions]
  #   type = ArpKernel
  #   variable = Arp
  #   em = em
  #   # mean_en = mean_en
  # [../]
  [./potential]
    type = PoissonKernel
    variable = potential
    # em = em
    # Arp = Arp
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
    # scaling = 1e-5
  [../]
  [./em]
    # scaling = 1e-11
  [../]
  # [./Arp]
  #   scaling = 1e0
  # [../]
  [./mean_en]
    # scaling = 1e-7
  [../]
[]

[BCs]
  [./potential_dirichlet_left]
    type = DirichletBC
    variable = potential
    boundary = left
    value = 1000
  [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  [../]
  [./em_diri_right]
    type = DirichletBC
    variable = em
    boundary = right
    value = 0
  [../]
  # [./em_diri_left]
  #   type = DirichletBC
  #   variable = em
  #   boundary = left
  #   value = 0
  # [../]
  [./em_physical]
    type = PhysicalElectronBC
    variable = em
    boundary = 'left'
    potential = potential
  [../]
  [./el_diri_right]
    type = DirichletBC
    variable = mean_en
    boundary = right
    value = 0
  [../]
  [./mean_el_en]
    type = PhysicalElectronEnergyBC
    variable = mean_en
    potential = potential
    em = em
    boundary = 'left'
  [../]
[]

[ICs]
  [./em_ic]
    type = FunctionIC
    variable = em
    function = density_ic_parsed_function
  [../]
  # [./ip_ic]
  #   type = ConstantIC
  #   variable = Arp
  #   value = 1
  # [../]
  [./mean_el_energy_ic]
    type = FunctionIC
    variable = mean_en
    function = en_ic_parsed_function
   [../]
 [./potential_ic]
   type = FunctionIC
   variable = potential
   function = potential_ic_function
 [../]
[]

[Functions]
  [./density_ic_parsed_function]
    type = ParsedFunction
    value = '-3*(1-(x/.05)^2)'
  [../]
  [./en_ic_parsed_function]
    type = ParsedFunction
    value = '-3*(1-(x/.05)^2)'
  [../]
  [./potential_ic_function]
    type = ParsedFunction
    value = '1000*(1-x/.05)'
  [../]
  # [./potential_bc_func]
#     type = ParsedFunction
#     value = '1.0*tanh(1e4*t)'
#   [../]
[]