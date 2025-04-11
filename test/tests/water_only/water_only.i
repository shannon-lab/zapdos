dom1Scale = 1e-7

[GlobalParams]
  potential_units = kV
  use_moles = true
[]

[Mesh]
  type = GeneratedMesh
  nx = 1000
  xmax = 10
  dim = 1
[]

[Problem]
  type = FEProblem
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Executioner]
  type = Transient
  end_time = 1e-1
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 1e-3'
  nl_rel_tol = 1e-4
  nl_abs_tol = 7.6e-5
  dtmin = 1e-12
  l_max_its = 20
  nl_max_its = 20
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
  [out]
    type = Exodus
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
  [emliq_time_deriv]
    type = ElectronTimeDerivative
    variable = emliq
  []
  [emliq_advection]
    type = EFieldAdvection
    variable = emliq
    position_units = ${dom1Scale}
  []
  [emliq_diffusion]
    type = CoeffDiffusion
    variable = emliq
    position_units = ${dom1Scale}
  []
  [emliq_reactant_first_order_rxn]
    type = ReactantFirstOrderRxn
    variable = emliq
  []
  [emliq_water_bi_sink]
    type = ReactantAARxn
    variable = emliq
  []

  [potential_diffusion]
    type = CoeffDiffusionLin
    variable = potential
    position_units = ${dom1Scale}
  []
  # [emliq_charge_source]
  #   type = ChargeSourceMoles_KV
  #   variable = potential
  #   charged = emliq
  # []
  # [OHm_charge_source]
  #   type = ChargeSourceMoles_KV
  #   variable = potential
  #   charged = OHm
  # []

  [OHm_time_deriv]
    type = ElectronTimeDerivative
    variable = OHm
  []
  [OHm_advection]
    type = EFieldAdvection
    variable = OHm
    position_units = ${dom1Scale}
  []
  [OHm_diffusion]
    type = CoeffDiffusion
    variable = OHm
    position_units = ${dom1Scale}
  []
  [OHm_product_first_order_rxn]
    type = ProductFirstOrderRxn
    variable = OHm
    v = emliq
  []
  [OHm_product_aabb_rxn]
    type = ProductAABBRxn
    variable = OHm
    v = emliq
  []
[]

[Variables]
  [potential]
  []
  [emliq]
  []
  [OHm]
  []
[]

[AuxVariables]
  [x]
    order = CONSTANT
    family = MONOMIAL
  []
  [x_node]
  []
  [emliq_lin]
    order = CONSTANT
    family = MONOMIAL
  []
  [OHm_lin]
    order = CONSTANT
    family = MONOMIAL
  []
  [Efield]
    order = CONSTANT
    family = MONOMIAL
  []
  [Current_emliq]
    order = CONSTANT
    family = MONOMIAL
  []
  [Current_OHm]
    order = CONSTANT
    family = MONOMIAL
  []
  [tot_liq_current]
    order = CONSTANT
    family = MONOMIAL
  []
  [tot_flux_OHm]
    order = CONSTANT
    family = MONOMIAL
  []
  [EFieldAdvAux_emliq]
    order = CONSTANT
    family = MONOMIAL
  []
  [DiffusiveFlux_emliq]
    order = CONSTANT
    family = MONOMIAL
  []
[]

[AuxKernels]
  [x_l]
    type = Position
    variable = x
    position_units = ${dom1Scale}
  []
  [x_nl]
    type = Position
    variable = x_node
    position_units = ${dom1Scale}
  []
  [tot_liq_current]
    type = ParsedAux
    variable = tot_liq_current
    coupled_variables = 'Current_emliq Current_OHm'
    expression = 'Current_emliq + Current_OHm'
    execute_on = 'timestep_end'
  []
  [emliq_lin]
    type = DensityMoles
    variable = emliq_lin
    density_log = emliq
  []
  [OHm_lin]
    type = DensityMoles
    variable = OHm_lin
    density_log = OHm
  []
  [Efield_l]
    type = Efield
    component = 0
    variable = Efield
    position_units = ${dom1Scale}
  []
  [Current_emliq]
    type = ADCurrent
    density_log = emliq
    variable = Current_emliq
    art_diff = false
    position_units = ${dom1Scale}
  []
  [Current_OHm]
    type = ADCurrent
    density_log = OHm
    variable = Current_OHm
    art_diff = false
    position_units = ${dom1Scale}
  []
  [tot_flux_OHm]
    type = ADTotalFlux
    density_log = OHm
    variable = tot_flux_OHm
  []
  [EFieldAdvAux_emliq]
    type = ADEFieldAdvAux
    density_log = emliq
    variable = EFieldAdvAux_emliq
    position_units = ${dom1Scale}
  []
  [DiffusiveFlux_emliq]
    type = ADDiffusiveFlux
    density_log = emliq
    variable = DiffusiveFlux_emliq
    position_units = ${dom1Scale}
  []
[]

[BCs]
  [potential_left]
    type = DirichletBC
    value = -6.5e-5
    variable = potential
    boundary = left
  []
  [potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  []
  [emliq_left]
    type = NeumannBC
    value = 300
    variable = emliq
    boundary = left
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
  [emliq_ic]
    type = ConstantIC
    variable = emliq
    value = -21
  []
  [OHm_ic]
    type = ConstantIC
    variable = OHm
    value = -15.6
  []
[]

[Materials]
 [water_block]
   type = Water
 []
 [field_solver]
   type = FieldSolverMaterial
   potential = potential
 []
[]
