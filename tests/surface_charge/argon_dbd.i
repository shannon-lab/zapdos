dom0Scale=1
dom1Scale=1
dom2Scale=1

[GlobalParams]
  offset = 40
  potential_units = kV
  use_moles = true
[]

[Mesh]
  [./file]
    type = FileMeshGenerator
    file = 'argon_dbd_mesh.msh'
  [../]
  [./dielectric_left]
    # left dielectric master
    type = SideSetsBetweenSubdomainsGenerator
    master_block = '0'
    paired_block = '1'
    new_boundary = 'master01_interface'
    input = file
  [../]
  [./plasma_left]
    # plasma master
    type = SideSetsBetweenSubdomainsGenerator
    master_block = '1'
    paired_block = '0'
    new_boundary = 'master10_interface'
    input = dielectric_left
  [../]
  [./plasma_right]
    # plasma master
    type = SideSetsBetweenSubdomainsGenerator
    master_block = '1'
    paired_block = '2'
    new_boundary = 'master12_interface'
    input = plasma_left
  [../]
  [./dielectric_right]
    # left dielectric master
    type = SideSetsBetweenSubdomainsGenerator
    master_block = '2'
    paired_block = '1'
    new_boundary = 'master21_interface'
    input = plasma_right
  [../]
  [./left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = dielectric_right
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
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  automatic_scaling = true
  compute_scaling_once = false
  end_time = 10e-5
  num_steps = 50
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  line_search = 'basic'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -snes_stol'
  petsc_options_value = 'lu NONZERO 1.e-10 0'
  nl_rel_tol = 1e-8
  dtmin = 1e-18
  dtmax = 1e-7
  l_max_its = 100
  nl_max_its = 25

  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.4
    dt = 1e-11
    growth_factor = 1.2
   optimal_iterations = 30
  [../]

  #[./TimeIntegrator]
    #type = BDF2
    #type = LStableDirk2
  #[../]

[]

[Outputs]
  perf_graph = true
  #[./out]
  #  type = Exodus
  #  output_material_properties = true
  #  show_material_properties = 'surface_charge'
  #[../]
  [./out]
    type = Exodus
    output_material_properties = false
  [../]
[]

[Variables]
  [./Arp]
    block = 1
  [../]
  [./em]
    block = 1
  [../]
  [./Ar*]
    block = 1
  [../]
  [./mean_en]
    block = 1
  [../]

  [./potential_dom0]
    block = 0
  [../]
  [./potential_dom1]
    block = 1
  [../]
  [./potential_dom2]
    block = 2
  [../]

[]

[Kernels]
  # Electrons
  [./d_em_dt]
    type = ADTimeDerivativeLog
    variable = em
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./em_advection]
    type = ADEFieldAdvection
    variable = em
    potential = potential_dom1
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./em_diffusion]
    type = ADCoeffDiffusion
    variable = em
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./em_offset]
    type = LogStabilizationMoles
    variable = em
    position_units = ${dom0Scale}
    block = 1
  [../]

  [./d_mean_en_dt]
    type = ADTimeDerivativeLog
    variable = mean_en
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./mean_en_advection]
    type = ADEFieldAdvectionEnergy
    em = em
    variable = mean_en
    potential = potential_dom1
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./mean_en_diffusion]
    type = ADCoeffDiffusion
    variable = mean_en
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./mean_en_joule_heating]
    type = ADJouleHeating
    variable = mean_en
    em = em
    potential = potential_dom1
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./mean_en_offset]
    type = LogStabilizationMoles
    variable = mean_en
    position_units = ${dom0Scale}
    block = 1
  [../]

  [./d_Arp_dt]
    type = ADTimeDerivativeLog
    variable = Arp
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./Arp_advection]
    type = ADEFieldAdvection
    variable = Arp
    potential = potential_dom1
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./Arp_diffusion]
    type = ADCoeffDiffusion
    variable = Arp
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./Arp_offset]
    type = LogStabilizationMoles
    variable = Arp
    position_units = ${dom0Scale}
    block = 1
  [../]

  [./d_Arex_dt]
    type = ADTimeDerivativeLog
    variable = Ar*
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./Arex_diffusion]
    type = ADCoeffDiffusion
    variable = Ar*
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./Arex_offset]
    type = LogStabilizationMoles
    variable = Ar*
    position_units = ${dom0Scale}
    block = 1
  [../]

  [./em_source]
    type = ChargeSourceMoles_KV
    variable = potential_dom1
    charged = em
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./Arp_source]
    type = ChargeSourceMoles_KV
    variable = potential_dom1
    charged = Arp
    position_units = ${dom0Scale}
    block = 1
  [../]

  [./potential_diffusion_dom0]
    type = CoeffDiffusionLin
    variable = potential_dom0
    block = 0
    position_units = ${dom0Scale}
  [../]
  [./potential_dom1_diffusion1_block]
    type = CoeffDiffusionLin
    variable = potential_dom1
    block = 1
    position_units = ${dom0Scale}
  [../]
  [./potential_diffusion_dom2]
    type = CoeffDiffusionLin
    variable = potential_dom2
    block = 2
    position_units = ${dom0Scale}
  [../]
