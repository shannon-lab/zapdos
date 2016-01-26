[GlobalParams]
  offset = 50
  potential_units = kV
[]

[Mesh]
  type = FileMesh
  file = 'just_plasma_reduced.msh'
  # type = GeneratedMesh
  # dim = 1
  # nx = 1
  # xmax = 1
[]

[MeshModifiers]
  [./left]
    type = SideSetsFromNormals
    normals = '-1 0 0'
    new_boundary = 'left'
  [../]
  [./right]
    type = SideSetsFromNormals
    normals = '1 0 0'
    new_boundary = 'right'
  [../]
[]

[Problem]
  type = FEProblem
  kernel_coverage_check = false
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  end_time = 1e-1
  solve_type = NEWTON
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 preonly 1e-3'
  # petsc_options = '-options_left -snes_test_display'
  # petsc_options_iname = '-snes_type'
  # petsc_options_value = 'test'
 nl_rel_tol = 1e-4
 nl_abs_tol = 2e-9
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
  print_linear_residuals = false
  [./out]
    type = Exodus
  [../]
  [./DOFMap]
    type = DOFMap
  [../]
[]

[Debug]
  show_var_residual_norms = true
[]

[UserObjects]
  [./data_provider]
    type = ProvideMobility
    # electrode_area = 1.1
    # ballast_resist = 1.1
    # e = 1.1
    electrode_area = 5.02e-7
    ballast_resist = 1e6
    e = 1.6e-19
  [../]
[]

[Kernels]
  [./em_time_deriv]
    type = ElectronTimeDerivative
    variable = em
  [../]
  [./em_advection]
    type = EFieldAdvectionElectrons
    variable = em
    potential = potential
    mean_en = mean_en
  [../]
  [./em_diffusion]
    type = CoeffDiffusionElectrons
    variable = em
    mean_en = mean_en
  [../]
  [./em_ionization]
    type = ElectronsFromIonization
    variable = em
    potential = potential
    mean_en = mean_en
  [../]
  [./em_log_stabilization]
    type = LogStabilizationMoles
    variable = em
  [../]

  [./potential_diffusion]
    type = CoeffDiffusionLin
    variable = potential
  [../]
  [./Arp_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = Arp
  [../]
  [./em_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = em
  [../]

  [./Arp_time_deriv]
    type = ElectronTimeDerivative
    variable = Arp
  [../]
  [./Arp_advection]
    type = EFieldAdvection
    variable = Arp
    potential = potential
  [../]
  [./Arp_diffusion]
    type = CoeffDiffusion
    variable = Arp
  [../]
  [./Arp_ionization]
    type = IonsFromIonization
    variable = Arp
    potential = potential
    em = em
    mean_en = mean_en
  [../]
  [./Arp_log_stabilization]
    type = LogStabilizationMoles
    variable = Arp
  [../]
  # [./Arp_advection_stabilization]
  #   type = EFieldArtDiff
  #   variable = Arp
  #   potential = potential
  # [../]

  [./mean_en_time_deriv]
    type = ElectronTimeDerivative
    variable = mean_en
  [../]
  [./mean_en_advection]
    type = EFieldAdvectionEnergy
    variable = mean_en
    potential = potential
    em = em
  [../]
  [./mean_en_diffusion]
    type = CoeffDiffusionEnergy
    variable = mean_en
    em = em
  [../]
  [./mean_en_joule_heating]
    type = JouleHeating
    variable = mean_en
    potential = potential
    em = em
  [../]
  [./mean_en_ionization]
    type = ElectronEnergyLossFromIonization
    variable = mean_en
    potential = potential
    em = em
  [../]
  [./mean_en_elastic]
    type = ElectronEnergyLossFromElastic
    variable = mean_en
    potential = potential
    em = em
  [../]
  [./mean_en_excitation]
    type = ElectronEnergyLossFromExcitation
    variable = mean_en
    potential = potential
    em = em
  [../]
  [./mean_en_log_stabilization]
    type = LogStabilizationMoles
    variable = mean_en
  [../]
[]

[Variables]
  [./potential]
  [../]
  [./em]
  [../]

  [./Arp]
  [../]

  [./mean_en]
  [../]
[]

[AuxVariables]
  [./e_temp]
  [../]
  [./x]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./rho]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./em_lin]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Arp_lin]
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
  [../]
  [./Current_Arp]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./tot_gas_current]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./EFieldAdvAux_em]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./DiffusiveFlux_em]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./e_temp]
    type = ElectronTemperature
    variable = e_temp
    electron_density = em
    mean_en = mean_en
  [../]
  [./x]
    type = Position
    variable = x
  [../]
  [./rho]
    type = ParsedAux
    variable = rho
    args = 'em_lin Arp_lin'
    function = 'Arp_lin - em_lin'
    execute_on = 'timestep_end'
  [../]
  [./tot_gas_current]
    type = ParsedAux
    variable = tot_gas_current
    args = 'Current_em Current_Arp'
    function = 'Current_em + Current_Arp'
    execute_on = 'timestep_end'
  [../]
  [./em_lin]
    type = Density
    variable = em_lin
    density_log = em
  [../]
  [./Arp_lin]
    type = Density
    variable = Arp_lin
    density_log = Arp
  [../]
  [./Efield]
    type = Efield
    potential = potential
    variable = Efield
  [../]
  [./Current_em]
    type = Current
    potential = potential
    density_log = em
    variable = Current_em
    art_diff = false
  [../]
  [./Current_Arp]
    type = Current
    potential = potential
    density_log = Arp
    variable = Current_Arp
    art_diff = false
  [../]
  [./EFieldAdvAux_em]
    type = EFieldAdvAux
    potential = potential
    density_log = em
    variable = EFieldAdvAux_em
  [../]
  [./DiffusiveFlux_em]
    type = DiffusiveFlux
    density_log = em
    variable = DiffusiveFlux_em
  [../]
