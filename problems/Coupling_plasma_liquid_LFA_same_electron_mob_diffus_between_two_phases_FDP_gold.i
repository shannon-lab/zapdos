[GlobalParams]
[]

[Mesh]
  type = FileMesh
  file = 'Plasma_liquid.unv'
  # type = GeneratedMesh
  # dim = 1
  # nx = 1000
  # xmin = 0
  # xmax = 1e-3
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
  [./left]
    type = SideSetsFromPoints
    new_boundary = 'left'
    points = '0.0 0 0'
  [../]
  [./right]
    type = SideSetsFromPoints
    new_boundary = 'right'
    points = '0.00105 0 0'
  [../]
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
  end_time = 1e-1
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type' # -pc_factor_mat_solver_package'
  petsc_options_value = 'lu NONZERO 1.e-10 preonly' # mumps'
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
    output_material_properties = true
    # show_material_properties = 'ElectronTotalFlux ElectronAdvectiveFlux ElectronDiffusiveFlux IonTotalFlux IonAdvectiveFlux IonDiffusiveFlux EField'
    show_material_properties = 'EField OHm_lin H3Op_lin'
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
  [./em_time_deriv]
    type = ElectronTimeDerivative
    variable = em
    block = '0 1'
  [../]
  [./em_advection]
    type = EFieldAdvection
    variable = em
    potential = potential
    block = '0 1'
  [../]
  [./em_diffusion]
    type = CoeffDiffusion
    variable = em
    block = '0 1'
  [../]
  [./em_ionization]
    type = ElectronsFromIonizationLFA
    variable = em
    potential = potential
    block = 0
  [../]
  [./em_log_stabilization]
    type = LogStabilization
    variable = em
    block = '0 1'
  [../]
  # [./em_water_mono_sink]
  #   type = ReactantFirstOrderRxn
  #   variable = em
  #   block = 1
  # [../]
  # [./em_water_bi_sink]
  #   type = ReactantAARxn
  #   variable = em
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
    type = IonsFromIonizationLFA
    variable = Arp
    potential = potential
    em = em
    block = 0
  [../]
  [./Arp_log_stabilization]
    type = LogStabilization
    variable = Arp
    block = 0
  [../]
  [./Arp_advection_stabilization]
    type = EFieldArtDiff
    variable = Arp
    potential = potential
    block = 0
  [../]

  [./potential_diffusion]
    type = Diffusion
    variable = potential
    block = '0 1'
  [../]
  [./Arp_charge_source]
    type = ChargeSource
    variable = potential
    charged = Arp
    block = 0
  [../]
  [./em_charge_source]
    type = ChargeSource
    variable = potential
    charged = em
    block = '0 1'
  [../]
  [./OHm_charge_source]
    type = ChargeSource
    variable = potential
    charged = OHm
    block = '1'
  [../]
  [./H3Op_charge_source]
    type = ChargeSource
    variable = potential
    charged = H3Op
    block = '1'
  [../]

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
    type = LogStabilization
    variable = OHm
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
    potential = potential
    block = 1
  [../]
  [./H3Op_diffusion]
    type = CoeffDiffusion
    variable = H3Op
    block = 1
  [../]
  [./H3Op_log_stabilization]
    type = LogStabilization
    variable = H3Op
    block = 1
  [../]
[]

[Variables]
  [./potential]
    scaling = 1e-5
    block = '0 1'
  [../]
  [./em]
    scaling = 1e-18
    block = '0 1'
  [../]
  [./Arp]
    scaling = 1e-18
    block = 0
  [../]
  [./OHm]
    scaling = 1e-18
    block = 1
  [../]
  [./H3Op]
    scaling = 1e-18
    block = 1
  [../]
[]

[AuxVariables]
  [./em_lin]
    block = '0 1'
  [../]
  [./Arp_lin]
    block = 0
  [../]
  [./e_temp]
    block = 0
  [../]
[]

[AuxKernels]
  [./em_lin]
    type = ElectronDensity
    variable = em_lin
    electron_density = em
    block = '0 1'
  [../]
  [./Arp_lin]
    type = IonDensity
    variable = Arp_lin
    ion_density = Arp
    block = 0
  [../]
[]

[BCs]
  [./potential_left]
    type = NeumannCircuitVoltage
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
  # [./potential_dirichlet_left]
  #   type = DirichletBC
  #   variable = potential
  #   boundary = left
  #   value = -1.25e3
  # [../]
  [./em_physical]
    type = DCElectronBC
    variable = em
    boundary = 'left right'
    potential = potential
    ip = Arp
  [../]
  [./Arp_physical]
    type = DCIonBC
    variable = Arp
    boundary = 'left master0_interface'
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
    value = 29.934
    block = '0 1'
  [../]
  [./Arp_ic]
    type = ConstantIC
    variable = Arp
    value = 29.934
    block = 0
  [../]
  [./OHm_ic]
    type = ConstantIC
    variable = OHm
    value = 45.54
    block = 1
  [../]
  [./H3Op_ic]
    type = ConstantIC
    variable = H3Op
    value = 45.54
    block = 1
  [../]
  # [./potential_ic]
  #   type = FunctionIC
  #   variable = potential
  #   function = potential_ic_func
  # [../]
  [./potential_ic]
    type = ConstantIC
    variable = potential
    value = 0
    block = '0 1'
  [../]
[]

[Functions]
  [./potential_bc_func]
    type = ParsedFunction
    value = '1.25e3*tanh(1e6*t)'
  [../]
  [./potential_ic_func]
    type = ParsedFunction
    value = -1.25e3*(.001-x)
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
   OHm = OHm
   H3Op = H3Op
   potential = potential
 [../]
[]
