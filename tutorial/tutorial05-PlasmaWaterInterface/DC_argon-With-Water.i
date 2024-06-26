#This tutorial is of an argon DC discharge over water at
#different reflection coefficients. Reflection coefficients
#for electron and mean energy at the water are on lines 297 and 315.

#Scaling for block 0 (Plasma)
dom0Scale = 1e-3
#caling for block 1 (Water)
dom1Scale = 1e-7

[GlobalParams]
  # off set for log stabilization, prevents log(0)
  offset = 20
  #Scales the potential by V or kV
  potential_units = kV
  #Converts density from #/m^3 to moles/m^3
  use_moles = true
[]

[Mesh]
  #Mesh is defined by a Gmsh file
  [file]
    type = FileMeshGenerator
    file = 'plasmaliquid.msh'
  []

  [interface]
    # interface allows for one directional fluxes
    # interface going from air to water
    type = SideSetsBetweenSubdomainsGenerator
    primary_block = '0' # block where the flux is coming from
    paired_block = '1' # block where the flux is going to
    new_boundary = 'master0_interface'
    input = file # first input is where the msh is coming and it is then named air_to_water
  []
  [interface_again]
    # interface going from water to air
    type = SideSetsBetweenSubdomainsGenerator
    primary_block = '1' # block where the flux is coming from
    paired_block = '0' # block where the flux is going to
    new_boundary = 'master1_interface'
    input = interface
  []
  #Renames all sides with the specified normal
  #For 1D, this is used to rename the end points of the mesh
  [left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = interface_again
  []
  [right]
    type = SideSetsFromNormalsGenerator
    normals = '1 0 0'
    new_boundary = 'right'
    input = left
  []
[]

#Defines the problem type, such as FE, eigen value problem, etc.
[Problem]
  type = FEProblem
[]

#The potential needs to be defined outside of the Action,
#since it is present in both Blocks
#Declare any variable that is present in mulitple blocks in the variables section
[Variables]
  [potential]
  []
[]

[DriftDiffusionAction]
  [Plasma]
    #User define name for electrons (usually 'em')
    electrons = em
    #User define name for ions
    charged_particle = Arp
    #User define name for potential (usually 'potential')
    potential = potential
    #Set False becuase both areas use the same potential
    Is_potential_unique = false
    #User define name for the electron mean energy density (usually 'mean_en')
    mean_energy = mean_en
    #Helps prevent the log(0)
    using_offset = true #helps prevent the log(0)
    #The position scaling for the mesh, define at top of input file
    position_units = ${dom0Scale}
    #Name of material block for plasma
    block = 0
    #Additional outputs, such as ElectronTemperature, Current, and EField.
    Additional_Outputs = 'ElectronTemperature Current EField'
  []
  # treats water as a dense plasma
  [Water]
    charged_particle = 'emliq OHm'
    potential = potential
    Is_potential_unique = false
    using_offset = true
    position_units = ${dom1Scale}
    #Name of material block for water
    block = 1
    Additional_Outputs = 'Current EField'
  []
[]

[Reactions]
  [Argon]
    #Name of reactant species that are variables
    species = 'em Arp'
    #Name of reactant species that are auxvariables
    aux_species = 'Ar'
    #Type of coefficient (rate or townsend)
    reaction_coefficient_format = 'townsend'
    #Name of background gas
    gas_species = 'Ar'
    #Name of the electron mean energy density (usually 'mean_en')
    electron_energy = 'mean_en'
    #Name of the electrons (usually 'em')
    electron_density = 'em'
    #Defines if electrons are tracked
    include_electrons = true
    #Defines directory holding rate text files
    file_location = 'townsend_coefficients'
    #Name of name for potential (usually 'potential')
    potential = 'potential'
    #Defines if log form is used (true for Zapdos)
    use_log = true
    #Defines if automatic differentiation is used (true for Zapdos)
    use_ad = true
    #The position scaling for the mesh, define at top of input file
    position_units = ${dom0Scale}
    #Name of material block for plasma
    block = 0
    #Inputs of the plasma chemsity
    #e.g. Reaction : Constant or EEDF dependent [Threshold Energy] (Text file name)
    #     em + Ar -> em + Ar*        : EEDF [-11.56] (reaction1)
    reactions = 'em + Ar -> em + Ar               : EEDF [elastic] (reaction1)
                 em + Ar -> em + Ar*              : EEDF [-11.5] (reaction2)
                 em + Ar -> em + em + Arp         : EEDF [-15.76] (reaction3)'
  []

  [Water]
    species = 'emliq OHm'
    reaction_coefficient_format = 'rate'
    use_log = true
    use_ad = true
    aux_species = 'H2O'
    block = 1
    reactions = 'emliq -> H + OHm : 1064
                 emliq + emliq -> H2 + OHm + OHm : 3.136e8'
  []
[]

[AuxVariables]
  #Background fluid in water
  [H2O]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 10.92252
    block = 1
  []
  #Background gas in plasma
  [Ar]
    block = 0
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 3.70109
  []
[]

[InterfaceKernels]
  # interface conditions allow one this to go another
  # These account for electrons going into the water
  # if you want to account for electrons going out of the water into the air then you would need there to be interface conditions for master interface 0
  [em_advection]
    type = InterfaceAdvection
    mean_en_neighbor = mean_en
    potential_neighbor = potential
    neighbor_var = em

    #the main variable being affected. The em is going into the water so em -> emliq
    # this affects emliq
    variable = emliq
    boundary = master1_interface
    position_units = ${dom1Scale}
    neighbor_position_units = ${dom0Scale}
  []
  [em_diffusion]
    type = InterfaceLogDiffusionElectrons
    mean_en_neighbor = mean_en
    neighbor_var = em
    variable = emliq
    boundary = master1_interface
    position_units = ${dom1Scale}
    neighbor_position_units = ${dom0Scale}
  []
[]

#Electrode data needed for 1D BC of 'NeumannCircuitVoltageMoles_KV'
[UserObjects]
  [data_provider]
    type = ProvideMobility
    electrode_area = 5.02e-7 # Formerly 3.14e-6
    ballast_resist = 1e6
    e = 1.6e-19
  []
[]

[BCs]
  #DC BC on the air electrode
  [potential_left]
    type = NeumannCircuitVoltageMoles_KV
    variable = potential
    boundary = left
    function = potential_bc_func
    ions = Arp
    data_provider = data_provider
    electrons = em
    electron_energy = mean_en
    r = 0
    position_units = ${dom0Scale}
    emission_coeffs = 0.05
  []
  #Ground electrode under the water
  [potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  []

  #Electrons on the powered electrode
  [em_physical_left]
    type = HagelaarElectronBC
    variable = em
    boundary = 'left'
    potential = potential
    electron_energy = mean_en
    r = 0
    position_units = ${dom0Scale}
  []
  [sec_electrons_left]
    type = SecondaryElectronBC
    variable = em
    boundary = 'left'
    potential = potential
    ions = Arp
    electron_energy = mean_en
    r = 0
    position_units = ${dom0Scale}
    emission_coeffs = 0.05
  []

  #Mean electron energy on the powered electrode
  [mean_en_physical_left]
    type = HagelaarEnergyBC
    variable = mean_en
    boundary = 'left'
    potential = potential
    electrons = em
    r = 0
    position_units = ${dom0Scale}
  []
  [secondary_energy_left]
    type = SecondaryElectronEnergyBC
    variable = mean_en
    boundary = 'left'
    potential = potential
    electrons = em
    ions = 'Arp'
    r = 0
    position_units = ${dom0Scale}
    emission_coeffs = 0.05
    secondary_electron_energy = 3
  []

  #Argon ions on the powered electrode
  [Arp_physical_left_diffusion]
    type = HagelaarIonDiffusionBC
    variable = Arp
    boundary = 'left'
    r = 0
    position_units = ${dom0Scale}
  []
  [Arp_physical_left_advection]
    type = HagelaarIonAdvectionBC
    variable = Arp
    boundary = 'left'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []

  #Electrons on the plasma-liquid interface
  [em_physical_right]
    type = HagelaarElectronBC
    variable = em
    boundary = 'master0_interface'
    potential = potential
    electron_energy = mean_en
    r = 0.00
    position_units = ${dom0Scale}
  []
  [Arp_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = Arp
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [mean_en_physical_right]
    #Mean electron energy on the plasma-liquid interface
    type = HagelaarEnergyBC
    variable = mean_en
    boundary = 'master0_interface'
    potential = potential
    electrons = em
    r = 0.00
    position_units = ${dom0Scale}
  []

  #Argon ions on the plasma-liquid interface
  [Arp_physical_right_advection]
    type = HagelaarIonAdvectionBC
    variable = Arp
    boundary = 'master0_interface'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []

  #Electrons on the electrode
  [emliq_right]
    type = DCIonBC
    variable = emliq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  #OH- on the ground electrode
  [OHm_physical]
    type = DCIonBC
    variable = OHm
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
[]

#Initial conditions for variables.
#If left undefine, the IC is zero
[ICs]
  [em_ic]
    type = ConstantIC
    variable = em
    value = -21
    block = 0
  []
  [emliq_ic]
    type = ConstantIC
    variable = emliq
    value = -21
    block = 1
  []
  [Arp_ic]
    type = ConstantIC
    variable = Arp
    value = -21
    block = 0
  []
  [mean_en_ic]
    type = ConstantIC
    variable = mean_en
    value = -20
    block = 0
  []
  [OHm_ic]
    type = ConstantIC
    variable = OHm
    value = -15.6
    block = 1
  []
  [potential_ic]
    type = FunctionIC
    variable = potential
    function = potential_ic_func
  []
[]

#Define function used throughout the input file (e.g. BCs and ICs)
[Functions]
  [potential_bc_func]
    type = ParsedFunction
    # expression = '1.25*tanh(1e6*t)'
    expression = -1.25
  []
  [potential_ic_func]
    type = ParsedFunction
    expression = '-1.25 * (1.0001e-3 - x)'
  []
[]

[Materials]
  #The material properties for electrons and ions in water
  [water_block]
    type = Water
    block = 1
    potential = potential
  []

  #The material properties for electrons in plasma
  #Also hold universal constant, such as Avogadro's number, elementary charge, etc.
  [electrons_in_plasma]
    type = GasElectronMoments
    interp_trans_coeffs = true
    interp_elastic_coeff = true
    ramp_trans_coeffs = false
    user_p_gas = 101325
    user_se_coeff = 0.05
    em = em
    potential = potential
    mean_en = mean_en
    block = 0
    property_tables_file = 'townsend_coefficients/moments.txt'
  []

  #Sets the pressure and temperature in the water
  [water_block1]
    type = GenericConstantMaterial
    block = 1
    prop_names = 'T_gas p_gas'
    prop_values = '300 1.01e5'
  []

  #The material properties of the argon ion
  [gas_species_0]
    type = ADHeavySpecies
    heavy_species_name = Arp
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    block = 0
  []

  #The material properties of the background argon gas
  [gas_species_2]
    type = ADHeavySpecies
    heavy_species_name = Ar
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
    block = 0
  []
[]

#Preconditioning options
#Learn more at: https://mooseframework.inl.gov/syntax/Preconditioning/index.html
[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

#How to execute the problem.
#Defines type of solve (such as steady or transient),
# solve type (Newton, PJFNK, etc.) and tolerances
[Executioner]
  type = Transient
  end_time = 1e-1
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'
  nl_rel_tol = 1e-4
  nl_abs_tol = 7.6e-5
  dtmin = 1e-15
  l_max_its = 20
  [TimeSteppers]
    [Adaptive]
      type = IterationAdaptiveDT
      cutback_factor = 0.4
      dt = 1e-11
      growth_factor = 1.2
      optimal_iterations = 30
    []
  []
[]

#Defines the output type of the file (multiple output files can be define per run)
[Outputs]
  perf_graph = true
  [out]
    type = Exodus
    execute_on = 'final'
  []
[]