[]

[BCs]
  [./potential_left]
    type = NeumannCircuitVoltageMoles_KV
    variable = potential
    boundary = left
    function = potential_bc_func
    ip = Arp
    data_provider = data_provider
    em = em
    mean_en = mean_en
    r = 0
  [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  [../]
  [./em_physical_right]
    type = HagelaarElectronBC
    variable = em
    boundary = 'right'
    potential = potential
    ip = Arp
    mean_en = mean_en
    r = 0.999
  [../]
  [./Arp_physical_right]
    type = HagelaarIonBC
    variable = Arp
    boundary = 'right'
    potential = potential
    r = 0.999
  [../]
  [./mean_en_bcs_right]
    type = HagelaarEnergyBC
    variable = mean_en
    boundary = 'right'
    potential = potential
    em = em
    ip = Arp
    r = 0.999
  [../]
  [./em_physical_left]
    type = HagelaarElectronBC
    variable = em
    boundary = 'left'
    potential = potential
    ip = Arp
    mean_en = mean_en
    r = 0
  [../]
  [./Arp_physical_left]
    type = HagelaarIonBC
    variable = Arp
    boundary = 'left'
    potential = potential
    r = 0
  [../]
  [./mean_en_bcs_left]
    type = HagelaarEnergyBC
    variable = mean_en
    boundary = 'left'
    potential = potential
    em = em
    ip = Arp
    r = 0
  [../]
[]

[ICs]
  [./em_ic]
    type = ConstantIC
    variable = em
    value = -23
  [../]
  [./Arp_ic]
    type = ConstantIC
    variable = Arp
    value = -23
  [../]
  [./mean_en_ic]
    type = ConstantIC
    variable = mean_en
    value = -22
  [../]
  [./potential_ic]
    type = FunctionIC
    variable = potential
    function = potential_ic_func
  [../]
  # [./u_ic]
  #   type = RandomIC
  #   variable = em
  # [../]
  # [./v_ic]
  #   type = RandomIC
  #   variable = Arp
  # [../]
  # [./w_ic]
  #   type = RandomIC
  #   variable = mean_en
  # [../]
  # [./p_ic]
  #   type = RandomIC
  #   variable = potential
  # [../]
[]

[Functions]
  [./potential_bc_func]
    type = ParsedFunction
    value = 1.25
  [../]
  [./potential_ic_func]
    type = ParsedFunction
    value = '-1.25 * (.001-x)'
  [../]
[]

[Materials]
  [./gas_block]
    type = Gas
    interp_trans_coeffs = true
    interp_elastic_coeff = true
    em = em
    potential = potential
    ip = Arp
    mean_en = mean_en
    block = 0
 [../]
  [./gas_boundary]
    type = Gas
    interp_trans_coeffs = true
    interp_elastic_coeff = true
    em = em
    potential = potential
    ip = Arp
    mean_en = mean_en
    boundary = 'left right'
 [../]
[]

# [Materials]
#   [./jac]
#     block = '0'
#     type = JacMat
#     mean_en = mean_en
#     em = em
#   [../]
#   [./jac_bnd]
#     boundary = 'left right'
#     type = JacMat
#     mean_en = mean_en
#     em = em
#   [../]
# []
