[GlobalParams]
[]

[Mesh]
  # type = FileMesh
  # file = 'Plasma_liquid.unv'
  type = GeneratedMesh
  dim = 1
  nx = 105
  xmin = 0
  xmax = 1.05e-3
[]

[MeshModifiers]
  [./subdomain1]
    type = SubdomainBoundingBox
    bottom_left = '1e-3 0 0'
    block_id = 1
    top_right = '1.05e-3 1.0 0'
  [../]
  [./interface]
    type = SideSetsBetweenSubdomains
    depends_on = subdomain1
    master_block = '0'
    paired_block = '1'
    new_boundary = 'master0_interface'
  [../]
  [./interface_again]
    type = SideSetsBetweenSubdomains
    depends_on = subdomain1
    master_block = '1'
    paired_block = '0'
    new_boundary = 'master1_interface'
  [../]
  # [./left]
  #   type = SideSetsFromPoints
  #   new_boundary = 'left'
  #   points = '0.0 0 0'
  # [../]
  # [./right]
  #   type = SideSetsFromPoints
  #   new_boundary = 'right'
  #   points = '0.00105 0 0'
  # [../]
  # [./left]
  #   type = AddExtraNodeset
  #   new_boundary = 'left'
  #   coord = '0.0'
  # [../]
  # [./right]
  #   type = AddExtraNodeset
  #   new_boundary = 'right'
  #   coord = '0.00105'
  # [../]
  # [./add_sideset]
  #   type = AddAllSideSetsByNormals
  # [../]
[]

[Problem]
  type = FEProblem
[]

[Preconditioning]
  [./smp]
    type = FDP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  # type = Steady
  end_time = 1e-1
  # solve_type = NEWTON
  # petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type' # -pc_factor_mat_solver_package'
  # petsc_options_value = 'lu NONZERO 1.e-10 preonly' # mumps'
 # nl_rel_tol = 1e-10
 # l_tol = 1e-3
 # trans_ss_check = true
 # ss_check_tol = 1e-7
 nl_abs_tol = 1e-3
  l_max_its = 10
 nl_max_its = 50
  dtmin = 1e-12
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.4
    dt = 1e-9
    growth_factor = 1.2
   optimal_iterations = 50
  [../]
[]

[Outputs]
  print_perf_log = true
  [./out]
    type = Exodus
    # output_material_properties = true
    # show_material_properties = 'ElectronTotalFlux ElectronAdvectiveFlux ElectronDiffusiveFlux IonTotalFlux IonAdvectiveFlux IonDiffusiveFlux EField'
    # show_material_properties = 'EField'
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
  # [./em_ionization]
  #   type = ElectronsFromIonizationLFA
  #   variable = em
  #   potential = potential
  #   block = 0
  # [../]
  [./em_log_stabilization]
    type = LogStabilization
    variable = em
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
    type = LogStabilization
    variable = emliq
    block = '1'
  [../]
  # [./emliq_water_mono_sink]
  #   type = ReactantFirstOrderRxn
  #   variable = emliq
  #   block = 1
  # [../]
  # [./emliq_water_bi_sink]
  #   type = ReactantAARxn
  #   variable = emliq
  #   block = 1
  # [../]

  # potential block
  [./potential_diffusion]
    type = CoeffDiffusionLin
    # type = Diffusion
    variable = potential
    block = 0
  [../]
  # [./Arp_charge_source]
  #   type = ChargeSource
  #   variable = potential
  #   charged = Arp
  #   block = 0
  # [../]
  # [./em_charge_source]
  #   type = ChargeSource
  #   variable = potential
  #   charged = em
  #   block = 0
  # [../]

  # potentialliq block
  [./potentialliq_diffusion]
    type = CoeffDiffusionLin
    # type = Diffusion
    variable = potentialliq
    block = 1
  [../]
  # [./emliq_charge_source]
  #   type = ChargeSource
  #   variable = potentialliq
  #   charged = emliq
  #   block = 1
  # [../]
  # [./OHm_charge_source]
  #   type = ChargeSource
  #   variable = potentialliq
  #   charged = OHm
  #   block = 1
  # [../]
  # [./H3Op_charge_source]
  #   type = ChargeSource
  #   variable = potentialliq
  #   charged = H3Op
  #   block = 1
  # [../]

  # [./Arp_time_deriv]
  #   type = ElectronTimeDerivative
  #   variable = Arp
  #   block = 0
  # [../]
  # [./Arp_advection]
  #   type = EFieldAdvection
  #   variable = Arp
  #   potential = potential
  #   block = 0
  # [../]
  # [./Arp_diffusion]
  #   type = CoeffDiffusion
  #   variable = Arp
  #   block = 0
  # [../]
  # # [./Arp_ionization]
  # #   type = IonsFromIonizationLFA
  # #   variable = Arp
  # #   potential = potential
  # #   em = em
  # #   block = 0
  # # [../]
  # [./Arp_log_stabilization]
  #   type = LogStabilization
  #   variable = Arp
  #   block = 0
  # [../]
  # [./Arp_advection_stabilization]
  #   type = EFieldArtDiff
  #   variable = Arp
  #   potential = potential
  #   block = 0
  # [../]

  # [./OHm_time_deriv]
  #   type = ElectronTimeDerivative
  #   variable = OHm
  #   block = 1
  # [../]
  # [./OHm_advection]
  #   type = EFieldAdvection
  #   variable = OHm
  #   potential = potentialliq
  #   block = 1
  # [../]
  # [./OHm_diffusion]
  #   type = CoeffDiffusion
  #   variable = OHm
  #   block = 1
  # [../]
  # [./OHm_log_stabilization]
  #   type = LogStabilization
  #   variable = OHm
  #   block = 1
  # [../]
  # [./OHm_advection_stabilization]
  #   type = EFieldArtDiff
  #   variable = OHm
  #   potential = potentialliq
  #   block = 1
  # [../]

  # [./H3Op_time_deriv]
  #   type = ElectronTimeDerivative
  #   variable = H3Op
  #   block = 1
  # [../]
  # [./H3Op_advection]
  #   type = EFieldAdvection
  #   variable = H3Op
  #   potential = potentialliq
  #   block = 1
  # [../]
  # [./H3Op_diffusion]
  #   type = CoeffDiffusion
  #   variable = H3Op
  #   block = 1
  # [../]
  # [./H3Op_log_stabilization]
  #   type = LogStabilization
  #   variable = H3Op
  #   block = 1
  # [../]
  # [./H3Op_advection_stabilization]
  #   type = EFieldArtDiff
  #   variable = H3Op
  #   potential = potentialliq
  #   block = 1
  # [../]
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
    # scaling = 1e-13
    scaling = 1
    block = 0
  [../]
  [./potentialliq]
    # scaling = 1e9
    scaling = 1
    block = 1
  [../]

  [./em]
    scaling = 1e-18
    block = 0
  [../]
  [./emliq]
    scaling = 1e-18
    block = 1
  [../]

  # [./Arp]
  #   scaling = 1e-18
  #   block = 0
  # [../]

  # [./OHm]
  #   scaling = 1e-18
  #   block = 1
  # [../]
  # [./H3Op]
  #   scaling = 1e-18
  #   block = 1
  # [../]
