[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 1
  nx = 1
[]

[Variables]

  [N2]
    family = SCALAR
    order = FIRST
    initial_condition = 19299982848142000000
    #scaling = 1e-9
  []

  [O2]
    family = SCALAR
    order = FIRST
    initial_condition = 5389880072740200000
    #scaling = 1e-9
  []

  [O2a]
    family = SCALAR
    order = FIRST
    initial_condition = 4392980278082
    # scaling = 1e-2
  []

  [O]
    family = SCALAR
    order = FIRST
    initial_condition = 79010709333.782
    #scaling = 1e-9
  []
  
  [NO]
    family = SCALAR
    order = FIRST
    initial_condition = 7192472486.3895
    #scaling = 1e-9
  []
    
  [NO+]
    family = SCALAR
    order = FIRST
    initial_condition = 242843.83858996
    #scaling = 1e-9
  []
  
  [N2O]
    family = SCALAR
    order = FIRST
    initial_condition = 98524619652527
    #scaling = 1e-9
  []
  
  [NO2]
    family = SCALAR
    order = FIRST
    initial_condition = 13690760674164
    #scaling = 1e-9
  []
  
  [NO2-]
    family = SCALAR
    order = FIRST
    initial_condition = 89650.411999741
    #scaling = 1e-9
  []
  
  [NO2+]
    family = SCALAR
    order = FIRST
    initial_condition = 16013225.303277
    #scaling = 1e-9
  []
  
  [NO3]
    family = SCALAR
    order = FIRST
    initial_condition = 430716446074.43
    #scaling = 1e-9
  []
  
  [NO3-]
    family = SCALAR
    order = FIRST
    initial_condition = 16165615.093313
    #scaling = 1e-9
  []

  [O3]
    family = SCALAR
    order = FIRST
    initial_condition = 73371989857752000
    #scaling = 1e-9
  []

  [N2O5]
    family = SCALAR
    order = FIRST
    initial_condition = 1562880237085.1
    #scaling = 1e-9
  []

  [N2O3]
    family = SCALAR
    order = FIRST
    initial_condition = 827263.35877595
    #scaling = 1e-9
  []

  [N2O4]
    family = SCALAR
    order = FIRST
    initial_condition = 3175698.5275614
    #scaling = 1e-9
  []
[]

[ScalarKernels]

  [dN2_dt]
    type = ODETimeDerivative
    variable = N2
  []

  [dO2_dt]
    type = ODETimeDerivative
    variable = O2
  []

  [dO2a_dt]
    type = ODETimeDerivative
    variable = O2a
  []

  [dO_dt]
    type = ODETimeDerivative
    variable = O
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
  
  [dN2O3_dt]
    type = ODETimeDerivative
    variable = N2O3
  []
  
  [dN2O4_dt]
    type = ODETimeDerivative
    variable = N2O4
  []

  [dN2O5_dt]
    type = ODETimeDerivative
    variable = N2O5
  []
[]

[AuxVariables]
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
  [neutral_sum]
    type = VariableSum
    variable = M
    args = 'N2 O2 O2a O O3 NO N2O NO2 NO3 N2O3 N2O4 N2O5'
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []
[]

[Executioner]
  type = Transient
  automatic_scaling = true
  compute_scaling_once = false
  start_time = 0.011
  end_time = 0.14
  solve_type = NEWTON
  dtmin = 1e-8
  dtmax = 1e-3
  line_search = 'basic'
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_factor_shift_type -pc_factor_shift_amount -snes_linesearch_minlambda'
  petsc_options_value = 'NONZERO 1.e-10 1e-3'
  steady_state_detection = false
  l_max_its = 20
  nl_max_its = 30
  [TimeSteppers]
    [cst1]
      type = ConstantDT
      dt = 0.005
    []
  []
[]

[Outputs]
  [out1]
    type = CSV
    interval = 10
  []

  [console]
    type = Console
    execute_scalars_on = 'INITIAL'
  []
[]

[GlobalReactions]
  [Air]
    species = 'NO+ NO2+ NO2- NO3- O O2a O3 NO N2O NO2 NO3 N2O3 N2O4 N2O5 N2 O2'
    file_location = 'data'
    aux_species = 'M'

    equation_constants = 'Tg'
    equation_values = '340'
    track_rates = true

    reactions = '
    O + O + O -> O2 + O                : 4.0e-33 * (300/Tg)^0.41 * 3.6
    O + O + M -> O2a + M               : 6.93e-35 * (Tg/300)^-0.63
    O + O2 + NO -> O2 + NO2            : 1e-31 * (300/Tg)^1.6
    O + N2O5 -> N2 + O2 + O2 + O2      : 3e-16 * (Tg/300)^0.5
    O + O3 + NO -> O3 + NO2            : 2e-31 * (300/Tg)^1.6
    O + O3 + NO2 -> O3 + NO3           : 2e-31 * (300/Tg)^2
    NO2 + NO2 + N2 -> N2O4 + N2        : 1.4e-33 * (300/Tg)^3.8
    NO2 + NO2 + O2 -> N2O4 + O2        : 1.4e-33 * (300/Tg)^3.8
    NO2 + NO3 + N2 -> N2O5 + N2        : 2.8e-30 * (300/Tg)^3.5
    NO2 + NO3 + O2 -> N2O5 + O2        : 2.8e-30 * (300/Tg)^3.5
    NO2+ + NO3- + M -> N2O5 + M        : 2e-25 * (Tg/300)^-2.5
    NO2+ + NO3- + M -> NO2 + NO3 + M   : 2e-25 * (Tg/300)^-2.5
    NO + NO2 -> N2O3                   : 7.9e-12 * (Tg/300)^1.4
    NO+ + NO2- + M -> NO + NO2 + M     : 2e-25 * (Tg/300)^-2.5
    NO+ + NO3- + M -> NO + NO3 + M     : 2e-25 * (Tg/300)^-2.5
    NO2+ + NO3- -> NO2 + NO3           : 2e-7 * (Tg/300)^-0.5
    NO2- + NO2+ -> NO2 + NO2           : 2e-7 * (300/Tg)^0.5
    NO2- + NO2+ + M -> NO2 + NO2 + M   : 2e-25 * (Tg/300)^-2.5
    NO2 + NO3 + O3 -> N2O5 + O3        : 6e-30 * (300/Tg)^3.5
    NO + NO2 + N2 -> N2O3 + N2         : 3.1e-34 *(Tg/300)^-7.7
    NO + NO2 + O2 -> N2O3 + O2         : 3.1e-34 *(Tg/300)^-7.7
    NO + NO2 + O3 -> N2O3 + O3         : 6.1e-34 *(Tg/300)^-7.7
    NO+ + NO2- -> NO + NO2             : 2e-7 * (300/Tg)^0.5
    NO+ + NO3- -> NO + NO3             : 2e-7 * (300/Tg)^0.5
    NO2 + NO2 + O3 -> N2O4 + O3        : 3e-33 * (300/Tg)^3.8
    O + O2 + M -> O3 + M               : 3.4e-34 * (300/Tg)^1.2
    O + NO + M -> NO2 + M              : 1e-31 * (300/Tg)^1.6
    O + NO2 + M -> NO3 + M             : 9e-32 * (300/Tg)^2
    O + O2a -> O2 + O                  : 7e-16
    O + NO2+ -> NO+ + O2               : 8e-12
    O + NO3 -> O2 + NO2                : 1.7e-11
    O + NO3- -> NO2- + O2              : 2.5e-12
    O2 + NO3 -> NO2 + O3               : 1e-17
    O3 + NO2 -> NO + O2 + O2           : 1e-18
    O3 + NO2- -> NO3- + O2             : 1.8e-11
    O3 + NO3- -> NO2- + O2 + O2        : 1e-13
    NO + NO2+ -> NO+ + NO2             : 2.9e-10
    NO+ + NO3- -> NO2 + NO + O         : 1e-7
    NO+ + N2O5 -> NO2+ + NO2 + NO2     : 5.9e-10
    NO2- + N2O -> NO3- + N2            : 5e-13
    NO2- + NO3 -> NO3- + NO2           : 5e-10
    NO2- + N2O5 -> NO3- + NO3 + NO     : 7e-10
    N2O5 + M -> NO2 + NO3 + M          : 1e-3 * (300/Tg)^3.5*exp(-11000/Tg)
    NO2 + NO2 -> NO3 + NO              : 1e-12 * (Tg/300)^0.73 *  exp(-10524.3/Tg)
    NO + NO3 -> NO + NO + O2           : 7.3e-12 * (Tg/300)^-0.23 * exp(-947/Tg)
    NO + N2O -> NO2 + N2               : 2.92e-13 * (Tg/300)^2.23 * exp(-23292/Tg)
    NO3 + NO3 -> NO2 + NO2 + O2        : 5e-12 * exp(-3000/Tg)
    O2 + NO -> NO2 + O                 : 2.8e-12 * exp(-23400/Tg)
    NO + NO + O2 -> NO2 + NO2          : 3.3e-39 * exp(530/Tg)
    NO + NO -> N2O + O                 : 7.22e-12 * exp(-33155/Tg)
    NO + NO -> N2 + O2                 : 2.51e-11 * exp(-30653/Tg)
    O2 + O2a -> O2 + O2                : 3.8e-18 * exp(-205/Tg)
    O3 + O3 -> O2 + O2 + O2            : 7.47e-12 * exp(-9310/Tg)
    O2a + O3 -> O2 + O3                : 6.8e-18 * exp(-200/Tg)
    O + O + M -> O2 + M                : 3.2e-35 * exp(900/Tg)
    NO2 + NO3 -> NO2 + NO + O2         : 4.5e-14 * exp(-1260/Tg)
    NO2 + NO2 -> NO + NO + O2          : 2.71e-12 * exp(-13110/Tg)
    N2O3 + M -> NO + NO2 + M           : 1.03e-10*exp(-2628/Tg)
    N2O4 + M -> NO2 + NO2 + M          : 1.09e-7*exp(-4952/Tg)
    O + O3 -> O2 + O2                  : 8e-12 * exp(-2060/Tg)
    O + N2O -> N2 + O2                 : 1.66e-10 * exp(-14100/Tg)
    O + N2O -> NO + NO                 : 1.15e-10 * exp(-13400/Tg)
    O + NO2 -> NO + O2                 : 6.5e-12*exp(120/Tg)
    O2a + O2a -> O2 + O2               : 9e-17 * exp(-560/Tg)
    O2a + O3 -> O + O2 + O2            : 9.7e-13 * exp(-1564/Tg)
    O2a + N2 -> O2 + N2                : 3e-18 * exp(-200/Tg)
    O3 + N2 -> O + O2 + N2             : 7.3e-10 * exp(-11400/Tg)
    O2 + O3 -> O + O2 + O2             : 7.3e-10 * exp(-11400/Tg)
    O3 + O3 -> O + O2 + O3             : 1.4e-9 * exp(-11400/Tg)
    O3 + NO -> NO2 + O2                : 3e-12*exp(-1560/Tg)
    O3 + NO2 -> NO3 + O2               : 1e-13 * exp(-2470/Tg)
    NO + NO3 -> NO2 + NO2              : 1.8e-11*exp(110/Tg)
    NO2+ + NO3- -> NO2 + NO2 + O       : 1e-7
    NO2+ + NO3- -> NO + NO3 + O        : 1e-7
    NO2+ + NO3- -> NO + NO2 + O + O    : 1e-7
    NO2- + NO2+ -> NO2 + NO + O        : 1e-7
    NO2- + NO2+ -> NO + NO + O + O     : 1e-7
    O2 + NO + NO -> NO2 + NO2          : 1.4e-38
    O2a + NO -> NO2 + O                : 4.88e-18
    O2 + O2a -> O3 + O                 : 3e-21
    O3 + NO+ -> NO2+ + O2              : 1e-15
    O3 + NO3 -> NO2 + O2 + O2          : 1e-17
    NO + NO3- ->  NO2- + NO2           : 3e-15
    NO+ + NO2- -> NO + NO + O          : 1e-7
    NO+ + NO3- -> NO2 + NO + O         : 1e-7
    NO2 + NO2- -> NO3- + NO            : 4e-12
    O2a -> O2                          : 2.7e-4
'
  []
[]

