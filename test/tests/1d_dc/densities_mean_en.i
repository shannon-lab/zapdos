dom0Scale = 1e-3
dom1Scale = 1e-7
# dom0Scale=1.1
# dom1Scale=1.1

[GlobalParams]
  offset = 20
  # offset = 0
  potential_units = kV
  use_moles = true
  # potential_units = V
[]

[Mesh]
  [file]
    type = FileMeshGenerator
    file = 'liquidNew.msh'
  []
  [interface]
    type = SideSetsBetweenSubdomainsGenerator
    primary_block = '0'
    paired_block = '1'
    new_boundary = 'master0_interface'
    input = file
  []
  [interface_again]
    type = SideSetsBetweenSubdomainsGenerator
    primary_block = '1'
    paired_block = '0'
    new_boundary = 'master1_interface'
    input = interface
  []
  [left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = interface_again
  []
  [right]
    type = SideSetsFromNormalsGenerator
    normals = '1 0 0'
    new_boundary = 'right'
    input = left
  []
[]

[Problem]
  type = FEProblem
  # kernel_coverage_check = false
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
    ksp_norm = none
  []
[]

[Executioner]
  type = Transient
  num_steps = 1
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 preonly 1e-3'
  nl_rel_tol = 1e-4
  nl_abs_tol = 7.6e-5
  dtmin = 1e-12
  l_max_its = 20
  [TimeSteppers]
    [Adaptive]
      type = IterationAdaptiveDT
      cutback_factor = 0.4
      dt = 1e-11
      growth_factor = 1.2
      optimal_iterations = 15
    []
  []
[]

[Outputs]
  perf_graph = true
  # print_linear_residuals = false
  [out]
    type = Exodus
    execute_on = 'final'
  []
  [dof_map]
    type = DOFMap
  []
[]

[Debug]
  show_var_residual_norms = true
[]

[UserObjects]
  [data_provider]
    type = ProvideMobility
    electrode_area = 5.02e-7 # Formerly 3.14e-6
    ballast_resist = 1e6
    e = 1.6e-19
    # electrode_area = 1.1
    # ballast_resist = 1.1
    # e = 1.1
  []
[]

[Kernels]
  [em_time_deriv]
    type = ElectronTimeDerivative
    variable = em
    block = 0
  []
  [em_advection]
    type = EFieldAdvection
    variable = em
    block = 0
    position_units = ${dom0Scale}
  []
  [em_diffusion]
    type = CoeffDiffusion
    variable = em
    block = 0
    position_units = ${dom0Scale}
  []
  [em_ionization]
    type = ElectronsFromIonization
    variable = em
    mean_en = mean_en
    em = em
    block = 0
    position_units = ${dom0Scale}
  []
  [em_log_stabilization]
    type = LogStabilizationMoles
    variable = em
    block = 0
  []

  [emliq_time_deriv]
    type = ElectronTimeDerivative
    variable = emliq
    block = 1
  []
  [emliq_advection]
    type = EFieldAdvection
    variable = emliq
    block = 1
    position_units = ${dom1Scale}
  []
  [emliq_diffusion]
    type = CoeffDiffusion
    variable = emliq
    block = 1
    position_units = ${dom1Scale}
  []
  [emliq_reactant_first_order_rxn]
    type = ReactantFirstOrderRxn
    variable = emliq
    block = 1
  []
  [emliq_water_bi_sink]
    type = ReactantAARxn
    variable = emliq
    block = 1
  []
  [emliq_log_stabilization]
    type = LogStabilizationMoles
    variable = emliq
    block = 1
  []

  [potential_diffusion_dom1]
    type = CoeffDiffusionLin
    variable = potential
    block = 0
    position_units = ${dom0Scale}
  []
  [potential_diffusion_dom2]
    type = CoeffDiffusionLin
    variable = potential
    block = 1
    position_units = ${dom1Scale}
  []
  [Arp_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = Arp
    block = 0
  []
  [em_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = em
    block = 0
  []
  [emliq_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = emliq
    block = 1
  []
  [OHm_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = OHm
    block = 1
  []

  [Arp_time_deriv]
    type = ElectronTimeDerivative
    variable = Arp
    block = 0
  []
  [Arp_advection]
    type = EFieldAdvection
    variable = Arp
    position_units = ${dom0Scale}
    block = 0
  []
  [Arp_diffusion]
    type = CoeffDiffusion
    variable = Arp
    block = 0
    position_units = ${dom0Scale}
  []
  [Arp_ionization]
    type = IonsFromIonization
    variable = Arp
    em = em
    mean_en = mean_en
    block = 0
    position_units = ${dom0Scale}
  []
  [Arp_log_stabilization]
    type = LogStabilizationMoles
    variable = Arp
    block = 0
  []

  [OHm_time_deriv]
    type = ElectronTimeDerivative
    variable = OHm
    block = 1
  []
  [OHm_advection]
    type = EFieldAdvection
    variable = OHm
    block = 1
    position_units = ${dom1Scale}
  []
  [OHm_diffusion]
    type = CoeffDiffusion
    variable = OHm
    block = 1
    position_units = ${dom1Scale}
  []
  [OHm_log_stabilization]
    type = LogStabilizationMoles
    variable = OHm
    block = 1
  []
  [OHm_product_first_order_rxn]
    type = ProductFirstOrderRxn
    variable = OHm
    v = emliq
    block = 1
  []
  [OHm_product_aabb_rxn]
    type = ProductAABBRxn
    variable = OHm
    v = emliq
    block = 1
  []

  [mean_en_time_deriv]
    type = ElectronTimeDerivative
    variable = mean_en
    block = 0
  []
  [mean_en_advection]
    type = EFieldAdvection
    variable = mean_en
    block = 0
    position_units = ${dom0Scale}
  []
  [mean_en_diffusion]
    type = CoeffDiffusion
    variable = mean_en
    block = 0
    position_units = ${dom0Scale}
  []
  [mean_en_joule_heating]
    type = JouleHeating
    variable = mean_en
    em = em
    block = 0
    position_units = ${dom0Scale}
  []
  [mean_en_ionization]
    type = ElectronEnergyLossFromIonization
    variable = mean_en
    em = em
    block = 0
    position_units = ${dom0Scale}
  []
  [mean_en_elastic]
    type = ElectronEnergyLossFromElastic
    variable = mean_en
    em = em
    block = 0
    position_units = ${dom0Scale}
  []
  [mean_en_excitation]
    type = ElectronEnergyLossFromExcitation
    variable = mean_en
    em = em
    block = 0
    position_units = ${dom0Scale}
  []
  [mean_en_log_stabilization]
    type = LogStabilizationMoles
    variable = mean_en
    block = 0
    offset = 15
  []
[]

[Variables]
  [potential]
  []
  [em]
    block = 0
  []
  [emliq]
    block = 1
    # scaling = 1e-5
  []

  [Arp]
    block = 0
  []

  [mean_en]
    block = 0
    # scaling = 1e-1
  []

  [OHm]
    block = 1
    # scaling = 1e-5
  []
[]

[AuxVariables]
  [e_temp]
    block = 0
    order = CONSTANT
    family = MONOMIAL
  []
  [x]
    order = CONSTANT
    family = MONOMIAL
  []
  [x_node]
  []
  [rho]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [rholiq]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  []
  [em_lin]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [emliq_lin]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  []
  [Arp_lin]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [OHm_lin]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  []
  [Efield]
    order = CONSTANT
    family = MONOMIAL
  []
  [Current_em]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [Current_emliq]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  []
  [Current_Arp]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [Current_OHm]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  []
  [tot_gas_current]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [tot_liq_current]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  []
  [tot_flux_OHm]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  []
  [EFieldAdvAux_em]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [DiffusiveFlux_em]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [EFieldAdvAux_emliq]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  []
  [DiffusiveFlux_emliq]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  []
  [PowerDep_em]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [PowerDep_Arp]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [ProcRate_el]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [ProcRate_ex]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [ProcRate_iz]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
[]

[AuxKernels]
  [PowerDep_em]
    type = ADPowerDep
    density_log = em
    art_diff = false
    potential_units = kV
    variable = PowerDep_em
    position_units = ${dom0Scale}
    block = 0
  []
  [PowerDep_Arp]
    type = ADPowerDep
    density_log = Arp
    art_diff = false
    potential_units = kV
    variable = PowerDep_Arp
    position_units = ${dom0Scale}
    block = 0
  []
  [ProcRate_el]
    type = ADProcRate
    em = em
    proc = el
    variable = ProcRate_el
    position_units = ${dom0Scale}
    block = 0
  []
  [ProcRate_ex]
    type = ADProcRate
    em = em
    proc = ex
    variable = ProcRate_ex
    position_units = ${dom0Scale}
    block = 0
  []
  [ProcRate_iz]
    type = ADProcRate
    em = em
    proc = iz
    variable = ProcRate_iz
    position_units = ${dom0Scale}
    block = 0
  []
  [e_temp]
    type = ElectronTemperature
    variable = e_temp
    electron_density = em
    mean_en = mean_en
    block = 0
  []
  [x_g]
    type = Position
    variable = x
    position_units = ${dom0Scale}
    block = 0
  []
  [x_l]
    type = Position
    variable = x
    position_units = ${dom1Scale}
    block = 1
  []
  [x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
    block = 0
  []
  [x_nl]
    type = Position
    variable = x_node
    position_units = ${dom1Scale}
    block = 1
  []
  [rho]
    type = ParsedAux
    variable = rho
    coupled_variables = 'em_lin Arp_lin'
    expression = 'Arp_lin - em_lin'
    execute_on = 'timestep_end'
    block = 0
  []
  [rholiq]
    type = ParsedAux
    variable = rholiq
    coupled_variables = 'emliq_lin OHm_lin' # H3Op_lin OHm_lin'
    expression = '-emliq_lin - OHm_lin' # 'H3Op_lin - em_lin - OHm_lin'
    execute_on = 'timestep_end'
    block = 1
  []
  [tot_gas_current]
    type = ParsedAux
    variable = tot_gas_current
    coupled_variables = 'Current_em Current_Arp'
    expression = 'Current_em + Current_Arp'
    execute_on = 'timestep_end'
    block = 0
  []
  [tot_liq_current]
    type = ParsedAux
    variable = tot_liq_current
    coupled_variables = 'Current_emliq Current_OHm' # Current_H3Op Current_OHm'
    expression = 'Current_emliq + Current_OHm' # + Current_H3Op + Current_OHm'
    execute_on = 'timestep_end'
    block = 1
  []
  [em_lin]
    type = Density
    variable = em_lin
    density_log = em
    block = 0
  []
  [emliq_lin]
    type = Density
    variable = emliq_lin
    density_log = emliq
    block = 1
  []
  [Arp_lin]
    type = Density
    variable = Arp_lin
    density_log = Arp
    block = 0
  []
  [OHm_lin]
    type = Density
    variable = OHm_lin
    density_log = OHm
    block = 1
  []
  [Efield_g]
    type = Efield
    component = 0
    variable = Efield
    position_units = ${dom0Scale}
    block = 0
  []
  [Efield_l]
    type = Efield
    component = 0
    variable = Efield
    position_units = ${dom1Scale}
    block = 1
  []
  [Current_em]
    type = ADCurrent
    density_log = em
    variable = Current_em
    art_diff = false
    block = 0
    position_units = ${dom0Scale}
  []
  [Current_emliq]
    type = ADCurrent
    density_log = emliq
    variable = Current_emliq
    art_diff = false
    block = 1
    position_units = ${dom1Scale}
  []
  [Current_Arp]
    type = ADCurrent
    density_log = Arp
    variable = Current_Arp
    art_diff = false
    block = 0
    position_units = ${dom0Scale}
  []
  [Current_OHm]
    block = 1
    type = ADCurrent
    density_log = OHm
    variable = Current_OHm
    art_diff = false
    position_units = ${dom1Scale}
  []
  [tot_flux_OHm]
    block = 1
    type = ADTotalFlux
    density_log = OHm
    variable = tot_flux_OHm
  []
  [EFieldAdvAux_em]
    type = ADEFieldAdvAux
    density_log = em
    variable = EFieldAdvAux_em
    block = 0
    position_units = ${dom0Scale}
  []
  [DiffusiveFlux_em]
    type = ADDiffusiveFlux
    density_log = em
    variable = DiffusiveFlux_em
    block = 0
    position_units = ${dom0Scale}
  []
  [EFieldAdvAux_emliq]
    type = ADEFieldAdvAux
    density_log = emliq
    variable = EFieldAdvAux_emliq
    block = 1
    position_units = ${dom1Scale}
  []
  [DiffusiveFlux_emliq]
    type = ADDiffusiveFlux
    density_log = emliq
    variable = DiffusiveFlux_emliq
    block = 1
    position_units = ${dom1Scale}
  []
[]

[InterfaceKernels]
  [em_advection]
    type = InterfaceAdvection
    mean_en_neighbor = mean_en
    neighbor_var = em
    variable = emliq
    boundary = master1_interface
    position_units = ${dom1Scale}
    neighbor_position_units = ${dom0Scale}
  []
  [em_diffusion]
    type = InterfaceLogDiffusionElectrons
    mean_en_neighbor = mean_en
    neighbor_var = em
    variable = emliq
    boundary = master1_interface
    position_units = ${dom1Scale}
    neighbor_position_units = ${dom0Scale}
  []
[]

[BCs]
  [potential_left]
    type = NeumannCircuitVoltageMoles_KV
    variable = potential
    boundary = left
    function = potential_bc_func
    ions = Arp
    data_provider = data_provider
    electrons = em
    electron_energy = mean_en
    r = 0
    position_units = ${dom0Scale}
    emission_coeffs = 0.05
  []
  [potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  []
  [em_physical_right]
    type = HagelaarElectronBC
    variable = em
    boundary = 'master0_interface'
    electron_energy = mean_en
    r = 0.99
    position_units = ${dom0Scale}
  []
  [Arp_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = Arp
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [Arp_physical_right_advection]
    type = HagelaarIonAdvectionBC
    variable = Arp
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [mean_en_physical_right]
    type = HagelaarEnergyBC
    variable = mean_en
    boundary = 'master0_interface'
    electrons = em
    r = 0.99
    position_units = ${dom0Scale}
  []
  [em_physical_left]
    type = HagelaarElectronBC
    variable = em
    boundary = 'left'
    electron_energy = mean_en
    r = 0
    position_units = ${dom0Scale}
  []
  [sec_electrons_left]
    type = SecondaryElectronBC
    variable = em
    boundary = 'left'
    ions = Arp
    electron_energy = mean_en
    r = 0
    position_units = ${dom0Scale}
    emission_coeffs = 0.05
  []
  [Arp_physical_left_diffusion]
    type = HagelaarIonDiffusionBC
    variable = Arp
    boundary = 'left'
    r = 0
    position_units = ${dom0Scale}
  []
  [Arp_physical_left_advection]
    type = HagelaarIonAdvectionBC
    variable = Arp
    boundary = 'left'
    r = 0
    position_units = ${dom0Scale}
  []
  [mean_en_physical_left]
    type = HagelaarEnergyBC
    variable = mean_en
    boundary = 'left'
    electrons = em
    r = 0
    position_units = ${dom0Scale}
  []
  [emliq_right]
    type = DCIonBC
    variable = emliq
    boundary = right
    position_units = ${dom1Scale}
  []
  [OHm_physical]
    type = DCIonBC
    variable = OHm
    boundary = 'right'
    position_units = ${dom1Scale}
  []
[]

[ICs]
  [em_ic]
    type = ConstantIC
    variable = em
    value = -21
    block = 0
  []
  [emliq_ic]
    type = ConstantIC
    variable = emliq
    value = -21
    block = 1
  []
  [Arp_ic]
    type = ConstantIC
    variable = Arp
    value = -21
    block = 0
  []
  [mean_en_ic]
    type = ConstantIC
    variable = mean_en
    value = -20
    block = 0
  []
  [OHm_ic]
    type = ConstantIC
    variable = OHm
    value = -15.6
    block = 1
  []
  [potential_ic]
    type = FunctionIC
    variable = potential
    function = potential_ic_func
  []
  # [em_ic]
  #   type = RandomIC
  #   variable = em
  #   block = 0
  #   min = -21.5
  #   max = -20.5
  # []
  # [emliq_ic]
  #   type = RandomIC
  #   variable = emliq
  #   block = 1
  #   min = -21.5
  #   max = -20.5
  # []
  # [Arp_ic]
  #   type = RandomIC
  #   variable = Arp
  #   block = 0
  #   min = -21.5
  #   max = -20.5
  # []
  # [mean_en_ic]
  #   type = RandomIC
  #   variable = mean_en
  #   block = 0
  #   min = -20.5
  #   max = -19.5
  # []
  #   type = RandomIC
  #   variable = OHm
  #   block = 1
  #   min = -16.1
  #   max = -15.1
  # []
[]

[Functions]
  [potential_bc_func]
    type = ParsedFunction
    # expression = '1.25*tanh(1e6*t)'
    expression = 1.25
  []
  [potential_ic_func]
    type = ParsedFunction
    expression = '-1.25 * (1.0001e-3 - x)'
  []
[]

[Materials]
  [gas_block]
    type = Gas
    interp_trans_coeffs = true
    interp_elastic_coeff = true
    ramp_trans_coeffs = false
    em = em
    ip = Arp
    mean_en = mean_en
    user_se_coeff = .05
    block = 0
    property_tables_file = td_argon_mean_en.txt
  []
  [water_block]
    type = Water
    block = 1
  []
  [field_solver]
    type = FieldSolverMaterial
    potential = potential
    block = '0 1'
  []
[]
