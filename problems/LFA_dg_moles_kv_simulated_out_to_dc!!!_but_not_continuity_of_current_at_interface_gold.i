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
 nl_rel_tol = 1e-50
 nl_abs_tol = 4e-8
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
    ballast_resist = 8.1e3
    # ballast_resist = 1e6
    e = 1.6e-19
  [../]
[]

[Kernels]
  # em block
  [./em_time_deriv]
    type = ElectronTimeDerivative
    variable = em
    block = 0
  [../]
  [./em_advection]
    type = EFieldAdvection
    variable = em
    potential = potential
    block = 0
  [../]
  [./em_diffusion]
    type = CoeffDiffusion
    variable = em
    block = 0
  [../]
  [./em_ionization]
    type = ElectronsFromIonizationLFA_KV
    variable = em
    potential = potential
    block = 0
  [../]
  [./em_log_stabilization]
    type = LogStabilizationMoles
    variable = em
    offset = 50
    block = 0
  [../]

  # emliq block
  [./emliq_time_deriv]
    type = ElectronTimeDerivative
    variable = emliq
    block = 1
  [../]
  [./emliq_advection]
    type = EFieldAdvection
    variable = emliq
    potential = potentialliq
    block = 1
  [../]
  [./emliq_diffusion]
    type = CoeffDiffusion
    variable = emliq
    block = 1
  [../]
  [./emliq_log_stabilization]
    type = LogStabilizationMoles
    offset = 50
    variable = emliq
    block = '1'
  [../]
  [./emliq_reactant_first_order_rxn]
    type = ReactantFirstOrderRxn
    variable = emliq
    block = 1
  [../]
  [./emliq_water_bi_sink]
    type = ReactantAARxn
    variable = emliq
    block = 1
  [../]

  # potential block
  [./potential_diffusion]
    type = CoeffDiffusionLin
    # type = Diffusion
    variable = potential
    block = 0
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

  # potentialliq block
  [./potentialliq_diffusion]
    type = CoeffDiffusionLin
    # type = Diffusion
    variable = potentialliq
    block = 1
  [../]
  [./emliq_charge_source]
    type = ChargeSourceMoles_KV
    variable = potentialliq
    charged = emliq
    block = 1
  [../]
  # [./Clm_charge_source]
  #   type = ChargeSourceMoles_KV
  #   variable = potentialliq
  #   charged = Clm
  #   block = 1
  # [../]
  [./OHm_charge_source]
    type = ChargeSourceMoles_KV
    variable = potentialliq
    charged = OHm
    block = 1
  [../]
  [./H3Op_charge_source]
    type = ChargeSourceMoles_KV
    variable = potentialliq
    charged = H3Op
    block = 1
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
    block = 0
  [../]
  [./Arp_diffusion]
    type = CoeffDiffusion
    variable = Arp
    block = 0
  [../]
  [./Arp_ionization]
    type = IonsFromIonizationLFA_KV
    variable = Arp
    potential = potential
    em = em
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

  # [./Clm_time_deriv]
  #   type = ElectronTimeDerivative
  #   variable = Clm
  #   block = 1
  # [../]
  # [./Clm_advection]
  #   type = EFieldAdvection
  #   variable = Clm
  #   potential = potentialliq
  #   block = 1
  # [../]
  # [./Clm_diffusion]
  #   type = CoeffDiffusion
  #   variable = Clm
  #   block = 1
  # [../]
  # [./Clm_log_stabilization]
  #   type = LogStabilizationMoles
  #   offset = 50
  #   variable = Clm
  #   block = 1
  # [../]
  # [./Clm_advection_stabilization]
  #   type = EFieldArtDiff
  #   variable = Clm
  #   potential = potentialliq
  #   block = 1
  #   scale = 1
  # [../]

  [./OHm_time_deriv]
    type = ElectronTimeDerivative
    variable = OHm
    block = 1
  [../]
  [./OHm_advection]
    type = EFieldAdvection
    variable = OHm
    potential = potentialliq
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
  [./OHm_advection_stabilization]
    type = EFieldArtDiff
    variable = OHm
    potential = potentialliq
    block = 1
  [../]
  [./OHm_product_first_order_rxn]
    type = ProductFirstOrderRxn
    variable = OHm
    v = emliq
    block = 1
  [../]
  [./OHm_product_aabb_rxn]
    type = ProductAABBRxn
    variable = OHm
    v = emliq
    block = 1
  [../]

  [./H3Op_time_deriv]
    type = ElectronTimeDerivative
    variable = H3Op
    block = 1
  [../]
  [./H3Op_advection]
    type = EFieldAdvection
    variable = H3Op
    potential = potentialliq
    block = 1
  [../]
  [./H3Op_diffusion]
    type = CoeffDiffusion
    variable = H3Op
    block = 1
  [../]
  [./H3Op_log_stabilization]
    type = LogStabilizationMoles
    offset = 50
    variable = H3Op
    block = 1
  [../]
  [./H3Op_advection_stabilization]
    type = EFieldArtDiff
    variable = H3Op
    potential = potentialliq
    block = 1
    scale = 1
  [../]
