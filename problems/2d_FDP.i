dom0Scale=1e-3

[GlobalParams]
  offset = 20
  potential_units = kV
[]

[Mesh]
  # type = GeneratedMesh
  # nx = 1
  # xmax = 1.1
  # dim = 1
  # boundary_id = '0 1'
  # boundary_name = 'anode cathode'
  type = FileMesh
  file = '2d.msh'
  boundary_id = '10 11 12 13'
  boundary_name = 'cathode anode walls axis'
[]


[Problem]
  type = FEProblem
  coord_type = RZ
  kernel_coverage_check = false
[]

[Preconditioning]
  [./smp]
    type = FDP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  end_time = 1e-8
  solve_type = NEWTON
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor -ksp_converged_reason'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 preonly 1e-3'
  # petsc_options = '-snes_test_display'
  # petsc_options_iname = '-snes_type'
  # petsc_options_value = 'test'
 nl_rel_tol = 1e-4
  dtmin = 1e-12
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.4
    dt = 1e-9
    growth_factor = 1.2
   optimal_iterations = 15
  [../]
[]

[Outputs]
  print_perf_log = true
  print_linear_residuals = true
  [./out]
    type = Exodus
  [../]
[]

[Debug]
  show_var_residual_norms = true
[]

[Kernels]
  [./em_time_deriv]
    type = ElectronTimeDerivative
    variable = em
    block = 0
  [../]
  [./em_advection]
    type = EFieldAdvectionElectrons
    variable = em
    potential = potential
    mean_en = mean_en
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./em_diffusion]
    type = CoeffDiffusionElectrons
    variable = em
    mean_en = mean_en
    block = 0
    position_units = ${dom0Scale}
  [../]
  # [./em_ionization]
  #   type = ElectronsFromIonization
  #   variable = em
  #   potential = potential
  #   mean_en = mean_en
  #   block = 0
  #   position_units = ${dom0Scale}
  # [../]
  [./em_ionization]
    type = ElectronRateIonization
    variable = em
    mean_en = mean_en
    block = 0
  [../]
  [./em_log_stabilization]
    type = LogStabilizationMoles
    variable = em
    block = 0
  [../]
  [./em_advection_stabilization]
    type = EFieldArtDiff
    variable = em
    potential = potential
    block = 0
    position_units = ${dom0Scale}
  [../]

  [./potential_diffusion_dom1]
    type = CoeffDiffusionLin
    variable = potential
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./Arp_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = Arp
    block = 0
  [../]
  [./em_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = em
    block = 0
  [../]

  [./Arp_time_deriv]
    type = ElectronTimeDerivative
    variable = Arp
    block = 0
  [../]
  [./Arp_advection]
    type = EFieldAdvection
    variable = Arp
    potential = potential
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./Arp_diffusion]
    type = CoeffDiffusion
    variable = Arp
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./Arp_ionization]
    type = IonRateIonization
    variable = Arp
    em = em
    mean_en = mean_en
    block = 0
  [../]
  # [./Arp_ionization]
  #   type = IonsFromIonization
  #   variable = Arp
  #   potential = potential
  #   em = em
  #   mean_en = mean_en
  #   block = 0
  #   position_units = ${dom0Scale}
  # [../]
  [./Arp_log_stabilization]
    type = LogStabilizationMoles
    variable = Arp
    block = 0
  [../]
  [./Arp_advection_stabilization]
    type = EFieldArtDiff
    variable = Arp
    potential = potential
    block = 0
    position_units = ${dom0Scale}
  [../]

  [./mean_en_time_deriv]
    type = ElectronTimeDerivative
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
    type = CoeffDiffusionEnergy
    variable = mean_en
    em = em
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./mean_en_joule_heating]
    type = JouleHeating
    variable = mean_en
    potential = potential
    em = em
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./mean_en_ionization]
    type = ElectronEnergyRateIonization
    variable = mean_en
    em = em
    block = 0
  [../]
  [./mean_en_elastic]
    type = ElectronEnergyRateElastic
    variable = mean_en
    em = em
    block = 0
  [../]
  [./mean_en_excitation]
    type = ElectronEnergyRateExcitation
    variable = mean_en
    em = em
    block = 0
  [../]
  # [./mean_en_ionization]
  #   type = ElectronEnergyLossFromIonization
  #   variable = mean_en
  #   potential = potential
  #   em = em
  #   block = 0
  #   position_units = ${dom0Scale}
  # [../]
  # [./mean_en_elastic]
  #   type = ElectronEnergyLossFromElastic
  #   variable = mean_en
  #   potential = potential
  #   em = em
  #   block = 0
  #   position_units = ${dom0Scale}
  # [../]
  # [./mean_en_excitation]
  #   type = ElectronEnergyLossFromExcitation
  #   variable = mean_en
  #   potential = potential
  #   em = em
  #   block = 0
  #   position_units = ${dom0Scale}
  # [../]
  [./mean_en_log_stabilization]
    type = LogStabilizationMoles
    variable = mean_en
    block = 0
    offset = 15
  [../]
  [./mean_en_advection_stabilization]
    type = EFieldArtDiff
    variable = mean_en
    potential = potential
    block = 0
    position_units = ${dom0Scale}
  [../]
[]

[Variables]
  [./potential]
  [../]
  [./em]
    block = 0
  [../]

  [./Arp]
    block = 0
  [../]

  [./mean_en]
    block = 0
  [../]
[]

