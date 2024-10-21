#Scaling for block 0
dom0Scale = 1e-3

[GlobalParams]
  # off set for log stabilization, prevents log(0)
  offset = 20
  #Scales the potential by V or kV
  potential_units = kV
  #Converts density from #/m^3 to moles/m^3
  use_moles = true
[]

[Mesh]
  #Sets up a 1D mesh from 0 to 0.5m with 1000 element
  [geo]
    type = GeneratedMeshGenerator
    xmin = 0
    xmax = 2
    nx = 200
    dim = 1
  []

  #Renames all sides with the specified normal
  #For 1D, this is used to rename the end points of the mesh
  [left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = geo
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

[Variables]
  [potential]
  []
  [N2]
    order = FIRST
    block =0
  []
  [O2]
    order = FIRST
    block = 0
  []
  [N2A3]
    order = FIRST
    block =0
  []
  [O2p]
    order = FIRST
    block = 0
  []
  [NOm]
    order = FIRST
    block = 0
  []
  [O2m]
    order = FIRST
    block = 0
  []
  [O2a]
    order = FIRST
    block = 0
  []
  [O3]
    order = FIRST
    block = 0
  []
  [NO]
    order = FIRST
    block = 0
  []
  [NO2]
    order = FIRST
    block = 0
  []
  [O]
    order = FIRST
    block = 0
  []
  [N]
    order = FIRST
    block = 0
  []
  [Om]
    order = FIRST
    block = 0
  []
[]

[DriftDiffusionAction]
  [Plasma]
    #User define name for electrons (usually 'em')
    electrons = em
    #User define name for ions
    charged_particle = 'N2p O2p Om NOm O2m'
    Neutrals = 'O2 N2 O N N2A3 NO NO2 O3'
    #User define name for potential (usually 'potential')
    potential = potential
    #Set False becuase both areas use the same potential
    Is_potential_unique = false
    #User define name for the electron mean energy density (usually 'mean_en')
    mean_energy = mean_en
    #Helps prevent the log(0)
    using_offset = true
    #The position scaling for the mesh, define at top of input file
    position_units = ${dom0Scale}
    #Name of material block for plasma
    block = 0
    #Additional outputs, such as ElectronTemperature, Current, and EField.
    Additional_Outputs = 'ElectronTemperature'
  []
[]

[Reactions]
  [Air]
    #Name of reactant species that are variables
    species = 'N2 O2 em N2p N2A3 O2p O Om N NOm O2m O3 NO NO2 O2a'
    #Type of coefficient (rate or townsend)
    reaction_coefficient_format = 'rate'
    #Name of the electron mean energy density (usually 'mean_en')
    electron_energy = 'mean_en'
    #Name of the electrons (usually 'em')
    electron_density = 'em'
    include_electrons = true
    file_location = 'air_test'
    potential = 'potential'
    #Defines if log form is used (true for Zapdos)
    use_log = true
    #Defines if automatic differentiation is used (true for Zapdos)
    use_ad = true
    equation_constants = 'Tgas'
    equation_variables = 'e_temp'
    equation_values = '300'
    convert_to_moles = true
    #The position scaling for the mesh, define at top of input file
    position_units = ${dom0Scale}
    block = 0
    reactions = '
    em + N2 -> em + N2A3                   : EEDF [6.17] (C11_N2_Excitation_6.17_eV)
    em + O2 -> em + O + O                  : EEDF [6.00] (C36_O2_Excitation_6.00_eV)
    em + O2a -> em + O + O                 : EEDF [6.00] (C58_O2a1_Excitation_6.00_eV)
    em + O2 -> em + O2a                    : EEDF [0.98] (C33_O2_Excitation_0.98_eV)
    em + N2 -> em + em + N2p               : EEDF [15.60] (C24_N2_Ionization_15.60_eV)
    em + N2A3 -> em + em + N2p             : EEDF [10.79] (C50_N2A3_Ionization_10.79_eV)
    em + N2 -> em + em + N2p               : EEDF [15.60] (C24_N2_Ionization_15.60_eV)
    em + O2 -> em + em + O2p               : EEDF [12.06] (C39_O2_Ionization_12.06_eV)
    em + O2a -> em + em + O2p              : EEDF [11.00] (C59_O2a1_Ionization_11.00_eV)
    em + O2 -> em + em + O2p               : EEDF [12.06] (C39_O2_Ionization_12.06_eV)
    em + N2A3 -> em + N2                   : EEDF [6.17] (C48_N2A3_De-excitation_6.17_eV)
    em + O2a -> em + O2                    : EEDF [0.98] (C55_O2a1_De-excitation_0.98_eV)
    em + O2 -> Om + O                      : EEDF (C25_O2_Attachment)
    em + NO -> Om + N                      : EEDF (C66_NO_Attachment)
    em + O3 -> Om + O2                     : EEDF (C76_O3_Attachment)
    em + O3 -> O2m + O                     : EEDF (C77_O3_Attachment)

    N + NO -> O + N2                       : {1.8e-17 * (Tgas/300.0)^0.5}

    em + NO2 -> Om + NO                    : 1.0e-17

    Om + NO -> NO2 + em                    : 2.6e-16
    Om + N2p -> O + N + N                  : 1.0e-13
    Om + O2p -> O + O + O                  : 1.0e-13              
    Om + O3 -> em + O2 + O2                : 3.0e-16
    Om + O -> O2 + em                      : 1.4e-16
    Om + N -> NO + em                      : 2.6e-16
    Om + O2a -> O3 + em                    : 3.0e-16
    Om + O2a -> O + O2 + em                : 6.9e-16
    Om + N2A3 -> N2 + O + em               : 2.2e-15

    N2A3 -> N2                             : 0.5e-6

    O2a -> O2                              : 2.6e-10
    O2a + Om -> O2m + o                    : 1.0e-16

    O2m + N -> NO2 + em                    : 5.0e-16
    O2m + O -> O3  + em                    : 1.5e-16
    O2m + N2p -> N + N + O2                : 1.0e-13
    O2m + O2p -> O + O + O2                : 1.0e-13
    O2m + N2A3 -> O2 + N2 + em             : 2.1e-15
    O2m + O2a -> O2 + O2 + em              : 3.6e-16

    em + N2p -> N + N                      : {1.8e-13 * (300/e_temp)^0.39}
    em + O2p -> O + O                      : {2.7e-13 * (300/e_temp)^0.7}
    '
  []
[]

[AuxVariables]
[]

[BCs]

  [potential_left]
    type = FunctionDirichletBC
    variable = potential
    boundary = 'left'
    function = potential_bc_func
    preset = false
  []
  [potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = 'right'
    value = 0
    preset = false
  []

  #Electrons on the powered electrode
  [em_physical]
    type = HagelaarElectronBC
    variable = em
    boundary = 'left right'
    potential = potential
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
  []
  [em_advection_left]
    type = HagelaarElectronAdvectionBC
    variable = em
    boundary = 'left right'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []
  [sec_electrons_left]
    type = SecondaryElectronBC
    variable = em
    boundary = 'left'
    potential = potential
    ip = 'N2p O2p'
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
  []

  #Mean electron energy on the powered electrode
  [mean_en_physical_left]
    type = HagelaarEnergyBC
    variable = mean_en
    boundary = 'left'
    potential = potential
    em = em
    r = 0
    position_units = ${dom0Scale}
  []
  [secondary_energy_left]
    type = SecondaryElectronEnergyBC
    variable = mean_en
    boundary = 'left'
    potential = potential
    em = em
    ip = 'N2p O2p'
    r = 0
    position_units = ${dom0Scale}
  []

  #Ions diffusion/advection
  [N2p_physical_left_diffusion]
    type = HagelaarIonDiffusionBC
    variable = N2p
    boundary = 'left'
    r = 0.1
    position_units = ${dom0Scale}
  []
  [N2p_physical_left_advection]
    type = HagelaarIonAdvectionBC
    variable = N2p
    boundary = 'left'
    potential = potential
    r = 0.1
    position_units = ${dom0Scale}
  []
  [N2p_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = N2p
    boundary = 'right'
    r = 0.0
    position_units = ${dom0Scale}
  []
  [N2p_physical_right_advection]
    type = HagelaarIonAdvectionBC
    variable = N2p
    boundary = 'right'
    potential = potential
    r = 0.0
    position_units = ${dom0Scale}
  []
  [O2p_physical_left_diffusion]
    type = HagelaarIonDiffusionBC
    variable = O2p
    boundary = 'left'
    r = 0.1
    position_units = ${dom0Scale}
  []
  [O2p_physical_left_advection]
    type = HagelaarIonAdvectionBC
    variable = O2p
    boundary = 'left'
    potential = potential
    r = 0.1
    position_units = ${dom0Scale}
  []
  [O2p_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = O2p
    boundary = 'right'
    r = 0.0
    position_units = ${dom0Scale}
  []
  [O2p_physical_right_advection]
    type = HagelaarIonAdvectionBC
    variable = O2p
    boundary = 'right'
    potential = potential
    r = 0.0
    position_units = ${dom0Scale}
  []
  [NOm_physical_diffusion]
    type = HagelaarIonDiffusionBC
    variable = NOm
    boundary = 'right left'
    r = 0
    position_units = ${dom0Scale}
  []
  [NOm_physical_advection]
    type = HagelaarIonAdvectionBC
    variable = NOm
    boundary = 'right left'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []
  [O2m_physical_diffusion]
    type = HagelaarIonDiffusionBC
    variable = O2m
    boundary = 'right left'
    r = 0
    position_units = ${dom0Scale}
  []
  [O2m_physical_advection]
    type = HagelaarIonAdvectionBC
    variable = O2m
    boundary = 'right left'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []
  [Om_physical_diffusion]
    type = HagelaarIonDiffusionBC
    variable = Om
    boundary = 'right left'
    r = 0
    position_units = ${dom0Scale}
  []
  [Om_physical_advection]
    type = HagelaarIonAdvectionBC
    variable = Om
    boundary = 'right left'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []

  #Neutrals BCs
  [O3_physical_right_diffusion]
    type = DriftDiffusionDoNothingBC
    variable = O3
    boundary = 'right'
    position_units = ${dom0Scale}
    potential = potential
    diff = 1e-5
    mu = 0
    sign = 1
  []
  [NO2_physical_right_diffusion]
    type = DriftDiffusionDoNothingBC
    variable = NO2
    boundary = 'right'
    position_units = ${dom0Scale}
    potential = potential
    diff = 3e-5
    mu = 0
    sign = 1
  []
  [NO_physical_right_diffusion]
    type = DriftDiffusionDoNothingBC
    variable = NO
    boundary = 'right'
    position_units = ${dom0Scale}
    potential = potential
    diff = 2e-5
    mu = 0
    sign = 1
  []
  [O2a_physical_right_diffusion]
    type = DriftDiffusionDoNothingBC
    variable = O2a
    boundary = 'right'
    position_units = ${dom0Scale}
    potential = potential
    diff = 2e-5
    mu = 0
    sign = 1
  []
  [O2_physical_left_diffusion]
    type = ADDirichletBC
    variable = O2
    boundary = 'left'
    value = 0.74518
  []
  [O2_physical_right_diffusion]
    type = DriftDiffusionDoNothingBC
    variable = O2
    boundary = 'right'
    position_units = ${dom0Scale}
    potential = potential
    diff = 2e-5
    mu = 0
    sign = 1
  []
  [N2_physical_left_diffusion]
    type = ADDirichletBC
    variable = N2
    boundary = 'left'
    value = 3
  []
  [N2_physical_right_diffusion]
    type = DriftDiffusionDoNothingBC
    variable = N2
    boundary = 'right'
    position_units = ${dom0Scale}
    potential = potential
    diff = 3e-5
    mu = 0
    sign = 1
  []
  [O_physical_right_diffusion]
    type = DriftDiffusionDoNothingBC
    variable = O
    boundary = 'right'
    position_units = ${dom0Scale}
    potential = potential
    diff = 1e-4
    mu = 0
    sign = 1
  []
  [N_physical_right_diffusion]
    type = DriftDiffusionDoNothingBC
    variable = N
    boundary = 'right'
    position_units = ${dom0Scale}
    potential = potential
    diff = 1e-4
    mu = 0
    sign = 1
  []
  [N2A3_physical_right_diffusion]
    type = DriftDiffusionDoNothingBC
    variable = N2A3
    boundary = 'right'
    position_units = ${dom0Scale}
    potential = potential
    diff = 3e-5
    mu = 0
    sign = 1
  []
[]

[ICs]
  [em_ic]
    type = ConstantIC
    variable = em
    value = -20
    block = 0
  []
  [NO2_ic]
    type = ConstantIC
    variable = NO2
    value = -28
    block = 0
  []
  [N2_ic]
    type = ConstantIC
    variable = N2
    value = 2.9807
    block = 0
  []
  [O2_ic]
    type = ConstantIC
    variable = O2
    value = 0.74518
    block = 0
  []
  [N2p_ic]
    type = ConstantIC
    variable = N2p
    value = -21
    block = 0
  []
  [O2p_ic]
    type = ConstantIC
    variable = O2p
    value = -21
    block = 0
  []
  [NOm_ic]
    type = ConstantIC
    variable = NOm
    value = -28
    block = 0
  []
  [O2m_ic]
    type = ConstantIC
    variable = O2m
    value = -21
    block = 0
  []
  [N_ic]
    type = ConstantIC
    variable = N
    value = -28
    block = 0
  []
  [O3_ic]
    type = ConstantIC
    variable = O3
    value = -25
    block = 0
  []
  [O_ic]
    type = ConstantIC
    variable = O
    value = -28
    block = 0
  []
  [Om_ic]
    type = ConstantIC
    variable = Om
    value = -21
    block = 0
  []
  [NO_ic]
    type = ConstantIC
    variable = NO
    value = -25
    block = 0
  []
  [mean_en_ic]
    type = ConstantIC
    variable = mean_en
    value = -20
    block = 0
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
    expression = '1*sin(2*3.1415926*1400*t)'
  []
  [potential_ic_func]
    type = ParsedFunction
    expression = '-1 * (2e-3 - x)'
  []
[]

[Materials]

  [electrons_in_plasma]
    type = GasElectronMoments
    interp_trans_coeffs = true
    interp_elastic_coeff = true
    ramp_trans_coeffs = false
    user_electron_diffusion_coeff = 0.9
    user_electron_mobility = 0.215
    user_p_gas = 101325
    user_se_coeff = 0.05
    em = em
    potential = potential
    mean_en = mean_en
    block = 0
    property_tables_file = 'townsend_coefficients/moments.txt'
  []

  [gas_species_0]
    type = ADHeavySpecies
    heavy_species_name = N2p
    heavy_species_mass = 4.66e-26
    heavy_species_charge = 1.0
    mobility = 1.55e-3
    diffusivity = 4e-5
    block = 0
  []

  [gas_species_1]
    type = ADHeavySpecies
    heavy_species_name = N2
    heavy_species_mass = 4.66e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 3e-5
    block = 0
  []

  [gas_species_2]
    type = ADHeavySpecies
    heavy_species_name = N2A3
    heavy_species_mass = 4.66e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 3e-5
    block = 0
  []
  [gas_species_3]
    type = ADHeavySpecies
    heavy_species_name = O2p
    heavy_species_mass = 5.32e-26
    heavy_species_charge = 1.0
    mobility = 7.74e-4
    diffusivity = 2e-5
    block = 0
  []
  [gas_species_4]
    type = ADHeavySpecies
    heavy_species_name = NOm
    heavy_species_mass = 4.99e-26
    heavy_species_charge = -1.0
    mobility = 7.74e-4
    diffusivity = 2e-5
    block = 0
  []
  [gas_species_5]
    type = ADHeavySpecies
    heavy_species_name = O2m
    heavy_species_mass = 5.32e-26
    heavy_species_charge = -1.0
    mobility = 7.74e-4
    diffusivity = 2e-5
    block = 0
  []
  [gas_species_6]
    type = ADHeavySpecies
    heavy_species_name = O2
    heavy_species_mass = 5.32e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 2e-5
    block = 0
  []
  [gas_species_8]
    type = ADHeavySpecies
    heavy_species_name = NO
    heavy_species_mass = 4.99e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 2e-5
    block = 0
  []
  [gas_species_9]
    type = ADHeavySpecies
    heavy_species_name = N
    heavy_species_mass = 2.33e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 1e-4
    block = 0
  []
  [gas_species_10]
    type = ADHeavySpecies
    heavy_species_name = O
    heavy_species_mass = 2.66e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 1e-4
    block = 0
  []
  [gas_species_11]
    type = ADHeavySpecies
    heavy_species_name = Om
    heavy_species_mass = 2.66e-26
    heavy_species_charge = -1.0
    mobility = 3.87e-3
    diffusivity = 1e-4
    block = 0
  []
  [gas_species_12]
    type = ADHeavySpecies
    heavy_species_name = NO2
    heavy_species_mass = 7.65e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 1.7e-5
    block = 0
  []
  [gas_species_13]
    type = ADHeavySpecies
    heavy_species_name = O2a
    heavy_species_mass = 5.32e-26
    heavy_species_charge = 1.0
    mobility = 0
    diffusivity = 2e-5
    block = 0
  []
  [gas_species_14]
    type = ADHeavySpecies
    heavy_species_name = O3
    heavy_species_mass = 8e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 1e-5
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

[Executioner]
  type = Transient
  end_time = 0.007
  petsc_options = '-snes_converged_reason'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'
  nl_rel_tol = 1e-4
  nl_abs_tol = 7.6e-5
  dtmin = 1e-11
  dtmax = 1e-6
  l_max_its = 15
  nl_max_its = 30


  [TimeSteppers]
    [Adaptive]
      type = IterationAdaptiveDT
      cutback_factor = 0.4
      dt = 1e-12
      growth_factor = 1.2
      optimal_iterations = 30
    []
  []
[]


#automatic_scaling = true
#compute_scaling_once = false

#Defines the output type of the file (multiple output files can be define per run)
[Outputs]
  perf_graph = true
  [out]
    type = Exodus
    execute_on = 'INITIAL TIMESTEP_END final'
    interval = 10
  []
[]