[]

[DGKernels]
  [./em_dg_advection_interface]
    type = DGAdvectionInterface
    variable = em
    neighbor_var = emliq
    boundary = master0_interface
    potential = potential
    potential_neighbor = potentialliq
  [../]
  [./em_dg_diffusion_interface]
    type = DGMatDiffusionLogInt
    variable = em
    neighbor_var = emliq
    boundary = master0_interface
  [../]
  [./em_penalty]
    type = DGPenaltyTiedValue
    variable = em
    neighbor_var = emliq
    boundary = master0_interface
  [../]

  [./potential_dg_diffusion_interface]
   type = DGMatDiffusionInt
   # type = DGDiffusionInt
   variable = potential
   neighbor_var = potentialliq
   boundary = master0_interface
 [../]

 # [./Clm_dg_advection]
 #   type = DGEFieldAdvection
 #   variable = Clm
 #   potential = potentialliq
 #   block = 1
 # [../]
 # [./Clm_dg_diffusion]
 #   type = DGCoeffDiffusion
 #   sigma = 6
 #   epsilon = -1
 #   variable = Clm
 #   block = 1
 # [../]

 # [./OHm_dg_advection]
 #   type = DGEFieldAdvection
 #   variable = OHm
 #   potential = potentialliq
 #   block = 1
 # [../]
 # [./OHm_dg_diffusion]
 #   type = DGCoeffDiffusion
 #   sigma = 6
 #   epsilon = -1
 #   variable = OHm
 #   block = 1
 # [../]

 # [./H3Op_dg_advection]
 #   type = DGEFieldAdvection
 #   variable = H3Op
 #   potential = potentialliq
 #   block = 1
 # [../]
 # [./H3Op_dg_diffusion]
 #   type = DGCoeffDiffusion
 #   sigma = 6
 #   epsilon = -1
 #   variable = H3Op
 #   block = 1
 # [../]


[]


[Variables]
  [./potential]
    block = 0
  [../]
  [./potentialliq]
    block = 1
  [../]

  [./em]
    block = 0
  [../]
  [./emliq]
    block = 1
  [../]

  [./Arp]
    block = 0
  [../]

  # [./Clm]
  #   # scaling = 1e4
  #   block = 1
  #   # order = FIRST
  #   # family = MONOMIAL
  # [../]
  [./OHm]
    block = 1
    # order = FIRST
    # family = MONOMIAL
  [../]
  [./H3Op]
    block = 1
    # order = FIRST
    # family = MONOMIAL
  [../]
[]

