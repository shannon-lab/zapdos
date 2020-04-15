#This file of a CCP RF agron plasma.
#The metastables are accelerated by an average rate of change
#scheme if the first 100 cycles and then accelerated by a
#Shooting Method scheme for the rest of the simulation.
#The simulation is terminated when a periodic relative difference
#is meet or at time=2e-4s

dom0Scale=25.4e-3

[GlobalParams]
  potential_units = kV
  use_moles = true
[]

[Mesh]
  [./geo]
    type = FileMeshGenerator
    file = 'Lymberopoulos_paper.msh'
  [../]
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
[]

#Action that sets the Drift Diffusion Equations and Potential Eqautions
[DriftDiffusionAction]
  [./Plasma]
    electrons = em
    charged_particle = Ar+
    Neutrals = Ar*
    potential = potential
    Is_potential_unique = true
    mean_energy = mean_en
    position_units = ${dom0Scale}
    Additional_Outputs = 'ElectronTemperature Current EField'
  [../]
[]

#Action that sets the Sources Terms of the species
[Reactions]
  [./Argon]
    species = 'Ar* em Ar+'
    aux_species = 'Ar'
    reaction_coefficient_format = 'rate'
    gas_species = 'Ar'
    electron_energy = 'mean_en'
    electron_density = 'em'
    include_electrons = true
    file_location = 'rate_coefficients'
    potential = 'potential'
    use_log = true
    position_units = ${dom0Scale}
    block = 0
    reactions = 'em + Ar -> em + Ar*        : EEDF [-11.56] (reaction1)
                 em + Ar -> em + em + Ar+   : EEDF [-15.7] (reaction2)
                 em + Ar* -> em + Ar        : EEDF [11.56] (reaction3)
                 em + Ar* -> em + em + Ar+  : EEDF [-4.14] (reaction4)
                 em + Ar* -> em + Ar_r      : 1.2044e11
                 Ar* + Ar* -> Ar+ + Ar + em : 373364000
                 Ar* + Ar -> Ar + Ar        : 1806.6
                 Ar* + Ar + Ar -> Ar_2 + Ar : 39890.9324'
  [../]
[]

#Variables for scaled nodes and background gas
[AuxVariables]
  [./x_node]
  [../]

  [./Ar]
  [../]
[]

