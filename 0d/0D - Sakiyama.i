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
    initial_condition = 1e9
    # scaling = 1e-2
  []

  [N2]
    family = SCALAR
    order = FIRST
    initial_condition = 1.953e19
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
    initial_condition = 5e8
    # scaling = 5e8
  []

  [O2+]
    family = SCALAR
    order = FIRST
    initial_condition = 5e8
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

  [N2B3]
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

  [O3+]
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

  [dN2B3_dt]
    type = ODETimeDerivative
    variable = N2B3
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

  [dO3+_dt]
    type = ODETimeDerivative
    variable = O3+
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
    species = 'N+ N2+ N3+ N4+ O+ O2+ O4+ NO+ N2O+ NO2+ e O- O2- O3- O4- NO- N2O- NO2- NO3- N2D N2A3 N2B3 O1D N O O2a1 O3 NO N2O NO2 NO3 N2O3 N2O4 N2O5 N2 O2'
    num_particles = '1 2 3 4 1 2 4 2 3 3 0 1 2 3 4 2 3 3 4 1 2 2 1 1 1 2 3 2 3 3 4 5 6 7 2 2'
    file_location = 'data'
    aux_species = 'M'

    # These are parameters required equation-based rate coefficients
    equation_constants = 'Tg pi kb'
    equation_values = '330 3.141 8.6173e-5'
    equation_variables = 'Te'
    sampling_variable = 'reduced_field'
    electron_density = 'e'
    include_electrons = true
    track_rates = true
    balance_check = true

    reactions = '
                 e + N2  -> N2D + N + e             : {3.99e-17*(Te^(2.24))*exp(-9.1/Te)}
                 e + N2  -> N2A3 + e                : {3.34e-16*(Te^(-0.06))*exp(-8.5/Te)}
                 e + N2  -> N2B3 + e                : {8.44e-15*(Te^(-0.33))*exp(-9.15/Te)}
                 e + N2  -> N2+ + e + e             : {1e-16*(Te^(1.9))*exp(-14.6/Te)}
                 e + N   -> N2D + e                 : {5.06e-15*exp(-10.8/(Te^(3.95)))}
                 e + N   -> N+ + e + e              : {1.45e-17*(Te^2.78)*exp(-8.54/Te)}
                 e + O2  -> O + O + e               : {2.03e-14*(Te^(-0.1))*exp(-8.47/Te)}
                 e + O2  -> O1D + O + e             : {1.82e-14*(Te^(-0.13))*exp(-10.7/Te)}
                 e + O2  -> O2a1 + e                : {1.04e-15*exp(-2.59/Te)}
                 e + O2  -> O2+ + e + e             : {9.54e-12*(Te^(-1.05))*exp(-55.6/Te)}
                 e + O3  -> O + O2 + e              : {1.78e-12*(Te^(-0.614))*exp(-11.5/Te)}
                 e + O   -> O1D + e                 : {7.46e-15*exp(-5.56/(Te^1.47))}
                 e + O   -> O+ + e + e              : {4.75e-15*(Te^0.61)*exp(-22.1/Te)}
                 e + N2O5 -> NO2+ + NO3 + e + e     : {2.43e-17*(Te^2.77)*exp(-14.9/Te)}
                 e + N+ + M -> N + M                : {3.12e-35/((0.66*Te/kb)^1.5)}
                 e + N2+ -> N + N                   : {1.66e-12/((0.66*Te/kb)^0.7)}
                 e + N2+ -> N2D + N                 : {1.5e-12/((0.66*Te/kb)^0.7)}
                 e + N2+ + M -> N2 + M              : {3.12e-35/((0.66*Te/kb)^1.5)}
                 e + N3+ -> N2 + N                  : {3.46e-12/((0.66*Te/kb)^0.5)}
                 e + N4+ -> N2 + N2                 : {4.73e-11/((0.66*Te/kb)^0.53)}
                 e + O+ + M -> O + M               : {3.12e-35/((0.66*Te/kb)^1.5)}
                 e + O2+ -> O + O                   : {1.68e-11/((0.66*Te/kb)^0.7)}
                 e + O2+ -> O + O1D                 : {1.24e-11/((0.66*Te/kb)^0.7)}
                 e + O2+ + M -> O2 + M              : {3.12e-35/((0.66*Te/kb)^1.5)}
                 e + O4+ -> O2 + O2                 : {2.42e-11/((0.66*Te/kb)^0.5)}
                 e + N2O+ -> N2 + O                 : {3.46e-12/((0.66*Te/kb)^0.5)}
                 e + NO+ -> N + O                   : {1.07e-11/((0.66*Te/kb)^0.85)}
                 e + NO+ -> N2D + O                 : {4.28e-11/((0.66*Te/kb)^0.85)}
                 e + NO+ + M -> NO + M              : {3.12e-35/((0.66*Te/kb)^1.5)}
                 e + NO2+ -> NO + O                 : {3.46e-12/((0.66*Te/kb)^0.5)}
                 e + e + N+ -> N + e                : {1e-31*(Tg/(0.66*Te/kb))^4.5}
                 e + e + N2+ -> N2 + e              : {1e-31*(Tg/(0.66*Te/kb))^4.5}
                 e + e + O+ -> O + e                : {1e-31*(Tg/(0.66*Te/kb))^4.5}
                 e + e + O2+ -> O2 + e              : {1e-31*(Tg/(0.66*Te/kb))^4.5}
                 e + e + NO+ -> NO + e              : {1e-31*(Tg/(0.66*Te/kb))^4.5}
                 e + O + O2 -> O- + O2              : 1e-43
                 e + O + O2 -> O2- + O              : 1e-43
                 e + O2 + O2 -> O2- + O2            : {1.4e-41*(Tg/(0.66*Te/kb))*exp(-600/Tg)*exp(700*((0.66*Te/kb)-Tg)/((0.66*Te/kb)*Tg))}
                 e + O2 + N2 -> O2- + N2            : {1.1e-43*(Tg/(0.66*Te/kb))^2*exp(-70/Tg)*exp(1500*((0.66*Te/kb)-Tg)/((0.66*Te/kb)*Tg))}
                 e + O2 -> O- + O                   : {2.63e-16*(Te^(-0.495))*exp(-5.65/Te)}
                 e + O2 -> O2-                      : {9.72e-15*(Te^(-1.62))*exp(-14.2/Te)}
                 e + O3 -> O- + O2                  : 1e-17
                 e + O3 -> O2- + O                  : 1e-15
                 e + O3 + M -> O3- + M              : 1e-43
                 e + N2O -> O- + N2                 : 2e-16
                 e + NO + M -> NO- + M              : 8e-43
                 e + NO2 -> O- + NO                 : 1e-17
                 e + NO2 + M -> NO2- + M            : 1.5e-42
                 e + NO3 + M -> NO3- + M            : 1e-42
                 O- + N -> NO + e                   : 2.6e-16
                 O- + N2 -> N2O + e                 : 1e-18
                 O- + N2A3 -> N2 + O + e            : 2.2e-15
                 O- + N2B3 -> N2 + O + e            : 1.9e-15
                 O- + O -> O2 + e                   : 1.4e-16
                 O- + O2 -> O3 + e                  : 1e-18
                 O- + O2a1 -> O3 + e                : 3e-16
                 O- + O3 -> O2 + O2 + e             : 3e-16
                 O- + NO -> NO2 + e                 : 2.6e-16
                 O2- + N -> NO2 + e                 : 5e-16
                 O2- + N2 -> N2 + O2 + e            : {1.9e-18*(Tg/300)^0.5*exp(-4990/Tg)}
                 O2- + N2A3 -> N2 + O2 + e          : 2.1e-15
                 O2- + N2B3 -> N2 + O2 + e          : 2.5e-15
                 O2- + O -> O3 + e                  : 1.5e-16
                 O2- + O2 -> O2 + O2 + e            : {2.7e-16*(Tg/300)^0.5*exp(-5590/Tg)}
                 O2- + O3 -> O3 + O2 + e            : 6e-16
                 O2- + O2a1 -> O2 + O2 + e          : 2e-16
                 O3- + O -> O2 + O2 + e             : 3e-16
                 O3- + O2 -> O3 + O2 + e            : 2.3e-16
                 O3- + O3 -> O2 + O2 + O2 + e       : 3e-16
                 NO- + M -> NO + M + e              : 2.40e-19
                 NO- + NO -> NO + NO + e            : 5e-18
                 NO- + N2O -> NO + N2O + e          : 5.1e-18
                 NO2- + O -> NO3 + e                : 1e-18
                 NO2- + N -> N2 + O2 + e            : 1e-18
                 NO3- + O -> NO2 + O2 + e           : 1e-18
                 NO3- + N -> N2 + O3 + e            : 1e-18
                 N+ + N + M -> N2+ + M              : 1e-41
                 N+ + N2 + M -> N3+ + M             : 4.6e-41
                 N+ + N2O -> NO+ + N2               : 5.5e-16
                 N+ + NO -> NO+ + N                 : 4.72e-16
                 N+ + NO -> N2+ + O                 : 8.33e-17
                 N+ + NO -> O+ + N2                 : 1e-18
                 N+ + NO2 -> NO2+ + N               : 3e-16
                 N+ + NO2 -> NO+ + NO               : 5e-16
                 N+ + O -> O+ + N                   : 1e-18
                 N+ + O + M -> NO+ + M              : 1e-41
                 N+ + O2 -> NO+ + O                 : 2.7e-16
                 N+ + O2 -> O+ + NO                 : 2.8e-17
                 N+ + O2 -> O2+ + N                 : 3e-16
                 N+ + O3 -> NO+ + O2                : 5e-16
                 N2+ + N -> N+ + N2                 : 1e-18
                 N2+ + N + M -> N3+ + M             : {1e-41*(300/Tg)}
                 N2+ + N2 + M -> N4+ + M            : {1e-41*(300/Tg)}
                 N2+ + N2A3 -> N3+ + N              : 3e-16
                 N2+ + N2O -> N2O+ + N2             : 6e-16
                 N2+ + N2O -> NO+ + N + N2          : 4e-16
                 N2+ + NO -> NO+ + N2               : 3.9e-16
                 N2+ + NO2 -> NO+ + N2O             : 5e-17
                 N2+ + NO2 -> NO2+ + N2             : 3e-16
                 N2+ + O -> NO+ + N                 : 1.4e-16
                 N2+ + O -> NO+ + N2D               : {1.8e-16*(300/Tg)}
                 N2+ + O -> O+ + N2                 : {1e-17*(300/Tg)^0.5}
                 N2+ + O2 -> O2+ + N2               : 5e-17
                 N2+ + O3 -> O2+ + O + N2           : 1e-16
                 N3+ + N ->  N2+ + N2               : 6.6e-17
                 N3+ + O2 -> O2+ + N + N2           : 2.3e-17
                 N3+ + O2 -> NO+ + O + N2           : 2e-17
                 N3+ + O2 -> NO2+ + N2              : 4.4e-17
                 N3+ + NO -> NO+ + N2 + N           : 7e-17
                 N3+ + NO -> N2O+ + N2              : 7e-17
                 N3+ + N2O -> NO+ + N2 + N2         : 5e-17
                 N3+ + NO2 -> NO+ + NO + N2         : 7e-17
                 N3+ + NO2 -> NO2+ + N + N2         : 7e-17
                 N4+ + N2 -> N2+ + N2 + N2          : {2.1e-16*exp(Tg/121)}
                 N4+ + N2O -> N2O+ + N2 + N2        : 3e-16
                 N4+ + N -> N+ + N2 + N2            : 1e-17
                 N4+ + NO -> NO+ + N2 + N2          : 3.9e16
                 N4+ + NO2 -> NO2+ + N2 + N2        : 2.5e-16
                 N4+ + NO2 -> NO+ + N2O + N2        : 5e-17
                 N4+ + O -> O+ + N2 + N2            : 2.5e-16
                 N4+ + O2 -> O2+ + N2 + N2          : 2.4e-16
                 O+ + N + M -> NO+ + M              : 1e-41 
                 O+ + N2 + M -> NO+ + N + M         : {6e-41*(300/Tg)^2}
                 O+ + O + M -> O2+ + M              : 1e-41
                 O+ + O2 -> O2+ + O                 : {2.1e-17*(300/Tg)^0.5}
                 O+ + O3 -> O2+ + O2                : 1e-16
                 O+ + N2D -> N+ + O                 : 1.3e-16
                 O+ + NO -> NO+ + O                 : 1e-18
                 O+ + NO -> O2+ + N                 : 3e-18
                 O+ + N2O -> N2O+ + O               : 6.3e-16
                 O+ + N2O -> NO+ + NO               : 2.3e-16
                 O+ + N2O -> O2+ + N2               : 2e-17
                 O+ + NO2 -> NO+ + O2               : 5e-16
                 O+ + NO2 -> NO2+ + O               : 1.6e-15
                 O2+ + O2 + M -> O4+ + M            : {5.5e-43*(300/Tg)^2.7} 
                 O2+ + N -> NO+ + O                 : 1.5e-16
                 O2+ + N2 -> NO+ + NO               : 1e-23
                 O2+ + N2O5 -> NO2+ + NO3 + O2      : 8.8e-16
                 O2+ + NO -> NO+ + O2               : 4.6e-16
                 O2+ + NO2 -> NO2+ + O2             : 6.6e-16
                 O2+ + NO2 -> NO+ + O3              : 1e-17
                 O4+ + O -> O2+ + O3                : 3e-16 
                 O4+ + O2 -> O2+ + O2 + O2          : {3.3e-12*(300/Tg)^4*exp(-5030/Tg)}
                 O4+ + NO -> NO+ + O2 + O2          : 6.8e-16
                 O4+ + NO2 -> NO2+ + O2 + O2        : 3e-16
                 O- + O2 + M -> O3- + M             : {1.1e-42*(300/Tg)} 
                 O- + O2a1 -> O2- + O               : 1e-16
                 O- + O3 -> O3- + O                 : 8e-16
                 O- + N2O -> NO- + NO               : 2e-16
                 O- + N2O -> N2O- + O               : 2e-18
                 O- + NO + M -> NO2- + M            : 1e-41
                 O- + NO2 -> NO2- + O               : 1.2e-15
                 O- + NO3 -> NO3- + O               : 3e-16
                 O2- + O -> O- + O2                 : 3.3e-16
                 O2- + O2 + M -> O4- + M            : {3.5e-43*(300/Tg)}
                 O2- + O3 -> O3- + O2               : 3.5e-16
                 O2- + N2O -> O3- + N2              : 1e-17
                 O2- + NO2 -> NO2- + O2             : 7e-16
                 O2- + NO3 -> NO3- + O2             : 5e-16
                 O3- + O -> O2- + O2                : 1e-17
                 O3- + NO -> NO2- + O2              : 1e-17
                 O3- + NO -> NO3- + O               : 1e-17
                 O3- + NO2 -> NO3- + O2             : 2e-17
                 O3- + NO2 -> NO2- + O3             : 7e-17
                 O3- + NO3 -> NO3- + O3             : 5e-16
                 O4- + NO -> NO3- + O2              : 2.5e-16
                 O4- + O -> O- + O2 + O2            : 3e-16
                 O4- + O -> O3- + O2                : 4e-16
                 O4- + N2 -> O2- + O2 + N2          : {1e-16*exp(-1044/Tg)}
                 N2O+ + NO -> NO+ + N2O             : 2.3e-16
                 N2O+ + N2O -> NO+ + NO + N2        : 1.2e-17
                 N2O+ + NO2 -> NO+ + N2 + O2        : 4.29e-16
                 N2O+ + NO2 -> NO2+ + N2O           : 2.21e-16
                 N2O+ + O2 -> NO+ + NO2             : 4.59e-17
                 N2O+ + O2 -> O2+ + N2O             : 2.24e-16
                 NO+ + N2O5 -> NO2+ + NO2 + NO2     : 5.9e-16
                 NO+ + O3 -> NO2+ + O2              : 1e-21
                 NO+ + N + M -> N2O+ + M            : {1e-41*(300/Tg)}
                 NO- + N2O -> NO2- + N2             : 2.8e-20
                 NO- + NO2 -> NO2- + NO             : 3e-16
                 NO- + NO3 -> NO3- + NO             : 3e-16
                 NO- + O2 -> O2- + NO               : 5e-16
                 NO- + O3 -> O3- + NO               : 3e-16
                 NO- + O -> O- + NO                 : 3e-16
                 NO2+ NO -> NO+ + NO2               : 2.75e-16
                 NO2- + N2O5 -> NO3- + NO3 + NO     : 7e-16
                 NO2- + NO -> NO- + NO2             : 2.75e-16
                 NO2- + NO2 -> NO3- + NO            : 4e-18
                 NO2- + NO3 -> NO3- + NO2           : 5e-16
                 NO2- + O3 -> NO3- + O2             : 1.8e-17
                 NO2- + N2O -> NO3- + N2            : 5e-19
                 NO3- + NO ->  NO2- + NO2           : 3e-21
                 O+ + O- -> O + O                   : {2e-13*(300/Tg)^0.5}
                 O+ + O2- -> O2 + O                 : {2e-13*(300/Tg)^0.5}
                 O+ + O3- -> O3 + O                 : {2e-13*(300/Tg)^0.5}
                 O+ + O4- -> O2 + O2 + O            : 1e-13
                 O+ + N2O- -> N2O + O               : {2e-13*(300/Tg)^0.5}
                 O+ + NO- -> NO + O                 : {2e-13*(300/Tg)^0.5}
                 O+ + NO2- -> NO2 + O               : {2e-13*(300/Tg)^0.5}
                 O+ + NO3- -> NO3 + O               : {2e-13*(300/Tg)^0.5}
                 O2+ + O- -> O + O + O              : 1e-13
                 O2+ + O- -> O + O2                 : {2e-13*(300/Tg)^0.5}
                 O2+ + O2- -> O2 + O2               : {2e-13*(300/Tg)^0.5}
                 O2+ + O2- -> O2 + O + O            : 1e-13
                 O2+ + O3- -> O3 + O2               : {2e-13*(300/Tg)^0.5} 
                 O2+ + O3- -> O3 + O + O            : 1e-13
                 O2+ + O4- -> O2 + O2 + O2          : 1e-13
                 O2+ + N2O- -> N2O + O2             : {2e-13*(300/Tg)^0.5}
                 O2+ + N2O- -> N2O + O + O          : 1e-13
                 O2+ + NO- -> NO + O2               : {2e-13*(300/Tg)^0.5}
                 O2+ + NO- -> NO + O + O            : 1e-13
                 O2+ + NO2- -> NO2 + O2             : {2e-13*(300/Tg)^0.5}
                 O2+ + NO2- -> NO2 + O + O          : 1e-13
                 O2+ + NO3- -> NO3 + O2             : {2e-13*(300/Tg)^0.5}
                 O2+ + NO3- -> NO3 + O + O          : 1e-13
                 O4+ + O- -> O + O2 + O2            : 1e-13
                 O4+ + O2- -> O2 + O2 + O2          : 1e-13
                 O4+ + O3- -> O3 + O2 + O2          : 1e-13
                 O4+ + O4- -> O2 + O2 + O2 + O2     : 1e-13
                 O4+ + N2O- -> N2O + O2 + O2        : 1e-13
                 O4+ + NO- -> NO + O2 + O2          : 1e-13
                 O4+ + NO2- -> NO2 + O2 + O2        : 1e-13
                 O4+ + NO3- -> NO3 + O2 + O2        : 1e-13
                 N+ + N2O- -> N2O + N               : {2e-13*(300/Tg)^0.5}
                 N+ + NO- -> NO + N                 : {2e-13*(300/Tg)^0.5}
                 N+ + NO2- -> NO2 + N               : {2e-13*(300/Tg)^0.5}
                 N+ + NO3- -> NO3 + N               : {2e-13*(300/Tg)^0.5}
                 N+ + O- -> O + N                   : {2e-13*(300/Tg)^0.5}
                 N+ + O2- -> O2 + N                 : {2e-13*(300/Tg)^0.5}
                 N+ + O3- -> O3 + N                 : {2e-13*(300/Tg)^0.5}
                 N+ + O4- -> O2 + O2 + N            : 1e-13
                 N2+ + N2O- -> N2O + N2             : {2e-13*(300/Tg)^0.5}
                 N2+ + N2O- -> N2O + N + N          : 1e-13
                 N2+ + NO- -> NO + N2               : {2e-13*(300/Tg)^0.5}
                 N2+ + NO- -> NO + N + N            : 1e-13
                 N2+ + NO2- -> NO2 + N2             : {2e-13*(300/Tg)^0.5}
                 N2+ + NO2- -> NO2 + N + N          : 1e-13
                 N2+ + NO3- -> NO3 + N2             : {2e-13*(300/Tg)^0.5}
                 N2+ + NO3- -> NO3 + N + N          : 1e-13
                 N2+ + O- -> O + N + N              : 1e-13
                 N2+ + O- -> O + N2                 : {2e-13*(300/Tg)^0.5}
                 N2+ + O2- -> O2 + N + N            : 1e-13
                 N2+ + O2- -> O2 + N2               : {2e-13*(300/Tg)^0.5}
                 N2+ + O3- -> O3 + N + N            : 1e-13
                 N2+ + O3- -> O3 + N2               : {2e-13*(300/Tg)^0.5}
                 N2+ + O4- -> O2 + O2 + N2          : 1e-13
                 N2O+ + N2O- -> N2O + N2O           : {2e-13*(300/Tg)^0.5}
                 N2O+ + N2O- -> N2O + N2 + O        : 1e-13
                 N2O+ + NO- -> NO + N2O             : {2e-13*(300/Tg)^0.5}
                 N2O+ + NO- -> NO + N2 + O          : 1e-13
                 N2O+ + NO2- -> NO2 + N2O           : {2e-13*(300/Tg)^0.5}
                 N2O+ + NO2- -> NO2 + N2 + O        : 1e-13
                 N2O+ + NO3- -> NO3 + N2O           : {2e-13*(300/Tg)^0.5}
                 N2O+ + NO3- -> NO3 + N2 + O        : 1e-13
                 N2O+ + O- -> O + N2O               : {2e-13*(300/Tg)^0.5}
                 N2O+ + O- -> O + N2 + O            : 1e-13
                 N2O+ + O2- -> O2 + N2O             : {2e-13*(300/Tg)^0.5}
                 N2O+ + O2- -> O2 + N2 + O          : 1e-13
                 N2O+ + O3- -> O3 + N2O             : {2e-13*(300/Tg)^0.5}
                 N2O+ + O3- -> O3 + N2 + O          : 1e-13
                 N2O+ + O4- -> O2 + O2 + N2O        : 1e-13
                 N3+ + N2O- -> N2O + N2 + N         : 1e-13
                 N3+ + NO- -> NO + N2 + N           : 1e-13
                 N3+ + NO2- -> NO2 + N2 + N         : 1e-13
                 N3+ + NO3- -> NO3 + N2 + N         : 1e-13
                 N3+ + O- -> O + N2 + N             : 1e-13
                 N3+ + O2- -> O2 + N2 + N           : 1e-13
                 N3+ + O3- -> O3 + N2 + N           : 1e-13
                 N3+ + O4- -> O2 + O2 + N + N2      : 1e-13
                 N3+ + N2O- -> N2O + N2 + N         : 1e-13
                 N3+ + NO- -> NO + N2 + N           : 1e-13
                 N3+ + NO2- -> NO2 + N2 + N         : 1e-13
                 N3+ + NO3- -> NO3 + N2 + N         : 1e-13
                 N3+ + O- -> O + N2 + N             : 1e-13
                 N3+ + O2- -> O2 + N2 + N           : 1e-13
                 N3+ + O3- -> O3 + N2 + N           : 1e-13
                 N3+ + O4- -> O2 + O2 + N + N2      : 1e-13
                 NO+ + N2O- -> N2O + NO             : {2e-13*(300/Tg)^0.5}
                 NO+ + N2O- -> N2O + N + O          : 1e-13
                 NO+ + NO- -> NO + NO               : {2e-13*(300/Tg)^0.5}
                 NO+ + NO- -> NO + N + O            : 1e-13
                 NO+ + NO2- -> NO2 + NO             : {2e-13*(300/Tg)^0.5}
                 NO+ + NO2- -> NO2 + N + O          : 1e-13
                 NO+ + NO3- -> NO3 + NO             : {2e-13*(300/Tg)^0.5}
                 NO+ + NO3- -> NO3 + N + O          : 1e-13
                 NO+ + O- -> O + N + O              : 1e-13
                 NO+ + O- -> O + NO                 : {2e-13*(300/Tg)^0.5}
                 NO+ + O2- -> O2 + N + O            : 1e-13
                 NO+ + O2- -> O2 + NO               : {2e-13*(300/Tg)^0.5}
                 NO+ + O3- -> O3 + N + O            : 1e-13
                 NO+ + O3- -> O3 + NO               : {2e-13*(300/Tg)^0.5}
                 NO+ + O4- -> O2 + O2 + NO          : 1e-13
                 NO2+ + N2O- -> N2O + NO2           : {2e-13*(300/Tg)^0.5}
                 NO2+ + N2O- -> N2O + N + O2        : 1e-13
                 NO2+ + NO- -> NO + NO2             : {2e-13*(300/Tg)^0.5}
                 NO2+ + NO- -> NO + N + O2          : 1e-13
                 NO2+ + NO2- -> NO2 + NO2           : {2e-13*(300/Tg)^0.5}
                 NO2+ + NO2- -> NO2 + N + O2        : 1e-13
                 NO2+ + NO3- -> NO3 + NO2           : {2e-13*(300/Tg)^0.5}
                 NO2+ + NO3- -> NO3 + N + O2        : 1e-13
                 NO2+ + O- -> O + NO2               : {2e-13*(300/Tg)^0.5}
                 NO2+ + O- -> O + N + O2            : 1e-13
                 NO2+ + O2- -> O2 + NO2             : {2e-13*(300/Tg)^0.5}
                 NO2+ + O2- -> O2 + N + O2          : 1e-13
                 NO2+ + O3- -> O3 + NO2             : {2e-13*(300/Tg)^0.5}
                 NO2+ + O3- -> O3 + N + O2          : 1e-13
                 NO2+ + O4- -> O2 + O2 + NO2        : 1e-13
                 N + N + M -> N2 + M                : {8.3e-46*exp(500/Tg)}
                 N + NO -> N2 + O                   : {2.1e-17*exp(100/Tg)}
                 N + NO2 -> N2O + O                 : {5.8e-18*exp(220/Tg)}
                 N + NO2 -> N2 + O + O              : 9.1e-19
                 N + NO2 -> NO + NO                 : 6e-19
                 N + NO2 -> N2 + O2                 : 7e-19
                 N + O + M -> NO + M                : {6.3e-45*exp(140/Tg)}
                 N + O2 -> NO + O                   : {1.5e-17*exp(-3600/Tg)}
                 N + O3 -> NO + O2                  : 5e-22
                 N2D + N2 -> N + N2                 : {5e-18*exp(-1620/Tg)}
                 N2D + N2O -> N2 + NO               : {1.5e-17*exp(-570/Tg)}
                 N2D + NO -> N2O                    : 6e-17
                 N2D + NO -> O + N2                 : 4.5e-17
                 N2D + O -> N + O                   : 7e-19
                 N2D + O2 -> NO + O                 : {1.5e-18*(Tg/300)^0.5}
                 N2D + O2 -> NO + O1D               : {6e-18*(Tg/300)^0.5}
                 N2A3 + N2 -> N2 + N2               : 2.2e-20
                 N2A3 + N2A3 -> N2B3 + N2           : 4e-16
                 N2A3 + N2O -> O + N2 + N2          : 8e-17
                 N2A3 + N2O -> NO + N + N2          : 8e-17
                 N2A3 + NO2 -> N2 + NO + O          : 1.3e-17
                 N2A3 + O2 -> N2 + O + O            : {5e-18*exp(-210/Tg)}
                 N2A3 + O2 -> O2a1 + N2             : 1e-18
                 N2A3 + N -> N + N2                 : 5e-17
                 N2A3 + O -> NO + N2D               : 7e-18
                 N2A3 + O -> O1D + N2               : 2.3e-17
                 N2B3 + N2 -> N2A3 + N2             : 5e-17
                 N2B3 -> N2A3                       : 1.25e5
                 N2B3 + NO -> N2A3 + NO             : 2.4e-16
                 N2B3 + O2 -> N2 + O + O            : 3e-16
                 O + O + M -> O2 + M                : {3.2e-47*exp(900/Tg)}
                 O + O2 + M -> O3 + M               : {3.4e-46*(300/Tg)^1.2}
                 O + O3 -> O2 + O2                  : {8e-18*exp(-2060/Tg)}
                 O + NO + M -> NO2 + M              : {1e-43*(300/Tg)^1.6}
                 O + NO2 -> NO + O2                 : {6.5e-18*exp(120/Tg)}
                 O + NO2 + M -> NO3 + M             : {9e-44*(300/Tg)^2}
                 O + NO3 -> O2 + NO2                : 1.7e-17
                 O1D + O2 -> O + O2                 : {6.4e-18*exp(67/Tg)}
                 O1D + O -> O + O                   : 8e-18
                 O1D + O2a1 -> O + O2               : 1e-17
                 O1D + O2 -> O + O2a1               : 1e-18
                 O1D + O3 -> O + O + O2             : 1.2e-16
                 O1D + O3 -> O2 + O2                : 1.2e-16
                 O1D + N2 -> O + N2                 : {1.8e-17*exp(107/Tg)}
                 O1D + N2 + M -> N2O + M            : 9e-49
                 O1D + N2O -> N2 + O2               : 4.4e-17
                 O1D + N2O -> NO + NO               : 7.2e-17
                 O1D + NO -> O + NO                 : 4e-17
                 O1D + NO2 -> NO + O2               : 1.4e-16
                 O2a1 + O2 -> O2 + O2               : {3.8e-24*exp(-205/Tg)}
                 O2a1 + O3 -> O + O2 + O2           : {5.2e-17*exp(-2840/Tg)}
                 O2a1 + M -> O2 + M                 : 8e-27
                 O2a1 + NO -> O2 + NO               : 2.5e-17
                 O2a1 + N2 -> O2 + N2               : 1.5e-24
                 O3 + NO -> NO2 + O2                : {1.8e-18*exp(-1370/Tg)}
                 O3 + NO2 -> NO3 + O2               : {1.4e-19*exp(-2470/Tg)}
                 O3 + M -> O + O2 + M               : {3.92e-16*exp(-11400/Tg)}
                 NO + NO2 + M -> N2O3 + M           : {3.09e-46*(300/Tg)^7.7}
                 NO + NO3 -> NO2 + NO2              : {1.8e-17*exp(110/Tg)}
                 NO2 + NO2 + M -> N2O4 + M          : {1.17e-45*(300/Tg)^3.8}
                 NO2 + NO3 + M -> N2O5 + M          : {2.8e-42*(300/Tg)^3.5}
                 NO2 + NO3 -> NO2 + NO + O2         : {2.3e-19*exp(-1600/Tg)}
                 NO3 + NO3 -> NO2 + NO2 + O2        : {5e-18*exp(-3000/Tg)}
                 N2O3 + M -> NO + NO2 + M           : {1.03e-16*exp(-2628/Tg)}
                 N2O4 + M -> NO2 + NO2 + M          : {1.09e-13*exp(-4952/Tg)}
                 N2O5 + M -> NO2 + NO3 + M          : {1e-9*(300/Tg)^3.5*exp(-11000/Tg)}