[AuxVariables]
  [./e_temp]
    block = 0
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
  [./em_lin]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  [../]
  [./Arp_lin]
    order = CONSTANT
    family = MONOMIAL
    block = 0
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
  [./Current_Arp]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  [../]
  [./tot_gas_current]
    order = CONSTANT
    family = MONOMIAL
    block = 0
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
  [./ProcRate_el]
   order = CONSTANT
   family = MONOMIAL
   block = 0
  [../]
  [./ProcRate_ex]
   order = CONSTANT
   family = MONOMIAL
   block = 0
  [../]
  [./ProcRate_iz]
   order = CONSTANT
   family = MONOMIAL
   block = 0
  [../]
[]

[AuxKernels]
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
  [./ProcRate_el]
    type = ProcRate
    em = em
    potential = potential
    proc = el
    variable = ProcRate_el
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./ProcRate_ex]
    type = ProcRate
    em = em
    potential = potential
    proc = ex
    variable = ProcRate_ex
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./ProcRate_iz]
    type = ProcRate
    em = em
    potential = potential
    proc = iz
    variable = ProcRate_iz
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./e_temp]
    type = ElectronTemperature
    variable = e_temp
    electron_density = em
    mean_en = mean_en
    block = 0
  [../]
  [./x_g]
    type = Position
    variable = x
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./rho]
    type = ParsedAux
    variable = rho
    args = 'em_lin Arp_lin'
    function = 'Arp_lin - em_lin'
    execute_on = 'timestep_end'
    block = 0
  [../]
  [./tot_gas_current]
    type = ParsedAux
    variable = tot_gas_current
    args = 'Current_em Current_Arp'
    function = 'Current_em + Current_Arp'
    execute_on = 'timestep_end'
    block = 0
  [../]
  [./em_lin]
    type = Density
    use_moles = true
    variable = em_lin
    density_log = em
    block = 0
  [../]
  [./Arp_lin]
    type = Density
    use_moles = true
    variable = Arp_lin
    density_log = Arp
    block = 0
  [../]
  [./Efield_g]
    type = Efield
    component = 0
    potential = potential
    variable = Efield
    position_units = ${dom0Scale}
    block = 0
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
  [./Current_Arp]
    type = Current
    potential = potential
    density_log = Arp
    variable = Current_Arp
    art_diff = false
    block = 0
    position_units = ${dom0Scale}
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
[]

[BCs]
  [./potential_cathode]
    type = CircuitDirichletPotential
    surface_potential = cathode_func
    current = cathode_flux
    boundary = cathode
    variable = potential
    surface = cathode
  [../]
  [./potential_anode]
    type = DirichletBC
    variable = potential
    boundary = anode
    value = 0
  [../]
  [./electrons]
    type = HagelaarElectronBC
    variable = em
    boundary = 'anode cathode walls'
    # boundary = 'anode cathode'
    potential = potential
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./sec_electrons]
    type = SecondaryElectronBC
    variable = em
    boundary = 'anode cathode walls'
    # boundary = 'anode cathode'
    potential = potential
    ip = Arp
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./ions_diffusion]
    type = HagelaarIonDiffusionBC
    variable = Arp
    boundary = 'anode cathode walls'
    # boundary = 'anode cathode'
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./ions_advection]
    type = HagelaarIonAdvectionBC
    variable = Arp
    boundary = 'anode cathode walls'
    # boundary = 'anode cathode'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./mean_en]
    type = HagelaarEnergyBC
    variable = mean_en
    boundary = 'anode cathode walls'
    # boundary = 'anode cathode'
    potential = potential
    em = em
    ip = Arp
    r = 0
    position_units = ${dom0Scale}
  [../]
[]

[ICs]
  [./em_ic]
    type = ConstantIC
    variable = em
    value = -21
    block = 0
  [../]
  [./Arp_ic]
    type = ConstantIC
    variable = Arp
    value = -21
    block = 0
  [../]
  [./mean_en_ic]
    type = ConstantIC
    variable = mean_en
    value = -20
    block = 0
  [../]
  [./potential_ic]
    type = ConstantIC
    variable = potential
    value = 0
  [../]
  # [./em_ic]
  #   type = RandomIC
  #   variable = em
  #   block = 0
  #   min = -21.5
  #   max = -20.5
  # [../]
  # [./Arp_ic]
  #   type = RandomIC
  #   variable = Arp
  #   block = 0
  #   min = -21.5
  #   max = -20.5
  # [../]
  # [./mean_en_ic]
  #   type = RandomIC
  #   variable = mean_en
  #   block = 0
  #   min = -20.5
  #   max = -19.5
  # [../]
  # [./potential_ic]
  #   type = RandomIC
  #   variable = potential
  #   min = -1
  #   max = 0
  # [../]
[]

[Materials]
  [./gas_block]
    type = Gas
    interp_trans_coeffs = false
    interp_elastic_coeff = true
    ramp_trans_coeffs = false
    use_moles = true
    em = em
    potential = potential
    ip = Arp
    mean_en = mean_en
    block = 0
 [../]
 # [./jac]
 #   type = JacMat
 #   mean_en = mean_en
 #   em = em
 #   block = '0'
 #  [../]
[]

[Postprocessors]
  [./cathode_flux]
    type = SideTotFluxIntegral
    execute_on = nonlinear
    # execute_on = linear
    boundary = cathode
    mobility = muArp
    potential = potential
    variable = Arp
    r = 0
    position_units = ${dom0Scale}
  [../]
[]

[Functions]
  [./cathode_func]
    type = ParsedFunction
    value = '-1.25 * tanh(1e6 * t)'
  [../]
[]