[]

[InterfaceKernels] 
  [./potential_left]
    type = ADPotentialSurfaceCharge
    neighbor_var = potential_dom0
    variable = potential_dom1
    ions = 'Arp'
    em = em
    mean_en = mean_en
    position_units = ${dom0Scale}
    neighbor_position_units = ${dom0Scale}
    boundary = master10_interface
  [../]

  [./potential_right]
    type = ADPotentialSurfaceCharge
    neighbor_var = potential_dom2
    variable = potential_dom1
    ions = 'Arp'
    em = em
    mean_en = mean_en
    position_units = ${dom0Scale}
    neighbor_position_units = ${dom0Scale}
    boundary = master12_interface
  [../]

  #[./potential_left2]
  #  type = PenaltyInterfaceDiffusion
  #  penalty = 1e6
  #  variable = potential_dom0
  #  neighbor_var = potential_dom1
  #  boundary = 'master01_interface'
  #[../]
  #[./potential_right2]
  #  type = PenaltyInterfaceDiffusion
  #  penalty = 1e6
  #  variable = potential_dom2
  #  neighbor_var = potential_dom1
  #  boundary = 'master21_interface'
  #[../]
[]

[AuxVariables]
  [./e_temp]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Ar_density]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./em_density]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Arp_density]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Ars_density]
    block = 1
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Ar]
    block = 1
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 3.70109
  [../]
  [./x]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Efield]
    order = CONSTANT
    family = MONOMIAL
  [../]
  #[./rho]
  #  order = CONSTANT
  #  family = MONOMIAL
  #  block = 1
  #[../]
  [./Current_em]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  [../]
  [./Current_Arp]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  [../]
  [./tot_gas_current]
    order = CONSTANT
    family = MONOMIAL
    block = 1
  [../]
[]

[AuxKernels]
  [./e_temp]
    type = ElectronTemperature
    variable = e_temp
    electron_density = em
    mean_en = mean_en
    block = 1
  [../]
  [./Ar_density]
    type = DensityMoles
    variable = Ar_density
    density_log = Ar
    use_moles = true
    block = 1
  [../]
  [./em_density]
    type = DensityMoles
    variable = Ar_density
    density_log = em
    use_moles = true
    block = 1
  [../]
  [./Arp_density]
    type = DensityMoles
    variable = Ar_density
    density_log = Arp
    use_moles = true
    block = 1
  [../]
  [./Ars_density]
    type = DensityMoles
    variable = Ars_density
    density_log = Ar*
    use_moles = true
    block = 1
  [../]
  [./x_g0]
    type = Position
    variable = x
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./x_g1]
    type = Position
    variable = x
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./x_g2]
    type = Position
    variable = x
    position_units = ${dom0Scale}
    block = 2
  [../]
  [./Efield_d0]
    type = Efield
    component = 0
    potential = potential_dom0
    variable = Efield
    position_units = ${dom0Scale}
    block = 0
  [../]
  [./Efield_d1]
    type = Efield
    component = 0
    potential = potential_dom1
    variable = Efield
    position_units = ${dom0Scale}
    block = 1
  [../]
  [./Efield_d2]
    type = Efield
    component = 0
    potential = potential_dom2
    variable = Efield
    position_units = ${dom0Scale}
    block = 2
  [../]
[]

