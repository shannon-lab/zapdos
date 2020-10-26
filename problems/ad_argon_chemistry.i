dom0Scale=1.0
dom1Scale=1.0

[GlobalParams]
  offset = 20
  # offset = 0
  potential_units = kV
  use_moles = true
  # potential_units = V
[]

[Mesh]
  [./file]
    type = FileMeshGenerator
    file = 'ad_argon_chemistry.msh'
  [../]
  [./interface]
    type = SideSetsBetweenSubdomainsGenerator
    primary_block = '0'
    paired_block = '1'
    new_boundary = 'master0_interface'
    input = file
  [../]
  [./interface_again]
    type = SideSetsBetweenSubdomainsGenerator
    primary_block = '1'
    paired_block = '0'
    new_boundary = 'master1_interface'
    input = interface
  [../]
  [./left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = interface_again
  [../]
  [./right]
    type = SideSetsFromNormalsGenerator
    normals = '1 0 0'
    new_boundary = 'right'
    input = left
  [../]
[]

[Problem]
  type = FEProblem
  # kernel_coverage_check = false
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
    #ksp_norm = none
    #ksp_norm = 'preconditioned'
  [../]
[]

[Executioner]
  type = Transient
  automatic_scaling = true
  compute_scaling_once = false
  end_time = 1e-3
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  # petsc_options = '-snes_test_display'
  solve_type = NEWTON
  #solve_type = PJFNK
  line_search = 'basic'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'
  #petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -snes_stol'
  #petsc_options_value = 'lu NONZERO 1.e-10 0'
  #petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  #petsc_options_value = 'lu NONZERO 1.e-10'
  #petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  #petsc_options_value = 'lu NONZERO 1.e-10 fgmres 1e-3'
  # petsc_options_iname = '-pc_type'
  # petsc_options_value = 'asm'
  # petsc_options_iname = '-snes_type'
  # petsc_options_value = 'test'
  nl_rel_tol = 1e-6
  nl_abs_tol = 1e-10
  dtmin = 1e-18
  l_max_its = 20
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.4
    dt = 1e-11
    # dt = 1.1
    growth_factor = 1.2
   optimal_iterations = 30
  [../]
  #[./TimeIntegrator]
  #  type = LStableDirk2
  #[../]
[]

[Outputs]
  perf_graph = true
  # print_linear_residuals = false
  [./out]
    type = Exodus
    #execute_on = 'final'
  [../]
  #[./dof_map]
  #  type = DOFMap
  #[../]
[]

[Debug]
  #show_var_residual_norms = true
[]

[UserObjects]
  [./data_provider]
    type = ProvideMobility
    electrode_area = 5.02e-7 # Formerly 3.14e-6
    ballast_resist = 1e6
    e = 1.6e-19
    # electrode_area = 1.1
    # ballast_resist = 1.1
    # e = 1.1
  [../]
[]

[Kernels]
  [./Arex_time_deriv]
    type = ElectronTimeDerivative
    variable = Ar*
    block = 0
  [../]
  [./Arex_diffusion]
    type = CoeffDiffusion
    variable = Ar*
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./Arex_log_stabilization]
    type = LogStabilizationMoles
    variable = Ar*
    block = 0
    #offset = 25
  [../]


  [./em_time_deriv]
    #type = ElectronTimeDerivative
    type = ADTimeDerivativeLog
    variable = em
    block = 0
  [../]
  [./em_advection]
    type = ADEFieldAdvection
    variable = em
    potential = potential
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./em_diffusion]
    type = ADCoeffDiffusion
    variable = em
    mean_en = mean_en
    block = 0
    position_units = ${dom0Scale}
  [../]

  [./em_log_stabilization]
    type = LogStabilizationMoles
    variable = em
    block = 0
  [../]

  [./emliq_time_deriv]
    #type = ElectronTimeDerivative
    type = ADTimeDerivativeLog
    variable = emliq
    block = 1
  [../]
  [./emliq_advection]
    type = ADEFieldAdvection
    variable = emliq
    potential = potential
    block = 1
    position_units = ${dom1Scale}
  [../]
  [./emliq_diffusion]
    type = ADCoeffDiffusion
    variable = emliq
    block = 1
    position_units = ${dom1Scale}
  [../]

  [./emliq_log_stabilization]
    type = LogStabilizationMoles
    variable = emliq
    block = 1
  [../]

  [./potential_diffusion_dom1]
    type = ADCoeffDiffusionLin
    variable = potential
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./potential_diffusion_dom2]
    type = ADCoeffDiffusionLin
    variable = potential
    block = 1
    position_units = ${dom1Scale}
  [../]
  [./Arp_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = Arp
    block = 0
  [../]
  [./Ar2p_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = Ar2p
    block = 0
  [../]
  [./em_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = em
    block = 0
  [../]
  [./emliq_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = emliq
    block = 1
  [../]
  [./OHm_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = OHm
    block = 1
  [../]

  [./Arp_time_deriv]
    #type = ElectronTimeDerivative
    type = ADTimeDerivativeLog
    variable = Arp
    block = 0
  [../]
  [./Arp_advection]
    type = ADEFieldAdvection
    variable = Arp
    potential = potential
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./Arp_diffusion]
    type = ADCoeffDiffusion
    variable = Arp
    block = 0
    position_units = ${dom0Scale}
  [../]

  [./Arp_log_stabilization]
    type = LogStabilizationMoles
    variable = Arp
    block = 0
  [../]

  [./Ar2p_time_deriv]
    #type = ElectronTimeDerivative
    type = ADTimeDerivativeLog
    variable = Ar2p
    block = 0
  [../]
  [./Ar2p_advection]
    type = ADEFieldAdvection
    variable = Ar2p
    potential = potential
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./Ar2p_diffusion]
    type = ADCoeffDiffusion
    variable = Ar2p
    block = 0
    position_units = ${dom0Scale}
  [../]

  [./Ar2p_log_stabilization]
    type = LogStabilizationMoles
    variable = Ar2p
    block = 0
  [../]

  [./OHm_time_deriv]
    #type = ElectronTimeDerivative
    type = ADTimeDerivativeLog
    variable = OHm
    block = 1
  [../]
  [./OHm_advection]
    type = ADEFieldAdvection
    variable = OHm
    potential = potential
    block = 1
    position_units = ${dom1Scale}
  [../]
  [./OHm_diffusion]
    type = ADCoeffDiffusion
    variable = OHm
    block = 1
    position_units = ${dom1Scale}
  [../]
  [./OHm_log_stabilization]
    type = LogStabilizationMoles
    variable = OHm
    block = 1
  [../]

  [./mean_en_time_deriv]
    #type = ElectronTimeDerivative
    type = ADTimeDerivativeLog
    variable = mean_en
    block = 0
  [../]
  [./mean_en_advection]
    type = EFieldAdvectionEnergy
    variable = mean_en
    potential = potential
    em = em
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./mean_en_diffusion]
    type = ADCoeffDiffusion
    variable = mean_en
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./mean_en_joule_heating]
    #type = JouleHeating
    type = ADJouleHeating
    variable = mean_en
    potential = potential
    em = em
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./mean_en_log_stabilization]
    type = LogStabilizationMoles
    variable = mean_en
    block = 0
    offset = 15
  [../]