[]

[AuxVariables]
  [./em_lin]
    block = 0
  [../]
  [./emliq_lin]
    block = 1
  [../]
  # [./Arp_lin]
  #   block = 0
  # [../]
  # [./OHm_lin]
  #   block = 1
  # [../]
  # [./H3Op_lin]
  #   block = 1
  # [../]
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
[]

[AuxKernels]
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
  # [./Arp_lin]
  #   type = Density
  #   variable = Arp_lin
  #   density_log = Arp
  #   block = 0
  # [../]
  # [./OHm_lin]
  #   type = Density
  #   variable = OHm_lin
  #   density_log = OHm
  #   block = 1
  # [../]
  # [./H3Op_lin]
  #   type = Density
  #   variable = H3Op_lin
  #   density_log = H3Op
  #   block = 1
  # [../]
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
[]

[BCs]
  # [./potential_left]
  #   type = NeumannCircuitVoltage
  #   variable = potential
  #   boundary = left
  #   function = potential_bc_func
  #   ip = Arp
  #   data_provider = data_provider
  # [../]
  [./potential_dirichlet_left]
    type = DirichletBC
    variable = potential
    boundary = left
    value = -1.25e3
  [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potentialliq
    boundary = right
    value = 0
  [../]
  [./potential_interface]
    type = MatchedValueBC
    variable = potentialliq
    boundary = master1_interface
    v = potential
  [../]
  # [./em_left]
  #   type = DCElectronBC
  #   variable = em
  #   boundary = left
  #   potential = potential
  #   ip = Arp
  # [../]
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
  [./em_interface]
    type = MatchedValueLogBC
    variable = emliq
    boundary = master1_interface
    v = em
  [../]
    
  # [./Arp_physical]
  #   type = DCIonBC
  #   variable = Arp
  #   boundary = 'left master0_interface'
  #   potential = potential
  # [../]
  # [./OHm_physical]
  #   type = DCIonBC
  #   variable = OHm
  #   boundary = 'right'
  #   potential = potentialliq
  # [../]
[]

[ICs]
  [./em_ic]
    type = ConstantIC
    variable = em
    value = 29.934
    block = 0
  [../]
  [./emliq_ic]
    type = ConstantIC
    variable = emliq
    value = 29.934
    block = 1
  [../]
  # [./Arp_ic]
  #   type = ConstantIC
  #   variable = Arp
  #   value = 29.934
  #   block = 0
  # [../]
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
    block = 0
  [../]

  # [./OHm_ic]
  #   type = ConstantIC
  #   variable = OHm
  #   value = 45.54
  #   block = 1
  # [../]
  # [./H3Op_ic]
  #   type = ConstantIC
  #   variable = H3Op
  #   value = 45.54
  #   block = 1
  # [../]
  [./potentialliq_ic]
    type = ConstantIC
    variable = potentialliq
    value = 0
    block = 1
  [../]
  # [./potentialliq_ic]
  #   type = FunctionIC
  #   variable = potentialliq
  #   function = potential_ic_func
  #   block = 1
  # [../]
[]

[Functions]
  [./potential_bc_func]
    type = ParsedFunction
    value = '1.25e3*tanh(1e6*t)'
  [../]
  [./potential_ic_func]
    type = ParsedFunction
    value = -1.25e3*(.00105-x)
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
   # OHm = OHm
   # H3Op = H3Op
   potential = potentialliq
 [../]
[]
