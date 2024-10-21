[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 1
  nx = 1
[]

[Variables]
  # ODE variables
  [e]
    family = SCALAR
    order = FIRST
    initial_condition = 12
    # scaling = 1e-2
  []

  [N2]
    family = SCALAR
    order = FIRST
    initial_condition = 19.26346294
    #scaling = 1e-9
  []

  [O2]
    family = SCALAR
    order = FIRST
    initial_condition = 18.78634169
    #scaling = 1e-9
  []

  [N2+]
    family = SCALAR
    order = FIRST
    initial_condition = 11.87506126
    # scaling = 5e8
  []

  [O2+]
    family = SCALAR
    order = FIRST
    initial_condition = 11.39794001
    # scaling = 5e8
  []

  [O2-]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    # scaling = 1e2
  []

  [N2D]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [N2A3]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [O2a]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    # scaling = 1e-2
  []
  
  [N]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [O]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [O1D]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
  
  [N+]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [N3+]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [O+]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [O-]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
  
  [NO]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
    
  [NO-]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
    
  [NO+]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
  
  [N2O]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
  
  [N2O+]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
  
  [N2O-]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
  
  [NO2]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
  
  [NO2-]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
  
  [NO2+]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
  
  [NO3]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
  
  [NO3-]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [O3]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
  [O3-]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [O4+]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [O4-]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [N4+]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [N2O5]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [N2O3]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []

  [N2O4]
    family = SCALAR
    order = FIRST
    initial_condition = 0.01
    #scaling = 1e-9
  []
[]

[ScalarKernels]
  [de_dt]
    type = ODETimeDerivativeLog
    variable = e
  []

  [dN2_dt]
    type = ODETimeDerivativeLog
    variable = N2
  []

  [dO2_dt]
    type = ODETimeDerivativeLog
    variable = O2
  []

  [dN2+_dt]
    type = ODETimeDerivativeLog
    variable = N2+
  []

  [dO2+_dt]
    type = ODETimeDerivativeLog
    variable = O2+
  []

  [dO2-_dt]
    type = ODETimeDerivativeLog
    variable = O2-
  []

  [dN2D_dt]
    type = ODETimeDerivativeLog
    variable = N2D
  []

  [dN2A3_dt]
    type = ODETimeDerivativeLog
    variable = N2A3
  []

  [dO2a_dt]
    type = ODETimeDerivativeLog
    variable = O2a
  []
  
  [dN_dt]
    type = ODETimeDerivativeLog
    variable = N
  []

  [dO_dt]
    type = ODETimeDerivativeLog
    variable = O
  []

  [dO1D_dt]
    type = ODETimeDerivativeLog
    variable = O1D
  []
  
  [dN+_dt]
    type = ODETimeDerivativeLog
    variable = N+
  []
  
  [dN3+_dt]
    type = ODETimeDerivativeLog
    variable = N3+
  []

  [dO+_dt]
    type = ODETimeDerivativeLog
    variable = O+
  []

  [dO-_dt]
    type = ODETimeDerivativeLog
    variable = O-
  []

  [dNO_dt]
    type = ODETimeDerivativeLog
    variable = NO
  []

  [dNO-_dt]
    type = ODETimeDerivativeLog
    variable = NO-
  []

  [dNO+_dt]
    type = ODETimeDerivativeLog
    variable = NO+
  []

  [dN2O_dt]
    type = ODETimeDerivativeLog
    variable = N2O
  []

  [dN2O+_dt]
    type = ODETimeDerivativeLog
    variable = N2O+
  []

  [dN2O-_dt]
    type = ODETimeDerivativeLog
    variable = N2O-
  []

  [dNO2_dt]
    type = ODETimeDerivativeLog
    variable = NO2
  []

  [dNO2-_dt]
    type = ODETimeDerivativeLog
    variable = NO2-
  []

  [dNO2+_dt]
    type = ODETimeDerivativeLog
    variable = NO2+
  []

  [dNO3_dt]
    type = ODETimeDerivativeLog
    variable = NO3
  []

  [dNO3-_dt]
    type = ODETimeDerivativeLog
    variable = NO3-
  []

  [dO3_dt]
    type = ODETimeDerivativeLog
    variable = O3
  []

  [dO3-_dt]
    type = ODETimeDerivativeLog
    variable = O3-
  []

  [dO4+_dt]
    type = ODETimeDerivativeLog
    variable = O4+
  []

  [dO4-_dt]
    type = ODETimeDerivativeLog
    variable = O4-
  []

  [dN4+_dt]
    type = ODETimeDerivativeLog
    variable = N4+
  []

  [dN2O5_dt]
    type = ODETimeDerivativeLog
    variable = N2O5
  []
  
  [dN2O3_dt]
    type = ODETimeDerivativeLog
    variable = N2O3
  []
  
  [dN2O4_dt]
    type = ODETimeDerivativeLog
    variable = N2O4
  []
[]




















































































[GlobalReactions]
  [Air]
    species = 'N+ N2+ N3+ N4+ O+ O2+ O4+ NO+ NO2+ e O- O2- O3- NO- NO2- NO3- N2D N2A3
     O1D N O O2a O3 NO N2O N2O+ N2O- NO2 NO3 N2O3 N2O4 N2O5 N2 O2 O4-'
    num_particles = '1 2 3 4 1 2 4 2 3 0 1 2 3 2 3 4 1 2 1 1 1 2 3 2 3 3 3 3 4 5 6 7 2 2 4'
    file_location = 'data'
    aux_species = 'M'

    # These are parameters required equation-based rate coefficients
    equation_constants = 'Tg pi kb'
    equation_values = '340 3.141 8.6173e-5'
    equation_variables = 'Te'
    sampling_variable = 'reduced_field'
    electron_density = 'e'
    include_electrons = true
    balance_check = true
    use_log = true

    reactions = '
    e + N2 -> e + N2A3                 : EEDF (C11_N2_Excitation_6.17_eV)
    e + N2 -> e + N2A3                 : EEDF (C12_N2_Excitation_7.00_eV)
    e + N2 -> e + N2A3                 : EEDF (C13_N2_Excitation_7.80_eV)
    e + N2 -> e + N + N2D              : EEDF (C23_N2_Excitation_13.00_eV)
    e + O2 -> e + O2a                 : EEDF (C33_O2_Excitation_0.98_eV)
    e + O2 -> e + O + O                : EEDF (C36_O2_Excitation_6.00_eV)
    e + O2 -> e + O + O1D              : EEDF (C37_O2_Excitation_8.40_eV)
    e + O2a -> e + O + O              : EEDF (C58_O2a1_Excitation_6.00_eV)
    e + O -> e + O1D                   : EEDF (C63_O_Excitation_1.97_eV)
    e + N2A3 -> e + N2                 : EEDF (C48_N2A3_De-excitation_6.17_eV)
    e + O2a -> e + O2                : EEDF (C55_O2a1_De-excitation_0.98_eV)
    e + N -> e + e + N+                : EEDF (C61_N_Ionization_14.55_eV)
    e + O -> e + e + O+                : EEDF (C65_O_Ionization_13.62_eV)
    e + N2 -> e + e + N2+              : EEDF (C24_N2_Ionization_15.60_eV)
    e + N2A3 -> e + e + N2+            : EEDF (C50_N2A3_Ionization_10.79_eV)
    e + O2 -> e + e + O2+              : EEDF (C39_O2_Ionization_12.06_eV)
    e + O2a -> e + e + O2+            : EEDF (C59_O2a1_Ionization_11.00_eV)
    e + NO -> e + e + NO+              : EEDF (C75_NO_Ionization_9.26_eV)
    e + N2+ -> N + N                   : {1.8e-7 * (300/Te)^0.39 * 0.5}
    e + N2+ -> N + N2D                 : {1.8e-7 * (300/Te)^0.39 * 0.45}
    e + O2+ -> O + O                   : {2.7e-7 * (300/Te)^0.7 * 0.55}
    e + O2+ -> O + O1D                 : {2.7e-7 * (300/Te)^0.7 * 0.40}
    e + NO+ -> O + N                   : {4.2e-7 * (300/Te)^0.85 * 0.2}
    e + NO+ -> O + N2D                 : {4.2e-7 * (300/Te)^0.85 * 0.8}
    e + N3+ -> N2 + N                  : {2.0e-7 * (300/Te)^0.5}
    e + N4+ -> N2 + N2                 : {2.3e-6 * (300/Te)^0.53}
    e + O4+ -> O2 + O2                 : {1.4e-6 * (300/Te)^0.5}
    e + e + N+ -> N + e                    : {7.0e-20 * (300/Te)^4.5}
    e + e + O+ -> O + e                    : {7.0e-20 * (300/Te)^4.5}
    e + N+ + M -> N + M    : {6.0e-27 * (300/Te)^1.5}
    e + O+ + M -> O + M    : {6.0e-27 * (300/Te)^1.5}
    e + O2 -> O- + O                     : EEDF (C25_O2_Attachment)
    e + NO -> O- + N                     : EEDF (C66_NO_Attachment)
    e + O3 -> O- + O2                    : EEDF (C76_O3_Attachment)
    e + O3 -> O2- + O                    : EEDF (C77_O3_Attachment)
    e + O + O2 -> O- + O2                : 1e-31
    e + O + O2 -> O2- + O                : 1e-31
    e + O3 + M -> O3- + M    : 1e-31
    e + NO + M -> NO- + M    : 1e-31
    e + O2 + N2 -> O2- + N2              : {1.1e-31 * (300/Te)^2 * exp(-70/Tg) * exp(1500*(Te-Tg)/(Te*Tg))}
    O-  + O -> O2  + e                   : 1.4e-10
    O-  + N -> NO  + e                   : 2.6e-10
    O-  + O2 -> O3  + e                  : 5.0e-15
    O-  + O2a -> O3  + e                : 3.0e-10
    O-  + N2A3 -> O   + N2 + e           : 2.2e-9
    O-  + O3 -> O2  + O2 + e             : 3.0e-10
    O2- + O -> O3  + e                   : 1.5e-10
    O2- + O2 -> O2  + O2 + e             : {2.7e-10 * (Tg/300)^0.5 * exp(-5590/Tg)}
    O2- + O2a -> O2  + O2 + e           : 2.0e-10
    O2- + N2 -> O2  + N2 + e             : {1.9e-12 * (Tg/300)^0.5 * exp(-4990/Tg)}
    O2- + N2A3 -> O2  + N2 + e           : 2.1e-9
    O3- + O -> O2  + O2 + e              : 3.0e-10
    O3- + N -> NO + O2 + e               : 5e-10
    O3- + N2A3 -> O3 + N2 + e            : 2.1e-9
    NO- + N2A3 -> NO + N2 + e            : 2.1e-9
    N2A3 -> N2                           : 0.5 
    O2a -> O2                           : 2.6e-4
    N2A3 + O -> NO + N2D                 : 7e-12
    N2A3 + N -> N2 + N                   : 2e-12
    N2A3 + O2 -> N2 + O + O1D            : {2.1e-12 * (Tg/300)^0.55}
    N2A3 + O2 -> N2 + O2a               : {2.0e-13 * (Tg/300)^0.55}
    N2A3 + N2 -> N2 + N2                 : 3e-16 
    N2A3 + NO -> N2 + NO                 : 6.9e-11
    N + N + N2 -> N2A3 + N2              : 1.7e-33
    N + N + O2 -> N2A3 + O2              : 1.7e-33
    N + N + NO -> N2A3 + NO              : 1.7e-33
    N + N + N -> N2A3 + N                : 1e-32
    N + N + O -> N2A3 + O                : 1e-32
    N2D + O -> N + O1D                   : 4e-13
    N2D + O2 -> NO + O                   : 5.2e-12
    N2D + NO -> N2 + O                   : 1.8e-10
    N2D + N2 -> N + N2                   : {1.0e-13 * exp(-510/Tg)}
    O2a + O -> O2 + O                   : 7.0e-16
    O2a + N -> NO + O                   : {2.0e-14 * exp(-600/Tg)}
    O2a + O2 -> O2 + O2                 : {3.8e-18 * exp(-205/Tg)}
    O2a + N2 -> O2 + N2                 : 3.0e-21
    O2a + NO -> O2 + NO                 : 2.5e-11
    O2a + O3 -> O2 + O2 + O1D           : {5.2e-11 * exp(-2840/Tg)}
    O + O3 -> O2 + O2a                  : {1.0e-11 * exp(-2300/Tg)}
    O1D + O -> O + O                     : 8.0e-12
    O1D + O2 -> O + O2                   : {6.4e-12 * exp(67/Tg)}
    O1D + O2 -> O + O2a                 : 1.0e-12
    O1D + N2 -> O + N2                   : 2.3e-11
    O1D + O3 -> O2 + O + O               : 1.2e-10
    O1D + O3 -> O2 + O2                  : 1.2e-10
    O1D + NO -> O2 + N                   : 1.7e-10
    N + NO -> O + N2                     : {1.8e-11 * (Tg/300.0)^0.5}
    N + O2 -> O + NO                     : {3.2e-12 * (Tg/300.0) * exp(-3150/Tg)}
    O + N2 -> N + NO                     : {3.0e-10 * exp(-38370/Tg)}
    O + NO -> N + O2                     : {7.5e-12 * (Tg/300.0) * exp(-19500/Tg)}
    NO + NO -> N2 + O2                   : {5.1e-13 * exp(-33660/Tg)}
    O2 + O2 -> O + O3                    : {2.0e-11 * exp(-49800/Tg)}
    N + N -> N2+ + e                     : {2.7e-11 * exp(-6.74e4/Tg)}
    N + O -> NO+ + e                     : {1.6e-12 * (Tg/300)^0.5 * (0.19+8.6*Tg) * exp(-32000/Tg)}
    N2 + N2 -> N + N + N2                : {5.4e-8 * (1.0 - exp(-3354/Tg)) * exp(-113200/Tg)}
    O2 + N2 -> N + N + O2                : {5.4e-8 * (1.0 - exp(-3354/Tg)) * exp(-113200/Tg)}
    NO + N2 -> N + N + NO                : {5.4e-8 * (1.0 - exp(-3354/Tg)) * exp(-113200/Tg)}
    O + N2 -> N + N + O                  : {5.4e-8 * (1.0 - exp(-3354/Tg)) * exp(-113200/Tg) * 6.6}
    N + N2 -> N + N + N                  : {5.4e-8 * (1.0 - exp(-3354/Tg)) * exp(-113200/Tg) * 6.6}
    O2 + N2 -> O + O + N2                : {6.1e-9 * (1.0 - exp(-2240/Tg)) * exp(-59380/Tg)}
    O2 + O2 -> O + O + O2                : {6.1e-9 * (1.0 - exp(-2240/Tg)) * exp(-59380/Tg) * 5.9}
    O2 + O -> O + O + O                  : {6.1e-9 * (1.0 - exp(-2240/Tg)) * exp(-59380/Tg) * 21}
    O2 + N -> O + O + N                  : {6.1e-9 * (1.0 - exp(-2240/Tg)) * exp(-59380/Tg)}
    O2 + NO -> O + O + NO                : {6.1e-9 * (1.0 - exp(-2240/Tg)) * exp(-59380/Tg)}
    NO + N2 -> N + O + N2                : {8.7e-9 * exp(-75994/Tg)}
    NO + O2 -> N + O + O2                : {8.7e-9 * exp(-75994/Tg)}
    NO + O -> N + O + O                  : {8.7e-9 * exp(-75994/Tg) * 20}
    NO + N -> N + O + N                  : {8.7e-9 * exp(-75994/Tg) * 20}
    NO + NO -> N + O + NO                : {8.7e-9 * exp(-75994/Tg) * 20}
    O3 + N2 -> O2 + O + N2               : {6.6e-10 * exp(-11600/Tg)}
    O3 + O2 -> O2 + O + O2               : {6.6e-10 * exp(-11600/Tg) * 0.38}
    O3 + N -> O2 + O + N                 : {6.6e-10 * exp(-11600/Tg) * 6.3*exp(170/Tg)}
    O3 + O -> O2 + O + O                 : {6.6e-10 * exp(-11600/Tg) * 6.3*exp(170/Tg)}
    N + N + N2 -> N2 + N2                : {8.3e-34 * exp(500/Tg)}
    N + N + O2 -> N2 + O2                : {1.8e-33 * exp(435/Tg)}
    N + N + NO -> N2 + NO                : {1.8e-33 * exp(435/Tg)}
    N + N + N -> N2 + N                  : {1.8e-33 * exp(435/Tg) * 3}
    N + N + O -> N2 + O                  : {1.8e-33 * exp(435/Tg) * 3}
    O + O + N2 -> O2 + N2                : {2.8e-34 * exp(720/Tg)}
    O + O + O2 -> O2 + O2                : {4.0e-33 * (300/Tg)^0.41}
    O + O + N -> O2 + N                  : {4.0e-33 * (300/Tg)^0.41 * 0.8}
    O + O + O -> O2 + O                  : {4.0e-33 * (300/Tg)^0.41 * 3.6}
    O + O + NO -> O2 + NO                : {4.0e-33 * (300/Tg)^0.41 * 0.17}
    N + O + N2 -> NO + N2                : {1.0e-32 * (300/Tg)^0.5}
    N + O + O2 -> NO + O2                : {1.0e-32 * (300/Tg)^0.5}
    N + O + N -> NO + N                  : {1.8e-31 * (300/Tg)}
    N + O + O -> NO + O                  : {1.8e-31 * (300/Tg)}
    N + O + NO -> NO + NO                : {1.8e-31 * (300/Tg)}
    O + O2 + N2 -> O3 + N2               : {5.8e-34 * (300/Tg)^2.8}
    O + O2 + O2 -> O3 + O2               : {7.6e-34 * (300/Tg)^1.9}
    O + O2 + NO -> O3 + NO               : {7.6e-34 * (300/Tg)^1.9}
    O + O2 + N -> O3 + N                 : {3.9e-33 * (300/Tg)^1.9}
    O + O2 + O -> O3 + O                 : {3.9e-33 * (300/Tg)^1.9}
    N+ + O   -> N + O+                              : 1.0e-12
    N+ + O2  -> O2+ + N                              : 2.8e-10
    N+ + O2  -> NO+ + O                              : 2.5e-10
    N+ + O2  -> O+ + NO                              : 2.8e-11
    N+ + O3  -> NO+ + O2                             : 5.0e-10
    N+ + NO  -> NO+ + N                              : 8.0e-10
    N+ + NO  -> N2+ + O                              : 3.0e-12
    N+ + NO  -> O+ + N2                              : 1.0e-12
    O+ + N2 -> NO+ + N                               : {( 1.5 - 2.0e-3*Tg + 9.6e-7*Tg^2 ) * 1.0e-12}
    O+ + O2 -> O2+ + O                               : {2.0e-11 * (300/Tg)^0.5}
    O+ + O3 -> O2+ + O2                              : 1.0e-10
    O+ + NO -> NO+ + O                               : 2.4e-11
    O+ + NO -> O2+ + N                               : 3.0e-12
    O+ + N2D -> N+ + O                               : 1.3e-10
    N2+ + O2 -> O2+ + N2                             : {6.0e-11 * (300/Tg)^0.5}
    N2+ + O  -> NO+ + N                              : {1.3e-10 * (300/Tg)^0.5}
    N2+ + O3 -> O2+ + O + N2                         : 1.0e-10
    N2+ + N  -> N+ + N2                              : {7.2e-13 * (Tg/300)}
    N2+ + NO -> NO+ + N2                             : 3.3e-10
    O2+ + N2 -> NO+ + NO                             : 1.0e-17
    O2+ + N  -> NO+ + O                              : 1.2e-10
    O2+ + NO -> NO+ + O2                             : 6.3e-10
    N3+ + O2 -> O2+ + N + N2                         : 2.3e-11
    N3+ + N  -> N2+ + N2                             : 6.6e-11
    N3+ + NO -> NO+ + N + N2                         : 7.0e-11
    N4+ + N2 -> N2+ + N2 + N2                        : 1.0e-10
    N4+ + O2 -> O2+ + N2 + N2                        : 2.5e-10
    N4+ + O  -> O+ + N2 + N2                         : 2.5e-10
    N4+ + N  -> N+ + N2 + N2                         : 1.0e-11
    N4+ + NO -> NO+ + N2 + N2                        : 4.0e-10
    O4+ + O2 -> O2+ + O2 + O2                        : {3.3e-6  * (300/Tg)^4   * exp(-5030/Tg)}
    O4+ + O2a -> O2+ + O2 + O2                      : 1.0e-10
    O4+ + O      -> O2+ + O3                         : 3.0e-10
    O4+ + NO     -> NO+ + O2 + O2                    : 1.0e-10
    N+ + N2 + N2 -> N3+ + N2                         : {1.7e-29 * (300/Tg)^2.1}
    N+ + O + M -> NO+ + M        : 1.0e-29
    N+ + N + M -> N2+ + M        : 1.0e-29
    O+ + N2 + M -> NO+ + N + M   : {6.0e-29 * (300/Tg)^2}
    O+ + O  + M -> O2+ + M       : 1.0e-29
    O+ + N  + M -> NO+ + M       : 1.0e-29
    N2+ + N2 + N2 -> N4+ + N2                        : {5.2e-29 * (300/Tg)^2.2}
    N2+ + N  + N2 -> N3+ + N2                        : {9.0e-30 * exp(400/Tg)}
    O2+ + O2 + O2 -> O4+ + O2                        : {2.4e-30 * (300/Tg)^3.2}
    O-   + O2a -> O2-  + O                          : 1.0e-10
    O-   + O3 -> O3-  + O                            : 8.0e-10
    O2-  + O -> O-   + O2                            : 3.3e-10
    O2-  + O3 -> O3-  + O2                           : 3.5e-10
    O3-  + O -> O2-  + O2                            : 1.0e-11
    NO-  + O2 -> O2-  + NO                           : 5.0e-10
    O4- + N2 -> O2- + O2 + N2                        : {1.0e-10 * exp(-1044/Tg)}
    O4- + O2 -> O2- + O2 + O2                        : {1.0e-10 * exp(-1044/Tg)}
    O4- + O -> O3-  + O2                             : 4.0e-10
    O4- + O -> O-   + O2  + O2                       : 3.0e-10
    O4- + O2a -> O2-  + O2  + O2                    : 1.0e-10
    O-  + O2 + M -> O3- + M      : {1.1e-30 * (300./Tg)}
    O2- + O2 + M -> O4- + M      : {3.5e-31 * (300./Tg)}
    O- + N+ -> O + N                                 : {2e-7 * (300/Tg)^0.5}
    O- + N2+ -> O + N2                               : {2e-7 * (300/Tg)^0.5}
    O- + O+ -> O + O                                 : {2e-7 * (300/Tg)^0.5}
    O- + O2+ -> O + O2                               : {2e-7 * (300/Tg)^0.5}
    O- + NO+ -> O + NO                               : {2e-7 * (300/Tg)^0.5}
    O2- + N+ -> O2 + N                               : {2e-7 * (300/Tg)^0.5}
    O2- + N2+ -> O2 + N2                              : {2e-7 * (300/Tg)^0.5}
    O2- + O+ -> O2 + O                                 : {2e-7 * (300/Tg)^0.5}
    O2- + O2+ -> O2 + O2                               : {2e-7 * (300/Tg)^0.5}
    O2- + NO+ -> O2 + NO                               : {2e-7 * (300/Tg)^0.5}
    O3- + N+ -> O3 + N                                 : {2e-7 * (300/Tg)^0.5}
    O3- + N2+ -> O3 + N2                               : {2e-7 * (300/Tg)^0.5}
    O3- + O+ -> O3 + O                                 : {2e-7 * (300/Tg)^0.5}
    O3- + O2+ -> O3 + O2                               : {2e-7 * (300/Tg)^0.5}
    O3- + NO+ -> O3 + NO                               : {2e-7 * (300/Tg)^0.5}
    NO- + N+ -> NO + N                                 : {2e-7 * (300/Tg)^0.5}
    NO- + N2+ -> NO + N2                               : {2e-7 * (300/Tg)^0.5}
    NO- + O+ -> NO + O                                 : {2e-7 * (300/Tg)^0.5}
    NO- + O2+ -> NO + O2                               : {2e-7 * (300/Tg)^0.5}
    NO- + NO+ -> NO + NO                               : {2e-7 * (300/Tg)^0.5}
    O- + N2+ -> O + N + N                              : 1e-7
    O- + N3+ -> O + N + N2                             : 1e-7
    O- + N4+ -> O + N2 + N2                            : 1e-7
    O- + O2+ -> O + O + O                              : 1e-7
    O- + O4+ -> O + O2 + O2                            : 1e-7
    O- + NO+ -> O + N + O                              : 1e-7
    O2- + N2+ -> O2 + N + N                              : 1e-7
    O2- + N3+ -> O2 + N + N2                             : 1e-7
    O2- + N4+ -> O2 + N2 + N2                            : 1e-7
    O2- + O2+ -> O2 + O + O                              : 1e-7
    O2- + O4+ -> O2 + O2 + O2                            : 1e-7
    O2- + NO+ -> O2 + N + O                              : 1e-7
    O3- + N2+ -> O3 + N + N                              : 1e-7
    O3- + N3+ -> O3 + N + N2                             : 1e-7
    O3- + N4+ -> O3 + N2 + N2                            : 1e-7
    O3- + O2+ -> O3 + O + O                              : 1e-7
    O3- + O4+ -> O3 + O2 + O2                            : 1e-7
    O3- + NO+ -> O3 + N + O                              : 1e-7
    NO- + N2+ -> NO + N + N                              : 1e-7
    NO- + N3+ -> NO + N + N2                             : 1e-7
    NO- + N4+ -> NO + N2 + N2                            : 1e-7
    NO- + O2+ -> NO + O + O                              : 1e-7
    NO- + O4+ -> NO + O2 + O2                            : 1e-7
    NO- + NO+ -> NO + N + O                              : 1e-7
    O4- + N+ -> O2 + O2 + N                              : 1e-7 
    O4- + N2+ -> O2 + O2 + N2                            : 1e-7 
    O4- + O+ -> O2 + O2 + O                              : 1e-7 
    O4- + O2+ -> O2 + O2 + O2                            : 1e-7 
    O4- + NO+ -> O2 + O2 + NO                            : 1e-7 
    O4- + N3+ -> O2 + O2 + N2 + N                        : 1e-7 
    O4- + N4+ -> O2 + O2 + N2 + N2                       : 1e-7 
    O4- + O4+ -> O2 + O2 + O2 + O2                       : 1e-7 
    O- + N+ + M -> O + N + M                 : {2e-25 * (300/Tg)^2.5}
    O- + N2+ + M -> O + N2 + M               : {2e-25 * (300/Tg)^2.5}
    O- + O+ + M -> O + O + M                 : {2e-25 * (300/Tg)^2.5}
    O- + O2+ + M -> O + O2 + M               : {2e-25 * (300/Tg)^2.5}
    O- + NO+ + M -> O + NO + M               : {2e-25 * (300/Tg)^2.5}
    O2- + N+ + M -> O2 + N + M               : {2e-25 * (300/Tg)^2.5}
    O2- + N2+ + M -> O2 + N2 + M             : {2e-25 * (300/Tg)^2.5}
    O2- + O+ + M -> O2 + O + M               : {2e-25 * (300/Tg)^2.5}
    O2- + O2+ + M -> O2 + O2 + M             : {2e-25 * (300/Tg)^2.5}
    O2- + NO+ + M -> O2 + NO + M             : {2e-25 * (300/Tg)^2.5}
    O- + N+ + M -> NO + M                    : {2e-25 * (300/Tg)^2.5}
    O- + O+ + M -> O2 + M                    : {2e-25 * (300/Tg)^2.5}
    O- + O2+ + M -> O3 + M                   : {2e-25 * (300/Tg)^2.5}
    O2- + O+ + M -> O3 + M                   : {2e-25 * (300/Tg)^2.5}
    O3- + N+ + M -> O3 + N + M               : {2e-25 * (300/Tg)^2.5}
    O3- + N2+ + M -> O3 + N2 + M             : {2e-25 * (300/Tg)^2.5}
    O3- + O+ + M -> O3 + O + M               : {2e-25 * (300/Tg)^2.5}
    O3- + O2+ + M -> O3 + O2 + M             : {2e-25 * (300/Tg)^2.5}
    O3- + NO+ + M -> O3 + NO + M             : {2e-25 * (300/Tg)^2.5}
    NO- + N+ + M -> NO + N + M               : {2e-25 * (300/Tg)^2.5}
    NO- + N2+ + M -> NO + N2 + M             : {2e-25 * (300/Tg)^2.5}
    NO- + O+ + M -> NO + O + M               : {2e-25 * (300/Tg)^2.5}
    NO- + O2+ + M -> NO + O2 + M             : {2e-25 * (300/Tg)^2.5}
    NO- + NO+ + M -> NO + NO + M             : {2e-25 * (300/Tg)^2.5}
    e + N2O -> e + e + N2O+            : EEDF (C88_N2O_Ionization_12.89_eV)
    e + N2O+ -> N2 + O                 : {2.0e-7 * (300/Te)^0.5}
    e + NO2+ -> NO + O                 : {2.0e-7 * (300/Te)^0.5}
    e + N2O -> NO- + N                   : EEDF (C80_N2O_Attachment)
    e + NO2 -> O- + NO                   : 1e-11
    e + N2O + M -> N2O- + M  : 1e-31
    O-  + NO -> NO2 + e                  : 2.6e-10
    O-  + N2 -> N2O + e                  : 5.0e-13
    NO- + N -> N2O + e                   : 5e-10 
    N2O- + N -> NO + N2 + e              : 5e-10
    NO2- + N -> NO + NO + e              : 5e-10
    NO3- + N -> NO + NO2 + e             : 5e-10
    NO- + O -> NO2 + e                   : 1.5e-10
    N2O- + O -> NO + NO + e              : 1.5e-10
    NO2- + O -> NO + O2 + e              : 1.5e-10
    NO3- + O -> NO + O3 + e              : 1.5e-10
    N2O- + N2A3 -> N2O + N2 + e          : 2.1e-9
    NO2- + N2A3 -> NO2 + N2 + e          : 2.1e-9
    NO3- + N2A3 -> NO3 + N2 + e          : 2.1e-9
    N2A3 + O2 -> N2O + O                 : {2.0e-14 * (Tg/300)^0.55}
    N2A3 + N2O -> N2 + N + NO            : 1.0e-11
    N2A3 + NO2 -> N2 + O + NO            : 1.0e-12
    N2D + N2O -> NO + N2                 : 3.5e-12
    O1D + N2O -> NO + NO                 : 7.2e-11
    O1D + N2O -> O2 + N2                 : 4.4e-11
    N + NO2 -> O + O + N2                : 9.1e-13
    N + NO2 -> O + N2O                   : 3.0e-12
    N + NO2 -> N2 + O2                   : 7.0e-13
    N + NO2 -> NO + NO                   : 2.3e-12
    O2- + N -> NO2 + e                   : 5.0e-10
    O + NO -> NO2                        : 4.2e-18
    O + N2O -> N2 + O2                   : {8.3e-12 * exp(-14000/Tg)}
    O + N2O -> NO + NO                   : {1.5e-10 * exp(-14090/Tg)}
    O + NO2 -> NO + O2                   : {9.1e-12 * (Tg/300)^0.18}
    O + NO3 -> O2 + NO2                  : 1.0e-11
    N2 + O2 -> O + N2O                   : {2.5e-10 * exp(-50390/Tg)}
    NO + NO -> N + NO2                   : {3.3e-16 * (300/Tg)^0.5 * exp(-39200/Tg)}
    NO + NO -> O + N2O                   : {2.2e-12 * exp(-32100/Tg)}
    NO + O2 -> O + NO2                   : {2.8e-12 * exp(-23400/Tg)}
    NO + O3 -> O2 + NO2                  : {2.5e-13 * exp(-765/Tg)}
    NO + N2O -> N2 + NO2                 : {4.6e-10 * exp(-25170/Tg)}
    NO + NO3 -> NO2 + NO2                : 1.7e-11
    O2 + NO2 -> NO + O3                  : {2.8e-12 * exp(-25400/Tg)}
    NO2 + NO2 -> NO + NO + O2            : {3.3e-12 * exp(-13500/Tg)}
    NO2 + NO2 -> NO + NO3                : {4.5e-10 * exp(-18500/Tg)}
    NO2 + O3 -> O2 + NO3                 : {1.2e-13 * exp(-2450/Tg)}
    NO2 + NO3 -> NO + NO2 + O2           : {2.3e-13 * exp(-1600/Tg)}
    NO3 + O2 -> NO2 + O3                 : {1.5e-12 * exp(-15020/Tg)}
    NO3 + NO3 -> O2 + NO2 + NO2          : {4.3e-12 * exp(-3850/Tg)}
    N2O + N2 -> N2 + O + N2              : {1.2e-8 * (300/Tg) * exp(-29000/Tg)}
    N2O + O2 -> N2 + O + O2              : {1.2e-8 * (300/Tg) * exp(-29000/Tg)}
    N2O + NO -> N2 + O + NO              : {1.2e-8 * (300/Tg) * exp(-29000/Tg) * 2}
    N2O + N2O -> N2 + O + N2O            : {1.2e-8 * (300/Tg) * exp(-29000/Tg) * 4}
    NO2 + N2 -> N2 + O + N2              : {6.8e-6 * (300/Tg)^2 * exp(-36180/Tg)}
    NO2 + O2 -> N2 + O + O2              : {6.8e-6 * (300/Tg)^2 * exp(-36180/Tg) * 0.78}
    NO2 + NO -> N2 + O + NO              : {6.8e-6 * (300/Tg)^2 * exp(-36180/Tg) * 7.8}
    NO2 + NO2 -> N2 + O + NO2            : {6.8e-6 * (300/Tg)^2 * exp(-36180/Tg) * 5.9}
    NO3 + N2 -> NO2 + O + N2             : {3.1e-5 * (300/Tg)^2 * exp(-25000/Tg)}
    NO3 + O2 -> NO2 + O + O2             : {3.1e-5 * (300/Tg)^2 * exp(-25000/Tg)}
    NO3 + NO -> NO2 + O + NO             : {3.1e-5 * (300/Tg)^2 * exp(-25000/Tg)}
    NO3 + N -> NO2 + O + N               : {3.1e-5 * (300/Tg)^2 * exp(-25000/Tg) * 10}
    NO3 + O -> NO2 + O + O               : {3.1e-5 * (300/Tg)^2 * exp(-25000/Tg) * 10}
    NO3 + N2 -> NO + O2 + N2             : {6.2e-5 * (300/Tg)^2 * exp(-25000/Tg)}
    NO3 + O2 -> NO + O2 + O2             : {6.2e-5 * (300/Tg)^2 * exp(-25000/Tg)}
    NO3 + NO -> NO + O2 + NO             : {6.2e-5 * (300/Tg)^2 * exp(-25000/Tg)}
    NO3 + N -> NO + O2 + N               : {6.2e-5 * (300/Tg)^2 * exp(-25000/Tg) * 12}
    NO3 + O -> NO + O2 + O               : {6.2e-5 * (300/Tg)^2 * exp(-25000/Tg) * 12}
    N2O5 + M -> NO2 + NO3 + M : {2.1e-11 * (300/Tg)^4.4 * exp(-11080/Tg)}
    O + N2 + M -> N2O + M    : {3.9e-35 * exp(-10400/Tg)}
    O + NO + N2 -> NO2 + N2              : {1.2e-31 * (300/Tg)^1.8}
    O + NO + O2 -> NO2 + O2              : {1.2e-31 * (300/Tg)^1.8 * 0.78}
    O + NO + NO -> NO2 + NO              : {1.2e-31 * (300/Tg)^1.8 * 0.78}
    O + NO2 + N2 -> NO3 + N2             : {8.9e-32 * (300/Tg)^2}
    O + NO2 + O2 -> NO3 + O2             : {8.9e-32 * (300/Tg)^2}
    O + NO2 + N -> NO3 + N               : {8.9e-32 * (300/Tg)^2 * 13}
    O + NO2 + O -> NO3 + O               : {8.9e-32 * (300/Tg)^2 * 13}
    O + NO2 + NO -> NO3 + NO             : {8.9e-32 * (300/Tg)^2 * 2.4}
    NO2 + NO3 + M -> N2O5 + M : {3.7e-30 * (300/Tg)^4.1}
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
    O- + N2O+ -> O + N2O                             : {2e-7 * (300/Tg)^0.5}
    O- + NO2+ -> O + NO2                             : {2e-7 * (300/Tg)^0.5}
    O2- + N2O+ -> O2 + N2O                             : {2e-7 * (300/Tg)^0.5}
    O2- + NO2+ -> O2 + NO2                             : {2e-7 * (300/Tg)^0.5}
    O3- + N2O+ -> O3 + N2O                             : {2e-7 * (300/Tg)^0.5}
    O3- + NO2+ -> O3 + NO2                             : {2e-7 * (300/Tg)^0.5}
    NO- + N2O+ -> NO + N2O                             : {2e-7 * (300/Tg)^0.5}
    NO- + NO2+ -> NO + NO2                             : {2e-7 * (300/Tg)^0.5}
    N2O- + N+ -> N2O + N                                 : {2e-7 * (300/Tg)^0.5}
    N2O- + N2+ -> N2O + N2                               : {2e-7 * (300/Tg)^0.5}
    N2O- + O+ -> N2O + O                                 : {2e-7 * (300/Tg)^0.5}
    N2O- + O2+ -> N2O + O2                               : {2e-7 * (300/Tg)^0.5}
    N2O- + NO+ -> N2O + NO                               : {2e-7 * (300/Tg)^0.5}
    N2O- + N2O+ -> N2O + N2O                             : {2e-7 * (300/Tg)^0.5}
    N2O- + NO2+ -> N2O + NO2                             : {2e-7 * (300/Tg)^0.5}
    NO2- + N+ -> NO2 + N                                 : {2e-7 * (300/Tg)^0.5}
    NO2- + N2+ -> NO2 + N2                               : {2e-7 * (300/Tg)^0.5}
    NO2- + O+ -> NO2 + O                                 : {2e-7 * (300/Tg)^0.5}
    NO2- + O2+ -> NO2 + O2                               : {2e-7 * (300/Tg)^0.5}
    NO2- + NO+ -> NO2 + NO                               : {2e-7 * (300/Tg)^0.5}
    NO2- + N2O+ -> NO2 + N2O                             : {2e-7 * (300/Tg)^0.5}
    NO2- + NO2+ -> NO2 + NO2                             : {2e-7 * (300/Tg)^0.5}
    NO3- + N+ -> NO3 + N                                 : {2e-7 * (300/Tg)^0.5}
    NO3- + N2+ -> NO3 + N2                               : {2e-7 * (300/Tg)^0.5}
    NO3- + O+ -> NO3 + O                                 : {2e-7 * (300/Tg)^0.5}
    NO3- + O2+ -> NO3 + O2                               : {2e-7 * (300/Tg)^0.5}
    NO3- + NO+ -> NO3 + NO                               : {2e-7 * (300/Tg)^0.5}
    NO3- + N2O+ -> NO3 + N2O                             : {2e-7 * (300/Tg)^0.5}
    NO3- + NO2+ -> NO3 + NO2                             : {2e-7 * (300/Tg)^0.5}
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
    N2O- + N4+ -> N2O + N2 + N2                          : 1e-7
    N2O- + O2+ -> N2O + O + O                            : 1e-7
    N2O- + O4+ -> N2O + O2 + O2                          : 1e-7
    N2O- + NO+ -> N2O + N + O                            : 1e-7
    N2O- + N2O+ -> N2O + N2 + O                          : 1e-7
    N2O- + NO2+ -> N2O + N + O2                          : 1e-7
    NO2- + N2+ -> NO2 + N + N                            : 1e-7
    NO2- + N3+ -> NO2 + N + N2                           : 1e-7
    NO2- + N4+ -> NO2 + N2 + N2                          : 1e-7
    NO2- + O2+ -> NO2 + O + O                            : 1e-7
    NO2- + O4+ -> NO2 + O2 + O2                          : 1e-7
    NO2- + NO+ -> NO2 + N + O                            : 1e-7
    NO2- + N2O+ -> NO2 + N2 + O                          : 1e-7
    NO2- + NO2+ -> NO2 + N + O2                          : 1e-7
    NO3- + N2+ -> NO3 + N + N                            : 1e-7
    NO3- + N3+ -> NO3 + N + N2                           : 1e-7
    NO3- + N4+ -> NO3 + N2 + N2                          : 1e-7
    NO3- + O2+ -> NO3 + O + O                            : 1e-7
    NO3- + O4+ -> NO3 + O2 + O2                          : 1e-7
    NO3- + NO+ -> NO3 + N + O                            : 1e-7
    NO3- + N2O+ -> NO3 + N2 + O                          : 1e-7
    NO3- + NO2+ -> NO3 + N + O2                          : 1e-7
    O4- + N2O+ -> O2 + O2 + N2O                          : 1e-7 
    O4- + NO2+ -> O2 + O2 + NO2                          : 1e-7 
    O- + N2+ + M -> N2O + M                  : {2e-25 * (300/Tg)^2.5}
    O3- + N2O+ + M -> O3 + N2O + M           : {2e-25 * (300/Tg)^2.5}
    O3- + NO2+ + M -> O3 + NO2 + M           : {2e-25 * (300/Tg)^2.5}
    NO- + N2O+ + M -> NO + N2O + M           : {2e-25 * (300/Tg)^2.5}
    NO- + NO2+ + M -> NO + NO2 + M           : {2e-25 * (300/Tg)^2.5}
    N2O- + N+ + M -> N2O + N + M             : {2e-25 * (300/Tg)^2.5}
    N2O- + N2+ + M -> N2O + N2 + M           : {2e-25 * (300/Tg)^2.5}
    N2O- + O+ + M -> N2O + O + M             : {2e-25 * (300/Tg)^2.5}
    N2O- + O2+ + M -> N2O + O2 + M           : {2e-25 * (300/Tg)^2.5}
    N2O- + NO+ + M -> N2O + NO + M           : {2e-25 * (300/Tg)^2.5}
    N2O- + N2O+ + M -> N2O + N2O + M         : {2e-25 * (300/Tg)^2.5}
    N2O- + NO2+ + M -> N2O + NO2 + M         : {2e-25 * (300/Tg)^2.5}
    NO2- + N+ + M -> NO2 + N + M             : {2e-25 * (300/Tg)^2.5}
    NO2- + N2+ + M -> NO2 + N2 + M           : {2e-25 * (300/Tg)^2.5}
    NO2- + O+ + M -> NO2 + O + M             : {2e-25 * (300/Tg)^2.5}
    NO2- + O2+ + M -> NO2 + O2 + M           : {2e-25 * (300/Tg)^2.5}
    NO2- + NO+ + M -> NO2 + NO + M           : {2e-25 * (300/Tg)^2.5}
    NO2- + N2O+ + M -> NO2 + N2O + M         : {2e-25 * (300/Tg)^2.5}
    NO2- + NO2+ + M -> NO2 + NO2 + M         : {2e-25 * (300/Tg)^2.5}
    NO3- + N+ + M -> NO3 + N + M             : {2e-25 * (300/Tg)^2.5}
    NO3- + N2+ + M -> NO3 + N2 + M           : {2e-25 * (300/Tg)^2.5}
    NO3- + O+ + M -> NO3 + O + M             : {2e-25 * (300/Tg)^2.5}
    NO3- + O2+ + M -> NO3 + O2 + M           : {2e-25 * (300/Tg)^2.5}
    NO3- + NO+ + M -> NO3 + NO + M           : {2e-25 * (300/Tg)^2.5}
    NO3- + N2O+ + M -> NO3 + N2O + M         : {2e-25 * (300/Tg)^2.5}
    NO3- + NO2+ + M -> NO3 + NO2 + M         : {2e-25 * (300/Tg)^2.5}
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
    O-  + NO + M -> NO2- + M                 : 1.0e-29
    O- + NO+ + M -> NO2 + M                  : {2e-25 * (300/Tg)^2.5}
    O2- + N+ + M -> NO2 + M                  : {2e-25 * (300/Tg)^2.5}
    O4- + NO -> NO3- + O2                            : 2.5e-10
    O2- + NO+ + M -> NO3 + M                 : {2e-25 * (300/Tg)^2.5}
'
  []
[]


#e + N2A3 -> e + N2                 : EEDF (C48_N2A3_De-excitation_6.17_eV)
#e + N2A3 -> e + e + N2+            : EEDF (C50_N2A3_Ionization_10.79_eV)
#e + O2a -> e + O2                  : EEDF (C55_O2a1_De-excitation_0.98_eV) 
#e + O2a -> e + O + O               : EEDF (C58_O2a1_Excitation_6.00_eV)
#e + O2a -> e + e + O2+             : EEDF (C59_O2a1_Ionization_11.00_eV)
#e + NO -> e + e + NO+              : EEDF (C75_NO_Ionization_9.26_eV)
#e + NO -> O- + N                   : EEDF (C66_NO_Attachment)
                  

[AuxVariables]
  [reduced_field]
    order = FIRST
    family = SCALAR
    initial_condition = 100
  []

  [Te]
    order = FIRST
    family = SCALAR
  []

  [Tg]
    order = FIRST
    family = SCALAR
    initial_condition = 340
  []
  
  [M]
    order = FIRST
    family = SCALAR
  []
[]


[AuxScalarKernels]
  #[reduced_field_calculate]
  #  type = ParsedAuxScalar
  #  variable = reduced_field
  #  constant_names = 'V d'
  #  constant_expressions = '20000 0.002'
  #  args = 'reduced_field M'
  #  function = 'V/(d*M*1e6*1e-21)'
  #  execute_on = 'TIMESTEP_END'
  #[]

  [reduced_field_calculation]
    type = ScalarLinearInterpolation
    variable = reduced_field
    use_time = true
    property_file = 'data/reduced_field.txt'
    execute_on = 'TIMESTEP_BEGIN'
  []

  [temperature_calculation]
    type = ScalarLinearInterpolation
    variable = Te
    sampler = reduced_field
    property_file = 'data/electron_temperature.txt'
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [neutral_sum]
    type = VariableSumLog
    variable = M
    args = 'N2 O2 N2A3 N N2D O2a O O1D O3 NO N2O NO2 NO3 N2O3 N2O4 N2O5'
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

[]

[Debug]
  show_var_residual_norms = false
[]

#[UserObjects]
#  active = 'value_provider'
#
#[./value_provider]
#  type = ValueProvider
#  property_file = 'data/electron_temperature.txt'
#[../]
#[]

[Executioner]
  type = Transient
  automatic_scaling = true
  compute_scaling_once = false
  end_time = 0.001
  solve_type = NEWTON
  dtmin = 1e-15
  dtmax = 1e-7
  line_search = 'basic'
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -snes_linesearch_minlambda -snes_stol -ksp_type'
  petsc_options_value = 'lu NONZERO 1.e-10 1e-3 0 fgmres'
  steady_state_detection = false
  [TimeSteppers]
    [adaptive]
      type = IterationAdaptiveDT
      cutback_factor = 0.95
      dt = 1e-12
      growth_factor = 1.05
    []
  []
  #[TimeIntegrator]
  #  type = LStableDirk2
  #[]
[]

#[Preconditioning]
#  [smp]
#    type = SMP
#    full = true
    #ksp_norm = none
#  []
#[]

[Outputs]
  [out]
    type = CSV
    interval = 10
  []
  [console]
    type = Console
    execute_scalars_on = 'none'
  []
[]