[]

[Variables]
  [./Ar*]
    initial_condition = -21
    block = 0
  [../]
  #[./Ar]
  #  block = 0
  #  initial_condition = 3.70109
  #[../]
  [./potential]
  [../]
  [./em]
    block = 0
  [../]
  [./emliq]
    block = 1
    # scaling = 1e-5
  [../]

  [./Arp]
    block = 0
  [../]
  [./Ar2p]
    block = 0
  [../]

  [./mean_en]
    block = 0
    # scaling = 1e-1
  [../]

  [./OHm]
    block = 1
    # scaling = 1e-5
  [../]
[]

[AuxVariables]
  [./H2O]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 10.92252
    block = 1
  [../]
  [./Arex_lin]
    block = 0
    order = CONSTANT
    family = MONOMIAL
  [../]
  #[./Ar_lin]
  #  block = 0
  #  order = CONSTANT
  #  family = MONOMIAL
  #[../]
  [./Ar]
    block = 0
    order = CONSTANT
    family = MONOMIAL
    #initial_condition = 2.43839813e25
    initial_condition = 3.70109
  [../]
  [./e_temp]
    block = 0
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./x]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./x_node]
  [../]
  [./rho]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  [../]
  [./rholiq]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./em_lin]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  [../]
  [./emliq_lin]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  [../]
  [./Arp_lin]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  [../]
  [./Ar2p_lin]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  [../]
  [./OHm_lin]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Efield]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Current_em]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  [../]
  [./Current_emliq]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  [../]
  [./Current_Arp]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  [../]
  [./Current_OHm]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./tot_gas_current]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  [../]
  [./tot_liq_current]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./tot_flux_OHm]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./EFieldAdvAux_em]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  [../]
  [./DiffusiveFlux_em]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  [../]
  [./EFieldAdvAux_emliq]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  [../]
  [./DiffusiveFlux_emliq]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  [../]
  [./PowerDep_em]
   order = CONSTANT
   family = MONOMIAL
   block = 0
  [../]
  [./PowerDep_Arp]
   order = CONSTANT
   family = MONOMIAL
   block = 0
  [../]
  #[./ProcRate_el]
  # order = CONSTANT
  # family = MONOMIAL
  # block = 0
  #[../]
  #[./ProcRate_ex]
  # order = CONSTANT
  # family = MONOMIAL
  # block = 0
  #[../]
  #[./ProcRate_iz]
  # order = CONSTANT
  # family = MONOMIAL
  # block = 0
  #[../]
