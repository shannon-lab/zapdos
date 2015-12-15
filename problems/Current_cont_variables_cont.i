[GlobalParams]
[]

[Mesh]
  type = FileMesh
  file = 'liquidNew.msh'
[]

[MeshModifiers]
  # [./interface]
  #   type = SideSetsBetweenSubdomains
  #   master_block = '0'
  #   paired_block = '1'
  #   new_boundary = 'master0_interface'
  # [../]
  # [./interface_again]
  #   type = SideSetsBetweenSubdomains
  #   master_block = '1'
  #   paired_block = '0'
  #   new_boundary = 'master1_interface'
  # [../]
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
  [./em_log_stabilization]
    type = LogStabilizationMoles
    variable = em
    offset = 50
  [../]

  [./potential_diffusion]
    type = CoeffDiffusionLin
    variable = potential
  [../]
[]

[Variables]
  [./potential]
    [../]
  [./em]
  [../]
[]

[AuxVariables]
  [./x]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./em_lin]
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
  [./Efield_gas]
    type = Efield
    potential = potential
    variable = Efield
  [../]

  [./x]
    type = Position
    variable = x
  [../]
  [./em_lin]
    type = Density
    variable = em_lin
    density_log = em
  [../]
  [./Current_em]
    type = Current
    potential = potential
    density_log = em
    variable = Current_em
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
    type = DirichletBC
    variable = potential
    boundary = left
    value = -1.25
  [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  [../]
  [./em_left]
    type = DCIonBC
    variable = em
    boundary = left
    potential = potential
  [../]
  [./emliq_right]
    type = DCIonBC
    variable = em
    boundary = right
    potential = potential
  [../]
[]

[ICs]
  [./em_ic]
    type = ConstantIC
    variable = em
    value = -25
  [../]
  [./potential_ic]
    type = ConstantIC
    variable = potential
    value = 0
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
   potential = potential
 [../]
[]