#Kernels that define the scaled nodes and background gas
[AuxKernels]
  [./x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
  [../]

  [./Ar_val]
    type = ConstantAux
    variable = Ar
    # value = 3.22e22
    value = -2.928623
    execute_on = INITIAL
  [../]
[]

[BCs]
#Voltage Boundary Condition
  [./potential_left]
    type = FunctionDirichletBC
    variable = potential
    boundary = 'left'
    function = potential_bc_func
  [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = 'right'
    value = 0
  [../]

#Boundary conditions for electons
  [./em_physical_right]
    type = LymberopoulosElectronBC
    variable = em
    boundary = 'right'
    gamma = 0.01
    ks = 1.19e5
    ion = Ar+
    potential = potential
    position_units = ${dom0Scale}
  [../]
  [./em_physical_left]
    type = LymberopoulosElectronBC
    variable = em
    boundary = 'left'
    gamma = 0.01
    ks = 1.19e5
    ion = Ar+
    potential = potential
    position_units = ${dom0Scale}
  [../]

#Boundary conditions for ions
  [./Ar+_physical_right_advection]
    type = LymberopoulosIonBC
    variable = Ar+
    potential = potential
    boundary = 'right'
    position_units = ${dom0Scale}
  [../]
  [./Ar+_physical_left_advection]
    type = LymberopoulosIonBC
    variable = Ar+
    potential = potential
    boundary = 'left'
    position_units = ${dom0Scale}
  [../]

#Boundary conditions for metastables
  [./Ar*_physical_right_diffusion]
    type = LogDensityDirichletBC
    variable = Ar*
    boundary = 'right'
    value = 1e-5
  [../]
  [./Ar*_physical_left_diffusion]
    type = LogDensityDirichletBC
    variable = Ar*
    boundary = 'left'
    value = 1e-5
  [../]

#Boundary conditions for mean energy
  [./mean_en_physical_right]
    type = ElectronTemperatureDirichletBC
    variable = mean_en
    em = em
    value = 0.5
    boundary = 'right'
  [../]
  [./mean_en_physical_left]
    type = ElectronTemperatureDirichletBC
    variable = mean_en
    em = em
    value = 0.5
    boundary = 'left'
  [../]
[]

#Initial Conditions
[ICs]
  [./em_ic]
    type = FunctionIC
    variable = em
    function = density_ic_func
  [../]
  [./Ar+_ic]
    type = FunctionIC
    variable = Ar+
    function = density_ic_func
  [../]
  [./Ar*_ic]
    type = FunctionIC
    variable = Ar*
    function = density_ic_func
  [../]
  [./mean_en_ic]
    type = FunctionIC
    variable = mean_en
    function = energy_density_ic_func
  [../]
[]

#Functions for IC and Potential BC
[Functions]
  [./potential_bc_func]
    type = ParsedFunction
    value = '0.100*sin(2*3.1415926*13.56e6*t)'
  [../]
  [./density_ic_func]
    type = ParsedFunction
    value = 'log((1e12)/6.022e23)'
  [../]
  [./energy_density_ic_func]
    type = ParsedFunction
    value = 'log(3./2.) + log((1e12)/6.022e23)'
  [../]
[]

#Material properties of species and background gas
[Materials]
  [./GasBasics]
    #If elecron mobility and diffusion are NOT constant, set
    #"interp_elastic_coeff = true". This lets the mobility and
    #diffusivity to be energy dependent, as dictated by the txt file
    type = GasElectronMoments
    em = em
    potential = potential
    mean_en = mean_en
    user_p_gas = 133.322
    user_electron_mobility = 30.0
    user_electron_diffusion_coeff = 119.8757763975
    property_tables_file = rate_coefficients/electron_moments.txt
    interp_trans_coeffs = false
    ramp_trans_coeffs = false
    interp_elastic_coeff = false
  [../]
  [./gas_species_0]
    type = HeavySpeciesMaterial
    heavy_species_name = Ar+
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    mobility = 0.144409938
    diffusivity = 6.428571e-3
  [../]
  [./gas_species_1]
    type = HeavySpeciesMaterial
    heavy_species_name = Ar*
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
    diffusivity = 7.515528e-3
  [../]
  [./gas_species_2]
    type = HeavySpeciesMaterial
    heavy_species_name = Ar
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
  [../]
[]

#Acceleration Schemes are dictated by MultiApps, Transfers,
#and PeriodicControllers
[MultiApps]
  #MultiApp of Acceleration by Shooting Method
  [./Shooting]
    type = FullSolveMultiApp
    input_files = 'RF_Plasma_acceleration_Shooting.i'
    execute_on = 'TIMESTEP_END'
    enable = false
  [../]

  #MultiApp of Acceleration by Averaging
  [./Averaging_Acceleration]
    type = FullSolveMultiApp
    input_files = 'RF_Plasma_acceleration_averaging.i'
    execute_on = 'TIMESTEP_END'
    enable = false
  [../]
[]

[Transfers]
  #MultiApp Transfers for Acceleration by Shooting Method
  [./em_to_Shooting]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Shooting
    source_variable = em
    variable = em
    enable = false
  [../]
  [./Ar+_to_Shooting]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Shooting
    source_variable = Ar+
    variable = Ar+
    enable = false
  [../]
  [./mean_en_to_Shooting]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Shooting
    source_variable = mean_en
    variable = mean_en
    enable = false
  [../]
  [./potential_to_Shooting]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Shooting
    source_variable = potential
    variable = potential
    enable = false
  [../]
  [./Ar*_to_Shooting]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Shooting
    source_variable = Ar*
    variable = Ar*
    enable = false
  [../]
  [./Ar*S_to_Shooting]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Shooting
    source_variable = Ar*
    variable = Ar*S
    enable = false
  [../]

  [./Ar*New_from_Shooting]
    type = MultiAppCopyTransfer
    direction = from_multiapp
    multi_app = Shooting
    source_variable = Ar*
    variable = Ar*
    enable = false
  [../]

  [./Ar*Relative_Diff]
    type = MultiAppPostprocessorTransfer
    direction = from_multiapp
    multi_app = Shooting
    from_postprocessor = Meta_Relative_Diff
    to_postprocessor = Meta_Relative_Diff
    reduction_type = minimum
    enable = false
  [../]

  #MultiApp Transfers for Acceleration by Averaging
  [./em_to_Averaging]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Averaging_Acceleration
    source_variable = em
    variable = em
    enable = false
  [../]
  [./Ar+_to_Averaging]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Averaging_Acceleration
    source_variable = Ar+
    variable = Ar+
    enable = false
  [../]
  [./mean_en_to_Averaging]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Averaging_Acceleration
    source_variable = mean_en
    variable = mean_en
    enable = false
  [../]
  [./potential_to_Averaging]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Averaging_Acceleration
    source_variable = potential
    variable = potential
    enable = false
  [../]
  [./Ar*_to_Averaging]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Averaging_Acceleration
    source_variable = Ar*
    variable = Ar*
    enable = false
  [../]
  [./Ar*S_to_Averaging]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Averaging_Acceleration
    source_variable = Ar*
    variable = Ar*S
    enable = false
  [../]


  [./Ar*New_from_Averaging]
    type = MultiAppCopyTransfer
    direction = from_multiapp
    multi_app = Averaging_Acceleration
    source_variable = Ar*
    variable = Ar*
    enable = false
  [../]
[]

#The Action the add the TimePeriod Controls to turn off and on the MultiApps
[PeriodicControllers]
  [./Shooting]
    Enable_at_cycle_start = 'MultiApps::Shooting
                              Transfers::em_to_Shooting *::Ar+_to_Shooting *::mean_en_to_Shooting
                              *::potential_to_Shooting *::Ar*_to_Shooting *::Ar*S_to_Shooting
                              Transfers::Ar*New_from_Shooting *::Ar*Relative_Diff'
    starting_cycle = 155
    cycle_frequency = 13.56e6
    cycles_between_controls = 55
    num_controller_set = 2000
    name = Shooting
  [../]

  [./Averaging_Acceleration]
    Enable_at_cycle_start = 'MultiApps::Averaging_Acceleration
                              Transfers::em_to_Averaging *::Ar+_to_Averaging *::mean_en_to_Averaging
                              *::potential_to_Averaging *::Ar*_to_Averaging *::Ar*S_to_Averaging
                              Transfers::Ar*New_from_Averaging'
    starting_cycle = 10
    cycle_frequency = 13.56e6
    cycles_between_controls = 10
    num_controller_set = 10
    name = Averaging_Acceleration
  [../]
[]

#The Action that calculate periodic relative difference
#Outputs as postprocessors named: 'var'_periodic_difference
[PeriodicRelativeNodalDifference]
  [./Plasma]
    periodic_variable_log = 'em Ar+ mean_en'
    periodic_variable = 'potential'
    starting_cycle = 0
    cycle_frequency = 13.56e6
    num_cycles = 2000
  [../]
[]

[Postprocessors]
  #Calculates Max plasma frequency
  [./InversePlasmaFreq]
    type = PlasmaFrequencyInverse
    variable = em
    use_moles = true
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  [../]

  #Counter how many cycles in a row the periodic relative difference
  #is below 1e-5
  [./em_counter]
    type = PeriodicComparisonCounter
    value1 = em_periodic_difference
    value2 = 1e-5
    frequency = 13.56e6
    comparison_type = less_than
  [../]
  [./ArIon_counter]
    type = PeriodicComparisonCounter
    value1 = Ar+_periodic_difference
    value2 = 1e-5
    frequency = 13.56e6
    comparison_type = less_than
  [../]
  [./mean_en_counter]
    type = PeriodicComparisonCounter
    value1 = mean_en_periodic_difference
    value2 = 1e-5
    frequency = 13.56e6
    comparison_type = less_than
  [../]
  [./potential_counter]
    type = PeriodicComparisonCounter
    value1 = potential_periodic_difference
    value2 = 1e-5
    frequency = 13.56e6
    comparison_type = less_than
  [../]

  #Hold the metastable relative difference during the
  #Shooting Method acceleration
  [./Meta_Relative_Diff]
    type = Receiver
  [../]
[]

#This terminates the simulation when electons, ions, mean energy,
#and potential's periodic differences is less than 1e-5 for
#10 cycles in a row and when the relative accelerated metastables
#density is less then 0.1%
[UserObjects]
  [./End]
    type = Terminator
    expression = '(if(em_counter>=10,1,0) +
                   if(ArIon_counter>=10,1,0) +
                   if(mean_en_counter>=10,1,0) +
                   if(potential_counter>=10,1,0) +
                   if(Meta_Relative_Diff<0.001,1,0)) = 5'
  [../]
[]

[Preconditioning]
  active = 'smp'
  [./smp]
    type = SMP
    full = true
  [../]

  [./fdp]
    type = FDP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  end_time = 2e-4
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 fgmres 1e-3'
  l_max_its = 20

  scheme = bdf2
  dt = 1e-9
  dtmin = 1e-14
[]

[Outputs]
  perf_graph = true
  [./out]
    type = Exodus
  [../]
[]
