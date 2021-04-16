dom0Scale=1.0
dom1Scale=1.0

[GlobalParams]
  #offset = 20
  #offset = 24
  #offset = 48
  offset = 20
  # offset = 0
  potential_units = kV
  use_moles = true
  # potential_units = V
[]

[Mesh]
  [./geo]
    type = FileMeshGenerator
    file = 'mesh.msh'
  [../]

  # The next two definitions create boundary conditions named
  # 'left' and 'right', where 'left' is at x = 0 and 'right' is at x = 1.1 mm.
  [./left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = geo
  [../]
  [./right]
    type = SideSetsFromNormalsGenerator
    normals = '1 0 0'
    new_boundary = 'right'
    input = left
  [../]
[]

[Problem]
  type = FEProblem
  # kernel_coverage_check = false
  #type = ReferenceResidualProblem
  #extra_tag_vectors = 'ref'
  #reference_vector = 'ref'
[]

[Preconditioning]
  active = smp

  [./smp]
    type = SMP
    full = true
    #ksp_norm = none
  [../]

  [./fsp]
    type = FSP
    topsplit = 'pc'
    #full = 'true'
    [./pc]
      splitting = 'p c'
      splitting_type = schur
      petsc_options_iname = '-pc_fieldsplit_schur_fact_type -pc_fieldsplit_schur_precondition'
      petsc_options_value = 'full selfp'
    [../]
    [./p]
      vars = 'potential'
      petsc_options_iname = '-pc_type -pc_hypre_type'
      petsc_options_value = 'hypre boomeramg'
    [../]
    [./c]
      vars = 'em Arp mean_en emliq OH- O- O2- O3- HO2- H+ O O2_1 O3 H H2 HO2 HO3 OH H2O2'
      petsc_options_iname = '-pc_type -pc_asm_overlap -sub_pc_type -sub_pc_factor_shift_type -sub_pc_factor_shift_amount'
      petsc_options_value = 'asm 2 ilu NONZERO 1e-10'
    [../]
  [../]
[]

[Executioner]
  type = Transient
  #end_time = 1e-1
  #end_time = 1e10
  end_time = 1e6
  automatic_scaling = true
  compute_scaling_once = false
  #resid_vs_jac_scaling_param = 1
  line_search = 'basic'
  petsc_options = '-snes_converged_reason'
  solve_type = newton
  #solve_type = pjfnk
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'
  nl_rel_tol = 1e-6
  nl_abs_tol = 1e-10
  dtmin = 1e-18
  l_max_its = 20
  nl_max_its = 20
  steady_state_detection = true
  steady_state_tolerance = 1e-8
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.4
    dt = 1e-14
    #dt = 2.56e-13
    growth_factor = 1.4
    optimal_iterations = 10
  [../]
[]

[Outputs]
  # perf_graph = true
  #print_densityear_residuals = false
  [out_01_greg_solely_drift_and_e_action]
    type = Exodus

  [../]
[]

[Debug]
  #show_var_residual_norms = true
[]

[UserObjects]
  [./data_provider]
    type = ProvideMobility
    electrode_area = 5.02e-7 # Formerly 3.14e-6
    ballast_resist = 1e6
    #ballast_resist = 2.5e5
    e = 1.6e-19
    # electrode_area = 1.1
    # ballast_resist = 1.1
    # e = 1.1
  [../]
[]

[DriftDiffusionActionAD]
  [./Plasma]
    #electrons = em
    #charged_particle = 'Arp Ar2p'
    #Neutrals = 'Ar* H2O OH'
    charged_particle = 'Arp'
    Neutrals = 'Ar*'
    #mean_energy = mean_en
    potential = potential
    Is_potential_unique = false
    using_offset = true
    offset = 30
    use_ad = true
    position_units = ${dom0Scale}
    block = 0
  [../]
[]

[Variables]
  [./potential]
    #block = 0
  [../]
  [./em]
    block = 0
    initial_condition = -20
  [../]

  [./Arp]
    block = 0
    initial_condition = -20.693147
  [../]
  #[./Ar2p]
  #  block = 0
  #  initial_condition = -20.693147
  #[../]
  #[OH]
  #  block = 0
  #  initial_condition = -20
  #[]

  [./Ar*]
    block = 0
    initial_condition = -25
  [../]

  [./mean_en]
    block = 0
    initial_condition = -20
    # scaling = 1e-1
  [../]
[]

[ElectronAction]
  electrons = em
  potential = potential
  mean_energy = mean_en
  block = 0
  position_units = ${dom0Scale}
  Using_offset = true
  mean_offset = 15
  boundary = 'left right'
  r = 0
[]

[Kernels]
  # Plasma potential kernels
  [./potential_diffusion_dom1]
    type = CoeffDiffusionLin
    variable = potential
    block = 0
    position_units = ${dom0Scale}
  [../]
  #include in action
  #[./em_charge_source]
  #  type = ChargeSourceMoles_KV
  #  variable = potential
  #  charged = em
  #  block = 0
  #[../]


  # Electron kernels

  #[./em_time_deriv]
  #  type = ADTimeDerivativeLog
  #  variable = em
  #  block = 0
  #[../]
  #[./em_advection]
  #  type = ADEFieldAdvection
  #  variable = em
  #  potential = potential
  #  block = 0
  #  position_units = ${dom0Scale}
  #[../]
  #[./em_diffusion]
  #  type = ADCoeffDiffusion
  #  variable = em
  #  mean_en = mean_en
  #  block = 0
  #  position_units = ${dom0Scale}
  #[../]
  #[./em_log_stabilization]
  #  type = LogStabilizationMoles
  #  variable = em
  #  block = 0
  #[../]

  # Electron energy kernels
  #[./mean_en_time_deriv]
  #  type = ADTimeDerivativeLog
  #  variable = mean_en
  #  block = 0
  #[../]
  #[./mean_en_advection]
  #  type = ADEFieldAdvection
  #  variable = mean_en
  #  potential = potential
  #  em = em
  #  block = 0
  #  position_units = ${dom0Scale}
  #[../]
  #[./mean_en_diffusion]
  #  type = ADCoeffDiffusion
  #  variable = mean_en
  #  block = 0
  #  position_units = ${dom0Scale}
  #[../]
  #[./mean_en_joule_heating]
  #  type = ADJouleHeating
  #  variable = mean_en
  #  potential = potential
  #  em = em
  #  block = 0
  #  position_units = ${dom0Scale}
  #[../]
  #[./mean_en_log_stabilization]
  #  type = LogStabilizationMoles
  #  variable = mean_en
  #  block = 0
  #  offset = 15
  #[../]
[]

[AuxVariables]
  [./Ar_density]
    block = 0
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Ar]
    block = 0
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 3.701920755421197
    #initial_condition = 3.704261
  [../]

  #[./O2]
  #  order = CONSTANT
  #  family = MONOMIAL
  #  initial_condition = -0.609203
  #  block = 1
  #[../]

  [./e_temp]
    block = 0
    order  = CONSTANT
    family = MONOMIAL
    initial_condition = 0
  [../]
  [./x]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 0
  [../]
  [./x_node]
    initial_condition = 0
  [../]
  [./Efield]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 0
  [../]
  [./ADCurrent_em]
    order = CONSTANT
    family = MONOMIAL
    block = 0
    initial_condition = 0
  [../]
  [./ADCurrent_Arp]
    order = CONSTANT
    family = MONOMIAL
    block = 0
    initial_condition = 0
  [../]
  [./tot_gas_current]
    order = CONSTANT
    family = MONOMIAL
    block = 0
    initial_condition = 0
  [../]
  [./ADEFieldAdvAux_em]
    order = CONSTANT
    family = MONOMIAL
    block = 0
    initial_condition = 0
  [../]
  [./ADDiffusiveFlux_em]
    order = CONSTANT
    family = MONOMIAL
    block = 0
    initial_condition = 0
  [../]
  [./ADPowerDep_em]
   order = CONSTANT
   family = MONOMIAL
   block = 0
    initial_condition = 0
  [../]
  [./ADPowerDep_Arp]
   order = CONSTANT
   family = MONOMIAL
   block = 0
    initial_condition = 0
  [../]
