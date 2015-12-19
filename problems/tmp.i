[GlobalParams]
[]

[Mesh]
  type = FileMesh
  file = 'liquidNew.msh'
[]

[MeshModifiers]
  [./interface]
    type = SideSetsBetweenSubdomains
    master_block = '0'
    paired_block = '1'
    new_boundary = 'master0_interface'
  [../]
  [./interface_again]
    type = SideSetsBetweenSubdomains
    master_block = '1'
    paired_block = '0'
    new_boundary = 'master1_interface'
  [../]
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
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  # type = Steady
  end_time = 1e-1
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 preonly 1e-3'
 nl_rel_tol = 1e-5
 nl_abs_tol = 3.2e-6
 # nl_max_its = 20
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
[]

[Debug]
  show_var_residual_norms = true
[]

[UserObjects]
  [./data_provider]
    type = ProvideMobility
    # electrode_area = 3.14e-6 # Formerly 3.14e-6
    electrode_area = 5.02e-7 # Formerly 3.14e-6
    # ballast_resist = 8.1e3
    ballast_resist = 1e6
    e = 1.6e-19
  [../]
[]

[Kernels]
  # em block
  [./em_time_deriv]
    type = ElectronTimeDerivative
    variable = em
  [../]
  [./em_advection]
    type = EFieldAdvection
    variable = em
    potential = potential
  [../]
  [./em_diffusion]
    type = CoeffDiffusion
    variable = em
  [../]
  [./em_ionization]
    type = ElectronsFromIonization
    variable = em
    potential = potential
    mean_en = mean_en
    block = 0
  [../]
  [./em_log_stabilization]
    type = LogStabilizationMoles
    variable = em
    offset = 50
  [../]
  # [./em_advection_stabilization]
  #   type = EFieldArtDiff
  #   variable = em
  #   potential = potential
  # [../]
  [./em_reactant_first_order_rxn]
    type = ReactantFirstOrderRxn
    variable = em
    block = 1
  [../]
  [./em_water_bi_sink]
    type = ReactantAARxn
    variable = em
    block = 1
  [../]

  [./potential_diffusion]
    type = CoeffDiffusionLin
    variable = potential
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
  [../]
  [./OHm_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = OHm
    block = 1
  [../]
  # [./H3Op_charge_source]
  #   type = ChargeSourceMoles_KV
  #   variable = potential
  #   charged = H3Op
  #   block = 1
  # [../]

  [./Arp_time_deriv]
    type = ElectronTimeDerivative
    variable = Arp
    block = 0
  [../]
  [./Arp_advection]
    type = EFieldAdvection
    variable = Arp
    potential = potential
    block = 0
  [../]
  [./Arp_diffusion]
    type = CoeffDiffusion
    variable = Arp
    block = 0
  [../]
  [./Arp_ionization]
    type = IonsFromIonization
    variable = Arp
    potential = potential
    em = em
    mean_en = mean_en
    block = 0
  [../]
  [./Arp_log_stabilization]
    type = LogStabilizationMoles
    offset = 50
    variable = Arp
    block = 0
  [../]
  # [./Arp_advection_stabilization]
  #   type = EFieldArtDiff
  #   variable = Arp
  #   potential = potential
  #   block = 0
  # [../]

  [./OHm_time_deriv]
    type = ElectronTimeDerivative
    variable = OHm
    block = 1
  [../]
  [./OHm_advection]
    type = EFieldAdvection
    variable = OHm
    potential = potential
    block = 1
  [../]
  [./OHm_diffusion]
    type = CoeffDiffusion
    variable = OHm
    block = 1
  [../]
  [./OHm_log_stabilization]
    type = LogStabilizationMoles
    offset = 50
    variable = OHm
    block = 1
  [../]
  # [./OHm_advection_stabilization]
  #   type = EFieldArtDiff
  #   variable = OHm
  #   potential = potential
  #   block = 1
  # [../]
  [./OHm_product_first_order_rxn]
    type = ProductFirstOrderRxn
    variable = OHm
    v = em
    block = 1
  [../]
  [./OHm_product_aabb_rxn]
    type = ProductAABBRxn
    variable = OHm
    v = em
    block = 1
  [../]

  # [./H3Op_time_deriv]
  #   type = ElectronTimeDerivative
  #   variable = H3Op
  #   block = 1
  # [../]
  # [./H3Op_advection]
  #   type = EFieldAdvection
  #   variable = H3Op
  #   potential = potential
  #   block = 1
  # [../]
  # [./H3Op_diffusion]
  #   type = CoeffDiffusion
  #   variable = H3Op
  #   block = 1
  # [../]
  # [./H3Op_log_stabilization]
  #   type = LogStabilizationMoles
  #   offset = 50
  #   variable = H3Op
  #   block = 1
  # [../]
  # # [./H3Op_advection_stabilization]
  # #   type = EFieldArtDiff
  # #   variable = H3Op
  # #   potential = potential
  # #   block = 1
  # #   scale = 1
  # # [../]

  [./mean_en_time_deriv]
    type = ElectronTimeDerivative
    variable = mean_en
    block = 0
  [../]
  [./mean_en_advection]
    type = EFieldAdvection
    variable = mean_en
    potential = potential
    block = 0
  [../]
  [./mean_en_diffusion]
    type = CoeffDiffusion
    variable = mean_en
    block = 0
  [../]
  [./mean_en_ionization]
    type = ElectronEnergyLossFromIonization
    variable = mean_en
    potential = potential
    em = em
    block = 0
  [../]
  [./mean_en_elastic]
    type = ElectronEnergyLossFromElastic
    variable = mean_en
    potential = potential
    em = em
    block = 0
  [../]
  [./mean_en_excitation]
    type = ElectronEnergyLossFromExcitation
    variable = mean_en
    potential = potential
    em = em
    block = 0
  [../]
  [./mean_en_log_stabilization]
    type = LogStabilizationMoles
    variable = mean_en
    offset = 50
    block = 0
  [../]
  # [./mean_en_advection_stabilization]
  #   type = EFieldArtDiff
  #   variable = mean_en
  #   potential = potential
  # [../]
[]

[Variables]
  [./potential]
  [../]
  [./em]
  [../]

  [./Arp]
    block = 0
  [../]

  [./OHm]
    block = 1
  [../]
  # [./H3Op]
  #   block = 1
  # [../]

  [./mean_en]
    block = 0
  [../]
[]

[AuxVariables]
  [./x]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./rho]
    block = 0
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./rholiq]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./em_lin]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Arp_lin]
    block = 0
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./OHm_lin]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  # [./H3Op_lin]
  #   block = 1
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
  [./Efield]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Current_em]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Current_Arp]
    block = 0
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Current_OHm]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  # [./Current_H3Op]
  #   block = 1
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
  [./tot_gas_current]
    block = 0
    order = CONSTANT
    family = MONOMIAL
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
  [./adv_flux_OHm]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./diff_flux_OHm]
    block = 1
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
    block = 0
  [../]
  [./rholiq]
    type = ParsedAux
    variable = rholiq
    args = 'em_lin OHm_lin' # H3Op_lin OHm_lin'
    function = '-em_lin - OHm_lin' # 'H3Op_lin - em_lin - OHm_lin'
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
    args = 'Current_em Current_OHm' # Current_H3Op Current_OHm'
    function = 'Current_em + Current_OHm' # + Current_H3Op + Current_OHm'
    execute_on = 'timestep_end'
    block = 1
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
    block = 0
  [../]
  [./OHm_lin]
    type = Density
    variable = OHm_lin
    density_log = OHm
    block = 1
  [../]
  # [./H3Op_lin]
  #   type = Density
  #   variable = H3Op_lin
  #   density_log = H3Op
  #   block = 1
  # [../]
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
    block = 0
    type = Current
    potential = potential
    density_log = Arp
    variable = Current_Arp
    art_diff = false
  [../]
  [./Current_OHm]
    block = 1
    type = Current
    potential = potential
    density_log = OHm
    variable = Current_OHm
    art_diff = false
  [../]
  # [./Current_H3Op]
  #   block = 1
  #   type = Current
  #   potential = potential
  #   density_log = H3Op
  #   variable = Current_H3Op
  #   art_diff = false
  # [../]
  [./tot_flux_OHm]
    block = 1
    type = TotalFlux
    potential = potential
    density_log = OHm
    variable = tot_flux_OHm
  [../]
  [./adv_flux_OHm]
    block = 1
    type = EFieldAdvAux
    potential = potential
    density_log = OHm
    variable = adv_flux_OHm
  [../]
  [./diff_flux_OHm]
    block = 1
    type = DiffusiveFlux
    density_log = OHm
    variable = diff_flux_OHm
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
  [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  [../]
  [./em_left]
    type = DCElectronBC
    variable = em
    boundary = left
    potential = potential
    ip = Arp
  [../]
  [./em_right]
    type = DCIonBC
    variable = em
    boundary = right
    potential = potential
  [../]
  [./Arp_physical]
    type = DCIonBC
    variable = Arp
    boundary = 'left'
    potential = potential
  [../]
  [./mean_en_bc]
    type = DCIonBC
    variable = mean_en
    boundary = 'left right'
    potential = potential
  [../]
  [./OHm_physical]
    type = DCIonBC
    variable = OHm
    boundary = 'right'
    potential = potential
  [../]
[]

[ICs]
  [./em_ic]
    type = ConstantIC
    variable = em
    value = -17
  [../]
  [./Arp_ic]
    type = ConstantIC
    variable = Arp
    value = -17
    block = 0
  [../]
  [./mean_en_ic]
    type = ConstantIC
    variable = mean_en
    value = -17
    block = 0
  [../]
  # [./potential_ic]
  #   type = FunctionIC
  #   variable = potential
  #   function = potential_ic_func
  #   block = 0
  # [../]
  [./potential_ic]
    type = ConstantIC
    variable = potential
    value = 0
  [../]

  [./OHm_ic]
    type = ConstantIC
    variable = OHm
    value = -15.6
    block = 1
  [../]
  # [./H3Op_ic]
  #   type = ConstantIC
  #   variable = H3Op
  #   value = .0455
  #   block = 1
  # [../]
[]

[Functions]
  [./potential_bc_func]
    type = ParsedFunction
    # value = '1.25*tanh(1e6*t)'
    value = 1.25
  [../]
  # [./potential_ic_func]
  #   type = ParsedFunction
  #   value = -1.25*(.00105-x)
  # [../]
[]

[Materials]
  [./argon_block]
    interp_trans_coeffs = false
    interp_elastic_coeff = true
    block = 0
    type = ArgonConstTD
    em = em
    potential = potential
    ip = Arp
 [../]
 [./water_block]
   type = Water
   block = 1
   potential = potential
 [../]
[]

# [Adaptivity]
#   marker = error_frac
#   max_h_level = 3
#   [./Indicators]
#     [./temp_jump]
#       type = GradientJumpIndicator
#       variable = rholiq
#       scale_by_flux_faces = true
#     [../]
#   [../]
#   [./Markers]
#     [./error_frac]
#       type = ErrorFractionMarker
#       coarsen = 0.1
#       indicator = temp_jump
#       refine = 0.6
#     [../]
#   [../]
# []