[BCs]
  ######
  # HAGELAAR BCS
  ######
  [./em_physical_bc]
    type = ADHagelaarElectronBC
    variable = em
    boundary = 'master10_interface master12_interface'
    potential = potential_dom1
    mean_en = mean_en
    r = 0.0
    position_units = ${dom0Scale}
  [../]
  [./sec_electrons_left]
    type = ADSecondaryElectronBC
    variable = em
    boundary = 'master10_interface master12_interface'
    potential = potential_dom1
    ip = 'Arp'
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
  [../]
  #[./sec_electrons_right]
  #  type = ADSecondaryElectronBC
  #  variable = em
  #  boundary = 'master12_interface'
  #  potential = potential_dom1
  #  ip = 'Arp'
  #  mean_en = mean_en
  #  r = 0
  #  position_units = ${dom0Scale}
  #[../]
  [./mean_en_physical]
    type = ADHagelaarEnergyBC
    variable = mean_en
    boundary = 'master10_interface master12_interface'
    potential = potential_dom1
    em = em
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./secondary_energy_left]
    type = ADSecondaryElectronEnergyBC
    variable = mean_en
    boundary = 'master10_interface master12_interface'
    potential = potential_dom1
    em = em
    ip = 'Arp'
    r = 0
    position_units = ${dom0Scale}
  [../]
  #[./secondary_energy_right]
  #  type = ADSecondaryElectronEnergyBC
  #  variable = mean_en
  #  boundary = 'master12_interface'
  #  potential = potential_dom1
  #  em = em
  #  ip = 'Arp'
  #  r = 0
  #  position_units = ${dom0Scale}
  #[../]
  [./Arp_bcs]
    type = ADHagelaarIonAdvectionBC
    variable = Arp
    boundary = 'master10_interface master12_interface'
    potential = potential_dom1
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./Arp_bcs2]
    type = ADHagelaarIonDiffusionBC
    variable = Arp
    boundary = 'master10_interface master12_interface'
    potential = potential_dom1
    r = 0
    position_units = ${dom0Scale}
  [../]
  [./Arex_bcs]
    type = ADHagelaarIonDiffusionBC
    variable = Ar*
    boundary = 'master10_interface master12_interface'
    potential = potential_dom1
    r = 0
    position_units = ${dom0Scale}
  [../]
  #########
  #########

  [./match_phi_left]
    type = MatchedValueBC
    variable = potential_dom0
    v = potential_dom1
    boundary = 'master01_interface'
  [../]
  [./match_phi_right]
    type = MatchedValueBC
    variable = potential_dom2
    v = potential_dom1
    boundary = 'master21_interface'
  [../]

  [./potential_left]
    type = FunctionDirichletBC
    variable = potential_dom0
    function = potential_input
    #function = potential_input_test
    boundary = 'left'
  [../]

  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential_dom2
    #variable = potential
    boundary = right
    value = 0
    preset = false
  [../]
[]

[ICs]
  [./potential_dom0_ic]
    type = FunctionIC
    variable = potential_dom0
    function = potential_ic_func
  [../]
  [./potential_dom1_ic]
    type = FunctionIC
    variable = potential_dom1
    function = potential_ic_func
  [../]
  [./potential_dom2_ic]
    type = FunctionIC
    variable = potential_dom2
    function = potential_ic_func
  [../]

  [./em_ic]
    type = ConstantIC
    variable = em
    value = -41
    block = 1
  [../]
  [./Arp_ic]
    type = ConstantIC
    variable = Arp
    value = -41
    block = 1
  [../]
  [./Arex_ic]
    type = ConstantIC
    variable = Ar*
    value = -45
    block = 1
  [../]
  [./mean_en_ic]
    type = ConstantIC
    variable = mean_en
    value = -41
    block = 1
  [../]
[]

[Functions]
  [./potential_input]
    type = ParsedFunction
    vars = 'f0'
    vals = '50e3'
    value = '-0.75*sin(2*3.1415926*f0*t)'
  [../]

  # Set the initial condition to a line from -10 V on the left and
  # 0 on the right.
  # (Poisson solver works better with a nonzero potential IC.)
  [./potential_ic_func]
    type = ParsedFunction
    value = '-0.01 * (3.0001e-4 - x)'
  [../]
[]

