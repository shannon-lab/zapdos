dom0Scale = 1
dom0Size = 5E-6 #m
vhigh = -0.15 #kV

[GlobalParams]
  offset = 20
  potential_units = kV
  # potential_units = V
  use_moles = true
[]

[Mesh]
  [file]
    type = FileMeshGenerator
    file = 'micro_fe.msh'
  []
  [left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = file
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
  []
[]

[Executioner]
  type = Transient
  end_time = 6E-6
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 preonly 1e-3'
  nl_rel_tol = 1e-4
  nl_abs_tol = 7.6e-5
  dtmin = 1e-15
  dtmax = 0.01E-7
  [TimeSteppers]
    [Adaptive]
      type = IterationAdaptiveDT
      cutback_factor = 0.4
      dt = 1e-12
      growth_factor = 1.2
      optimal_iterations = 15
    []
  []
[]

[Outputs]
  perf_graph = true
  print_linear_residuals = false
  [out]
    type = Exodus
    #       execute_on = 'final'
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
    mean_en = mean_en
    block = 0
    position_units = ${dom0Scale}
  []
  [em_diffusion]
    type = CoeffDiffusion
    variable = em
    mean_en = mean_en
    block = 0
    position_units = ${dom0Scale}
  []
  [em_ionization]
    type = ElectronsFromIonization
    em = em
    variable = em
    mean_en = mean_en
    block = 0
    position_units = ${dom0Scale}
  []
  [em_log_stabilization]
    type = LogStabilizationMoles
    variable = em
    block = 0
  []
  # [em_advection_stabilization]
  #               type = EFieldArtDiff
  #               variable = em
  #               block = 0
  # []

  [potential_diffusion_dom1]
    type = CoeffDiffusionLin
    variable = potential
    block = 0
    position_units = ${dom0Scale}
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
  # [Arp_advection_stabilization]
  #               type = EFieldArtDiff
  #               variable = Arp
  #               block = 0
  # []

  [mean_en_time_deriv]
    type = ElectronTimeDerivative
    variable = mean_en
    block = 0
  []
  [mean_en_advection]
    type = EFieldAdvection
    variable = mean_en
    em = em
    block = 0
    position_units = ${dom0Scale}
  []
  [mean_en_diffusion]
    type = CoeffDiffusion
    variable = mean_en
    em = em
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
  # [mean_en_advection_stabilization]
  #               type = EFieldArtDiff
  #               variable = mean_en
  #               block = 0
  # []
[]

[Variables]
  [potential]
  []
  [em]
    block = 0
  []
  [Arp]
    block = 0
  []
  [mean_en]
    block = 0
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
  [em_lin]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [Arp_lin]
    order = CONSTANT
    family = MONOMIAL
    block = 0
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
  [Current_Arp]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [tot_gas_current]
    order = CONSTANT
    family = MONOMIAL
    block = 0
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
    type = PowerDep
    density_log = em
    art_diff = false
    potential_units = kV
    variable = PowerDep_em
    position_units = ${dom0Scale}
    block = 0
  []
  [PowerDep_Arp]
    type = PowerDep
    density_log = Arp
    art_diff = false
    potential_units = kV
    variable = PowerDep_Arp
    position_units = ${dom0Scale}
    block = 0
  []
  [ProcRate_el]
    type = ProcRate
    em = em
    proc = el
    variable = ProcRate_el
    position_units = ${dom0Scale}
    block = 0
  []
  [ProcRate_ex]
    type = ProcRate
    em = em
    proc = ex
    variable = ProcRate_ex
    position_units = ${dom0Scale}
    block = 0
  []
  [ProcRate_iz]
    type = ProcRate
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
  [x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
    block = 0
  []
  [rho]
    type = ParsedAux
    variable = rho
    coupled_variables = 'em_lin Arp_lin'
    expression = 'Arp_lin - em_lin'
    execute_on = 'timestep_end'
    block = 0
  []
  [tot_gas_current]
    type = ParsedAux
    variable = tot_gas_current
    coupled_variables = 'Current_em Current_Arp'
    expression = 'Current_em + Current_Arp'
    execute_on = 'timestep_end'
    block = 0
  []
  [em_lin]
    type = Density
    #               convert_moles = true
    variable = em_lin
    density_log = em
    block = 0
  []
  [Arp_lin]
    type = Density
    #               convert_moles = true
    variable = Arp_lin
    density_log = Arp
    block = 0
  []
  [Efield_g]
    type = Efield
    component = 0
    variable = Efield
    position_units = ${dom0Scale}
    block = 0
  []
  [Current_em]
    type = Current
    density_log = em
    variable = Current_em
    art_diff = false
    block = 0
    position_units = ${dom0Scale}
  []
  [Current_Arp]
    type = Current
    density_log = Arp
    variable = Current_Arp
    art_diff = false
    block = 0
    position_units = ${dom0Scale}
  []
  [EFieldAdvAux_em]
    type = EFieldAdvAux
    density_log = em
    variable = EFieldAdvAux_em
    block = 0
    position_units = ${dom0Scale}
  []
  [DiffusiveFlux_em]
    type = DiffusiveFlux
    density_log = em
    variable = DiffusiveFlux_em
    block = 0
    position_units = ${dom0Scale}
  []
[]

[BCs]
  [potential_left]
    type = NeumannCircuitVoltageMoles_KV
    variable = potential
    boundary = left
    function = potential_bc_func
    ip = Arp
    data_provider = data_provider
    em = em
    mean_en = mean_en
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
    boundary = right
    mean_en = mean_en
    r = 0.99
    position_units = ${dom0Scale}
  []

  [Arp_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = Arp
    boundary = right
    r = 0
    position_units = ${dom0Scale}
  []
  [Arp_physical_right_advection]
    type = HagelaarIonAdvectionBC
    variable = Arp
    boundary = right
    r = 0
    position_units = ${dom0Scale}
  []
  [mean_en_physical_right]
    type = HagelaarEnergyBC
    variable = mean_en
    boundary = right
    em = em
    ip = Arp
    r = 0.99
    position_units = ${dom0Scale}
  []
  [em_physical_left]
    type = HagelaarElectronBC
    variable = em
    boundary = 'left'
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
  []
  #       [sec_electrons_left]
  #               type = SecondaryElectronBC
  #               variable = em
  #               boundary = 'left'
  #               ip = Arp
  #               mean_en = mean_en
  #               r = 0
  #               position_units = ${dom0Scale}
  #       []
  [FieldEmission_left]
    type = FieldEmissionBC
    variable = em
    boundary = 'left'
    ip = Arp
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
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
    em = em
    ip = Arp
    r = 0
    position_units = ${dom0Scale}
  []
[]

[ICs]
  [em_ic]
    type = ConstantIC
    variable = em
    value = -21
    block = 0
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

  [potential_ic]
    type = FunctionIC
    variable = potential
    function = potential_ic_func
  []
  # [em_ic]
  #               type = RandomIC
  #               variable = em
  #               block = 0
  # []
  # [Arp_ic]
  #               type = RandomIC
  #               variable = Arp
  #               block = 0
  # []
  # [mean_en_ic]
  #               type = RandomIC
  #               variable = mean_en
  #               block = 0
  # []
  # [potential_ic]
  #               type = RandomIC
  #               variable = potential
  # []
[]

[Functions]
  [potential_bc_func]
    type = ParsedFunction
    symbol_names = 'period dutyCycle riseTime VHigh VLow'
    symbol_values = '3E-6 0.1 5E-7 ${vhigh} -0.001'
    expression = 'if((t % period) < dutyCycle*period           , VHigh                                                                  ,
                                 if((t % period) < dutyCycle*period + riseTime, ((VLow - VHigh)/riseTime) * ((t % period) - period * dutyCycle) + VHigh,
                                 if((t % period) < period - riseTime          , VLow                                                                                                                               ,
                                 if((t % period) < period                                         , ((VHigh - VLow)/riseTime) * ((t % period) - period) + VHigh            ,
                                        0))))'
  []
  [potential_ic_func]
    type = ParsedFunction
    expression = '-${vhigh} * (${dom0Size} - x) / ${dom0Size}'
  []
  [cathode_temperature]
    type = ParsedFunction
    expression = 1500
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
    user_se_coeff = 0.05
    user_work_function = 4.55 # eV
    user_field_enhancement = 55
    property_tables_file = td_argon_mean_en.txt
    block = 0
  []
[]