'
  []
[]

    #O2 + O2a -> O3 + O                                  : 3e-15
    #O2+ + NO2 -> NO+ + O3                               : 1e-11
    #O2- + N2O -> N2 + O3-                               : 9e-13
    #O + NO3- -> NO + O3 + e                             : 1.5e-10

    ##SMOL

    #O + NO -> N + O + O                                 : {8.7e-9 * exp(-75994/Tg) * 20}
    #N2 + N2 -> N + N + N2                               : {5.4e-8 * (1.0 - exp(-3354/Tg)) * exp(-113200/Tg)}
    #N2 + NO -> N + N + NO                               : {5.4e-8 * (1.0 - exp(-3354/Tg)) * exp(-113200/Tg)}
    #N2 + NO -> N + O + N2                               : {8.7e-9 * exp(-75994/Tg)}
    #N + N2 -> N + N + N                                 : {5.4e-8 * (1.0 - exp(-3354/Tg)) * exp(-113200/Tg) * 6.6}
    #N + N -> N2+ + e                                    : {2.7e-11 * exp(-6.74e4/Tg)}
    #NO + NO2 -> N2 + O2 + NO                            : {6.8e-6 * (300/Tg)^2 * exp(-36180/Tg) * 7.8}

[AuxVariables]
  [reduced_field]
    order = FIRST
    family = SCALAR
    initial_condition = 200
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
    type = ScalarSplineInterpolation
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
    type = VariableSum
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
  end_time = 0.003
  solve_type = linear
  dtmin = 1e-12
  dtmax = 5e-7
  line_search = none
  steady_state_detection = false
  [TimeSteppers]
    [adaptive]
      type = IterationAdaptiveDT
      cutback_factor = 0.9
      dt = 1e-12
      growth_factor = 1.01
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