[]

[AuxKernels]
  [./Arex_lin]
    type = DensityMoles
    variable = Arex_lin
    density_log = Ar*
    block = 0
  [../]
  #[./Ar_lin]
  #  type = DensityMoles
  #  variable = Ar_lin
  #  density_log = Ar
  #  block = 0
  #[../]
  [./PowerDep_em]
    type = PowerDep
    density_log = em
    potential = potential
    art_diff = false
    potential_units = kV
    variable = PowerDep_em
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./PowerDep_Arp]
    type = PowerDep
    density_log = Arp
    potential = potential
    art_diff = false
    potential_units = kV
    variable = PowerDep_Arp
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./e_temp]
    type = ElectronTemperature
    variable = e_temp
    electron_density = em
    mean_en = mean_en
    execute_on = 'initial timestep_end'
    block = 0
  [../]
  [./x_g]
    type = Position
    variable = x
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./x_l]
    type = Position
    variable = x
    position_units = ${dom1Scale}
    block = 1
  [../]
  [./x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./x_nl]
    type = Position
    variable = x_node
    position_units = ${dom1Scale}
    block = 1
  [../]
  [./rho]
    type = ParsedAux
    variable = rho
    args = 'em_lin Arp_lin Ar2p_lin'
    function = '(Arp_lin + Ar2p_lin) - em_lin'
    execute_on = 'timestep_end'
    block = 0
  [../]
  [./rholiq]
    type = ParsedAux
    variable = rholiq
    args = 'emliq_lin OHm_lin' # H3Op_lin OHm_lin'
    function = '-emliq_lin - OHm_lin' # 'H3Op_lin - em_lin - OHm_lin'
    execute_on = 'timestep_end'
    block = 1
  [../]
  [./tot_gas_current]
    type = ParsedAux
    variable = tot_gas_current
    args = 'Current_em Current_Arp'
    function = 'Current_em + Current_Arp'
    execute_on = 'timestep_end'
    block = 0
  [../]
  [./tot_liq_current]
    type = ParsedAux
    variable = tot_liq_current
    args = 'Current_emliq Current_OHm' # Current_H3Op Current_OHm'
    function = 'Current_emliq + Current_OHm' # + Current_H3Op + Current_OHm'
    execute_on = 'timestep_end'
    block = 1
  [../]
  [./em_lin]
    type = DensityMoles
    variable = em_lin
    density_log = em
    block = 0
  [../]
  [./emliq_lin]
    type = DensityMoles
    variable = emliq_lin
    density_log = emliq
    block = 1
  [../]
  [./Arp_lin]
    type = DensityMoles
    variable = Arp_lin
    density_log = Arp
    block = 0
  [../]
  [./Ar2p_lin]
    type = DensityMoles
    variable = Ar2p_lin
    density_log = Ar2p
    block = 0
  [../]
  [./OHm_lin]
    type = DensityMoles
    variable = OHm_lin
    density_log = OHm
    block = 1
  [../]
  [./Efield_g]
    type = Efield
    component = 0
    potential = potential
    variable = Efield
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./Efield_l]
    type = Efield
    component = 0
    potential = potential
    variable = Efield
    position_units = ${dom1Scale}
    block = 1
  [../]
  [./Current_em]
    type = Current
    potential = potential
    density_log = em
    variable = Current_em
    art_diff = false
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./Current_emliq]
    type = Current
    potential = potential
    density_log = emliq
    variable = Current_emliq
    art_diff = false
    block = 1
    position_units = ${dom1Scale}
  [../]
  [./Current_Arp]
    type = Current
    potential = potential
    density_log = Arp
    variable = Current_Arp
    art_diff = false
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./Current_OHm]
    block = 1
    type = Current
    potential = potential
    density_log = OHm
    variable = Current_OHm
    art_diff = false
    position_units = ${dom1Scale}
  [../]
  [./tot_flux_OHm]
    block = 1
    type = TotalFlux
    potential = potential
    density_log = OHm
    variable = tot_flux_OHm
  [../]
  [./EFieldAdvAux_em]
    type = EFieldAdvAux
    potential = potential
    density_log = em
    variable = EFieldAdvAux_em
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./DiffusiveFlux_em]
    type = DiffusiveFlux
    density_log = em
    variable = DiffusiveFlux_em
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./EFieldAdvAux_emliq]
    type = EFieldAdvAux
    potential = potential
    density_log = emliq
    variable = EFieldAdvAux_emliq
    block = 1
    position_units = ${dom1Scale}
  [../]
  [./DiffusiveFlux_emliq]
    type = DiffusiveFlux
    density_log = emliq
    variable = DiffusiveFlux_emliq
    block = 1
    position_units = ${dom1Scale}
  [../]