[AuxVariables]
  # [./h_size]
  #   block = '0 1'
  # [../]
  [./x]
    block = '0 1'
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
    block = 0
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./emliq_lin]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Arp_lin]
    block = 0
    order = CONSTANT
    family = MONOMIAL
  [../]
  # [./Clm_lin]
  #   block = 1
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
  [./OHm_lin]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./H3Op_lin]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Efield_gas]
    block = 0
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Efield_liq]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Current_em]
    block = 0
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Current_Arp]
    block = 0
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Current_emliq]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Current_OHm]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Current_H3Op]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  # [./Current_Clm]
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
  # [./EFieldAdvAux_em]
  #   block = 0
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
  # [./EFieldAdvAux_emliq]
  #   block = 1
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
  # [./DiffusiveFlux_em]
  #   block = 0
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
  # [./DiffusiveFlux_emliq]
  #   block = 1
  #   order = CONSTANT
  #   family = MONOMIAL
  # [../]
[]

[AuxKernels]
  # [./h_size]
  #   type = HSize
  #   variable = h_size
  # [../]
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
  [./rholiq]
    type = ParsedAux
    variable = rholiq
    args = 'emliq_lin H3Op_lin OHm_lin'
    function = 'H3Op_lin - emliq_lin - OHm_lin'
    execute_on = 'timestep_end'
  [../]
  [./tot_gas_current]
    type = ParsedAux
    variable = tot_gas_current
    args = 'Current_em Current_Arp'
    function = 'Current_em + Current_Arp'
    execute_on = 'timestep_end'
  [../]
  [./tot_liq_current]
    type = ParsedAux
    variable = tot_liq_current
    args = 'Current_emliq Current_H3Op Current_OHm'
    function = 'Current_emliq + Current_H3Op + Current_OHm'
    execute_on = 'timestep_end'
  [../]
  [./em_lin]
    type = Density
    variable = em_lin
    density_log = em
    block = 0
  [../]
  [./emliq_lin]
    type = Density
    variable = emliq_lin
    density_log = emliq
    block = 1
  [../]
  [./Arp_lin]
    type = Density
    variable = Arp_lin
    density_log = Arp
    block = 0
  [../]
  # [./Clm_lin]
  #   type = Density
  #   variable = Clm_lin
  #   density_log = Clm
  #   block = 1
  # [../]
  [./OHm_lin]
    type = Density
    variable = OHm_lin
    density_log = OHm
    block = 1
  [../]
  [./H3Op_lin]
    type = Density
    variable = H3Op_lin
    density_log = H3Op
    block = 1
  [../]
  [./Efield_gas]
    type = Efield
    potential = potential
    variable = Efield_gas
    block = 0
  [../]
  [./Efield_liq]
    type = Efield
    potential = potentialliq
    variable = Efield_liq
    block = 1
  [../]
  [./Current_em]
    block = 0
    type = Current
    potential = potential
    density_log = em
    variable = Current_em
  [../]
  [./Current_Arp]
    block = 0
    type = Current
    potential = potential
    density_log = Arp
    variable = Current_Arp
  [../]
  [./Current_emliq]
    block = 1
    type = Current
    potential = potentialliq
    density_log = emliq
    variable = Current_emliq
  [../]
  [./Current_OHm]
    block = 1
    type = Current
    potential = potentialliq
    density_log = OHm
    variable = Current_OHm
  [../]
  [./Current_H3Op]
    block = 1
    type = Current
    potential = potentialliq
    density_log = H3Op
    variable = Current_H3Op
  [../]
  [./tot_flux_OHm]
    block = 1
    type = TotalFlux
    potential = potentialliq
    density_log = OHm
    variable = tot_flux_OHm
  [../]
  [./adv_flux_OHm]
    block = 1
    type = EFieldAdvAux
    potential = potentialliq
    density_log = OHm
    variable = adv_flux_OHm
  [../]
  [./diff_flux_OHm]
    block = 1
    type = DiffusiveFlux
    density_log = OHm
    variable = diff_flux_OHm
  [../]

  # [./Current_Clm]
  #   block = 1
  #   type = Current
  #   potential = potentialliq
  #   density_log = Clm
  #   variable = Current_Clm
  # [../]
  # [./EFieldAdvAux_em]
  #   block = 0
  #   type = EFieldAdvAux
  #   potential = potential
  #   density_log = em
  #   variable = EFieldAdvAux_em
  # [../]
  # [./EFieldAdvAux_emliq]
  #   block = 1
  #   type = EFieldAdvAux
  #   potential = potentialliq
  #   density_log = emliq
  #   variable = EFieldAdvAux_emliq
  # [../]
  # [./DiffusiveFlux_em]
  #   block = 0
  #   type = DiffusiveFlux
  #   density_log = em
  #   variable = DiffusiveFlux_em
  # [../]
  # [./DiffusiveFlux_emliq]
  #   block = 1
  #   type = DiffusiveFlux
  #   density_log = emliq
  #   variable = DiffusiveFlux_emliq
  # [../]
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
    variable = potentialliq
    boundary = right
    value = 0
  [../]
  [./potential_interface]
    type = MatchedValueBC
    variable = potential
    boundary = master1_interface
    v = potentialliq
  [../]
  [./em_left]
    type = DCElectronBC
    variable = em
    boundary = left
    potential = potential
    ip = Arp
  [../]
  [./emliq_right]
    type = DCIonBC
    variable = emliq
    boundary = right
    potential = potentialliq
  [../]
  # [./em_interface]
  #   type = MatchedValueLogBC
  #   variable = emliq
  #   boundary = master1_interface
  #   v = em
  # [../]

  [./Arp_physical]
    type = DCIonBC
    variable = Arp
    # boundary = 'left master0_interface'
    boundary = 'left'
    potential = potential
  [../]
  # [./Clm_physical]
  #   type = DCIonBC
  #   variable = Clm
  #   boundary = 'right'
  #   potential = potentialliq
  # [../]
  [./OHm_physical]
    type = DCIonBC
    variable = OHm
    boundary = 'right'
    potential = potentialliq
  [../]
  # [./H3Op_physical]
  #   type = DCIonBC
  #   variable = H3Op
  #   boundary = 'right'
  #   potential = potentialliq
  # [../]
