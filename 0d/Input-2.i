#This tutorial is of an argon DC discharge over water at
#different reflection coefficients. Reflection coefficients
#for electron and mean energy at the water are on lines 297 and 315.

#Scaling for block 0 (Plasma)
dom0Scale = 1e-3
#Scaling for block 1 (Water)
dom1Scale = 1e-7

[GlobalParams]
  # off set for log stabilization, prevents log(0)
  offset = 20
  potential_units = kV
  #Converts density from #/m^3 to moles/m^3
  use_moles = true
[]

[Mesh]
  #Mesh is define by a Gmsh file
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
  [N2]
    order = FIRST
    block =0
  []
  [O2]
    order = FIRST
    block = 0
  []
  [O2liq]
    order = FIRST
    block = 1
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
  [NO2m]
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
  [O3liq]
    order = FIRST
    block = 1
  []
  [NO]
    order = FIRST
    block = 0
  []
  [NO2]
    order = FIRST
    block = 0
  []
  [NOliq]
    order = FIRST
    block = 1
  []
  [NO2liq]
    order = FIRST
    block = 1
  []
  [NO3liq]
    order = FIRST
    block = 1
  []
  [NO2mliq]
    order = FIRST
    block = 1
  []
  [NO3mliq]
    order = FIRST
    block = 1
  []
  [Hliq]
    order = FIRST
    block = 1
  []
  [H2liq]
    order = FIRST
    block = 1
  []
  [OHliq]
    order = FIRST
    block = 1
  []
  [O]
    order = FIRST
    block = 0
  []
  [Oliq]
    order = FIRST
    block = 1
  []
  [N]
    order = FIRST
    block = 0
  []
  [Om]
    order = FIRST
    block = 0
  []
  [Omliq]
    order = FIRST
    block = 1
  []
  [O2mliq]
    order = FIRST
    block = 1
  []
  [O3mliq]
    order = FIRST
    block = 1
  []
[]

[DriftDiffusionAction]
  [Plasma]
    #User define name for electrons (usually 'em')
    electrons = em
    #User define name for ions
    charged_particle = 'N2p O2p Om NOm NO2m O2m'
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
  # treats water as a dense plasma
  [Water]
    charged_particle = 'emliq OHm H2Om NOmliq NO2mliq NO3mliq Omliq O2mliq O3mliq'
    Neutrals = 'NOliq NO2liq NO3liq Hliq H2liq OHliq Oliq O2liq O3liq'
    potential = potential
    Is_potential_unique = false
    using_offset = true
    position_units = ${dom1Scale}
    block = 1
    Additional_Outputs = ''
  []
[]