[]

[InterfaceKernels]
  [./em_advection]
    type = InterfaceAdvection
    mean_en_neighbor = mean_en
    potential_neighbor = potential
    neighbor_var = em
    variable = emliq
    boundary = master1_interface
    position_units = ${dom1Scale}
    neighbor_position_units = ${dom0Scale}
  [../]
  [./em_diffusion]
    type = InterfaceLogDiffusionElectrons
    mean_en_neighbor = mean_en
    neighbor_var = em
    variable = emliq
    boundary = master1_interface
    position_units = ${dom1Scale}
    neighbor_position_units = ${dom0Scale}
  [../]
[]

[BCs]
  [./mean_en_physical_right]
    type = ADHagelaarEnergyBC
    variable = mean_en
    boundary = 'master0_interface'
    potential = potential
    em = em
    ip = Arp
    #r = 0.99
    r = 0.0
    position_units = ${dom0Scale}
  [../]
  [./mean_en_physical_left]
    type = ADHagelaarEnergyBC
    variable = mean_en
    boundary = 'left'
    potential = potential
    em = em
    ip = 'Arp Ar2p'
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./secondary_energy_left]
    type = ADSecondaryElectronEnergyBC
    variable = mean_en
    boundary = 'left'
    potential = potential
    em = em
    ip = 'Arp Ar2p'
    r = 0
    position_units = ${dom0Scale}
  [../]

  [./potential_left]
    #type = NeumannCircuitVoltageMoles_KV
    type = ADNeumannCircuitVoltageMoles_KV
    variable = potential
    boundary = left
    function = potential_bc_func
    ip = 'Arp Ar2p'
    data_provider = data_provider
    em = em
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./potential_dirichlet_right]
    type = ADDirichletBC
    variable = potential
    boundary = right
    value = 0
  [../]
  [./em_physical_right]
    type = ADHagelaarElectronBC
    variable = em
    boundary = 'master0_interface'
    potential = potential
    mean_en = mean_en
    #r = 0.99
    r = 0.0
    position_units = ${dom0Scale}
  [../]
  [./Arp_physical_right_diffusion]
    type = ADHagelaarIonDiffusionBC
    variable = Arp
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./Arp_physical_right_advection]
    type = ADHagelaarIonAdvectionBC
    variable = Arp
    boundary = 'master0_interface'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./Ar2p_physical_right_diffusion]
    type = ADHagelaarIonDiffusionBC
    variable = Ar2p
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./Ar2p_physical_right_advection]
    type = ADHagelaarIonAdvectionBC
    variable = Ar2p
    boundary = 'master0_interface'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  [../]

  [./em_physical_left]
    type = ADHagelaarElectronBC
    variable = em
    boundary = 'left'
    potential = potential
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./sec_electrons_left]
    type = ADSecondaryElectronBC
    variable = em
    boundary = 'left'
    potential = potential
    ip = Arp
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./Arp_physical_left_diffusion]
    type = ADHagelaarIonDiffusionBC
    variable = Arp
    boundary = 'left'
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./Arp_physical_left_advection]
    type = ADHagelaarIonAdvectionBC
    variable = Arp
    boundary = 'left'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./Ar2p_physical_left_diffusion]
    type = ADHagelaarIonDiffusionBC
    variable = Ar2p
    boundary = 'left'
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./Ar2p_physical_left_advection]
    type = ADHagelaarIonAdvectionBC
    variable = Ar2p
    boundary = 'left'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  [../]

  [./emliq_right]
    type = ADDCIonBC
    variable = emliq
    boundary = right
    potential = potential
    position_units = ${dom1Scale}
  [../]
  [./OHm_physical]
    type = ADDCIonBC
    variable = OHm
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  [../]
[]