[]

[ICs]
  [./em_ic]
    type = ConstantIC
    variable = em
    value = -25
    block = 0
  [../]
  [./emliq_ic]
    type = ConstantIC
    variable = emliq
    value = -25
    block = 1
  [../]
  [./Arp_ic]
    type = ConstantIC
    variable = Arp
    value = -25
    block = 0
  [../]
  [./potential_ic]
    type = FunctionIC
    variable = potential
    function = potential_ic_func
    block = 0
  [../]
  # [./potential_ic]
  #   type = ConstantIC
  #   variable = potential
  #   value = 0
  #   block = 0
  # [../]

  # [./Clm_ic]
  #   type = ConstantIC
  #   variable = Clm
  #   value = .0455
  #   block = 1
  # [../]
  [./OHm_ic]
    type = ConstantIC
    variable = OHm
    value = .0455
    block = 1
  [../]
  [./H3Op_ic]
    type = ConstantIC
    variable = H3Op
    value = .0455
    block = 1
  [../]
  # [./potentialliq_ic]
  #   type = ConstantIC
  #   variable = potentialliq
  #   value = 0
  #   block = 1
  # [../]
  [./potentialliq_ic]
    type = FunctionIC
    variable = potentialliq
    function = potential_ic_func
    block = 1
  [../]
[]

[Functions]
  [./potential_bc_func]
    type = ParsedFunction
    value = '1.25*tanh(1e6*t)'
    # value = 1.25e3
  [../]
  [./potential_ic_func]
    type = ParsedFunction
    value = -1.25*(.00105-x)
  [../]
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
   potential = potentialliq
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
