[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 1
  nx = 1

[]

[Variables]
  [./e]
    family = SCALAR
    order = FIRST
    initial_condition = 1e6
  [../]

  [./Ar+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e6
  [../]

  [./Ar]
    family = SCALAR
    order = FIRST
    initial_condition = 3.21883e18
    scaling = 1e-18
  [../]

  [./Ar*]
    family = SCALAR
    order = FIRST
    initial_condition = 1e6
  [../]

  [./Ar2+]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  [../]
[]

[ScalarKernels]
  [./de_dt]
    type = ODETimeDerivative
    variable = e
  [../]

  [./dAr+_dt]
    type = ODETimeDerivative
    variable = Ar+
  [../]

  [./dAr_dt]
    type = ODETimeDerivative
    variable = Ar
  [../]

  [./dAr*_dt]
    type = ODETimeDerivative
    variable = Ar*
  [../]

  [./dAr2_dt]
    type = ODETimeDerivative
    variable = Ar2+
  [../]
[]


[ChemicalReactions]
  [./ScalarNetwork]
    species = 'e Ar* Ar+ Ar Ar2+'
    reaction_coefficient_format = 'rate'
    file_location = 'Example2'

    # These are parameters required equation-based rate coefficients
    equation_constants = 'Tgas J pi'
    equation_values = '300 2.405 3.141'
    equation_variables = 'Te'
    rate_provider_var = 'reduced_field'


    reactions = 'e + Ar -> e + e + Ar+          : EEDF
                 e + Ar -> Ar* + e              : EEDF
                 e + Ar* -> Ar + e              : EEDF
                 e + Ar* -> Ar+ + e + e         : EEDF
                 Ar2+ + e -> Ar* + Ar           : {8.5e-7*((Te/1.5)*11600/300.0)^(-0.67)}
                 Ar2+ + Ar -> Ar+ + Ar + Ar     : {(6.06e-6/Tgas)*exp(-15130.0/Tgas)}
                 Ar* + Ar* -> Ar2+ + e          : 6.0e-10
                 Ar+ + e + e -> Ar + e          : {8.75e-27*((Te/1.5)^(-4.5))}
                 Ar* + Ar + Ar -> Ar + Ar + Ar  : 1.399e-32
                 Ar+ + Ar + Ar -> Ar2+ + Ar     : {2.25e-31*(Tgas/300.0)^(-0.4)}
                 e -> W                         : {1.52*(760/100)*(Tgas/273.16)*(Te/1.5)*((J/0.4)^2 + (pi/0.4)^2)}
                 Ar+ -> W                       : {1.52*(760/100)*(Tgas/273.16)*(Te/1.5)*((J/0.4)^2 + (pi/0.4)^2)}
                 Ar2+ -> W                      : {1.52*(760/100)*(Tgas/273.16)*(Te/1.5)*((J/0.4)^2 + (pi/0.4)^2)}'
  [../]
[]


[AuxVariables]
  [./all_neutral]
    order = FIRST
    family = SCALAR
    initial_condition = 3.21883e18
  [../]

  [./reduced_field]
    order = FIRST
    family = SCALAR
    initial_condition = 7.7667949e-20
  [../]

  [./mobility]
    order = FIRST
    family = SCALAR
    initial_condition = 2.546334e-01
  [../]

  [./Te]
    order = FIRST
    family = SCALAR
    initial_condition = 50000
  [../]

  [./current]
    order = FIRST
    family = SCALAR
    initial_condition = 0
  [../]
[]

[AuxScalarKernels]
  [./species_sum]
    type = VariableSum
    variable = all_neutral
    args = 'Ar Ar*'
    execute_on = 'LINEAR TIMESTEP_END'
  [../]

  [./reduced_field_calculate]
    type = ParsedAuxScalar
    variable = reduced_field
    constant_names = 'V d qe R'
    constant_expressions = '1000 0.004 1.602e-19 1e5'
    args = 'reduced_field all_neutral current'
    function = 'V/(d+R*current/(reduced_field*all_neutral*1e6))/(all_neutral*1e6)'
    execute_on = 'TIMESTEP_END'
  [../]

  [./e_drift]
    type = ParsedAuxScalar
    variable = current
    constant_names = 'r pi'
    constant_expressions = '0.004 3.1415926'
    args = 'reduced_field mobility all_neutral e'
    function = '(reduced_field * mobility * all_neutral*1e6) * 1.6e-19 * pi*(r^2.0) * (e*1e6)'
    execute_on = 'TIMESTEP_BEGIN'
  [../]

  [./mobility_calculation]
    type = DataReadScalar
    variable = mobility
    sampler = reduced_field
    property_file = 'Example2/electron_mobility.txt'
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  [../]

  [./temperature_calculation]
    type = DataReadScalar
    variable = Te
    sampler = reduced_field
    property_file = 'Example2/electron_temperature.txt'
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  [../]
[]

[UserObjects]
  active = 'value_provider'

  [./value_provider]
    type = ValueProvider
    property_file = 'Example2/electron_temperature.txt'
  [../]
[]

[Executioner]
  type = Transient
  end_time = 1e-3
  solve_type = 'linear'
  dtmin = 1e-20
  dtmax = 1e-5
  petsc_options_iname = '-snes_linesearch_type'
  petsc_options_value = 'basic'
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.9
    dt = 1e-10
    growth_factor = 1.01
  [../]
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Outputs]
  [./out]
    type = Exodus
    execute_on = 'TIMESTEP_END'
  [../]
[]