[]

[AuxKernels]
  [./ADPowerDep_em]
    type = ADPowerDep
    density_log = em
    potential = potential
    art_diff = false
    execute_on = 'initial timestep_end'
    potential_units = kV
    variable = ADPowerDep_em
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./ADPowerDep_Arp]
    type = ADPowerDep
    density_log = Arp
    potential = potential
    art_diff = false
    potential_units = kV
    variable = ADPowerDep_Arp
    execute_on = 'initial timestep_end'
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./e_temp]
    type = ElectronTemperature
    variable = e_temp
    electron_density = em
    execute_on = 'initial timestep_end'
    mean_en = mean_en
    block = 0
  [../]
  [./x_g]
    type = Position
    variable = x
    position_units = ${dom0Scale}
    execute_on = 'initial timestep_end'
    block = 0
  [../]
  [./x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
    execute_on = 'initial timestep_end'
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
  [./ADCurrent_em]
    type = ADCurrent
    potential = potential
    density_log = em
    variable = ADCurrent_em
    art_diff = false
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./ADCurrent_Arp]
    type = ADCurrent
    potential = potential
    density_log = Arp
    variable = ADCurrent_Arp
    art_diff = false
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./ADEFieldAdvAux_em]
    type = ADEFieldAdvAux
    potential = potential
    density_log = em
    variable = ADEFieldAdvAux_em
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./ADDiffusiveFlux_em]
    type = ADDiffusiveFlux
    density_log = em
    variable = ADDiffusiveFlux_em
    block = 0
    position_units = ${dom0Scale}
  [../]
  [Ar_density]
  type = DensityMoles
  variable = Ar_density
  density_log = Ar
  execute_on = 'initial'
  block = 0
  []