[ICs]
  [./em_ic]
    type = ConstantIC
    variable = em
    value = -21
    block = 0
  [../]
  [./emliq_ic]
    type = ConstantIC
    variable = emliq
    value = -21
    block = 1
  [../]
  [./Arp_ic]
    type = ConstantIC
    variable = Arp
    value = -21.6931472
    block = 0
  [../]
  [./Ar2p_ic]
    type = ConstantIC
    variable = Ar2p
    value = -21.6931472
    block = 0
  [../]
  [./mean_en_ic]
    type = ConstantIC
    variable = mean_en
    value = -20
    block = 0
  [../]
  [./OHm_ic]
    type = ConstantIC
    variable = OHm
    value = -15.6
    block = 1
  [../]
  [./potential_ic]
    type = FunctionIC
    variable = potential
    function = potential_ic_func
  [../]
[]

[Functions]
  [./potential_bc_func]
    type = ParsedFunction
    # value = '1.25*tanh(1e6*t)'
    value = 1.25
  [../]
  [./potential_ic_func]
    type = ParsedFunction
    value = '-1.25 * (1.0001e-3 - x)'
  [../]
[]

[Materials]
  [./electron_moments]
    type = ADGasElectronMoments
    block = 0
    em = em
    mean_en = mean_en
    property_tables_file = 'ad_argon_chemistry/electron_moments.txt'
  [../]

  [./gas_constants]
    type = GenericConstantMaterial
    block = 0
    prop_names = ' e         N_A      diffpotential k_boltz eps  se_coeff se_energy T_gas massem   p_gas  n_gas'
    prop_values = '1.6e-19 6.022e23 8.85e-12      1.38e-23 8.854e-12 0.05     3.        300   9.11e-31 1.01e5 40.4915'
  [../]

  [./liquid_constants]
    type = GenericConstantMaterial
    prop_names = 'N_A e diffpotential diffpotential_liq T_gas p_gas'
    prop_values = '6.022e23 1.602e-19 7.0832e-10 7.0832e-10 300 1.013e5'
    block = 1
  [../]

  [./water_electron_data]
    type = GenericConstantMaterial
    prop_names = 'diffemliq muemliq sgnemliq'
    prop_values = '4.5e-9 0.000173913 -1'
    block = 1
  [../]
  [./OHm_mat]
    type = HeavySpeciesMaterial
    heavy_species_name = OHm
    heavy_species_mass = 2.82420e-26
    heavy_species_charge = -1
    diffusivity = 5.26e-9
    block = 1
  [../]

  [./gas_species_0]
    type = HeavySpeciesMaterial
    heavy_species_name = Arp
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    #mobility = 0.144409938
    #diffusivity = 6.428571e-3
    block = 0
  [../]
  [./gas_species_1]
    type = HeavySpeciesMaterial
    heavy_species_name = Ar2p
    heavy_species_mass = 1.328e-25
    heavy_species_charge = 1.0
    block = 0
  [../]

  [./gas_species_2]
    type = HeavySpeciesMaterial
    heavy_species_name = Ar
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
    block = 0
  [../]

  [./gas_species_3]
    type = HeavySpeciesMaterial
    heavy_species_name = Ar*
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
    block = 0
  [../]
