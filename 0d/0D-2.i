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

  [N2a1]
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

  [O2b]
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
    
  [NO-]
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

  [dN2a1_dt]
    type = ODETimeDerivative
    variable = N2a1
  []

  [dN2A3_dt]
    type = ODETimeDerivative
    variable = N2A3
  []

  [dO2a_dt]
    type = ODETimeDerivative
    variable = O2a
  []

  [dO2b_dt]
    type = ODETimeDerivative
    variable = O2b
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

  [dNO-_dt]
    type = ODETimeDerivative
    variable = NO-
  []

  [dN2O_dt]
    type = ODETimeDerivative
    variable = N2O
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
    species = 'e N2 O2 N2+ O2+ O2- N2D N2a1 N2A3 O2a O2b N O O1D N+ O- O+ NO NO+ NO- N2O NO2 NO2- NO2+ NO3 NO3- O3 O3+ O3- N4+ O4+ N2O5 N2O3 N2O4 N3+'
    num_particles = '0 2 2 2 2 2 1 2 2 2 2 1 1 1 1 1 1 2 2 2 3 3 3 3 4 4 3 3 3 4 4 7 5 6 3'
    file_location = 'data'
    aux_species = 'M'

    equation_constants = 'Tg pi kb'
    equation_values = '330 3.141 8.6173e-5'
    equation_variables = 'Te'
    sampling_variable = 'reduced_field'
    track_rates = 'true'
    balance_check = 'true'
    electron_density = 'e'

    reactions = '
    e + N2 -> N2+ + e + e                               : {1e-10 * Te^1.90 * exp(-14.6/Te)}
    e + O2 -> O2+ + e + e                               : {9.54e-6 * Te^-1.05 * exp(-55.6/Te)}
    e + N -> N+ + e + e                                 : {1.45e-11 * Te^2.58 * exp(-8.54/Te)}
    e + O -> O+ + e + e                                 : {4.75e-9 * Te^0.61 * exp(-22.1/Te)}
    e + N2O5 -> NO2+ + NO3 + e + e                      : {2.43e-11 * Te^2.77 * exp(-5.62/Te)}

    e + N2 -> N2A3 + e                                  : {3.34e-10 * Te^-0.06 * exp(-8.50/Te)}

    e + O2 -> e + O + O                                 : {2.03e-8 * Te^(-0.1) * exp(-8.47/Te)}
    e + O3 -> O + O2 + e                                : {1.78e-6 * Te^-0.614 * exp(-11.5/Te)}

    e + N2+ -> N + N                                    : {1.66e-6 * (0.66*Te/kb)^-0.7}
    e + O2+ -> O + O                                    : {1.68e-5 * (0.66*Te/kb)^-0.7}
    e + e + N+ -> N + e                                 : {1e-19 * (Tg/(0.66*Te/kb))^4.5} 
    e + e + O+ -> O + e                                 : {1e-19 * (Tg/(0.66*Te/kb))^4.5}
    e + e + N2+ -> N2 + e                               : {1e-19 * (Tg/(0.66*Te/kb))^4.5} 
    e + e + O2+ -> O2 + e                               : {1e-19 * (Tg/(0.66*Te/kb))^4.5}
    e + e + NO+ -> O2 + e                               : {1e-19 * (Tg/(0.66*Te/kb))^4.5}
    e + O+ + M -> O + M                                 : {3.12e-23 * (0.66*Te/kb)^-1.5}
    e + O2+ + M -> O2 + M                               : {3.12e-23 * (0.66*Te/kb)^-1.5}
    e + N+ + M -> N + M                                 : {3.12e-23 * (0.66*Te/kb)^-1.5}
    e + N2+ + M -> N2 + M                               : {3.12e-23 * (0.66*Te/kb)^-1.5}

    e + O3 -> O2- + O                                   : 1e-9
    e + O3 + M -> O3- + M                               : 1e-31
    e + N2O -> O- + N2                                  : 2e-10
    e + NO + M -> NO- + M                               : 8e-31
    e + NO2 -> O- + NO                                  : 1e-11
    e + NO2 + M -> NO2- + M                             : 1.5e-30
    e + NO3 + M -> NO3- + M                             : 1e-30

    N + NO -> O + N2                                    : {2.1e-11 * exp(100/Tg)}
    N + NO2 -> N2O + O                                  : {1.66e-12 * exp(220/Tg)}
    N + NO2 -> O + O + N2                               : 9.1e-13
    N + NO2 -> NO + NO                                  : {1.33e-12 * exp(220/Tg)}
    N + NO2 -> N2 + O2                                  : {4.0e-13 * exp(220/Tg)}
    N + O2 -> NO + O                                    : {1.5e-11 * exp(-3600/Tg)}
    N + O3 -> O2 + NO                                   : 5e-16
    O + O + N -> NO + O                                 : {1.8e-29 * (300/Tg)}
    O + O + NO -> O2 + NO                               : {4.0e-30 * (300/Tg)^0.41 * 0.17}
    O + O2 + NO -> NO2 + O2                             : {1e-31 * (300/Tg)^1.6}
    O + O + M -> O2 + M                                 : {3.2e-35 * exp(900/Tg)}
    O + O2 + M -> O3 + M                                : {3.4e-34 * (300/Tg)^1.2}
    O + O3 -> O2 + O2                                   : {8e-12 * exp(-2060/Tg)}
    O + N + M -> NO + M                                 : {6.3e-33 * exp(140/Tg)}
    O + N2A3 -> N2 + O                                  : 2.7e-11
    O + N2A3 -> N + NO                                  : 7e-12
    O + NO + M -> NO2 + M                               : {1e-31 * exp(300/Tg)^1.6}
    O + NO2 -> NO + O2                                  : {6.5e-12 * exp(120/Tg)}
    O + NO2 + M -> NO3 + M                              : {9e-32 * exp(300/Tg)^2}
    O + NO3 -> O2 + NO2                                 : 1.7e-11
    O- + N -> NO + e                                    : 2.6e-10
    O- + N2 -> N2O + e                                  : 2.2e-12
    O- + N2A3 -> N2 + O + e                             : 2.2e-9 
    O2 + N2A3 -> N2 + O + O                             : 1e-12
    O2 + N2A3 -> NO + NO                                : 2.0e-14
    O2 + N2A3 -> N2 + O2                                : 8.1e-13
    O2- + O -> O3 + e                                   : 1.5e-10
    O2- + O2 -> O2 + O2 + e                             : {1.9e-12 * (Tg/300)^0.5 * exp(-5590/Tg)}
    O2- + O3 -> O3 + O2 + e                             : 6e-10
    O2- + N -> NO2 + e                                  : 5e-10
    O2- + N2 -> N2 + O2 + e                             : {1.9e-12 * (Tg/300)^0.5 * exp(-4990/Tg)}
    O2- + N2A3 -> N2 + O2 + e                           : 2.1e-9
    O3 + N2A3 -> NO + NO + O                            : 8.4e-12
    O3 + N2A3 -> N2 + O2 + O                            : 3.36e-11
    O2 + N2+ -> N2 + O2+                                : {6e-11 * (Tg/300)^-0.5}
    O3 + N2+ -> O2+ + O + N2                            : 1.0e-10
    O3 + NO -> NO2 + O2                                 : {1.8e-12 * exp(-1370/Tg)}
    O3 + NO2 -> NO3 + O2                                : {1.4e-13 * exp(-2470/Tg)}
    O3 + NO2 -> NO + O2 + O2                            : 1e-18
    O3 + NO3 -> NO2 + O2 + O2                           : 1e-17
    O3 + M -> O + O2 + M                                : {3.92e-10 * exp(-11400/Tg)}
    O3- + O -> O2 + O2 + e                              : 3e-10
    O3- + O2 -> O3 + O2 + e                             : 2.3e-11
    O3- + O3 -> O2 + O2 + O2 + e                        : 3e-10
    N2 + N2A3 -> N2 + N2                                : 3.7e-16
    N2A3 -> N2                                          : 0.5
    NO + NO3 -> NO2 + NO2                               : {1.8e-11 * exp(110/Tg)}
    NO + NO2 + M -> N2O3 + M                            : {3.09e-34 * (300/Tg)^7.7}
    NO2 + NO2 + M -> N2O4 + M                           : {1.17e-33 * (300/Tg)^3.8}
    NO2 + NO3 + M -> N2O5 + M                           : {2.8e-30 * (300/Tg)^3.5}
    NO2 + NO3 -> NO2 + NO + O2                          : {2.3e-13 * exp(-1600/Tg)}
    NO3 + NO3 -> NO2 + NO2 + O2                         : {5e-12 * exp(-3000/Tg)}
    N2O3 + M -> NO + NO2 + M                            : {1.03e-10 * exp(-2628/Tg)}
    N2O4 + M -> NO2 + NO2 + M                           : {1.09e-7 * exp(-4592/Tg)}
    N2O5 + M -> NO2 + NO3 + M                           : {1e-3 * (300/Tg)^3.5 * exp(-1000/Tg)}
    '
  []
[]

#

[AuxVariables]
  [reduced_field]
    order = FIRST
    family = SCALAR
    initial_condition = 400
  []

  [Te]
    order = FIRST
    family = SCALAR
    initial_condition = 10
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
    args = 'N2 O2 N O O3 NO N2O NO2 NO3 N2O3 N2O4 N2O5'
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
  dtmax = 1e-7
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

[Outputs]
  [out]
    type = CSV
  []
  [console]
    type = Console
    execute_scalars_on = 'none'
  []
[]