[]

[BCs]
  # H2O evaporation boundary condition
  #[OH_right]
  #  type = ADHagelaarIonDiffusionBC
  #  variable = OH
  #  boundary = 'left master0_interface'
  #  r = 0
  #  position_units = ${dom0Scale}
  #[]

  [./Arex_physical_diffusion]
    type = ADHagelaarIonDiffusionBC
    variable = Ar*
    boundary = 'left right'
    r = 0
    position_units = ${dom0Scale}
  [../]
  #[./Ar2p_physical_diffusion]
  #  type = ADHagelaarIonDiffusionBC
  #  variable = Ar2p
  #  boundary = 'left master0_interface'
  #  r = 0
  #  position_units = ${dom0Scale}
  #[../]
  #[./Ar2p_physical_advection]
  #  type = ADHagelaarIonAdvectionBC
  #  variable = Ar2p
  #  boundary = 'left master0_interface'
  #  potential = potential
  #  r = 0
  #  position_units = ${dom0Scale}
  #[../]
  [./potential_left]
    type = ADNeumannCircuitVoltageMoles_KV
    variable = potential
    boundary = left
    function = potential_bc_func
    #ip = 'Arp Ar2p'
    ip = 'Arp'
    data_provider = data_provider
    em = em
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  [../]
  #[./em_bc]
  #  type = ADHagelaarElectronBC
  #  variable = em
  #  boundary = 'left right'
  #  potential = potential
  #  #ip = Arp
  #  mean_en = mean_en
  #  #r = 0.99
  #  r = 0.0
  #  position_units = ${dom0Scale}
  #[../]
  [./Arp_physical_right_diffusion]
    type = ADHagelaarIonDiffusionBC
    variable = Arp
    boundary = 'left right'
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./Arp_physical_right_advection]
    type = ADHagelaarIonAdvectionBC
    variable = Arp
    boundary = 'left right'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  [../]
  #[./mean_en_bc]
  #  type = ADHagelaarEnergyBC
  #  variable = mean_en
  #  boundary = 'left right'
  #  potential = potential
  #  em = em
  #  #r = 0.99
  #  r = 0.0
  #  position_units = ${dom0Scale}
  #[../]

  # Secondary electrons are only emitted from the cathode (left boundary)
  # in this case
  [./sec_electrons_left]
    type = ADSecondaryElectronBC
    variable = em
    boundary = 'left'
    potential = potential
    #ip = 'Arp Ar2p'
    ip = 'Arp'
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./sec_electrons_energy_left]
    type = ADSecondaryElectronEnergyBC
    variable = mean_en
    boundary = 'left'
    potential = potential
    #ip = 'Arp Ar2p'
    ip = 'Arp'
    em = em
    r = 0
    position_units = ${dom0Scale}
  [../]
[]

[ICs]
  [./potential_ic]
    type = FunctionIC
    variable = potential
    function = potential_ic_func
    #block = 0
  [../]
[]

[Functions]
  [./potential_bc_func]
    type = ParsedFunction
    value = -1.5
  [../]
  [./potential_ic_func]
    type = ParsedFunction
    value = '-1.5 * (1.001e-3 - x)'
  [../]
[]

#[HeavySpeciesTransport]

#  [./H20_mat]
#    name = H2O
#    mass = 2.9907e-26
#    charge = 0
#    diffusivity = 2.3e-5
#    position_units = ${dom0Scale}
#    potential = potential
#    potential_units = kV
#  [../]
#  [./Arp]
#    name = Arp
#    mass = 6.64e-26
#    charge = 1.0
#  potential = potential
#    potential_units = kV
#    aux_var = false
#    using_offset = true
#    offset = 30
#  [../]
  #[./Ar_species]
  #  name = Ar
  #  mass = 6.64e-26
  #  charge = 0.0
  #  block = 0
  #  position_units = ${dom0Scale}
  #  potential = potential
  #  potential_units = kV
  #  conserved_particle = true
  #  nonconserved = 'Arp Ar*'
    #Ar2p can't be set in _nonconserved
    #its its not a coupled variable that can be found
    #it is commented out in the variables block

    #Ar is an aux varaible not a non linear varaible
    #does it still have adcoeef diffusion Kernels
    #tried without any kernels, result vary slightly now
    #how to track conserved_density
  #[../]