[]

[Reactions]
  # This argon reaction network based on a ZDPlasKin example:
  # zdplaskin.laplace.univ-tlse.fr
  # Example: "Micro-cathode sustained discharged in Ar"
  [./Argon]
    species = 'em Arp Ar2p Ar*'
    aux_species = 'Ar'
    reaction_coefficient_format = 'townsend'
    gas_species = 'Ar'
    electron_energy = 'mean_en'
    electron_density = 'em'
    include_electrons = true
    file_location = 'ad_argon_chemistry'
    equation_constants = 'Tgas e_temp'
    equation_values = '300 34800'
    potential = 'potential'
    use_log = true
    position_units = ${dom0Scale}
    #track_rates = true
    use_ad = true
    block = 0

    reactions = 'em + Ar -> em + Ar               : EEDF [elastic] (rxn_elastic)
                 em + Ar -> em + Ar*              : EEDF [-11.5]   (rxn_excitation)
                 em + Ar -> em + em + Arp         : EEDF [-15.76]  (rxn_ionization)
                 em + Ar* -> em + Ar              : EEDF [11.5]    (rxn_deexcitation)
                 em + Ar* -> em + em + Arp        : EEDF [-4.3]    (rxn_excited_ionization)
                 Ar2p + em -> Ar* + Ar            : {5.1187e11 * (e_temp/300)^(-0.67)}
                 Ar2p + Ar -> Arp + Ar + Ar       : {3.649332e12 / Tgas * exp(-15130/Tgas)}
                 Ar* + Ar* -> Ar2p + em           : 3.6132e8
                 Arp + em + em -> Ar + em         : {3.17314235e9 * (e_temp/11600)^(-4.5)}
                 Ar* + Ar + Ar -> Ar + Ar + Ar    : 5077.02776
                 Arp + Ar + Ar -> Ar2p + Ar       : {81595.089 * (Tgas/300)^(-0.4)}'
  [../]

  [./Water]
    species = 'emliq OHm'
    reaction_coefficient_format = 'rate'
    use_log = true
    aux_species = 'H2O'
    block = 1
    reactions = 'emliq -> H + OHm : 1064
                 emliq + emliq -> H2 + OHm + OHm : 3.136e8'
  [../]
[]
