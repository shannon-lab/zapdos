dom0Scale = 1
dom0Size = 2E-6 #m
vhigh = 230E-3 #kV
relaxTime = 1e-9 #s
resistance = 1
area = 5.02e-7 # Formerly 3.14e-6

[GlobalParams]
  potential_units = kV
  use_moles = true
[]

[Mesh]
  [file]
    type = FileMeshGenerator
    file = 'Geometry.msh'
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
  #        kernel_coverage_check = false
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Executioner]
  type = Transient
  #       line_search = none
  end_time = 10E-6

  steady_state_detection = 1
  steady_state_tolerance = 1E-15
  steady_state_start_time = '${fparse 3 * relaxTime}'

  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type'
  petsc_options_value = 'lu'
  line_search = 'none'

  nl_abs_tol = 2e-6

  dtmin = 1e-15
  # dtmax = 1E-6
  nl_max_its = 50
  [TimeSteppers]
    [Adaptive]
      type = IterationAdaptiveDT
      cutback_factor = 0.4
      dt = 1e-13
      growth_factor = 1.2
      optimal_iterations = 20
    []
  []
[]

[Outputs]
  perf_graph = true
  print_linear_residuals = false
  [out]
    type = Exodus
    execute_on = 'final'
  []
[]

[Debug]
  show_var_residual_norms = true
[]

[UserObjects]
  [current_density_user_object]
    type = CurrentDensityShapeSideUserObject
    boundary = left
    potential = potential
    em = em
    ip = Arp
    mean_en = mean_en
    execute_on = 'linear nonlinear'
  []
  [data_provider]
    type = ProvideMobility
    electrode_area = ${area}
    ballast_resist = ${resistance}
    e = 1.6e-19
  []
[]

[Kernels]
  ## Stabilization
  [Arp_log_stabilization]
    type = LogStabilizationMoles
    variable = Arp
    offset = 20
    block = 0
  []
  [em_log_stabilization]
    type = LogStabilizationMoles
    variable = em
    offset = 20
    block = 0
  []
  [mean_en_log_stabilization]
    type = LogStabilizationMoles
    variable = mean_en
    block = 0
    offset = 35
  []
  #       [mean_en_advection_stabilization]
  #               type = EFieldArtDiff
  #               variable = mean_en
  #               block = 0
  #       []

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
    em = em
    variable = em
    mean_en = mean_en
    block = 0
    position_units = ${dom0Scale}
  []

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
    type = DensityMoles
    #               convert_moles = true
    variable = em_lin
    density_log = em
    block = 0
  []
  [Arp_lin]
    type = DensityMoles
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
    type = ADCurrent
    density_log = em
    variable = Current_em
    art_diff = false
    block = 0
    position_units = ${dom0Scale}
  []
  [Current_Arp]
    type = ADCurrent
    density_log = Arp
    variable = Current_Arp
    art_diff = false
    block = 0
    position_units = ${dom0Scale}
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
[]

[BCs]
  ## Potential boundary conditions ##
  #       [potential_left]
  #               type = NeumannCircuitVoltageMoles_KV
  #               variable = potential
  #               boundary = left
  #               function = potential_bc_func
  #               ions = Arp
  #               data_provider = data_provider
  #               electrons = em
  #               electron_energy = mean_en
  #               r = 0
  #               position_units = ${dom0Scale}
  #       []

  [potential_left]
    boundary = left
    type = PenaltyCircuitPotential
    variable = potential
    current = current_density_user_object
    surface_potential = -${vhigh}
    surface = 'cathode'
    penalty = 1000
    data_provider = data_provider
    electrons = em
    ions = Arp
    electron_energy = mean_en
    area = ${area}
    potential_units = 'kV'
    position_units = ${dom0Scale}
    resistance = ${resistance}
  []

  [potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  []

  ## Electron boundary conditions ##
  [Emission_left]
    type = SchottkyEmissionBC
    #               type = SecondaryElectronBC
    variable = em
    boundary = 'left'
    ions = Arp
    electron_energy = mean_en
    r = 1
    position_units = ${dom0Scale}
    tau = ${relaxTime}
    relax = true
    emission_coeffs = 0.02
  []

  # [em_physical_left]
  #       type = HagelaarElectronBC
  #       variable = em
  #       boundary = 'left'
  #       mean_en = mean_en
  #       r = 0
  #       position_units = ${dom0Scale}
  # []

  [em_physical_right]
    type = HagelaarElectronAdvectionBC
    variable = em
    boundary = right
    r = 0
    position_units = ${dom0Scale}
  []

  ## Argon boundary conditions ##
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

  ## Mean energy boundary conditions ##
  [mean_en_physical_left]
    type = HagelaarEnergyBC
    variable = mean_en
    boundary = 'left'
    electrons = em
    r = 0
    position_units = ${dom0Scale}
  []

  [mean_en_physical_right]
    type = HagelaarEnergyBC
    variable = mean_en
    boundary = right
    electrons = em
    r = 0
    position_units = ${dom0Scale}
  []
[]

[ICs]
  [potential_ic]
    type = FunctionIC
    variable = potential
    function = potential_ic_func
  []

  [em_ic]
    type = ConstantIC
    variable = em
    value = -30
    block = 0
  []

  [Arp_ic]
    type = ConstantIC
    variable = Arp
    value = -30
    block = 0
  []

  [mean_en_ic]
    type = ConstantIC
    variable = mean_en
    value = -25
    block = 0
  []
[]

[Functions]
  [potential_bc_func]
    type = ParsedFunction
    symbol_names = 'VHigh'
    symbol_values = '${vhigh}'
    expression = 'VHigh'
  []
  [potential_ic_func]
    type = ParsedFunction
    expression = '-${vhigh} * (${dom0Size} - x) / ${dom0Size}'
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
    user_se_coeff = 0.02
    user_work_function = 4.55 # eV
    user_field_enhancement = 55
    user_Richardson_coefficient = 80E4
    user_cathode_temperature = 1273
    property_tables_file = td_argon_mean_en.txt
    block = 0
  []
  [field_solver]
    type = FieldSolverMaterial
    potential = potential
  []
[]