[Reactions]
  [Air]
    #Name of reactant species that are variables
    species = 'N2 O2 em N2p N2A3 O2p O Om N NOm NO2m O2m O3 NO NO2 O2a'
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
    reactions = 'em + N2 -> em + N2A3                   : EEDF [6.17] (C11_N2_Excitation_6.17_eV)
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
                 O2m  + NO2 -> NO2m + O2                : 7.0e-16

                 Om  + NO2 -> NO2m + O                  : 1.2e-9
                 
                 NOm + NO2 -> NO2m + NO                 : 7.4e-16

                 NO2m + N2p -> NO2 + N2                 : 2e-13
                 NO2m + O2p -> NO2 + O2                 : 2e-13
                 NO2m + N2p -> NO2 + N + N              : 1e-13
                 NO2m + O2p -> NO2 + O + O              : 1e-13

                 em + N2p -> N + N                      : {1.8e-13 * (300/e_temp)^0.39}
                 em + O2p -> O + O                      : {2.7e-13 * (300/e_temp)^0.7}
                 '
  []
                 #O2a + N2 -> O2 + N2                    : 3.0e-28

  [Water]
    species = 'emliq Hliq OHliq H2liq OHm NOliq NO2liq NO2mliq NO3liq NO3mliq Oliq O2liq O3liq H2Om Omliq O2mliq O3mliq'
    reaction_coefficient_format = 'rate'
    use_log = true
    use_ad = true
    aux_species = 'H2O' 
    block = 1
    reactions = 'emliq -> Hliq + OHm                        : 1064
                 emliq + H2O -> H2Om                        : 5e-21
                 H2Om + H2O -> Hliq + OHm + H2O             : 3e-26
                 OHliq + Hliq -> H2O                        : 3e-17
                 Omliq + H2O -> OHm + OHliq                 : 3e-21
                 H2Om + Hliq -> H2liq + OHm                    : 4e-17
                 H2Om + Oliq -> Omliq + H2O                 : 3e-17
                 H2Om + O2liq -> O2mliq + H2O               : 3e-17
                 H2Om + OHliq -> OHm + OHm                  : 2e-17
                 OHliq + OHm -> Omliq + OHm                 : 8e-18
                 OHliq + O2mliq -> O2liq + OHm              : 1.5e-17
                 OHliq + NO2mliq -> OHm + NO2liq            : 1.7e-17
                 O2mliq + NOliq -> NO3mliq                  : 6e-18
                 O2liq + NOliq + NOliq -> NO2liq + NO2liq   : 7.7e-48
                 O3liq -> O2liq + Oliq                      : 3e-6
                 Oliq + O2liq -> O3liq                      : 5e-18
                 Oliq + H2O -> OHliq + OHliq                : 2.2e-23
                 Omliq + O2liq -> O3mliq                    : 5e-12
                 O3mliq -> O2liq + Omliq                    : 2.6e3
                 O3mliq + Omliq -> O2mliq + O2mliq          : 1.7e-19
                 O2mliq + NOliq -> NO3mliq                  : 6e-18
                 Hliq + NO2mliq -> NOliq + OHm              : 1.7e-16
                 Omliq + H2liq -> Hliq + OHm                : 1.3e-13
                 O2mliq + Omliq + H2O -> O2liq + OHm + OHm  : 2.98e-47
                 Hliq + H2O -> H2liq + OHliq                : 1.5e-27
                 Hliq + Hliq -> H2liq                       : 1.5e-17
                 Hliq + OHm -> H2Om                         : 3e-20

                 OHliq + NO2liq -> Hliq + NO3liq            : 2e-17
                 OHliq + NOliq -> Hliq + NO2liq             : 3.3e-17
                 '
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
  [NOm_diffusion]
    type = InterfaceDiffusion
    neighbor_var = NOm
    variable = NOliq
    D = 0.001
    D_neighbor = 1
    boundary = master1_interface
  []
  [NO_diffusion]
    type = InterfaceDiffusion
    neighbor_var = NO
    variable = NOliq
    D = 1
    D_neighbor = 1
    boundary = master1_interface
  []
  [NO2_diffusion]
    type = InterfaceDiffusion
    neighbor_var = NO2
    variable = NO2liq
    D = 0.01
    D_neighbor = 1
    boundary = master1_interface
  []
  [O_diffusion]
    type = InterfaceDiffusion
    neighbor_var = O
    variable = Oliq
    D = 0.001
    D_neighbor = 1
    boundary = master1_interface
  []
  [O2_diffusion]
    type = InterfaceDiffusion
    neighbor_var = O2
    variable = O2liq
    D = 0.001
    D_neighbor = 1
    boundary = master1_interface
  []
  [O3_diffusion]
    type = InterfaceDiffusion
    neighbor_var = O3
    variable = O3liq
    D = 0.001
    D_neighbor = 1
    boundary = master1_interface
  []
  [Omliq_diffusion]
    type = InterfaceDiffusion
    neighbor_var = Om
    variable = Omliq
    D = 0.001
    D_neighbor = 1
    boundary = master1_interface
  []
  [O2mliq_diffusion]
    type = InterfaceDiffusion
    neighbor_var = O2m
    variable = O2mliq
    D = 0.001
    D_neighbor = 1
    boundary = master1_interface
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
  
  [NO_match]
    type = MatchedValueBC
    variable = NOliq
    boundary = master1_interface
    v = NO
  #  u_coeff = 4.4e-2
  []
  [NO2_match]
    type = MatchedValueBC
    variable = NO2liq
    boundary = master1_interface
   # u_coeff = 2.8e-1
    v = NO2
  []
  #[Om_match]
  #  type = MatchedValueBC
  #  variable = Omliq
  # boundary = master1_interface
  #  v = Om
  #[]
  #[O_match]
  #  type = MatchedValueBC
  #  variable = Oliq
  #  boundary = master1_interface
  #  v = O
  #[]
  #[O2_match]
  #  type = MatchedValueBC
  #  variable = O2liq
  #  boundary = master1_interface
  #  v = O2
  #[]
  #[O3_match]
  # type = MatchedValueBC
  #  variable = O3liq
  # boundary = master1_interface
  #  v = O3
  #[]
  #[O2m_match]
  #  type = MatchedValueBC
  # variable = O2mliq
  #  boundary = master1_interface
  #  v = O2m
  #[]

  #DC BC on the air electrode
  [potential_left]
    type = NeumannCircuitVoltageMoles_KV
    variable = potential
    boundary = left
    function = potential_bc_func
    ip = 'N2p O2p NOm NO2m O2m Om' 
    data_provider = data_provider
    em = em
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
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
    mean_en = mean_en
    r = 0
    position_units = ${dom0Scale}
  []
  [sec_electrons_left]
    type = SecondaryElectronBC
    variable = em
    boundary = 'left'
    potential = potential
    ip = 'N2p O2p NOm NO2m O2m Om'
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
    ip = 'N2p O2p NOm NO2m O2m Om'
    r = 0
    position_units = ${dom0Scale}
  []

  #Ions on the powered electrode
  [N2p_physical_left_diffusion]
    type = HagelaarIonDiffusionBC
    variable = N2p
    boundary = 'left'
    r = 0
    position_units = ${dom0Scale}
  []
  [N2p_physical_left_advection]
    type = HagelaarIonAdvectionBC
    variable = N2p
    boundary = 'left'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []
  [O2p_physical_left_diffusion]
    type = HagelaarIonDiffusionBC
    variable = O2p
    boundary = 'left'
    r = 0
    position_units = ${dom0Scale}
  []
  [O2p_physical_left_advection]
    type = HagelaarIonAdvectionBC
    variable = O2p
    boundary = 'left'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []
  [NOm_physical_left_diffusion]
    type = HagelaarIonDiffusionBC
    variable = NOm
    boundary = 'left'
    r = 0
    position_units = ${dom0Scale}
  []
  [NOm_physical_left_advection]
    type = HagelaarIonAdvectionBC
    variable = NOm
    boundary = 'left'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []
  [NO2m_physical_left_diffusion]
    type = HagelaarIonDiffusionBC
    variable = NO2m
    boundary = 'left'
    r = 0
    position_units = ${dom0Scale}
  []
  [NO2m_physical_left_advection]
    type = HagelaarIonAdvectionBC
    variable = NO2m
    boundary = 'left'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []
  [O2m_physical_left_diffusion]
    type = HagelaarIonDiffusionBC
    variable = O2m
    boundary = 'left'
    r = 0
    position_units = ${dom0Scale}
  []
  [O2m_physical_left_advection]
    type = HagelaarIonAdvectionBC
    variable = O2m
    boundary = 'left'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []
  [Om_physical_left_diffusion]
    type = HagelaarIonDiffusionBC
    variable = Om
    boundary = 'left'
    r = 0
    position_units = ${dom0Scale}
  []
  [Om_physical_left_advection]
    type = HagelaarIonAdvectionBC
    variable = Om
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
    mean_en = mean_en
    r = 0.00
    position_units = ${dom0Scale}
  []
  [N2p_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = N2p
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [O2p_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = O2p
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [NOm_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = NOm
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [NO2m_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = NO2m
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [O2m_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = O2m
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [Om_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = Om
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []

  #Mean electron energy on the plasma-liquid interface
  [mean_en_physical_right]
    type = HagelaarEnergyBC
    variable = mean_en
    boundary = 'master0_interface'
    potential = potential
    em = em
    r = 0.00
    position_units = ${dom0Scale}
  []

  #Ions on the plasma-liquid interface
  [N2p_physical_right_advection]
    type = HagelaarIonAdvectionBC
    variable = N2p
    boundary = 'master0_interface'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []
  [O2p_physical_right_advection]
    type = HagelaarIonAdvectionBC
    variable = O2p
    boundary = 'master0_interface'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []
  [NOm_physical_right_advection]
    type = HagelaarIonAdvectionBC
    variable = NOm
    boundary = 'master0_interface'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []
  [NO2m_physical_right_advection]
    type = HagelaarIonAdvectionBC
    variable = NO2m
    boundary = 'master0_interface'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []
  [O2m_physical_right_advection]
    type = HagelaarIonAdvectionBC
    variable = O2m
    boundary = 'master0_interface'
    potential = potential
    r = 0
    position_units = ${dom0Scale}
  []
  [Om_physical_right_advection]
    type = HagelaarIonAdvectionBC
    variable = Om
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
  [NOliq_right]
    type = DCIonBC
    variable = NOliq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [NO2liq_right]
    type = DCIonBC
    variable = NO2liq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [NO3liq_right]
    type = DCIonBC
    variable = NO3liq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [OHliq_physical]
    type = DCIonBC
    variable = OHliq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [OHm_physical]
    type = DCIonBC
    variable = OHm
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [H2liq_physical]
    type = DCIonBC
    variable = H2liq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [H2Om_physical]
    type = DCIonBC
    variable = H2Om
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [Oliq_physical]
    type = DCIonBC
    variable = Oliq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [O2liq_physical]
    type = DCIonBC
    variable = O2liq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [Omliq_physical]
    type = DCIonBC
    variable = Omliq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [O2mliq_physical]
    type = DCIonBC
    variable = O2mliq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [O3mliq_physical]
    type = DCIonBC
    variable = O3mliq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [NOmliq_physical]
    type = DCIonBC
    variable = NOmliq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [NO2mliq_physical]
    type = DCIonBC
    variable = NO2mliq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  [NO3mliq_physical]
    type = DCIonBC
    variable = NO3mliq
    boundary = 'right'
    potential = potential
    position_units = ${dom1Scale}
  []
  #Neutrals BCs
  [O3_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = O3
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [O3_physical_left_diffusion]
    type = ADDirichletBC
    variable = O3
    boundary = 'left'
    value = -28
  []
  [NO2_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = NO2
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [NO2_physical_left_diffusion]
    type = ADDirichletBC
    variable = NO2
    boundary = 'left'
    value = -28
  []
  [NO_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = NO
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [NO_physical_left_diffusion]
    type = ADDirichletBC
    variable = NO
    boundary = 'left'
    value = -28
  []
  [O2a_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = O2a
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [O2a_physical_left_diffusion]
    type = ADDirichletBC
    variable = O2a
    boundary = 'left'
    value = -28
  []
  [O2_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = O2
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [O2_physical_left_diffusion]
    type = ADDirichletBC
    variable = O2
    boundary = 'left'
    value = 0.74518
  []
  [N2_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = N2
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [N2_physical_left_diffusion]
    type = ADDirichletBC
    variable = N2
    boundary = 'left'
    value = 3
  []
  [O_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = O
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [O_physical_left_diffusion]
    type = ADDirichletBC
    variable = O
    boundary = 'left'
    value = -28
  []
  [N_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = N
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [N_physical_left_diffusion]
    type = ADDirichletBC
    variable = N
    boundary = 'left'
    value = -28
  []
  [N2A3_physical_right_diffusion]
    type = HagelaarIonDiffusionBC
    variable = N2A3
    boundary = 'master0_interface'
    r = 0
    position_units = ${dom0Scale}
  []
  [N2A3_physical_left_diffusion]
    type = ADDirichletBC
    variable = N2A3
    boundary = 'left'
    value = -28
  []
[]

[ICs]
  [em_ic]
    type = ConstantIC
    variable = em
    value = -20
    block = 0
  []
  [emliq_ic]
    type = ConstantIC
    variable = emliq
    value = -21
    block = 1
  []
  [NO2_ic]
    type = ConstantIC
    variable = NO2
    value = -28
    block = 0
  []
  [NOliq_ic]
    type = ConstantIC
    variable = NOliq
    value = -28
    block = 1
  []
  [NO2liq_ic]
    type = ConstantIC
    variable = NO2liq
    value = -28
    block = 1
  []
  [NO3liq_ic]
    type = ConstantIC
    variable = NO3liq
    value = -28
    block = 1
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
  [NO_ic]
    type = ConstantIC
    variable = NO
    value = -28
    block = 0
  []
  [NOm_ic]
    type = ConstantIC
    variable = NOm
    value = -28
    block = 0
  []
  [NO2m_ic]
    type = ConstantIC
    variable = NO2m
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
    value = -28
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
    value = -28
    block = 0
  []
  [mean_en_ic]
    type = ConstantIC
    variable = mean_en
    value = -20
    block = 0
  []
  [OHliq_ic]
    type = ConstantIC
    variable = OHliq
    value = -15.6
    block = 1
  []
  [OHm_ic]
    type = ConstantIC
    variable = OHm
    value = -15.6
    block = 1
  []
  [H2Om_ic]
    type = ConstantIC
    variable = H2Om
    value = -15.6
    block = 1
  []
  [Omliq_ic]
    type = ConstantIC
    variable = Omliq
    value = -28
    block = 1
  []
  [O2mliq_ic]
    type = ConstantIC
    variable = O2mliq
    value = -28
    block = 1
  []
  [O3mliq_ic]
    type = ConstantIC
    variable = O3mliq
    value = -28
    block = 1
  []
  [NOmliq_ic]
    type = ConstantIC
    variable = NOmliq
    value = -28
    block = 1
  []
  [NO2mliq_ic]
    type = ConstantIC
    variable = NO2mliq
    value = -28
    block = 1
  []
  [NO3mliq_ic]
    type = ConstantIC
    variable = NO3mliq
    value = -28
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
    expression = '1.5*sin(2*3.1415926*1400*t)'
  []
  [potential_ic_func]
    type = ParsedFunction
    expression = '-1.5 * (1.0001e-3 - x)'
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
  #Also hold universal constant, such as Avogadros number, elementary charge, etc.
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

  [gas_species_0]
    type = ADHeavySpecies
    heavy_species_name = N2p
    heavy_species_mass = 4.65e-26
    heavy_species_charge = 1.0
    diffusivity = 4e-5
    block = 0
  []

  [gas_species_1]
    type = ADHeavySpecies
    heavy_species_name = N2
    heavy_species_mass = 4.65e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 4e-5
    block = 0
  []

  [gas_species_2]
    type = ADHeavySpecies
    heavy_species_name = N2A3
    heavy_species_mass = 4.65e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 4e-5
    block = 0
  []
  [gas_species_3]
    type = ADHeavySpecies
    heavy_species_name = O2p
    heavy_species_mass = 5.32e-26
    heavy_species_charge = 1.0
    diffusivity = 4e-5
    block = 0
  []
  [gas_species_32]
    type = ADHeavySpecies
    heavy_species_name = NOm
    heavy_species_mass = 7.67e-26
    heavy_species_charge = -1.0
    diffusivity = 2e-5
    block = 0
  []
  [gas_species_30]
    type = ADHeavySpecies
    heavy_species_name = NO2m
    heavy_species_mass = 4.985e-26
    heavy_species_charge = -1.0
    diffusivity = 1.7e-5
    block = 0
  []
  [gas_species_4]
    type = ADHeavySpecies
    heavy_species_name = O2m
    heavy_species_mass = 5.32e-26
    heavy_species_charge = -1.0
    diffusivity = 2e-5
    block = 0
  []
  [gas_species_5]
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
    heavy_species_name = O2liq
    heavy_species_mass = 5.32e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 2e-9
    block = 1
  []
  [gas_species_6]
    type = ADHeavySpecies
    heavy_species_name = NO
    heavy_species_mass = 4.985e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 2e-5
    block = 0
  []
  [gas_species_7]
    type = ADHeavySpecies
    heavy_species_name = N
    heavy_species_mass = 2.325e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 1e-4
    block = 0
  []
  [gas_species_9]
    type = ADHeavySpecies
    heavy_species_name = NOliq
    heavy_species_mass = 4.985e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 2.2e-9
    block = 1
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
  [gas_species_12]
    type = ADHeavySpecies
    heavy_species_name = Oliq
    heavy_species_mass = 2.66e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 1e-8
    block = 1
  []
  [gas_species_11]
    type = ADHeavySpecies
    heavy_species_name = Om
    heavy_species_mass = 2.66e-26
    heavy_species_charge = -1.0
    diffusivity = 1e-4
    block = 0
  []
  [gas_species_13]
    type = ADHeavySpecies
    heavy_species_name = NO2
    heavy_species_mass = 7.67e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 1.7e-5
    block = 0
  []
  [gas_species_14]
    type = ADHeavySpecies
    heavy_species_name = NO2liq
    heavy_species_mass = 1.033e-25
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 1.85e-9
    block = 1
  []
  [gas_species_16]
    type = ADHeavySpecies
    heavy_species_name = NO3liq
    heavy_species_mass = 1.033e-25
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 1.7e-9
    block = 1
  []
  [gas_species_17]
    type = ADHeavySpecies
    heavy_species_name = O2a
    heavy_species_mass = 5.32e-26
    heavy_species_charge = 1.0
    mobility = 0
    diffusivity = 2e-5
    block = 0
  []
  [gas_species_18]
    type = ADHeavySpecies
    heavy_species_name = O3
    heavy_species_mass = 8e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 1e-5
    block = 0
  []
  [gas_species_19]
    type = ADHeavySpecies
    heavy_species_name = O3liq
    heavy_species_mass = 8e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 5e-9
    block = 1
  []
  [gas_species_21]
    type = ADHeavySpecies
    heavy_species_name = H2Om
    heavy_species_mass = 6.3e-26
    heavy_species_charge = -1.0
    mobility = 0
    diffusivity = 5e-9
    block = 1
  []
  [gas_species_22]
    type = ADHeavySpecies
    heavy_species_name = Omliq
    heavy_species_mass = 2.66e-26
    heavy_species_charge = -1.0
    mobility = -3.87e-7
    diffusivity = 1e-8
    block = 1
  []
  [gas_species_23]
    type = ADHeavySpecies
    heavy_species_name = O2mliq
    heavy_species_mass = 2.66e-26
    heavy_species_charge = -1.0
    mobility = -1.93e-7
    diffusivity = 5e-9
    block = 1
  []
  [gas_species_24]
    type = ADHeavySpecies
    heavy_species_name = NO2mliq
    heavy_species_mass = 1.033e-25
    heavy_species_charge = -1.0
    mobility = -6.58e-8
    diffusivity = 1.7e-9
    block = 1
  []
  [gas_species_25]
    type = ADHeavySpecies
    heavy_species_name = NO3mliq
    heavy_species_mass = 1.033e-25
    heavy_species_charge = -1.0
    mobility = -6.58e-8
    diffusivity = 1.7e-9
    block = 1
  []
  [gas_species_26]
    type = ADHeavySpecies
    heavy_species_name = Hliq
    heavy_species_mass = 2.66e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 5e-9
    block = 1
  []
  [gas_species_27]
    type = ADHeavySpecies
    heavy_species_name = H2liq
    heavy_species_mass = 2.66e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 4.5e-9
    block = 1
  []
  [gas_species_28]
    type = ADHeavySpecies
    heavy_species_name = O3mliq
    heavy_species_mass = 8e-26
    heavy_species_charge = -1.0
    mobility = -8.51e-8
    diffusivity = 2.2e-9
    block = 1
  []
  [gas_species_29]
    type = ADHeavySpecies
    heavy_species_name = NOmliq
    heavy_species_mass = 4.985e-26
    heavy_species_charge = -1.0
    mobility = -8.51e-8
    diffusivity = 2.2e-9
    block = 1
  []
  [gas_species_31]
    type = ADHeavySpecies
    heavy_species_name = OHliq
    heavy_species_mass = 2.66e-26
    heavy_species_charge = 0.0
    mobility = 0
    diffusivity = 4.5e-9
    block = 1
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
  end_time = 1e-3
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'
  nl_rel_tol = 1e-4
  nl_abs_tol = 7.6e-5
  dtmin = 1e-13
  l_max_its = 10
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

#Defines the output type of the file (multiple output files can be define per run)
[Outputs]
  perf_graph = true
  [out]
    type = Exodus
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []
[]