[Materials]
  #########
  # Define secondary electron emission coefficients on the left and right 
  # dielectrics.
  #########
  [./se_left]
    type = GenericConstantMaterial
    boundary = 'master10_interface'
    prop_names = 'se_coeff'
    prop_values = '0.01'
  [../]
  [./se_right]
    type = GenericConstantMaterial
    boundary = 'master12_interface'
    prop_names = 'se_coeff'
    prop_values = '1e-6'
  [../]

  #########
  # Define electron transport coefficients 
  #########
  [./electron_moments_ad]
    type = ADGasElectronMoments
    block = 1
    em = em
    mean_en = mean_en
    property_tables_file = 'dbd_data/electron_mobility_diffusion.txt'
  [../]

  #########
  # Define some necessary constants.
  # Energy of secondary electrons is set to 1 eV here. 
  #########
  [./gas_constants]
    type = GenericConstantMaterial
    block = 1
    prop_names = ' e       N_A      k_boltz  eps         se_energy T_gas  massem   p_gas  n_gas'
    prop_values = '1.6e-19 6.022e23 1.38e-23 8.854e-12   1.        400    9.11e-31 1.01e5 40.4915'
  [../]

  
  #########
  # Define surface charge on left and right boundaries
  # bc_type is 'Hagelaar' by default. 
  # Other options are 'Lymberopoulos' and 'Sakiyama'. 
  # For charge consistency, the bc_type and BCs should be consistent.
  #########
  [./Test]
    type = ADSurfaceCharge
    potential = potential_dom1
    bc_type = 'Hagelaar'
    r_electron = 0
    r_ion = 0
    mean_en = mean_en
    em = em
    ions = 'Arp'
    se_coeff = 0.01
    #se_coeff = 0.005
    position_units = ${dom0Scale}
    boundary = 'master10_interface'
  [../]
  [./Test2]
    type = ADSurfaceCharge
    potential = potential_dom1
    bc_type = 'Hagelaar'
    r_electron = 0
    r_ion = 0
    mean_en = mean_en
    em = em
    ions = 'Arp'
    se_coeff = 1e-6
    #se_coeff = 0.5e-6
    position_units = ${dom0Scale}
    boundary = 'master12_interface'
  [../]


  ######
  # Diffusion coefficients for the potential in each region must be defined.
  # Here a GenericConstantMaterial is used for simplicity.
  # For all variables, potential included, diffusivity is defined as: 
  # "diff" + [variable name]
  ######
  [./dielectric_left_side]
    type = GenericConstantMaterial
    prop_names = 'diffpotential_dom0'
    prop_values = '8.85e-11'
    block = 0
  [../]
  [./gas_phase]
    type = GenericConstantMaterial
    prop_names = 'diffpotential_dom1'
    prop_values = '8.85e-12'
    block = 1
  [../]
  [./dielectric_right_side]
    type = GenericConstantMaterial
    prop_names = 'diffpotential_dom2'
    prop_values = '8.85e-11'
    block = 2
  [../]

  ######
  # HeavySpeciesMaterial defines charge, mass, transport coefficients, and
  # temperature for each species. 
  #
  # Transport coefficients and temperature are defined as ADMaterialProperties.
  # Although they currently (as of June 16, 2020) remain constant, future 
  # implementations may include mixture-averaged diffusion coefficients and
  # effective ion temperatures with nonlinear dependence on other variables.
  ######
  [./gas_species_0]
    type = ADHeavySpeciesMaterial
    heavy_species_name = Arp
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    diffusivity = 1.6897e-5
    block = 1
  [../]
  [./gas_species_2]
    type = ADHeavySpeciesMaterial
    heavy_species_name = Ar
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
    diffusivity = 1.6897e-5
    block = 1
  [../]
  [./gas_species_3]
    type = ADHeavySpeciesMaterial
    heavy_species_name = Ar*
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
    diffusivity = 1.6897e-5
    block = 1
  [../]
[]

[Reactions]
  # Note that rate coefficients are in molar units. 
  # For a two-body reaction, units are [m^3 mol^-1 s^-1]
  [./Argon]
    species = 'em Arp Ar*'
    aux_species = 'Ar'
    reaction_coefficient_format = 'townsend'
    gas_species = 'Ar'
    electron_energy = 'mean_en'
    electron_density = 'em'
    include_electrons = true
    file_location = 'dbd_data'
    potential = 'potential_dom1'
    use_log = true
    use_ad = true
    position_units = ${dom1Scale}
    block = 1

    reactions = 'em + Ar -> em + Ar               : EEDF [elastic] (C1_Ar_Elastic)
                 em + Ar -> em + Ar*              : EEDF [-11.5] (C2_Ar_Excitation_11.50_eV)
                 em + Ar -> em + em + Arp         : EEDF [-15.76] (C3_Ar_Ionization_15.80_eV)
                 em + Ar* -> em + Ar              : EEDF [11.5] (C4_Ars_De-excitation_11.50_eV)
                 em + Ar* -> em + em + Arp        : EEDF [-4.43] (C5_Ars_Ionization_4.43_eV)
                 Ar* + Ar -> Ar + Ar              : 1807
                 Ar* + Ar* -> em + Ar + Arp       : 3.3734e8'
  [../]
[]
