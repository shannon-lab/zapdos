#Scaling for block 0 (Plasma)
dom0Scale = 1e-3
#Scaling for block 1 (Water)
dom1Scale = 1e-7

[GlobalParams]
  # off set for log stabilization, prevents log(0)
  offset = 20

  potential_units = kV
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
    potential = potential
    #Set False becuase both areas use the same potential
    Is_potential_unique = false
    mean_energy = mean_en
    using_offset = true #helps prevent the log(0)
    #The position scaling for the mesh, define at top of input file
    position_units = ${dom0Scale}
    #Name of material block for plasma
    block = 0
    Additional_Outputs = 'ElectronTemperature'
  []

  [Water]
    charged_particle = 'emliq OHm'
    potential = potential
    Is_potential_unique = false
    using_offset = true
    position_units = ${dom1Scale}
    #Name of material block for water
    block = 1
    Additional_Outputs = ''
  []
[]

[Reactions]
  [Air]
    species = 'em N2 N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N2A3 N2B3 N2a_1 N N2D N2P N+ N2+ N3+ O2 O2v1 O2v2 O2v3 O2v4 O2a1 O2b1 O O3 O+ O2+ O4+ O- O2- O3- NO N2O NO2 NO3 N2O5 NO+ N2O+ NO2+ NO- N2O- NO2- NO3- O2pN2'
    aux_species = 'M'
    reaction_coefficient_format = 'rate'
    gas_species = 'M'
    electron_energy = 'mean_en'
    electron_density = 'em'
    include_electrons = true
    file_location = 'townsend_coefficients'
    potential = 'potential'
    equation_constants = 'Tgas'
    equation_values = '300'
    use_log = true
    use_ad = true
    position_units = ${dom0Scale}
    block = 0
    #Reaction rates for 300K in meters
    reactions = '
                 # excitation of electronic levels by electron impact (Bolsig+)
                 # Note that CRANE will need to be modified to allow duplicate reactions here...
                 #####
                 em + N2 -> em + N2A3                 : EEDF (C11_N2_Excitation_6.17_eV)
                 em + N2 -> em + N2A3                 : EEDF (C12_N2_Excitation_7.00_eV)
                 em + N2 -> em + N2A3                 : EEDF (C13_N2_Excitation_7.80_eV)
                 em + N2 -> em + N2B3                 : EEDF (C14_N2_Excitation_7.35_eV)
                 em + N2 -> em + N2B3                 : EEDF (C15_N2_Excitation_7.36_eV)
                 em + N2 -> em + N2B3                 : EEDF (C16_N2_Excitation_8.16_eV)
                 em + N2 -> em + N2a_1                : EEDF (C17_N2_Excitation_8.40_eV)
                 em + N2 -> em + N2a_1                : EEDF (C18_N2_Excitation_8.55_eV)
                 em + N2 -> em + N2a_1                : EEDF (C19_N2_Excitation_8.89_eV)
                 em + O2 -> em + O2a1                 : EEDF (C33_O2_Excitation_0.98_eV)
                 em + O2 -> em + O2b1                 : EEDF (C34_O2_Excitation_1.63_eV)
                 em + O2 -> em + O + O                : EEDF (C36_O2_Excitation_6.00_eV)
                 em + O2a1 -> em + O + O              : EEDF (C58_O2a1_Excitation_6.00_eV)
                 ####
                 # de-excitation of electronic levels by electron impact (BOLSIG+)
                 ####
                 em + N2A3 -> em + N2                 : EEDF (C48_N2A3_De-excitation_6.17_eV)
                 em + O2a1 -> em + O2                 : EEDF (C55_O2a1_De-excitation_0.98_eV)
                 ####
                 # ionization by electron impact (BOLSIG+)
                 # note the missing data section in the inp file (4 extra reactions - not shown here)
                 ####
                 em + N -> em + em + N+                : EEDF (C61_N_Ionization_14.55_eV)
                 em + O -> em + em + O+                : EEDF (C65_O_Ionization_13.62_eV)
                 em + N2 -> em + em + N2+              : EEDF (C24_N2_Ionization_15.60_eV)
                 em + N2A3 -> em + em + N2+            : EEDF (C50_N2A3_Ionization_10.79_eV)
                 em + O2 -> em + em + O2+              : EEDF (C39_O2_Ionization_12.06_eV)
                 em + O2a1 -> em + em + O2+            : EEDF (C59_O2a1_Ionization_11.00_eV)
                 em + NO -> em + em + NO+              : EEDF (C75_NO_Ionization_9.26_eV)
                 ####
                 # electron-ion recombination
                 ####
                 em + N2+ -> N + N                   : {1.8e-7 * (300/Te)^0.39 * 0.5}
                 em + N2+ -> N + N2D                 : {1.8e-7 * (300/Te)^0.39 * 0.45}
                 em + N2+ -> N + N2P                 : {1.8e-7 * (300/Te)^0.39 * 0.05}
                 em + O2+ -> O + O                   : {2.7e-7 * (300/Te)^0.7 * 0.55}
                 em + NO+ -> O + N                   : {4.2e-7 * (300/Te)^0.85 * 0.2}
                 em + NO+ -> O + N2D                 : {4.2e-7 * (300/Te)^0.85 * 0.8}
                 em + N3+ -> N2 + N                  : {2.0e-7 * (300/Te)^0.5}
                 em + O4+ -> O2 + O2                 : {1.4e-6 * (300/Te)^0.5}
                 em + O2pN2 -> O2 + N2               : {1.3e-6 * (300/Te)^0.5}
                 em + em + N+ -> N + em                 : {7.0e-20 * (300/Te)^4.5}
                 em + em + O+ -> O + em                 : {7.0e-20 * (300/Te)^4.5}
                 em + N+ + M -> N + M                   : {6.0e-27 * (300/Te)^1.5}
                 em + O+ + M -> O + M                   : {6.0e-27 * (300/Te)^1.5}
                 ####
                 em + O2 -> O- + O                      : EEDF (C25_O2_Attachment)
                 em + NO -> O- + N                      : EEDF (C66_NO_Attachment)
                 em + O3 -> O- + O2                     : EEDF (C76_O3_Attachment)
                 em + O3 -> O2- + O                     : EEDF (C77_O3_Attachment)
                 em + O + O2 -> O- + O2                 : 1e-31
                 em + O + O2 -> O2- + O                 : 1e-31
                 em + O3 + M -> O3- + M                 : 1e-31
                 em + NO + M -> NO- + M                 : 1e-31
                 em + O2 + N2 -> O2- + N2               : {1.1e-31 * (300/Te)^2 * exp(-70/Tgas) * exp(1500*(Te-Tgas)/(Te*Tgas))}
                 ####
                 # electron detachment
                 ####
                 O-  + O -> O2  + em                    : 1.4e-10
                 O-  + N -> NO  + em                    : 2.6e-10
                 O-  + O2 -> O3  + em                   : 5.0e-15
                 O-  + O2a1 -> O3  + em                 : 3.0e-10
                 O-  + O2b1 -> O   + O2 + em            : 6.9e-10
                 O-  + N2A3 -> O   + N2 + em            : 2.2e-9
                 O-  + N2B3 -> O   + N2 + em            : 1.9e-9
                 O-  + O3 -> O2  + O2 + em              : 3.0e-10
                 O2- + O -> O3  + em                    : 1.5e-10
                 O2- + O2 -> O2  + O2 + em              : {2.7e-10 * (TeffN2/300)^0.5 * exp(-5590/TeffN2)}
                 O2- + O2a1 -> O2  + O2 + em            : 2.0e-10
                 O2- + O2b1 -> O2  + O2 + em            : 3.6e-10
                 O2- + N2 -> O2  + N2 + em              : {1.9e-12 * (TeffN2/300)^0.5 * exp(-4990/TeffN2)}
                 O2- + N2A3 -> O2  + N2 + em            : 2.1e-9
                 O2- + N2B3 -> O2  + N2 + em            : 2.5e-9
                 O3- + O -> O2  + O2 + em               : 3.0e-10
                 ####
                 # Detachment for O3- NO- N2O- NO2- NO3- has to be verified (from inp source file)
                 ####
                 O3- + N -> NO + O2 + em                : 5e-10
                 O3- + N2A3 -> O3 + N2 + em             : 2.1e-9
                 NO- + N2A3 -> NO + N2 + em             : 2.1e-9
                 O3- + N2B3 -> O3 + N2 + em             : 2.5e-9
                 NO- + N2B3 -> NO + N2 + em             : 2.5e-9
                 ####
                 # optical transitions and predissociation (Capitelli2000, page 157)
                 ####
                 N2A3 -> N2                             : 0.5 
                 N2B3 -> N2A3                           : 1.34e5
                 N2a_1 -> N2                            : 1e2
                 O2a1 -> O2                             : 2.6e-4
                 O2b1 -> O2a1                           : 1.5e-3
                 O2b1 -> O2                             : 8.5e-2
                 ####
                 # quenching and excitation of N2 (Capitelli2000, page 159)
                 ####
                 N2A3 + O -> NO + N2D                 : 7e-12
                 N2A3 + N -> N2 + N                   : 2e-12
                 N2A3 + N -> N2 + N2P                 : {4.0e-11 * (300/Tgas)^0.667}
                 N2A3 + O2 -> N2 + O2a1               : {2.0e-13 * (Tgas/300)^0.55}
                 N2A3 + O2 -> N2 + O2b1               : {2.0e-13 * (Tgas/300)^0.55}
                 N2A3 + N2 -> N2 + N2                 : 3e-16 
                 N2A3 + NO -> N2 + NO                 : 6.9e-11
                 N2A3 + N2A3 -> N2 + N2B3             : 3e-10
                 N2B3 + N2 -> N2A3 + N2               : 3e-11
                 N2B3 + N2 -> N2 + N2                 : 2e-12
                 N2B3 + O2 -> N2 + O + O              : 3e-10
                 N2B3 + NO -> N2A3 + NO               : 2.4e-10
                 N2a_1 + N2 -> N2B3 + N2              : 1.93e-13
                 N2a_1 + O2 -> N2 + O + O             : 2.8e-11
                 N2a_1 + NO -> N2 + N + O             : 3.6e-10
                 N + N + N2 -> N2A3 + N2              : 1.7e-33
                 N + N + O2 -> N2A3 + O2              : 1.7e-33
                 N + N + NO -> N2A3 + NO              : 1.7e-33
                 N + N + N -> N2A3 + N                : 1e-32
                 N + N + O -> N2A3 + O                : 1e-32
                 N + N + N2 -> N2B3 + N2              : 2.4e-33
                 N + N + O2 -> N2B3 + O2              : 2.4e-33
                 N + N + NO -> N2B3 + NO              : 2.4e-33
                 N + N + N -> N2B3 + N                : 1.4e-32
                 N + N + O -> N2B3 + O                : 1.4e-32
                 ####
                 # deactivation of N metastables (Capitelli2000, page 161)
                 ####
                 N2D + O2 -> NO + O                   : 5.2e-12
                 N2D + NO -> N2 + O                   : 1.8e-10
                 N2D + N2 -> N + N2                   : {1.0e-13 * exp(-510/Tgas)}
                 N2P + N -> N + N                     : 1.8e-12
                 N2P + O -> N + O                     : 1.0e-12
                 N2P + N -> N2D + N                   : 6.0e-13
                 N2P + N2 -> N + N2                   : 6.0e-14
                 N2P + N2D -> N2+ + em                 : 1.0e-13
                 N2P + O2 -> NO + O                   : 2.6e-12
                 N2P + NO -> N2A3 + O                 : 3.0e-11
                 ####
                 # quenching and excitation of O2 (Capitelli2000, page 160)
                 ####
                 O2a1 + O -> O2 + O                   : 7.0e-16
                 O2a1 + N -> NO + O                   : {2.0e-14 * exp(-600/Tgas)}
                 O2a1 + O2 -> O2 + O2                 : {3.8e-18 * exp(-205/Tgas)}
                 O2a1 + N2 -> O2 + N2                 : 3.0e-21
                 O2a1 + NO -> O2 + NO                 : 2.5e-11
                 O2a1 + O2a1 -> O2 + O2b1             : {7.0e-28 * Tgas^3.8 * exp(700/Tgas)}
                 O + O3 -> O2 + O2a1                  : {1.0e-11 * exp(-2300/Tgas)}
                 O2b1 + O -> O2a1 + O                 : 8.1e-14
                 O2b1 + O2 -> O2a1 + O2               : {4.3e-22 * Tgas^2.4 * exp(-281/Tgas)}
                 O2b1 + N2 -> O2a1 + N2               : {1.7e-15 * (Tgas/300)}
                 O2b1 + NO -> O2a1 + NO               : 6.0e-14
                 O2b1 + O3 -> O2 + O2 + O             : 2.2e-11
                 ####
                 # bimolecular nitrogen-oxygen reactions (Capitelli2000, page 168)
                 # Two missing reactions: 
                 # N + O3 -> NO + O2 : < 2.0e-16
                 # O + N2O5 -> product : < 3.0e-16
                 ####
                 N + NO -> O + N2                     : {1.8e-11 * (Tgas/300.0)^0.5}
                 N + O2 -> O + NO                     : {3.2e-12 * (Tgas/300.0) * exp(-3150/Tgas)}
                 O + N2 -> N + NO                     : {3.0e-10 * exp(-38370/Tgas)}
                 O + NO -> N + O2                     : {7.5e-12 * (Tgas/300.0) * exp(-19500/Tgas)}
                 NO + NO -> N2 + O2                   : {5.1e-13 * exp(-33660/Tgas)}
                 O2 + O2 -> O + O3                    : {2.0e-11 * exp(-49800/Tgas)}
                 N + N -> N2+ + em                     : {2.7e-11 * exp(-6.74e4/Tgas)}
                 N + O -> NO+ + em                     : {1.6e-12 * (Tgas/300)^0.5 * (0.19+8.6*Tgas) * exp(-32000/Tgas)}
                 ####
                 # dissociation of nitrogen-oxygen molecules (Capitelli2000, page 169)
                 ####
                 N2 + N2 -> N + N + N2                : {5.4e-8 * (1.0 - exp(-3354/Tgas)) * exp(-113200/Tgas)}
                 O2 + N2 -> N + N + O2                : {5.4e-8 * (1.0 - exp(-3354/Tgas)) * exp(-113200/Tgas)}
                 NO + N2 -> N + N + NO                : {5.4e-8 * (1.0 - exp(-3354/Tgas)) * exp(-113200/Tgas)}
                 O + N2 -> N + N + O                  : {5.4e-8 * (1.0 - exp(-3354/Tgas)) * exp(-113200/Tgas) * 6.6}
                 N + N2 -> N + N + N                  : {5.4e-8 * (1.0 - exp(-3354/Tgas)) * exp(-113200/Tgas) * 6.6}
                 O2 + N2 -> O + O + N2                : {6.1e-9 * (1.0 - exp(-2240/Tgas)) * exp(-59380/Tgas)}
                 O2 + O2 -> O + O + O2                : {6.1e-9 * (1.0 - exp(-2240/Tgas)) * exp(-59380/Tgas) * 5.9}
                 O2 + O -> O + O + O                  : {6.1e-9 * (1.0 - exp(-2240/Tgas)) * exp(-59380/Tgas) * 21}
                 O2 + N -> O + O + N                  : {6.1e-9 * (1.0 - exp(-2240/Tgas)) * exp(-59380/Tgas)}
                 O2 + NO -> O + O + NO                : {6.1e-9 * (1.0 - exp(-2240/Tgas)) * exp(-59380/Tgas)}
                 NO + N2 -> N + O + N2                : {8.7e-9 * exp(-75994/Tgas)}
                 NO + O2 -> N + O + O2                : {8.7e-9 * exp(-75994/Tgas)}
                 NO + O -> N + O + O                  : {8.7e-9 * exp(-75994/Tgas) * 20}
                 NO + N -> N + O + N                  : {8.7e-9 * exp(-75994/Tgas) * 20}
                 NO + NO -> N + O + NO                : {8.7e-9 * exp(-75994/Tgas) * 20}
                 O3 + N2 -> O2 + O + N2               : {6.6e-10 * exp(-11600/Tgas)}
                 O3 + O2 -> O2 + O + O2               : {6.6e-10 * exp(-11600/Tgas) * 0.38}
                 O3 + N -> O2 + O + N                 : {6.6e-10 * exp(-11600/Tgas) * 6.3*exp(170/Tgas)}
                 O3 + O -> O2 + O + O                 : {6.6e-10 * exp(-11600/Tgas) * 6.3*exp(170/Tgas)}
                 ####
                 # recombination of nitrogen-oxygen molecules (Capitelli, page 170)
                 # note "max" rate coefficients in the source file.
                 # Do not know how to implement something similar in CRANE.
                 ####
                 N + N + N2 -> N2 + N2                : {8.3e-34 * exp(500/Tgas)}
                 N + N + O2 -> N2 + O2                : {1.8e-33 * exp(435/Tgas)}
                 N + N + NO -> N2 + NO                : {1.8e-33 * exp(435/Tgas)}
                 N + N + N -> N2 + N                  : {1.8e-33 * exp(435/Tgas) * 3}
                 N + N + O -> N2 + O                  : {1.8e-33 * exp(435/Tgas) * 3}
                 O + O + N2 -> O2 + N2                : {2.8e-34 * exp(720/Tgas)}
                 O + O + O2 -> O2 + O2                : {4.0e-33 * (300/Tgas)^0.41}
                 O + O + N -> O2 + N                  : {4.0e-33 * (300/Tgas)^0.41 * 0.8}
                 O + O + O -> O2 + O                  : {4.0e-33 * (300/Tgas)^0.41 * 3.6}
                 O + O + NO -> O2 + NO                : {4.0e-33 * (300/Tgas)^0.41 * 0.17}
                 N + O + N2 -> NO + N2                : {1.0e-32 * (300/Tgas)^0.5}
                 N + O + O2 -> NO + O2                : {1.0e-32 * (300/Tgas)^0.5}
                 N + O + N -> NO + N                  : {1.8e-31 * (300/Tgas)}
                 N + O + O -> NO + O                  : {1.8e-31 * (300/Tgas)}
                 N + O + NO -> NO + NO                : {1.8e-31 * (300/Tgas)}
                 O + O2 + N2 -> O3 + N2               : {5.8e-34 * (300/Tgas)^2.8}
                 O + O2 + O2 -> O3 + O2               : {7.6e-34 * (300/Tgas)^1.9}
                 O + O2 + NO -> O3 + NO               : {7.6e-34 * (300/Tgas)^1.9}
                 O + O2 + N -> O3 + N                 : {3.9e-33 * (300/Tgas)^1.9}
                 O + O2 + O -> O3 + O                 : {3.9e-33 * (300/Tgas)^1.9}
                 ####
                 # positive ion reactions (Capitelli, 179)
                 ####
                 N+ + O   -> N + O+                              : 1.0e-12
                 N+ + O2  -> O2+ + N                              : 2.8e-10
                 N+ + O2  -> NO+ + O                              : 2.5e-10
                 N+ + O2  -> O+ + NO                              : 2.8e-11
                 N+ + O3  -> NO+ + O2                             : 5.0e-10
                 N+ + NO  -> NO+ + N                              : 8.0e-10
                 N+ + NO  -> N2+ + O                              : 3.0e-12
                 N+ + NO  -> O+ + N2                              : 1.0e-12
                 O+ + N2 -> NO+ + N                               : {( 1.5 - 2.0e-3*TeffN + 9.6e-7*TeffN^2 ) * 1.0e-12}
                 O+ + O2 -> O2+ + O                               : {2.0e-11 * (300/TeffN)^0.5}
                 O+ + O3 -> O2+ + O2                              : 1.0e-10
                 O+ + NO -> NO+ + O                               : 2.4e-11
                 O+ + NO -> O2+ + N                               : 3.0e-12
                 O+ + N2D -> N+ + O                               : 1.3e-10
                 N2+ + O2 -> O2+ + N2                             : {6.0e-11 * (300/TeffN2)^0.5}
                 N2+ + O  -> NO+ + N                              : {1.3e-10 * (300/TeffN2)^0.5}
                 N2+ + O3 -> O2+ + O + N2                         : 1.0e-10
                 N2+ + N  -> N+ + N2                              : {7.2e-13 * (TeffN2/300)}
                 N2+ + NO -> NO+ + N2                             : 3.3e-10
                 O2+ + N2 -> NO+ + NO                             : 1.0e-17
                 O2+ + N  -> NO+ + O                              : 1.2e-10
                 O2+ + NO -> NO+ + O2                             : 6.3e-10
                 N3+ + O2 -> O2+ + N + N2                         : 2.3e-11
                 N3+ + N  -> N2+ + N2                             : 6.6e-11
                 N3+ + NO -> NO+ + N + N2                         : 7.0e-11
                 O4+ + N2 -> O2pN2 + O2                           : {4.6e-12 * (TeffN4/300)^2.5 * exp(-2650/TeffN4)}
                 O4+ + O2 -> O2+ + O2 + O2                        : {3.3e-6  * (300/TeffN4)^4   * exp(-5030/TeffN4)}
                 O4+ + O2a1 -> O2+ + O2 + O2                      : 1.0e-10
                 O4+ + O2b1 -> O2+ + O2 + O2                      : 1.0e-10
                 O4+ + O      -> O2+ + O3                         : 3.0e-10
                 O4+ + NO     -> NO+ + O2 + O2                    : 1.0e-10
                 O2pN2 + N2 -> O2+ + N2 + N2                      : {1.1e-6 * (300/TeffN4)^5.3 * exp(-2360/TeffN4)}
                 O2pN2 + O2 -> O4+ + N2                           : 1.0e-9
                 N+ + N2 + N2 -> N3+ + N2                         : {1.7e-29 * (300/TeffN)^2.1}
                 N+ + O + M -> NO+ + M        : 1.0e-29
                 N+ + N + M -> N2+ + M        : 1.0e-29
                 O+ + N2 + M -> NO+ + N + M   : {6.0e-29 * (300/TeffN)^2}
                 O+ + O  + M -> O2+ + M       : 1.0e-29
                 O+ + N  + M -> NO+ + M       : 1.0e-29
                 N2+ + N  + N2 -> N3+ + N2                        : {9.0e-30 * exp(400/TeffN2)}
                 O2+ + O2 + O2 -> O4+ + O2                        : {2.4e-30 * (300/TeffN2)^3.2}
                 O2+ + N2 + N2 -> O2pN2 + N2                      : {9.0e-31 * (300/TeffN2)^2}
                 ####
                 # negative ion reactions (Capitelli, 182-183)
                 # NOTE missing reactions: 
                 # O2^- + N2O    => O3^-  + N2                       ! < 1.0d-12
                 #O3^- + N2     => NO2^- + NO                       ! < 5.0d-14
                 ####
                 O-   + O2a1 -> O2-  + O                          : 1.0e-10
                 O-   + O3 -> O3-  + O                            : 8.0e-10
                 O2-  + O -> O-   + O2                            : 3.3e-10
                 O2-  + O3 -> O3-  + O2                           : 3.5e-10
                 O3-  + O -> O2-  + O2                            : 1.0e-11
                 NO-  + O2 -> O2-  + NO                           : 5.0e-10
                 O-  + O2 + M -> O3- + M      : {1.1e-30 * (300./TeffN)}
                 ####
                 # ion-ion recombination (Kossyi1992)
                 ####
                 O- + N+ -> O + N                                 : {2e-7 * (300/TionN)^0.5}
                 O- + N2+ -> O + N2                               : {2e-7 * (300/TionN)^0.5}
                 O- + O+ -> O + O                                 : {2e-7 * (300/TionN)^0.5}
                 O- + O2+ -> O + O2                               : {2e-7 * (300/TionN)^0.5}
                 O- + NO+ -> O + NO                               : {2e-7 * (300/TionN)^0.5}
                 O2- + N+ -> O2 + N                               : {2e-7 * (300/TionN)^0.5}
                 O2- + N2+ -> O2 + N2                              : {2e-7 * (300/TionN)^0.5}
                 O2- + O+ -> O2 + O                                 : {2e-7 * (300/TionN)^0.5}
                 O2- + O2+ -> O2 + O2                               : {2e-7 * (300/TionN)^0.5}
                 O2- + NO+ -> O2 + NO                               : {2e-7 * (300/TionN)^0.5}
                 O3- + N+ -> O3 + N                                 : {2e-7 * (300/TionN)^0.5}
                 O3- + N2+ -> O3 + N2                               : {2e-7 * (300/TionN)^0.5}
                 O3- + O+ -> O3 + O                                 : {2e-7 * (300/TionN)^0.5}
                 O3- + O2+ -> O3 + O2                               : {2e-7 * (300/TionN)^0.5}
                 O3- + NO+ -> O3 + NO                               : {2e-7 * (300/TionN)^0.5}
                 NO- + N+ -> NO + N                                 : {2e-7 * (300/TionN)^0.5}
                 NO- + N2+ -> NO + N2                               : {2e-7 * (300/TionN)^0.5}
                 NO- + O+ -> NO + O                                 : {2e-7 * (300/TionN)^0.5}
                 NO- + O2+ -> NO + O2                               : {2e-7 * (300/TionN)^0.5}
                 NO- + NO+ -> NO + NO                               : {2e-7 * (300/TionN)^0.5}
                 O- + N2+ -> O + N + N                              : 1e-7
                 O- + N3+ -> O + N + N2                             : 1e-7
                 O- + O2+ -> O + O + O                              : 1e-7
                 O- + O4+ -> O + O2 + O2                            : 1e-7
                 O- + NO+ -> O + N + O                              : 1e-7
                 O- + O2pN2 -> O + O2 + N2                          : 1e-7
                 O2- + N2+ -> O2 + N + N                              : 1e-7
                 O2- + N3+ -> O2 + N + N2                             : 1e-7
                 O2- + O2+ -> O2 + O + O                              : 1e-7
                 O2- + O4+ -> O2 + O2 + O2                            : 1e-7
                 O2- + NO+ -> O2 + N + O                              : 1e-7
                 O2- + O2pN2 -> O2 + O2 + N2                          : 1e-7
                 O3- + N2+ -> O3 + N + N                              : 1e-7
                 O3- + N3+ -> O3 + N + N2                             : 1e-7
                 O3- + O2+ -> O3 + O + O                              : 1e-7
                 O3- + O4+ -> O3 + O2 + O2                            : 1e-7
                 O3- + NO+ -> O3 + N + O                              : 1e-7
                 O3- + O2pN2 -> O3 + O2 + N2                          : 1e-7
                 NO- + N2+ -> NO + N + N                              : 1e-7
                 NO- + N3+ -> NO + N + N2                             : 1e-7
                 NO- + O2+ -> NO + O + O                              : 1e-7
                 NO- + O4+ -> NO + O2 + O2                            : 1e-7
                 NO- + NO+ -> NO + N + O                              : 1e-7
                 NO- + O2pN2 -> NO + O2 + N2                          : 1e-7
                 O- + N+ + M -> O + N + M                 : {2e-25 * (300/TionN)^2.5}
                 O- + N2+ + M -> O + N2 + M               : {2e-25 * (300/TionN)^2.5}
                 O- + O+ + M -> O + O + M                 : {2e-25 * (300/TionN)^2.5}
                 O- + O2+ + M -> O + O2 + M               : {2e-25 * (300/TionN)^2.5}
                 O- + NO+ + M -> O + NO + M               : {2e-25 * (300/TionN)^2.5}
                 O2- + N+ + M -> O2 + N + M               : {2e-25 * (300/TionN)^2.5}
                 O2- + N2+ + M -> O2 + N2 + M             : {2e-25 * (300/TionN)^2.5}
                 O2- + O+ + M -> O2 + O + M               : {2e-25 * (300/TionN)^2.5}
                 O2- + O2+ + M -> O2 + O2 + M             : {2e-25 * (300/TionN)^2.5}
                 O2- + NO+ + M -> O2 + NO + M             : {2e-25 * (300/TionN)^2.5}
                 O- + N+ + M -> NO + M                    : {2e-25 * (300/TionN)^2.5}
                 O- + O+ + M -> O2 + M                    : {2e-25 * (300/TionN)^2.5}
                 O- + O2+ + M -> O3 + M                   : {2e-25 * (300/TionN)^2.5}
                 O2- + O+ + M -> O3 + M                   : {2e-25 * (300/TionN)^2.5}
                 ####
                 # Three-body recombination of O3- NO- N2O- NO2- NO3- has to be verified
                 ####
                 O3- + N+ + M -> O3 + N + M               : {2e-25 * (300/TionN2)^2.5}
                 O3- + N2+ + M -> O3 + N2 + M             : {2e-25 * (300/TionN2)^2.5}
                 O3- + O+ + M -> O3 + O + M               : {2e-25 * (300/TionN2)^2.5}
                 O3- + O2+ + M -> O3 + O2 + M             : {2e-25 * (300/TionN2)^2.5}
                 O3- + NO+ + M -> O3 + NO + M             : {2e-25 * (300/TionN2)^2.5}
                 NO- + N+ + M -> NO + N + M               : {2e-25 * (300/TionN2)^2.5}
                 NO- + N2+ + M -> NO + N2 + M             : {2e-25 * (300/TionN2)^2.5}
                 NO- + O+ + M -> NO + O + M               : {2e-25 * (300/TionN2)^2.5}
                 NO- + O2+ + M -> NO + O2 + M             : {2e-25 * (300/TionN2)^2.5}
                 NO- + NO+ + M -> NO + NO + M             : {2e-25 * (300/TionN2)^2.5}
                 em + N2O -> em + em + N2O+            : EEDF (C88_N2O_Ionization_12.89_eV)
                 em + N2O+ -> N2 + O                 : {2.0e-7 * (300/Te)^0.5}
                 em + NO2+ -> NO + O                 : {2.0e-7 * (300/Te)^0.5}
                 em + N2O -> NO- + N                   : EEDF (C80_N2O_Attachment)
                 em + NO2 -> O- + NO                   : 1e-11
                 em + N2O + M -> N2O- + M  : 1e-31
                 O-  + NO -> NO2 + em                  : 2.6e-10
                 O-  + N2 -> N2O + em                  : 5.0e-13
                 NO- + N -> N2O + em                   : 5e-10 
                 N2O- + N -> NO + N2 + em              : 5e-10
                 NO2- + N -> NO + NO + em              : 5e-10
                 NO3- + N -> NO + NO2 + em             : 5e-10
                 NO- + O -> NO2 + em                   : 1.5e-10
                 N2O- + O -> NO + NO + em              : 1.5e-10
                 NO2- + O -> NO + O2 + em              : 1.5e-10
                 NO3- + O -> NO + O3 + em              : 1.5e-10
                 N2O- + N2A3 -> N2O + N2 + em          : 2.1e-9
                 NO2- + N2A3 -> NO2 + N2 + em          : 2.1e-9
                 NO3- + N2A3 -> NO3 + N2 + em          : 2.1e-9
                 N2O- + N2B3 -> N2O + N2 + em          : 2.5e-9
                 NO2- + N2B3 -> NO2 + N2 + em          : 2.5e-9
                 NO3- + N2B3 -> NO3 + N2 + em          : 2.5e-9
                 N2A3 + O2 -> N2O + O                 : {2.0e-14 * (Tgas/300)^0.55}
                 N2A3 + N2O -> N2 + N + NO            : 1.0e-11
                 N2A3 + NO2 -> N2 + O + NO            : 1.0e-12
                 N2D + N2O -> NO + N2                 : 3.5e-12
                 N + NO2 -> O + O + N2                : 9.1e-13
                 N + NO2 -> O + N2O                   : 3.0e-12
                 N + NO2 -> N2 + O2                   : 7.0e-13
                 N + NO2 -> NO + NO                   : 2.3e-12
                 O2- + N -> NO2 + em                   : 5.0e-10
                 O + NO -> NO2                        : 4.2e-18
                 O + N2O -> N2 + O2                   : {8.3e-12 * exp(-14000/Tgas)}
                 O + N2O -> NO + NO                   : {1.5e-10 * exp(-14090/Tgas)}
                 O + NO2 -> NO + O2                   : {9.1e-12 * (Tgas/300)^0.18}
                 O + NO3 -> O2 + NO2                  : 1.0e-11
                 N2 + O2 -> O + N2O                   : {2.5e-10 * exp(-50390/Tgas)}
                 NO + NO -> N + NO2                   : {3.3e-16 * (300/Tgas)^0.5 * exp(-39200/Tgas)}
                 NO + NO -> O + N2O                   : {2.2e-12 * exp(-32100/Tgas)}
                 NO + O2 -> O + NO2                   : {2.8e-12 * exp(-23400/Tgas)}
                 NO + O3 -> O2 + NO2                  : {2.5e-13 * exp(-765/Tgas)}
                 NO + N2O -> N2 + NO2                 : {4.6e-10 * exp(-25170/Tgas)}
                 NO + NO3 -> NO2 + NO2                : 1.7e-11
                 O2 + NO2 -> NO + O3                  : {2.8e-12 * exp(-25400/Tgas)}
                 NO2 + NO2 -> NO + NO + O2            : {3.3e-12 * exp(-13500/Tgas)}
                 NO2 + NO2 -> NO + NO3                : {4.5e-10 * exp(-18500/Tgas)}
                 NO2 + O3 -> O2 + NO3                 : {1.2e-13 * exp(-2450/Tgas)}
                 NO2 + NO3 -> NO + NO2 + O2           : {2.3e-13 * exp(-1600/Tgas)}
                 NO3 + O2 -> NO2 + O3                 : {1.5e-12 * exp(-15020/Tgas)}
                 NO3 + NO3 -> O2 + NO2 + NO2          : {4.3e-12 * exp(-3850/Tgas)}
                 N2O + N2 -> N2 + O + N2              : {1.2e-8 * (300/Tgas) * exp(-29000/Tgas)}
                 N2O + O2 -> N2 + O + O2              : {1.2e-8 * (300/Tgas) * exp(-29000/Tgas)}
                 N2O + NO -> N2 + O + NO              : {1.2e-8 * (300/Tgas) * exp(-29000/Tgas) * 2}
                 N2O + N2O -> N2 + O + N2O            : {1.2e-8 * (300/Tgas) * exp(-29000/Tgas) * 4}
                 NO2 + N2 -> N2 + O + N2              : {6.8e-6 * (300/Tgas)^2 * exp(-36180/Tgas)}
                 NO2 + O2 -> N2 + O + O2              : {6.8e-6 * (300/Tgas)^2 * exp(-36180/Tgas) * 0.78}
                 NO2 + NO -> N2 + O + NO              : {6.8e-6 * (300/Tgas)^2 * exp(-36180/Tgas) * 7.8}
                 NO2 + NO2 -> N2 + O + NO2            : {6.8e-6 * (300/Tgas)^2 * exp(-36180/Tgas) * 5.9}
                 NO3 + N2 -> NO2 + O + N2             : {3.1e-5 * (300/Tgas)^2 * exp(-25000/Tgas)}
                 NO3 + O2 -> NO2 + O + O2             : {3.1e-5 * (300/Tgas)^2 * exp(-25000/Tgas)}
                 NO3 + NO -> NO2 + O + NO             : {3.1e-5 * (300/Tgas)^2 * exp(-25000/Tgas)}
                 NO3 + N -> NO2 + O + N               : {3.1e-5 * (300/Tgas)^2 * exp(-25000/Tgas) * 10}
                 NO3 + O -> NO2 + O + O               : {3.1e-5 * (300/Tgas)^2 * exp(-25000/Tgas) * 10}
                 NO3 + N2 -> NO + O2 + N2             : {6.2e-5 * (300/Tgas)^2 * exp(-25000/Tgas)}
                 NO3 + O2 -> NO + O2 + O2             : {6.2e-5 * (300/Tgas)^2 * exp(-25000/Tgas)}
                 NO3 + NO -> NO + O2 + NO             : {6.2e-5 * (300/Tgas)^2 * exp(-25000/Tgas)}
                 NO3 + N -> NO + O2 + N               : {6.2e-5 * (300/Tgas)^2 * exp(-25000/Tgas) * 12}
                 NO3 + O -> NO + O2 + O               : {6.2e-5 * (300/Tgas)^2 * exp(-25000/Tgas) * 12}
                 N2O5 + M -> NO2 + NO3 + M                        : {2.1e-11 * (300/Tgas)^4.4 * exp(-11080/Tgas)}
                 O + N2 + M -> N2O + M                            : {3.9e-35 * exp(-10400/Tgas)}
                 O + NO + N2 -> NO2 + N2                          : {1.2e-31 * (300/Tgas)^1.8}
                 O + NO + O2 -> NO2 + O2                          : {1.2e-31 * (300/Tgas)^1.8 * 0.78}
                 O + NO + NO -> NO2 + NO                          : {1.2e-31 * (300/Tgas)^1.8 * 0.78}
                 O + NO2 + N2 -> NO3 + N2                         : {8.9e-32 * (300/Tgas)^2}
                 O + NO2 + O2 -> NO3 + O2                         : {8.9e-32 * (300/Tgas)^2}
                 O + NO2 + N -> NO3 + N                           : {8.9e-32 * (300/Tgas)^2 * 13}
                 O + NO2 + O -> NO3 + O                           : {8.9e-32 * (300/Tgas)^2 * 13}
                 O + NO2 + NO -> NO3 + NO                         : {8.9e-32 * (300/Tgas)^2 * 2.4}
                 NO2 + NO3 + M -> N2O5 + M                        : {3.7e-30 * (300/Tgas)^4.1}
                 N+ + N2O -> NO+ + N2                             : 5.5e-10
                 O+ + N2O -> NO+ + NO                             : 2.3e-10
                 O+ + N2O -> N2O+ + O                             : 2.2e-10
                 O+ + N2O -> O2+ + N2                             : 2.0e-11
                 O+ + NO2 -> NO2+ + O                             : 1.6e-9
                 N2+ + N2O -> N2O+ + N2                           : 5.0e-10
                 N2+ + N2O -> NO+ + N + N2                        : 4.0e-10
                 N3+ + NO -> N2O+ + N2                            : 7.0e-11
                 NO2+ + NO -> NO+ + NO2                           : 2.9e-10
                 N2O+ + NO -> NO+ + N2O                           : 2.9e-10
                 O-   + NO2 -> NO2- + O                           : 1.2e-9
                 O-   + N2O -> NO-  + NO                          : 2.0e-10
                 O-   + N2O -> N2O- + O                           : 2.0e-12
                 NO-  + NO2 -> NO2- + NO                          : 7.4e-10
                 NO-  + N2O -> NO2- + N2                          : 2.8e-14
                 NO2- + O3 -> NO3- + O2                           : 1.8e-11
                 NO2- + NO2 -> NO3- + NO                          : 4.0e-12
                 NO2- + NO3 -> NO3- + NO2                         : 5.0e-10
                 NO2- + N2O5 -> NO3- + NO2 + NO2                  : 7.0e-10
                 NO3- + NO -> NO2- + NO2                          : 3.0e-15
                 O- + N2O+ -> O + N2O                             : {2e-7 * (300/TionN)^0.5}
                 O- + NO2+ -> O + NO2                             : {2e-7 * (300/TionN)^0.5}
                 O2- + N2O+ -> O2 + N2O                             : {2e-7 * (300/TionN)^0.5}
                 O2- + NO2+ -> O2 + NO2                             : {2e-7 * (300/TionN)^0.5}
                 O3- + N2O+ -> O3 + N2O                             : {2e-7 * (300/TionN)^0.5}
                 O3- + NO2+ -> O3 + NO2                             : {2e-7 * (300/TionN)^0.5}
                 NO- + N2O+ -> NO + N2O                             : {2e-7 * (300/TionN)^0.5}
                 NO- + NO2+ -> NO + NO2                             : {2e-7 * (300/TionN)^0.5}
                 N2O- + N+ -> N2O + N                                 : {2e-7 * (300/TionN)^0.5}
                 N2O- + N2+ -> N2O + N2                               : {2e-7 * (300/TionN)^0.5}
                 N2O- + O+ -> N2O + O                                 : {2e-7 * (300/TionN)^0.5}
                 N2O- + O2+ -> N2O + O2                               : {2e-7 * (300/TionN)^0.5}
                 N2O- + NO+ -> N2O + NO                               : {2e-7 * (300/TionN)^0.5}
                 N2O- + N2O+ -> N2O + N2O                             : {2e-7 * (300/TionN)^0.5}
                 N2O- + NO2+ -> N2O + NO2                             : {2e-7 * (300/TionN)^0.5}
                 NO2- + N+ -> NO2 + N                                 : {2e-7 * (300/TionN)^0.5}
                 NO2- + N2+ -> NO2 + N2                               : {2e-7 * (300/TionN)^0.5}
                 NO2- + O+ -> NO2 + O                                 : {2e-7 * (300/TionN)^0.5}
                 NO2- + O2+ -> NO2 + O2                               : {2e-7 * (300/TionN)^0.5}
                 NO2- + NO+ -> NO2 + NO                               : {2e-7 * (300/TionN)^0.5}
                 NO2- + N2O+ -> NO2 + N2O                             : {2e-7 * (300/TionN)^0.5}
                 NO2- + NO2+ -> NO2 + NO2                             : {2e-7 * (300/TionN)^0.5}
                 NO3- + N+ -> NO3 + N                                 : {2e-7 * (300/TionN)^0.5}
                 NO3- + N2+ -> NO3 + N2                               : {2e-7 * (300/TionN)^0.5}
                 NO3- + O+ -> NO3 + O                                 : {2e-7 * (300/TionN)^0.5}
                 NO3- + O2+ -> NO3 + O2                               : {2e-7 * (300/TionN)^0.5}
                 NO3- + NO+ -> NO3 + NO                               : {2e-7 * (300/TionN)^0.5}
                 NO3- + N2O+ -> NO3 + N2O                             : {2e-7 * (300/TionN)^0.5}
                 NO3- + NO2+ -> NO3 + NO2                             : {2e-7 * (300/TionN)^0.5}
                 O- + N2O+ -> O + N2 + O                            : 1e-7
                 O- + NO2+ -> O + N + O2                            : 1e-7
                 O2- + N2O+ -> O2 + N2 + O                            : 1e-7
                 O2- + NO2+ -> O2 + N + O2                            : 1e-7
                 O3- + N2O+ -> O3 + N2 + O                            : 1e-7
                 O3- + NO2+ -> O3 + N + O2                            : 1e-7
                 NO- + N2O+ -> NO + N2 + O                            : 1e-7
                 NO- + NO2+ -> NO + N + O2                            : 1e-7
                 N2O- + N2+ -> N2O + N + N                            : 1e-7
                 N2O- + N3+ -> N2O + N + N2                           : 1e-7
                 N2O- + O2+ -> N2O + O + O                            : 1e-7
                 N2O- + O4+ -> N2O + O2 + O2                          : 1e-7
                 N2O- + NO+ -> N2O + N + O                            : 1e-7
                 N2O- + N2O+ -> N2O + N2 + O                          : 1e-7
                 N2O- + NO2+ -> N2O + N + O2                          : 1e-7
                 N2O- + O2pN2 -> N2O + O2 + N2                        : 1e-7
                 NO2- + N2+ -> NO2 + N + N                            : 1e-7
                 NO2- + N3+ -> NO2 + N + N2                           : 1e-7
                 NO2- + O2+ -> NO2 + O + O                            : 1e-7
                 NO2- + O4+ -> NO2 + O2 + O2                          : 1e-7
                 NO2- + NO+ -> NO2 + N + O                            : 1e-7
                 NO2- + N2O+ -> NO2 + N2 + O                          : 1e-7
                 NO2- + NO2+ -> NO2 + N + O2                          : 1e-7
                 NO2- + O2pN2 -> NO2 + O2 + N2                        : 1e-7
                 NO3- + N2+ -> NO3 + N + N                            : 1e-7
                 NO3- + N3+ -> NO3 + N + N2                           : 1e-7
                 NO3- + O2+ -> NO3 + O + O                            : 1e-7
                 NO3- + O4+ -> NO3 + O2 + O2                          : 1e-7
                 NO3- + NO+ -> NO3 + N + O                            : 1e-7
                 NO3- + N2O+ -> NO3 + N2 + O                          : 1e-7
                 NO3- + NO2+ -> NO3 + N + O2                          : 1e-7
                 NO3- + O2pN2 -> NO3 + O2 + N2                        : 1e-7
                 O- + N2+ + M -> N2O + M                          : {2e-25 * (300/TionN)^2.5}
                 O3- + N2O+ + M -> O3 + N2O + M                   : {2e-25 * (300/TionN2)^2.5}
                 O3- + NO2+ + M -> O3 + NO2 + M                   : {2e-25 * (300/TionN2)^2.5}
                 NO- + N2O+ + M -> NO + N2O + M                   : {2e-25 * (300/TionN2)^2.5}
                 NO- + NO2+ + M -> NO + NO2 + M                   : {2e-25 * (300/TionN2)^2.5}
                 N2O- + N+ + M -> N2O + N + M                     : {2e-25 * (300/TionN2)^2.5}
                 N2O- + N2+ + M -> N2O + N2 + M                   : {2e-25 * (300/TionN2)^2.5}
                 N2O- + O+ + M -> N2O + O + M                     : {2e-25 * (300/TionN2)^2.5}
                 N2O- + O2+ + M -> N2O + O2 + M                   : {2e-25 * (300/TionN2)^2.5}
                 N2O- + NO+ + M -> N2O + NO + M                   : {2e-25 * (300/TionN2)^2.5}
                 N2O- + N2O+ + M -> N2O + N2O + M                 : {2e-25 * (300/TionN2)^2.5}
                 N2O- + NO2+ + M -> N2O + NO2 + M                 : {2e-25 * (300/TionN2)^2.5}
                 NO2- + N+ + M -> NO2 + N + M                     : {2e-25 * (300/TionN2)^2.5}
                 NO2- + N2+ + M -> NO2 + N2 + M                   : {2e-25 * (300/TionN2)^2.5}
                 NO2- + O+ + M -> NO2 + O + M                     : {2e-25 * (300/TionN2)^2.5}
                 NO2- + O2+ + M -> NO2 + O2 + M                   : {2e-25 * (300/TionN2)^2.5}
                 NO2- + NO+ + M -> NO2 + NO + M                   : {2e-25 * (300/TionN2)^2.5}
                 NO2- + N2O+ + M -> NO2 + N2O + M                 : {2e-25 * (300/TionN2)^2.5}
                 NO2- + NO2+ + M -> NO2 + NO2 + M                 : {2e-25 * (300/TionN2)^2.5}
                 NO3- + N+ + M -> NO3 + N + M                     : {2e-25 * (300/TionN2)^2.5}
                 NO3- + N2+ + M -> NO3 + N2 + M                   : {2e-25 * (300/TionN2)^2.5}
                 NO3- + O+ + M -> NO3 + O + M                     : {2e-25 * (300/TionN2)^2.5}
                 NO3- + O2+ + M -> NO3 + O2 + M                   : {2e-25 * (300/TionN2)^2.5}
                 NO3- + NO+ + M -> NO3 + NO + M                   : {2e-25 * (300/TionN2)^2.5}
                 NO3- + N2O+ + M -> NO3 + N2O + M                 : {2e-25 * (300/TionN2)^2.5}
                 NO3- + NO2+ + M -> NO3 + NO2 + M                 : {2e-25 * (300/TionN2)^2.5}
                 O2+ + NO2 -> NO+ + O3                            : 1.0e-11
                 O2+ + NO2 -> NO2+ + O2                           : 6.6e-10
                 N3+ + O2 -> NO2+ + N2                            : 4.4e-11
                 O2-  + NO2 -> NO2- + O2                          : 7.0e-10
                 O2-  + NO3 -> NO3- + O2                          : 5.0e-10
                 O3-  + NO -> NO3- + O                            : 1.0e-11
                 O3-  + NO -> NO2- + O2                           : 2.6e-12
                 O3-  + NO2 -> NO2- + O3                          : 7.0e-11
                 O3-  + NO2 -> NO3- + O2                          : 2.0e-11
                 O3-  + NO3 -> NO3- + O3                          : 5.0e-10
                 O-  + NO + M -> NO2- + M                         : 1.0e-29
                 O- + NO+ + M -> NO2 + M                          : {2e-25 * (300/TionN)^2.5}
                 O2- + N+ + M -> NO2 + M                          : {2e-25 * (300/TionN)^2.5}
                 O2- + NO+ + M -> NO3 + M                         : {2e-25 * (300/TionN)^2.5}
                '
  []

  [Water]
    species = 'emliq OHm'
    reaction_coefficient_format = 'rate'
    use_log = true
    use_ad = true
    aux_species = 'H2O'
    block = 1
    #Reaction rates for 300K in meters (73 reactions)
    reactions = 'emliq -> H2Om                      : 5e-21
                 Hp -> H3Op                         : 5e-21
                 H2Op -> H3Op + OH                  : 1e-23
                 Hm -> H2Om + H                     : 5e-21
                 H2Om -> H + OHm                    : 3e-26
                 Om -> OHm + OH                     : 3e-21
                 H3Op + O2m -> HO2                  : 5e-17
                 HNO2 -> H3Op + NO2m                : 5e-21
                 H3Op + NO2m -> H + HO2 + NO3m      : 6.81e-16
                 HNO3 -> H3Op + NO3m                : 3e-24
                 H3Op + NO3m -> HNO3                : 7e-22
                 OH + H ->                          : 3e-17
                 H2Om + H -> H2 + OHm               : 4e-17
                 H2Om + O -> Om                     : 3e-17
                 H2Om + O2 ->  O2m                  : 3e-17
                 H2Om + OH -> OHm                   : 5e-17
                 H2Om + H2O2 -> OH + OHm            : 2e-17
                 H2Om + Om -> OHm + OHm             : 2e-17
                 H2Om + HO2m -> OHm + OHm + OH      : 5e-18
                 H2Om +H2Om -> H2 + OHm + OHm       : 1e-17
                 H3Op + OHm -> H + OH               : 1e-16
                 OH + H ->                          : 3e-17
                 H2Om + H2Op -> H + OH              : 1e-15
                 OH + OH -> H2O2                    : 1.7e-17
                 OH + H2 -> H                       : 6e-20
                 OH + HO2 -> O2                     : 2e-17
                 OH + H2O2 -> HO2                   : 1e-19
                 OH + OHm -> Om                     : 8e-18
                 OH + Om -> HO2m                    : 4e-17
                 OH + O2m -> O2 + OHm               : 1.5e-17
                 OH + HO2m -> HO2 +OHm              : 1.5e-17
                 H -> H2 + OH                       : 1.5e-27
                 H + H -> H2                        : 1.5e-17
                 H + OHm -> H2Om                    : 3e-20
                 H + HO2 -> H2O2                    : 3e-17
                 H + H2O2 -> OH                     : 1.5e-19
                 H2 + H2O2 -> H + OH                : 1e-20
                 Hm + H2Op -> H                     : 3e-12
                 Hm + H3Op -> H2                    : 3e-12
                 O -> OH + OH                       : 2.2e-23
                 O + O2 -> O3                       : 5e-18
                 O2 + H -> HO2                      : 5e-17
                 Om + H2 -> H + OHm                 : 1.3e-19
                 Om + O2 -> O3m                     : 5e-18
                 Om + H2O2 -> O2m                   : 8e-19
                 Om + OH2m -> O2m + OHm             : 8e-19
                 O3m + OH -> O2m + HO2              : 1.41e-17
                 O3m + OH -> O2m + HO2              : 1.7e-19
                 O3m + H3Op -> O2 + OH              : 1.5e-16
                 O3m -> O2 + Om                     : 2.6e3
                 O2m + H2O2 -> O2 + OH + OHm        : 2.16e-28
                 O3 -> O2 + O                       : 3e-6
                 Op -> H2Op + O                     : 1.2e-18
                 Op + O2 -> O2p + O                 : 1.9e-17
                 O3 + OHm -> O2m + HO2              : 1.16e-25
                 O3 + O2m -> O3m + O2               : 2.66e-18
                 N + N -> N2                        : 5e-20
                 Op + N2 -> NOp + N                 : 1.2e-18
                 OH + NO2m -> OHm + NO2             : 1.7e-27
                 H + NO2m -> NO + OHm               : 2e-18
                 O2m + NO -> NO3m                   : 6e-18
                 NO3 -> HNO3 + OH                   : 4.8e-20
                 NO + HO2 -> HNO3                   : 5.33e-18
                 NO2 + H -> HNO2                    : 1.67e-17
                 OH + NO -> HNO2                    : 3.3e-17
                 OH + NO2 -> HNO3                   : 2e-17
                 OH + HNO3 -> NO3                   : 2.17e-19
                 H + NO2 -> NO                      : 7.5e-19
                 HNO + O2 -> HO2 + NO               : 8.01e-27
                 HNO + O3 -> O2 + HNO2              : 9.61e-21
                 HNO + OH -> NO                     : 8e-17
                 OH + N2O -> HNO + NO               : 3.8e-23
                 NO2m + N2O -> NO3m + N2            : 5e-19'
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
  [O2]
    block = 0
    order = FIRST
    family = SCALAR
    initial_condition =  6.114228819695872e18
  []
  [N2]
  block = 0
    family = SCALAR
    order = FIRST
    initial_condition = 1.834268645908762e19
  []
[]

[AuxScalarKernels]
  [neutral_sum]
    type = VariableSum
    variable = M
    args = 'N2 O2 N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N2A3 N2B3 N2a_1 N N2D N2P O2v1 O2v2 O2v3 O2v4 O2a1 O2b1 O O3 NO N2O NO2 NO3 N2O5'
    execute_on = 'initial linear nonlinear'
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
    em = 1.6e-19
  []
[]

[BCs]
  #DC BC on the air electrode
  [potential_left]
    type = NeumannCircuitVoltageMoles_KV
    variable = potential
    boundary = left
    function = potential_bc_func
    ip = Arp
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
    ip = Arp
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
    ip = 'Arp'
    r = 0
    position_units = ${dom0Scale}
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
    mean_en = mean_en
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
    heavy_species_name = Arp
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    block = 0
  []

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
  petsc_options_value = 'lu NONZERO 1.em-10'
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

[Outputs]
  perf_graph = true
  [out]
    type = Exodus
    execute_on = 'final'
  []
[]