#  [./gas_species_1]
#    name = Ar2p
#    mass = 13.28e-26
#    charge = 1.0
#    block = 0
#    position_units = ${dom0Scale}
#    potential = potential
#    potential_units = kV
#  [../]
#  [./gas_species_2]
#    name = Ar*
#    mass = 6.64e-26
#    charge = 0
#    block = 0
#    position_units = ${dom0Scale}
#    potential = potential
#    potential_units = kV
#    aux_var = false
#    using_offset = true
#    offset = 30
#  [../]
#  [./OH_mat]
#    name = OH
#    mass = 2.82420e-26
#    charge = 0
#    diffusivity = 4e-5
#    block = 0
#    position_units = ${dom0Scale}
#    potential = potential
#    potential_units = kV
#  [../]
#[]



[Materials]
  [./se_coefficient]
    type = GenericConstantMaterial
    prop_names = 'se_coeff'
    prop_values = '0.01'
    boundary = 'left right'
  [../]
 [./GasBasics]
   #type = GasBase
   type = ADGasElectronMoments
   interp_elastic_coeff = true
   interp_trans_coeffs = true
   ramp_trans_coeffs = false
   # user_p_gas = 1.01325e5
   user_p_gas = 1.01e5
   em = em
   potential = potential
   mean_en = mean_en
   user_se_coeff = 0.05
   #property_tables_file = cpc_test/e_vals_test.txt
   #property_tables_file = '/home/shane/projects/zapdos/problems/argon_water_prelim_files/electron_mobility_diffusion.txt'
   property_tables_file = 'argon_chemistry_rates/electron_moments.txt'
   block = 0
 [../]
 [gas_constants]
   type = GenericConstantMaterial
   prop_names = 'e    N_A    k_boltz    eps     se_energy    T_gas    massem    p_gas diffpotential'
   prop_values = '1.6e-19 6.022e23 1.38e-23 8.854e-12 1 400 9.11e-31 1.01e5 8.854e-12'
   block = 0
 []

 [H2O_mat]
   type = ADHeavySpeciesMaterial
   heavy_species_name = H2O
   heavy_species_mass = 2.9907e-26
   heavy_species_charge = 0
   diffusivity = 2.3e-5
 []

  [./gas_species_0]
    type = ADHeavySpeciesMaterial
    heavy_species_name = Arp
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    block = 0
  [../]
  [./Ar_species]
    type = ADHeavySpeciesMaterial
    heavy_species_name = Ar
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
    block = 0
  [../]
  [./gas_species_1]
    type = ADHeavySpeciesMaterial
    heavy_species_name = Ar2p
    heavy_species_mass = 13.28e-26
    heavy_species_charge = 1.0
    block = 0
  [../]
  [./gas_species_2]
    type = ADHeavySpeciesMaterial
    heavy_species_name = Ar*
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0
    block = 0
  [../]

  [OH_mat]
    type = ADHeavySpeciesMaterial
    heavy_species_name = OH
    heavy_species_mass = 2.82420e-26
    heavy_species_charge = 0
    diffusivity = 4e-5
    block = 0
  []
[]

[Reactions]
  [./Argon]
    #species = 'em Arp Ar2p Ar* OH'
    #aux_species = 'Ar H2O'
    species = 'em Arp Ar*'
    reaction_coefficient_format = 'townsend'
    gas_species = 'Ar'
    electron_energy = 'mean_en'
    electron_density = 'em'
    include_electrons = true
    file_location = 'argon_chemistry_rates'
    equation_constants = 'Tgas'
    equation_values = '300'
    equation_variables = 'e_temp'
    potential = 'potential'
    use_log = true
    position_units = ${dom0Scale}
    use_ad = true
    block = 0

    reactions = 'em + Ar -> em + Ar               : EEDF [elastic] (reaction1)
                 em + Ar -> em + Ar*              : EEDF [-11.5]   (reaction2)
                 em + Ar -> em + em + Arp         : EEDF [-15.76]  (reaction3)
                 em + Ar* -> em + Ar              : EEDF [11.5]    (reaction4)
                 em + Ar* -> em + em + Arp        : EEDF [-4.3]    (reaction5)'
  [../]
[]
