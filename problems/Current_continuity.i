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
  end_time = 1e-1
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 preonly 1e-3'
 nl_rel_tol = 1e-50
 nl_abs_tol = 4e-8
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

  [./potential_diffusion]
    type = CoeffDiffusionLin
    variable = potential
    block = 0
  [../]

  [./potentialliq_diffusion]
    type = CoeffDiffusionLin
    variable = potentialliq
    block = 1
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
  [./Current_emliq]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./EFieldAdvAux_em]
    block = 0
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./EFieldAdvAux_emliq]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./DiffusiveFlux_em]
    block = 0
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./DiffusiveFlux_emliq]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
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

  [./x]
    type = Position
    variable = x
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
  [./Current_em]
    block = 0
    type = Current
    potential = potential
    density_log = em
    variable = Current_em
  [../]
  [./Current_emliq]
    block = 1
    type = Current
    potential = potentialliq
    density_log = emliq
    variable = Current_emliq
  [../]
  [./EFieldAdvAux_em]
    block = 0
    type = EFieldAdvAux
    potential = potential
    density_log = em
    variable = EFieldAdvAux_em
  [../]
  [./EFieldAdvAux_emliq]
    block = 1
    type = EFieldAdvAux
    potential = potentialliq
    density_log = emliq
    variable = EFieldAdvAux_emliq
  [../]
  [./DiffusiveFlux_em]
    block = 0
    type = DiffusiveFlux
    density_log = em
    variable = DiffusiveFlux_em
  [../]
  [./DiffusiveFlux_emliq]
    block = 1
    type = DiffusiveFlux
    density_log = emliq
    variable = DiffusiveFlux_emliq
  [../]
[]

[BCs]
  [./potential_left]
    type = DirichletBC
    variable = potential
    boundary = left
    value = -1.25
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
    type = DCIonBC
    variable = em
    boundary = left
    potential = potential
  [../]
  [./emliq_right]
    type = DCIonBC
    variable = emliq
    boundary = right
    potential = potentialliq
  [../]
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
  [./potential_ic]
    type = ConstantIC
    variable = potential
    value = 0
    block = 0
  [../]
  [./potentialliq_ic]
    type = ConstantIC
    variable = potentialliq
    value = 0
    block = 1
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
    # ip = Arp
 [../]
 [./water_block]
   type = Water
   block = 1
   potential = potentialliq
 [../]
[]