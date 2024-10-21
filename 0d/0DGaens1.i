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
    initial_condition = 1e16
    # scaling = 1e-2
  []

  [N2]
    family = SCALAR
    order = FIRST
    initial_condition = 1.93e19
    #scaling = 1e-9
  []

  [O2]
    family = SCALAR
    order = FIRST
    initial_condition = 5.5e18
    #scaling = 1e-9
  []

  [N2+]
    family = SCALAR
    order = FIRST
    initial_condition = 9e15
    # scaling = 5e8
  []

  [O2+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e15
    # scaling = 5e8
  []

  [O2-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    # scaling = 1e2
  []

  [N2D]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []

  [N2A3]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []

  [O2a]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    # scaling = 1e-2
  []
  
  [N]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []

  [O]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []

  [O1D]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
  
  [N+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []

  [N3+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []

  [O+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []

  [O-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
  
  [NO]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
    
  [NO-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
    
  [NO+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
  
  [N2O]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
  
  [N2O+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
  
  [N2O-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
  
  [NO2]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
  
  [NO2-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
  
  [NO2+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
  
  [NO3]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
  
  [NO3-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []

  [O3]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
  [O3-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []

  [O4+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []

  [N4+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []

  [N2O5]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []

  [N2O3]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []

  [N2O4]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-9
  []
[]

[ScalarKernels]
  [de_dt]
    type = ODETimeDerivative
    variable = e
  []

  [dN2_dt]
    type = ODETimeDerivative
    variable = N2
  []

  [dO2_dt]
    type = ODETimeDerivative
    variable = O2
  []

  [dN2+_dt]
    type = ODETimeDerivative
    variable = N2+
  []

  [dO2+_dt]
    type = ODETimeDerivative
    variable = O2+
  []

  [dO2-_dt]
    type = ODETimeDerivative
    variable = O2-
  []

  [dN2D_dt]
    type = ODETimeDerivative
    variable = N2D
  []

  [dN2A3_dt]
    type = ODETimeDerivative
    variable = N2A3
  []

  [dO2a_dt]
    type = ODETimeDerivative
    variable = O2a
  []
  [dN_dt]
    type = ODETimeDerivative
    variable = N
  []

  [dO_dt]
    type = ODETimeDerivative
    variable = O
  []

  [dO1D_dt]
    type = ODETimeDerivative
    variable = O1D
  []
  
  [dN+_dt]
    type = ODETimeDerivative
    variable = N+
  []
  
  [dN3+_dt]
    type = ODETimeDerivative
    variable = N3+
  []

  [dO+_dt]
    type = ODETimeDerivative
    variable = O+
  []

  [dO-_dt]
    type = ODETimeDerivative
    variable = O-
  []

  [dNO_dt]
    type = ODETimeDerivative
    variable = NO
  []

  [dNO-_dt]
    type = ODETimeDerivative
    variable = NO-
  []

  [dNO+_dt]
    type = ODETimeDerivative
    variable = NO+
  []

  [dN2O_dt]
    type = ODETimeDerivative
    variable = N2O
  []

  [dN2O+_dt]
    type = ODETimeDerivative
    variable = N2O+
  []

  [dN2O-_dt]
    type = ODETimeDerivative
    variable = N2O-
  []

  [dNO2_dt]
    type = ODETimeDerivative
    variable = NO2
  []

  [dNO2-_dt]
    type = ODETimeDerivative
    variable = NO2-
  []

  [dNO2+_dt]
    type = ODETimeDerivative
    variable = NO2+
  []

  [dNO3_dt]
    type = ODETimeDerivative
    variable = NO3
  []

  [dNO3-_dt]
    type = ODETimeDerivative
    variable = NO3-
  []

  [dO3_dt]
    type = ODETimeDerivative
    variable = O3
  []

  [dO3-_dt]
    type = ODETimeDerivative
    variable = O3-
  []

  [dO4+_dt]
    type = ODETimeDerivative
    variable = O4+
  []

  [dN4+_dt]
    type = ODETimeDerivative
    variable = N4+
  []

  [dN2O5_dt]
    type = ODETimeDerivative
    variable = N2O5
  []
  
  [dN2O3_dt]
    type = ODETimeDerivative
    variable = N2O3
  []
  
  [dN2O4_dt]
    type = ODETimeDerivative
    variable = N2O4
  []
[]






























































[GlobalReactions]
  [Air]
    species = 'N+ N2+ N3+ N4+ O+ O2+ O4+ NO+ NO2+ e O- O2- O3- NO- NO2- NO3- N2D N2A3
     O1D N O O2a O3 NO N2O N2O+ N2O- NO2 NO3 N2O3 N2O4 N2O5 N2 O2'
    num_particles = '1 2 3 4 1 2 4 2 3 0 1 2 3 2 3 4 1 2 1 1 1 2 3 2 3 3 3 3 4 5 6 7 2 2'
    file_location = 'data'
    aux_species = 'M'

    # These are parameters required equation-based rate coefficients
    equation_constants = 'Tg pi kb'
    equation_values = '330 3.141 8.6173e-5'
    equation_variables = 'Te'
    sampling_variable = 'reduced_field'
    electron_density = 'e'
    include_electrons = true
    balance_check = true
    track_rates = true

    reactions = '
    e + O -> e + O1D                   : EEDF (C63_O_Excitation_1.97_eV)
    e + O -> e + e + O+                : EEDF (C65_O_Ionization_13.62_eV)
    e + O + O2 -> O- + O2              : 1e-31
    e + e + O+ -> O + e                : {7.1e-27 * (0.66*Te/kb)^-4.5}
    e + O+ + M -> O + M                : {4.31e-34 * ((0.66*Te/kb)^-1.5)}
    e + O2 -> e + O2a                  : EEDF (C33_O2_Excitation_0.98_eV)
    e + O2 -> e + e + O2+              : EEDF (C39_O2_Ionization_12.06_eV)
    e + O2 -> e + O + O                : EEDF (C36_O2_Excitation_6.00_eV)
    e + O2 -> O- + O                   : EEDF (C25_O2_Attachment)
    e + O2 + O2 -> O2- + O2            : {1.4e-29*(Tg/(0.66*Te/kb))*exp(-600/Tg)*exp(700*((0.66*Te/kb)-Tg)/((0.66*Te/kb)*Tg))}
    e + O2 + N2 -> O2- + N2            : {1.1e-31*(Tg/(0.66*Te/kb))^2*exp(-70/Tg)*exp(1500*((0.66*Te/kb)-Tg)/((0.66*Te/kb)*Tg))}
    e + O2a -> e + O + O               : EEDF (C58_O2a1_Excitation_6.00_eV)
    e + O2a -> e + O2                  : EEDF (C55_O2a1_De-excitation_0.98_eV) 
    e + O2a -> e + e + O2+             : EEDF (C59_O2a1_Ionization_11.00_eV)
    e + O2+ -> O + O                   : {1.68e-5 * (0.66*Te/kb^-0.7)}
    e + O2+ + M -> O2 + M              : {4.31e-34 * ((0.66*Te/kb)^-1.5)}
    e + e + O2+ -> O2 + e              : {7.18e-27 * (0.66*Te/kb)^-4.5}
    e + O3 -> O + O2 + e               : {1.78e-6 * (Te^(-0.614))*exp(-11.5/Te)}
    e + O3 -> O- + O2                  : EEDF (C76_O3_Attachment)
    e + O3 -> O2- + O                  : EEDF (C77_O3_Attachment)
    e + N -> N2D + e                   : {5.06e-9 * exp(-10.8/(Te^(3.95)))}
    e + e + N+ -> N + e                : {5.4e-24 * (0.66*Te/kb)^-4.5}
    e + N+ + M -> N + M                : {2.49e-29 * (0.66*Te/kb)^-1.5}
    e + N2 -> e + N2A3                 : EEDF (C11_N2_Excitation_6.17_eV.txt)
    e + N2 -> e + e + N2+              : EEDF (C24_N2_Ionization_15.60_eV)
    e + N2A3 -> e + N2                 : EEDF (C48_N2A3_De-excitation_6.17_eV)
    e + N2A3 -> e + e + N2+            : EEDF (C50_N2A3_Ionization_10.79_eV)
    e + N2+ -> N + N                   : {1.66e-6 * (0.66*Te/kb)^-0.7}
    e + e + N2+ -> N2 + e              : {7.18e-27 * (0.66*Te/kb)^-4.5}
    e + N2+ + M -> N2 + M              : {4.31e-34 * ((0.66*Te/kb)^-4.5)}
    e + NO -> O- + N                   : EEDF (C66_NO_Attachment)
    e + NO -> e + e + NO+              : EEDF (C75_NO_Ionization_9.26_eV)
    e + NO+ -> N + O                   : {1.07e-5 * (0.66*Te/kb)^-0.85}
    e + NO+ -> N2D + O                 : {4.28e-5 * (0.66*Te/kb)^-0.85}
    e + NO2 -> NO + O + e              : {5.6e-9 * exp(-3.11/(0.66*Te/kb))}
    e + NO2+ -> NO + O                 : {3.46e-6 / ((0.66*Te/kb)^0.5)}
    e + NO2+ -> NO + O1D               : {3.46e-6 / ((0.66*Te/kb)^0.5)}
    e + N2O -> O- + N2                 : 2e-10
    e + N2O -> N2 + O + e              : {1.4e-9 * exp(-1.67/(0.66*Te/kb))}
    e + N2O -> N2 + O1D + e            : {1.2e-9 * exp(-3.64/(0.66*Te/kb))}
    e + N2O -> NO + N + e              : {1e-10 * exp(-4.93/(0.66*Te/kb))}    
    O + O + O -> O2 + O                : {4.0e-33 * (300/Tg)^0.41 * 3.6}
    O + O + O2 -> O2 + O2              : {5.2e-35 * exp(900/Tg)}
    O + O + O3 -> O2 + O3              : {1.3e-34 * exp(900/Tg)}
    O + O + M -> O2a + M               : {6.93e-35 * (Tg/300)^-0.63}
    O + O1D + M -> O2 + M              : 9.9e-33
    O + O+ + M -> O2+ + M              : 1e-29
    O + O- -> O2 + e                   : 1.5e-10
    O + O2 + O2 -> O3 + O2             : {6.4e-35 * exp(663/Tg)}
    O + O2 + N2 -> O3 + N2             : {6.4e-35 * exp(663/Tg)}
    O + O2 + O3 -> O3 + O3             : {1.3e-34 * exp(663/Tg)}
    O + O2- -> O3 + e                  : 1.5e-10
    O + O2- -> O- + O2                 : {1.5e-10 * (Tg/300)^0.5}
    O + O3 -> O2 + O2                  : {8e-12 * exp(-2060/Tg)}
    O + O3- -> O2 + O2 + e             : 3e-10
    O + O3- -> O2- + O2                : 3.2e-10
    O1D + O2 -> O + O2a                : {2.6e-11*exp(67/Tg)}
    O1D + O3 -> O2a + O2               : 2.65e-10
    O1D + M -> O + M                   : 5e-12
    O- + O+ -> O + O                   : {2e-7 * (300/Tg)^0.5}
    O- + O+ + M -> O + O + M           : {2e-25 * (300/Tg)^2.5}
    O+ + O2 -> O2+ + O                 : 2.1e-11
    O+ + O2- -> O + O2                 : {2.7e-7 * (300/Tg)^0.5}
    O+ + O2- -> O + O + O              : 1e-7
    O+ + O2- + M -> O3 + M             : {2e-28 * (Tg/300)^-2.5}
    O+ + O2- + M -> O2 + O + M         : {2e-25 * (300/Tg)^2.5}
    O+ + O3 -> O2+ + O2                : 1e-10
    O+ + O3- -> O2 + O + O             : 1e-7
    O+ + O3- -> O3 + O                 : {2e-7 * (Tg/300)^-0.5}
    O+ + O3- + M -> O3 + O + M         : {2e-25 * (300/Tg)^2.5}
    O- + O2 -> O2- + O                 : 1e-10
    O- + O2 + M -> O3- + M             : {1.1e-30*(300/Tg)} 
    O- + O2a -> O3 + e                 : 3e-10
    O- + O2a -> O2- + O                : 1e-10
    O- + O2+ -> O + O2                 : {2e-7 * (300/Tg)^0.5}
    O- + O2+ -> O + O + O              : 1.0e-7
    O- + O2+ + M -> O + O2 + M         : {2e-25 * (300/Tg)^2.5}
    O- + O3 -> O3- + O                 : 5.3e-10
    O2 + O2+ + M -> O4+ + M            : {2.4e-30 * (300/Tg)^3.2}
    O2a + O2a -> O2 + O2               : {9e-17 * exp(-560/Tg)}
    O2- + O2a -> O2 + O2 + e           : 2e-10
    O2a + O3 -> O + O2 + O2            : 1e-14
    O2a + N2 -> O2 + N2                : {3e-18 * exp(-200/Tg)}
    O2- + O2+ -> O + O + O + O         : 1e-7
    O2- + O2+ -> O2 + O + O            : 1e-7
    O2- + O2+ -> O2 + O2               : {1e-7 * (300/Tg)^0.5}
    O2- + O2+ + M -> O2 + O2 + M       : {1e-24 * (300/Tg)^2.5}
    O2+ + O3- -> O3 + O2               : {2e-7 * (300/Tg)^0.5}
    O2+ + O3- -> O2 + O2 + O           : 1e-7
    O2+ + O3- -> O2 + O + O + O        : 1e-7
    O2+ + O3- M -> O3 + O2 + M         : {1e-25 * (300/Tg)^2.5}
    O2- + O3 -> O3- + O2               : 4e-10
    O2- + M -> O2 + M + e              : {2.7e-10 * (Tg/300)^0.5 * exp(-5590/Tg)}
    O3 + N2 -> O + O2 + N2             : {7.3e-10 * exp(-11400/Tg)}
    O2 + O3 -> O + O2 + O2             : {7.3e-10 * exp(-11400/Tg)}
    O3 + O3 -> O + O2 + O3             : {1.4e-9 * exp(-11400/Tg)}
    O4+ + M -> O2+ + O2 + M            : {3.3e-6 * (Tg/300)^-2.5 * exp(-2650/Tg)}
    N + N2+ + M -> N3+ + M             : {9e-30 * (400/Tg)}
    N + N3+ ->  N2+ + N2               : 6.6e-11
    N + N4+ -> N+ + N2 + N2            : 1e-11
    N2D + M -> N + M                   : 2.4e-14
    N+ + N2 -> N + N2+                 : 4.45e-10
    N+ + N2 + M -> N3+ + M             : {9e-30 * exp(400/Tg)}
    N2 + N2+ + M -> N4+ + M            : {6.8e-29 * (300/Tg)^1.64}
    O2 + N2A3 -> O2 + N2               : 8.1e-13
    O + N2A3 -> O + N2                 : 2.7e-11
    N2A3 + NO -> N2 + NO               : 1.5e-10
    N3+ + M -> N2+ + N + M             : 6.6e-11
    N4+ + M -> N2+ + N2 + M            : 2e-15
    O + N+ -> O+ + N                   : 1e-12
    O + N+ + M -> NO+ + M              : 1e-29
    O + N2A3 -> NO + N2D               : 1e-12
    O + N2A3 -> NO + N                 : 7e-12
    O + N2+ -> O+ + N2                 : {1e-11 * (300/Tg)^0.2}
    O + N2+ -> NO+ + N                 : {1.3e-10 * (300/Tg)^0.5}
    O + N4+ -> O+ + N2 + N2            : 2.5e-10
    O + NO + N2 -> NO2 + N2            : {1e-31 * (300/Tg)^1.6}
    O + NO2 -> NO + O2                 : {6.5e-12*exp(120/Tg)}
    O + NO2 + N2 -> NO3 + N2           : {9e-32 * (300/Tg)^2}
    O + NO2 + O2 -> NO3 + O2           : {9e-32 * (300/Tg)^2}
    O + NO2+ -> NO+ + O2               : 8e-12
    O + NO2- -> NO3 + e                : 1e-11
    O + NO3 -> O2 + NO2                : 1.7e-11
    O + NO3- -> NO2 + O2-              : 2.5e-12
    O + NO3- -> NO2- + O2              : 2.5e-12
    O + NO3- -> NO2 + O2 + e           : 2.5e-12
    O1D + NO -> O2 + N                 : 1.7e-10
    O+ + N + M -> NO+ + M              : 1e-29
    O+ + N2 -> NO+ + N                 : {3e-12 * exp(-0.0031/Tg)}
    O+ + N2D -> N+ + O                 : 1.3e-10
    O+ + N2 + M -> NO+ + N + M         : {6e-29*(300/Tg)^2}
    O+ + NO -> NO+ + O                 : 2.4e-11
    O+ + NO -> O2+ + N                 : 3e-12
    O+ + NO2 -> NO2+ + O               : 1.6e-9
    O+ + NO2- + M -> NO3 + M           : {2e-25 * (Tg/300)^-2.5}
    O- + N+ + M -> O + N + M           : {2e-25 * (300/Tg)^2.5}
    O- + N+ + M -> NO + M              : {2e-25 * (300/Tg)^2.5}
    O- + N2 -> N2O + e                 : 1e-12
    O- + N2A3 -> N2 + O + e            : 2.2e-9
    O- + N2+ + M -> N2 + O + M         : {2e-25 * (Tg/300)^-2.5}
    O- + N2+ + M -> N2O + M            : {2e-25 * (Tg/300)^-2.5}
    O- + NO -> NO2 + e                 : 2.6e-10
    O- + NO + M -> NO2- + M            : 1e-29
    O- + NO+ -> O + NO                 : {2e-7 * (300/Tg)^0.5} 
    O- + NO+ + M -> O + NO + M         : {2e-25 * (300/Tg)^2.5}
    O- + NO+ + M -> NO2 + M            : {2e-25 * (300/Tg)^2.5}
    O- + NO2 -> NO2- + O               : 1.2e-9
    O- + NO2+ + M -> NO2 + O + M       : {2e-25 * (300/Tg)^2.5}
    O- + NO2+ + M -> NO3 + M           : {2e-25 * (300/Tg)^2.5}
    O2 + N -> NO + O                   : {3.3e-12 * (Tg/300) * exp(-3150/Tg)}
    O2 + N2D -> NO + O                 : {1.5e-12*(Tg/300)^0.5}
    O2 + N2D -> NO + O1D               : {6e-12*(Tg/300)^0.5}
    O2 + N+ -> NO+ + O                 : 2.5e-10
    O2 + N+ -> O+ + NO                 : 2.8e-11
    O2 + N+ -> O2+ + N                 : 3e-10
    O2 + N2A3 -> N2 + O + O            : 2.54e-12
    O2 + N2A3 -> O2a + N2              : 1.29e-12
    O2 + N2A3 -> N2O + O               : 7.8e-14
    O2 + N2A3 -> N2O + O1D             : 3e-14
    O2 + N2+ -> O2+ + N2               : {6e-11 * (Tg/300)^-0.5}
    O2 + N3+ -> NO+ + N2O              : 3.6e-11
    O2 + N3+ -> NO2+ + N2              : 1.5e-11
    O2 + N4+ -> O2+ + N2 + N2          : 2.5e-10
    O2 + NO3 -> NO2 + O3               : 1e-17
    O2a + N2A3 -> N2 + O + O           : 2e-11
    O2+ + N -> NO+ + O                 : 1.2e-10
    O2+ + NO -> NO+ + O2               : 4.4e-10
    O2+ + NO2 -> NO2+ + O2             : 6.6e-10
    O2+ + NO2- -> NO2 + O2             : {2e-7*(300/Tg)^0.5}
    O2+ + NO2- -> NO2 + O + O          : 1e-7
    O2+ + NO2- -> NO + O + O2          : 1e-7
    O2+ + NO2- -> NO + O + O + O       : 1e-7
    O2+ + NO2- + M -> NO2 + O2 + M     : {2e-25*(300/Tg)^2.5}
    O2+ + NO3- -> NO3 + O2             : {2e-7*(300/Tg)^0.5}
    O2+ + NO3- -> NO3 + O + O          : 1e-7
    O2+ + NO3- -> NO2 + O + O2          : 1e-7
    O2+ + NO3- -> NO2 + O + O + O       : 1e-7
    O2+ + NO3- + M -> NO3 + O2 + M     : {2e-25*(300/Tg)^2.5}
    O2+ + N2O5 -> NO2+ + NO3 + O2      : 8.8e-10
    O2- + N -> NO2 + e                 : 5e-10
    O2- + N2A3 -> O2 + N2 + e          : 2.1e-9
    O2- + NO+ + M -> NO3 + M           : {2e-25 * (300/Tg)^2.5}
    O2- + NO+ + M -> O2 + NO + M       : {2e-25 * (300/Tg)^2.5}
    O2- + NO2 -> NO2- + O2             : 7e-10
    O2- + NO2+ -> O2 + NO2             : {2e-7*(300/Tg)^0.5}
    O2- + NO2+ + M -> O2 + NO2 + M     : {2e-25 * (300/Tg)^2.5}
    O3 + N2A3 -> N2 + O2 + O           : 3.36e-11
    O3 + N2A3 -> NO + NO + O           : 8.4e-12
    O3 + NO -> NO2 + O2                : {3e-12*exp(-1560/Tg)}
    O3 + NO2 -> NO + O2 + O2           : 1e-18
    O3 + NO2 -> NO3 + O2               : {1e-13 * exp(-2470/Tg)}
    O3 + NO2- -> NO3- + O2             : 1.8e-11
    O3 + NO3- -> NO2- + O2 + O2        : 1e-13
    O3- + N2+ + M -> O3 + N2 + M        : {2e-25 * (300/Tg)^2.5}
    O3- + NO -> NO3- + O               : 1e-11
    O3- + NO+ + M -> O3 + NO + M       : {2.0e-25 * (300/Tg)^2.5}
    O3- + NO2 -> NO2- + O3             : 7.0e-10
    O3- + NO2+ + M -> O3 + NO2 + M     : {2.0e-25 * (300/Tg)^2.5}
    O3- + NO3 -> NO3- + O3             : 5e-10
    N + NO -> N2 + O                   : {8.2e-11 * exp(410/Tg)}
    N + NO2 -> NO + NO                 : {1.33e-12 * exp(220/Tg)}
    N + NO2 -> N2O + O                 : {5.8e-12 * exp(220/Tg)}
    N + NO3 -> NO + NO2                : 3e-12
    N + NO3- -> NO + NO2-              : 5e-12
    N2D + NO -> N2O                    : 6e-11
    N2A3 + NO2 -> N2 + NO + O          : 1.3e-11
    N2A3 + N2O -> O + N2 + N2          : {9.3e-12 * exp(120/Tg)}
    N2A3 + N2O -> NO + N + N2          : 1e-11
    NO + NO2 -> N2O3                   : {7.9e-12 * (Tg/300)^1.4}
    NO + NO2+ -> NO+ + NO2             : 2.9e-10
    NO + NO3 -> NO2 + NO2              : {1.8e-11*exp(110/Tg)}
    NO+ + NO2- + M -> NO + NO2 + M     : {2e-25 * (Tg/300)^-2.5}
    NO+ + NO3- -> NO3 + N + O          : 1e-7
    NO+ + NO3- -> NO2 + NO + O         : 1e-7
    NO+ + NO3- + M -> NO + NO3 + M     : {2e-25 * (Tg/300)^-2.5}
    NO+ + N2O5 -> NO2+ + NO2 + NO2     : 5.9e-10
    NO2 + NO2 + N2 -> N2O4 + N2        : {1.4e-33 * (300/Tg)^3.8}
    NO2 + NO2 + O2 -> N2O4 + O2        : {1.4e-33 * (300/Tg)^3.8}
    NO2 + NO3 + N2 -> N2O5 + N2        : {2.8e-30 * (300/Tg)^3.5}
    NO2 + NO3 + O2 -> N2O5 + O2        : {2.8e-30 * (300/Tg)^3.5}
    NO2+ + NO3- + M -> N2O5 + M        : {2e-25 * (Tg/300)^-2.5}
    NO2+ + NO3- + M -> NO2 + NO3 + M   : {2e-25 * (Tg/300)^-2.5}
    NO2- + N2O -> NO3- + N2            : 5e-13
    NO2- + NO3 -> NO3- + NO2           : 5e-10
    NO2- + N2O5 -> NO3- + NO3 + NO     : 7e-10
    N2O3 + M -> NO + NO2 + M           : {1.03e-10*exp(-2628/Tg)}
    N2O4 + M -> NO2 + NO2 + M          : {1.09e-7*exp(-4952/Tg)}
    N2O5 + M -> NO2 + NO3 + M          : {1e-3 * (300/Tg)^3.5*exp(-11000/Tg)}
    N + N+ + M -> N2+ + M              : 1e-29
    N + N2+ -> N+ + N2                 : 7.2e-13
    N + N + N2 -> N2 + N2              : {1.38e-34 * exp(500/Tg)}
    N + N + O2 -> N2 + O2              : {1.38e-34 * exp(500/Tg)}
    N + N + O3 -> N2 + O3              : {2.5e-33 * exp(500/Tg)}
    N2D + N2+ -> N+ + N2               : 1e-10
    O+ + NO2 -> NO+ + O2               : 5e-10
    O+ + NO2- -> NO2 + O               : {2e-7*(300/Tg)^0.5}
    O+ + NO2- -> NO + O + O            : 1e-7
    O+ + NO2- + M -> NO2 + O + M       : {2e-25 * (Tg/300)^-2.5}
    O+ + N2O -> NO+ + NO               : 2.3e-10
    O+ + N2O -> O2+ + N2               : 2e-11
    O+ + NO3- -> NO3 + O               : {2e-7*(300/Tg)^0.5}
    O+ + NO3- -> NO2 + O + O           : 1e-7
    O+ + NO3- + M -> NO3 + O + M       : {2e-25 * (Tg/300)^-2.5}
    O + N2O -> N2 + O2                 : {1.66e-10 * exp(-14100/Tg)}
    O + N2O -> NO + NO                 : {1.15e-10 * exp(-13400/Tg)}
    O + N2O5 -> N2 + O2 + O2 + O2      : {3e-16 * (Tg/300)^0.5}
    O + O3 + NO -> O3 + NO2            : {2e-31 * (300/Tg)^1.6}
    O + O3 + NO2 -> O3 + NO3           : {2e-31 * (300/Tg)^2}
    O2- + NO3 -> NO3- + O2             : 5e-10
    O3 + N2D -> NO + O2                : 1e-10
    O3 + N+ -> NO+ + O2                : 5e-10
    O2- + N2O -> O3- + N2              : 9e-13
    O2- + N2O -> NO2- + NO             : 1e-14
    O4+ + NO -> NO+ + O2 + O2          : 6.8e-10
    O4+ + NO2 -> NO2+ + O2 + O2        : 3e-10
    O4+ + NO2- -> NO2 + O2 + O2        : 1e-7
    O4+ + NO2- + M -> NO2 + O2 + O2 + M                 : {2e-25 * (Tg/300)^-2.5}
    O4+ + NO3- -> NO3 + O2 + O2        : 1e-7
    O4+ + NO3- -> NO2 + O + O2 + O2    : 1e-7
    O4+ + NO3- + M -> NO3 + O2 + O2 + M                 : {2e-25 * (Tg/300)^-2.5}
    N2+ + NO3- -> NO3 + N2             : {2e-7*(300/Tg)^0.5}
    N2+ + NO3- -> NO3 + N + N          : 1e-7
    N2+ + NO3- -> NO2 + O + N2         : 1e-7
    N2+ + NO3- -> NO2 + O + N + N      : 1e-7
    N2+ + NO3- + M -> NO3 + N2 + M     : {2e-25 * (300/Tg)^2.5}
    N2+ + NO2- -> NO2 + N2             : {2e-7 * (300/Tg)^0.5}
    N2+ + NO2- -> NO2 + N + N          : 1e-7
    N2+ + NO2- -> NO + O + N2          : 1e-7
    N2+ + NO2- -> NO + O + N + N       : 1e-7
    N2+ + NO2- + M -> NO2 + N2 + M     : {2e-25 * (300/Tg)^2.5}
    N2+ + N2O -> NO+ + N + N2          : 4e-10
    N2+ + NO2 -> NO+ + N2O             : 5e-11
    N2+ + NO2 -> NO2+ + N2             : 3e-10
    N2+ + NO -> NO+ + N2               : 3.3e-10
    N2D + NO -> N2 + O                 : 4.5e-11
    N2D + NO -> N2 + O1D               : 4.5e-11
    N2D + N2O -> N2 + NO               : {1.5e-11*exp(-570/Tg)}
    N2D + NO2 -> N2O + O               : {1.5e-12*exp(-570/Tg)}
    N2D + NO2 -> NO + NO               : {1.5e-12*exp(-570/Tg)}
    N+ + N2O -> NO+ + N2               : 5.5e-10
    N+ + NO3- -> NO3 + N               : {2e-7 * (Tg/300)^-0.5}
    N+ + NO3- -> NO2 + O + N           : 1e-7
    N+ + NO3- + M -> NO3 + N + M       : {2e-25 * (Tg/300)^-2.5}
    N2D + N2 -> N + N2                 : {5e-12*exp(-1620/Tg)}
    N+ + NO2- -> NO2 + N               : {2e-7 * (300/Tg)^0.5}
    N+ + NO2- -> NO + O + N            : 1e-7
    N+ + NO2- + M -> NO2 + N + M       : {2e-25 * (Tg/300)^-2.5}
    N+ + NO2 -> NO2+ + N               : 3e-10
    N+ + NO2 -> NO+ + NO               : 5e-10
    N+ + NO -> NO+ + N                 : 8.0e-10
    N+ + NO -> N2+ + O                 : 3e-12
    N+ + NO -> O+ + N2                 : 1e-12
    NO2+ + NO3- -> NO2 + NO3           : {2e-7 * (Tg/300)^-0.5}
    NO2+ + NO3- -> NO2 + NO2 + O       : 1e-7
    NO2+ + NO3- -> NO + NO3 + O        : 1e-7
    NO2+ + NO3- -> NO + NO2 + O + O    : 1e-7
    NO2- + NO2+ -> NO2 + NO2           : {2e-7 * (300/Tg)^0.5}
    NO2- + NO2+ -> NO2 + NO + O        : 1e-7
    NO2- + NO2+ -> NO + NO + O + O     : 1e-7
    NO2- + NO2+ + M -> NO2 + NO2 + M   : {2e-25 * (Tg/300)^-2.5}
    NO2 + NO3 + O3 -> N2O5 + O3        : {6e-30 * (300/Tg)^3.5}
    NO3 + NO3 -> NO2 + NO2 + O2        : {5e-12 * exp(-3000/Tg)}
    NO2- + N2O5 -> NO3- + NO3 + NO     : 7e-10
    e + O + O2 -> O- + O2              : 1e-31
    e + N3+ -> N2 + N                  : {3.22e-8 * ((0.66*Te/kb)^-0.5)}
    e + N4+ -> N2 + N2                 : {3.21e-7 * ((0.66*Te/kb)^-0.5)}
    e + N4+ -> N2 + N + N              : {3.13e-7 * ((0.66*Te/kb)^-0.41)}
    e + NO+ + M -> NO + M              : {7.18e-29 / ((0.66*Te/kb)^1.5)}
    O2a + N2A3 -> N2 + O2a             : 8.1e-13
    N2A3 + N2O -> N2O + N2             : 1.7e-10
    N + N2A3 -> N + N2                 : 2e-11
    N2A3 + N2A3 -> N2A3 + N2           : 2e-12
    N2 + N2A3 -> N2 + N2               : 3.7e-16
    O + N + O2 -> NO + O2              : {1.0e-32 * (300/Tg)^0.5}
    O + N + O3 -> NO + O3              : {2.02e-32 * (300/Tg)^0.5}
    O + N + N2 -> NO + N2              : {1.0e-32 * (300/Tg)^0.5}
    O + N2D -> N + O1D                 : 2.8e-13
    O1D + N2O -> N2 + O2               : 4.83e-11
    O1D + N2O -> NO + NO               : 8.2e-11
    O1D + N2O -> N2O + O               : 5.5e-12
    O1D + N2 + N2 -> N2O + N2          : 2.8e-36
    O1D + O2 + N2 -> N2O + O2          : 2.8e-36
    O1D + O3 + N2 -> N2O + O3          : 5e-36
    O1D + NO2 -> NO + O2               : 3e-10
    O2 + N2+ -> NO + NO+               : 1e-17
    O2 + NO + NO -> NO2 + NO2          : 1.4e-38
    O2 + NO -> NO2 + O                 : {2.8e-12 * exp(-23400/Tg)}
    O2a + N -> NO + O                  : {2e-14 * exp(-600/Tg)}
    O2a + NO -> NO2 + O                : 4.88e-18
    O2+ + N2 -> NO+ + NO               : 1e-17
    O2+ + NO2 -> NO+ + O3              : 1e-11
    O2- + N+ -> O2 + N                 : {2e-7*(300/Tg)^0.5}
    O2- + N+ -> O + O + N              : 1e-7
    O2- + N+ + M -> O2 + N + M         : {2e-25 * (Tg/300)^-25}
    O2- + N+ + M -> O + O + N + M      : {2e-25 * (Tg/300)^-25}
    O2- + N2+ -> O2 + N + N            : 1e-7
    O2- + N2+ -> O + O + N + N         : 1e-7
    O2- + N2+ -> O + O + N2            : 1e-7
    O2- + N2+ -> O2 + N2               : {2e-7*(300/Tg)^0.5}
    O2- + N2+ + M -> O2 + N2 + M       : {2e-25*(300/Tg)^2.5}
    O2- + N3+ -> O2 + N2 + N           : 1e-7
    O2- + N3+ -> O + O + N2 + N        : 1e-7
    O2- + N4+ -> O2 + N2 + N2          : 1e-7
    O2- + N4+ -> O + O + N2 + N2       : 1e-7
    
    O2- + NO2+ -> NO + O + O2          : 1e-7
    O2- + NO2+ -> O2 + N + O2          : 1e-7
    O2- + NO+ -> N + O + O2            : 1e-7
    O2- + NO+ -> N + O + O + O         : 1e-7
    O2- + NO+ -> O2 + NO               : {2e-7 * (300/Tg)^2.5}
    O- + NO+ -> O + N + O              : 1e-7
    NO + NO + O2 -> NO2 + NO2          : {3.3e-39 * exp(530/Tg)}
    NO + NO -> N2O + O                 : {7.22e-12 * exp(-33155/Tg)}
    NO + NO -> N2 + O2                 : {2.51e-11 * exp(-30653/Tg)}
    NO + NO2 + N2 -> N2O3 + N2         : {3.1e-34 *(Tg/300)^-7.7}
    NO + NO2 + O2 -> N2O3 + O2         : {3.1e-34 *(Tg/300)^-7.7}
    NO + NO2 + O3 -> N2O3 + O3         : {6.1e-34 *(Tg/300)^-7.7}
    N3+ + NO -> NO+ + N2 + N           : 1.4e-10
    N3+ + N2O -> NO+ + N2 + N2         : 5e-11
    N3+ + NO2 -> NO+ + NO + N2         : 7e-11
    N3+ + NO2 -> NO2+ + N + N2         : 7e-11
    N3+ + NO2- -> NO + O + N2 + N      : 1e-7
    N3+ + NO2- -> NO2 + N2 + N         : 1e-7
    N3+ + NO3- -> NO3 + N2 + N         : 1e-7
    N3+ + NO3- -> NO2 + O + N2 + N     : 1e-7
    N4+ + NO -> NO+ + N2 + N2          : 3.9e-16
    N4+ + NO2 -> NO2+ + N2 + N2        : 2.5e-10
    N4+ + NO2 -> NO+ + N2O + N2        : 5e-11
    N4+ + NO2- -> NO2 + N2 + N2        : 1e-7
    N4+ + NO2- -> NO + O + N2 + N2     : 1e-7
    N4+ + NO3- -> NO3 + N2 + N2        : 1e-7
    N4+ + NO3- -> NO2 + O + N2 + N2    : 1e-7
    N + NO2+ -> NO + NO+               : 8e-10
    O + O4+ -> O2+ + O3                : 3e-10 
    O1D + O3 -> O + O + O2             : 1.2e-10
    O1D + O3 -> O2 + O2                : 2.4e-10
    O1D + O2+ -> O2a + O+              : {1e-12 * (Tg/300)^-0.5}
    O+ + O2a -> O + O2+                : 2.1e-11
    O- + O2 -> O3 + e                  : 5e-15
    O- + O4+ -> O + O2 + O2            : 1e-7
    O- + O4+ + M -> O + O2 + O2 + M    : {2e-25 * (300/Tg)^2.5}
    O2 + O2a -> O3 + O                 : 3e-21
    O2 + O2a -> O2 + O2                : {3.8e-18 * exp(-200/Tg)}
    
    O2- + O4+ -> O2 + O2 + O2          : 1e-7
    O2- + O4+ + M -> O2 + O2 + O2 + M  : {2e-25 * (Tg/300)^-2.5}
    O2- + O4+ -> O + O + O2 + O2       : 1e-7
    O3 + O3 -> O2 + O2 + O2            : {7.47e-12 * exp(-9310/Tg)}
    O3- + O4+ -> O + O2 + O2 + O2      : 1e-7
    O3- + O4+ -> O3 + O2 + O2          : 1e-7
    O3- + O4+ + M -> O + O2 + O2 + O2 + M               : {2e-25 * (300/Tg)^2.5}
    O2a + O3 -> O2 + O3                : {6.8e-18 * exp(-200/Tg)}
    O + O2 + NO -> O2 + NO2            : {1e-31 * (300/Tg)^1.6}
    O + NO -> N + O2                   : {9e-13 * (Tg/300) * exp(-19500/Tg)}
    O- + N -> NO + e                   : 2.6e-10
    O- + N+ -> O + N                   : {2e-7*(300/Tg)^0.5}
    O- + N2+ -> O + N + N              : 1e-7
    O- + N2+ -> O + N2                 : {2e-7 * (300/Tg)^0.5}
    O- + N3+ -> O + N2 + N             : 1e-7
    O- + N4+ -> O + N2 + N2            : 1e-7
    
    O2a + O4+ -> O2 + O2 + O2+         : 1e-10
    O- + NO2+ -> O + NO2               : {2e-7 * (300/Tg)^0.5} 
    O- + NO2+ -> O + NO + O            : 1e-7
    O3 + N -> NO + O2                  : 5e-16
    O3 + N2+ -> O2+ + O + N2           : 1e-10
    O3 + NO+ -> NO2+ + O2              : 1e-15
    O3 + NO3 -> NO2 + O2 + O2          : 1e-17
    O3- + N2+ -> N2 + O + O2           : 1e-7
    O3- + N2+ -> N + N + O + O2        : 1e-7
    O3- + N2+ -> O3 + N + N            : 1e-7
    O3- + N2+ -> O3 + N2               : {2e-7 * (300/Tg)^0.5}
    O3- + N+ -> O2 + O + N             : 1e-7
    O3- + N+ -> O3 + N                 : {2e-7 * (Tg/300)^-0.5}
    O3- + N+ M -> O3 + N + M           : {2e-25 * (Tg/300)^-2.5}
    O3- + N3+ -> N + N2 + O3           : 1e-7
    O3- + N3+ -> N + N2 + O + O2       : 1e-7
    O3- + N4+ -> O3 + N2 + N2          : 1e-7
    O3- + NO+ -> O3 + NO               : {2e-7 * (300/Tg)^0.5}
    O3- + NO+ -> O3 + N + O            : 1e-7
    O3- + NO+ -> O + O2 + NO           : 1e-7
    O3- + NO+ -> O + O + N + O2        : 1e-7
    O3- + NO -> NO2- + O2              : 2.6e-12
    O3- + NO2 -> NO3- + O2             : 2.0e-11
    O3- + NO2+ -> O3 + NO2             : {2e-7 * (300/Tg)^0.5}
    O3- + NO2+ -> O2 + O + NO2         : 1e-7
    O3- + NO2+ -> O3 + O + NO          : 1e-7
    O3- + NO2+ -> O2 + O + O + NO      : 1e-7
    NO + N2O -> NO2 + N2               : {2.92e-13 * (Tg/300)^2.23 * exp(-23292/Tg)}

    NO + NO3- ->  NO2- + NO2           : 3e-15
    NO + NO3 -> NO + NO + O2           : {7.3e-12 * (Tg/300)^-0.23 * exp(-947/Tg)}
    NO+ + NO2- -> NO + NO2             : {2e-7 * (300/Tg)^0.5}
    NO+ + NO2- -> NO2 + N + O          : 1e-7
    NO+ + NO2- -> NO + NO + O          : 1e-7
    NO+ + NO2- -> NO + N + O + O       : 1e-7
    NO+ + NO3- -> NO + NO3             : {2e-7 * (300/Tg)^0.5}
    NO+ + NO3- -> NO2 + NO + O         : 1e-7
    NO2 + NO2 -> NO + NO + O2          : {2.71e-12 * exp(-13110/Tg)}
    NO2 + NO2 -> NO3 + NO              : {1e-12 * (Tg/300)^0.73 *  exp(-10524.3/Tg)}
    NO2 + NO2 + O3 -> N2O4 + O3        : {3e-33 * (300/Tg)^3.8}
    NO2 + NO2- -> NO3- + NO            : 4e-12
    NO2 + NO3 -> NO2 + NO + O2         : {4.5e-14 * exp(-1260/Tg)}
'
  []
[]

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
    initial_condition = 330
  []
  
  [M]
    order = FIRST
    family = SCALAR
  []
[]

[Functions]
  [reduced_field_time]
    type = ParsedFunction
    symbol_names = 'M'
    symbol_values = 'M'
    expression = '10000 * abs(sin(1000*3.1415926*t + 1000*3.1415926*0.0003))/(0.2*M*1e-17)'
  []
[]

[AuxScalarKernels]
  [neutral_sum]
    type = VariableSum
    variable = M
    args = 'N2 O2 N2A3 N N2D O2a O O1D O3 NO N2O NO2 NO3 N2O3 N2O4 N2O5'
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [field_calc]
    type = FunctionScalarAux
    variable = reduced_field
    function = reduced_field_time
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

  [temperature_calculation]
    type = ScalarLinearInterpolation
    variable = Te
    sampler = reduced_field
    property_file = 'data/electron_temperature.txt'
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
  end_time = 0.0025
  solve_type = NEWTON
  dtmin = 1e-15
  dtmax = 1e-7
  line_search = 'basic'
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_factor_shift_type -pc_factor_shift_amount -snes_linesearch_minlambda'
  petsc_options_value = 'NONZERO 1.e-10 1e-3'
  steady_state_detection = false
  l_max_its = 10
  nl_max_its = 20
  [TimeSteppers]
    [adaptive]
      type = IterationAdaptiveDT
      cutback_factor = 0.9975
      dt = 1e-13
      growth_factor = 1.05
    []
  []
[]

[Outputs]
  [out]
    type = CSV
    interval = 100
  []
  [console]
    type = Console
    execute_scalars_on = 'none'
  []
[]
