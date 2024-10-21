[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 1
[]

[Variables]
  [./e]
    order = FIRST
    family = SCALAR
    initial_condition = 1e11
    # scaling = 1e-11
  [../]

  [./He]
    order = FIRST
    family = SCALAR
    initial_condition = 1e18
    # scaling = 1e-12
  [../]

  [./He*]
    order = FIRST
    family = SCALAR
    initial_condition = 0
    # scaling = 1e-14
  [../]

  [./He2*]
    order = FIRST
    family = SCALAR
    initial_condition = 0
    # scaling = 1e-10
  [../]

  [./He+]
    order = FIRST
    family = SCALAR
    initial_condition = 0
    # scaling = 1e-16
  [../]

  [./He2+]
    order = FIRST
    family = SCALAR
    initial_condition = 0
    # scaling = 1e-13
  [../]

  [./O]
    order = FIRST
    family = SCALAR
    initial_condition = 0
    # scaling = 1e-16
  [../]

  [./O2]
    order = FIRST
    family = SCALAR
    initial_condition = 1e16
    # scaling = 1e-10
  [../]

  [./O3]
    order = FIRST
    family = SCALAR
    initial_condition = 0
    # scaling = 1e-11
  [../]

  [./O2+]
    order = FIRST
    family = SCALAR
    initial_condition = 0
    # scaling = 1e-9
  [../]

  [./O2-]
    order = FIRST
    family = SCALAR
    initial_condition = 0
    # scaling = 1e-7
  [../]

  [./O4+]
    order = FIRST
    family = SCALAR
    initial_condition = 0
  [../]
[]

[ScalarKernels]
  [./de_dt]
    type = ODETimeDerivative
    variable = e
  [../]

  [./dHe_dt]
    type = ODETimeDerivative
    variable = He
  [../]

  [./dHe*_dt]
    type = ODETimeDerivative
    variable = He*
  [../]

  [./dHe2*_dt]
    type = ODETimeDerivative
    variable = He2*
  [../]

  [./dHe+_dt]
    type = ODETimeDerivative
    variable = He+
  [../]

  [./dHe2+_dt]
    type = ODETimeDerivative
    variable = He2+
  [../]

  [./dO_dt]
    type = ODETimeDerivative
    variable = O
  [../]

  [./dO2_dt]
    type = ODETimeDerivative
    variable = O2
  [../]

  [./dO3_dt]
    type = ODETimeDerivative
    variable = O3
  [../]

  [./dO2+_dt]
    type = ODETimeDerivative
    variable = O2+
  [../]

  [./dO2-_dt]
    type = ODETimeDerivative
    variable = O2-
  [../]

  [./dO4+_dt]
    type = ODETimeDerivative
    variable = O4+
  [../]
[]

[AuxVariables]
  [./M]
    family = SCALAR
    order = FIRST
    initial_condition = 1e18
  [../]

  [./T0]
    family = SCALAR
    order = FIRST
    initial_condition = 300
  [../]

  [./Teg]
    family = SCALAR
    order = FIRST
    initial_condition = 300
  [../]
[]

[AuxScalarKernels]
  [./M_calculate]
    type = VariableSum
    variable = M
    args = 'He He* He2* O O2 O3'
    execute_on = 'TIMESTEP_BEGIN'
  [../]

  [./T0_calculate]
    type = ParsedAuxScalar
    variable = T0
    constant_names = 'Tg'
    constant_expressions = '345'
    function = 'Tg/300'
    execute_on = 'INITIAL'
  [../]

  [./Teg_calculate]
    type = ParsedAuxScalar
    variable = Teg
    constant_names = 'Te Tg'
    constant_expressions = '2.5 345'
    function = '(Te*11600)/Tg'
    execute_on = 'INITIAL'
  [../]
[]

# Evil reaction:
# O + O + O3 -> O2 + O3     : {4.6e-34 * exp(1050/Te)}
# Look at that exponent!
[ChemicalReactions]
  [./ScalarNetwork]
    species = 'e He He* He2* He+ He2+ O O2 O3 O2+ O2- O4+ M'
    aux_species = 'M'
    equation_constants = 'Tg Te'
    equation_values = '345 2.5'
    equation_variables = 'T0 Teg'

    reactions = 'e + He* -> He + e         : {7.0e-10 * (Teg)^(0.5)}
    e + He2* -> He + He + e                : {4.0e-9 * (Teg)^(0.5)}
    e + O2 -> O + O + e                    : {1.41e-9 * Te^(0.22) * exp(-12.62/Te)}
    e + O2 -> O2-                          : {9.72e-9 * Te^(-1.62) * exp(-14.2/Te)}
    e + O3 -> O + O2 + e                   : {1.78e-6 * Te^(-0.614) * exp(-11.5/Te)}
    e + O3 -> O + O2-                      : {5.87e-9 * Te^(-1.5) * exp(-1.59/Te)}
    O2- + He -> He + O2 + e                : {3.9e-10 * exp(-7400/Tg)}
    O2- + He* -> He + O2 + e               : 3.0e-10
    O2- + He2* -> He + He + O2 + e         : 3.0e-10
    O2- + O -> O3 + e                      : {1.5e-10 * (T0)^(0.5)}
    O2- + O2 -> O2 + O2 + e                : {2.7e-10 * (T0)^(0.5) * exp(-5590/Tg)}
    O2- + O3 -> O2 + O3 + e                : 6.0e-10
    e + O2 + M -> O2- + M                  : {3.6e-31 * Te^(-0.5)}
    e + O + O2 -> O + O2-                  : 1.0e-31
    He+ + O2 -> He + O2+                   : {3.3e-11 * (T0)^(0.5)}
    He2+ + He* -> He + He + He+            : 1.0e-10
    He2+ + O2 -> He + He + O2+             : {1.0e-9 * (T0)^(0.5)}
    O2+ + O2 -> O2 + O2+                   : {1.0e-9 * (T0)^(-0.5)}
    O2+ + O2 -> O4+                        : {4.0e-30 * (T0)^(-2.9)}
    O4+ + He -> He + O2 + O2+              : 3.6e-14
    O4+ + He* -> He + O2 + O2+             : 1.0e-10
    O4+ + O -> O3 + O2+                    : 3.0e-10
    O4+ + O2 -> O2 + O2 + O2+              : {3.3e-6 * (T0)^(-4.0) * exp(-5030/Tg)}
    He+ + He + He -> He + He2+             : 6.6e-32
    O2+ + O2 + M -> O4+ + M                : {5.5e-31 * (T0)^(-2.7)}
    He + He2* -> He + He + He              : 4.9e-16
    He + O2 -> He + O + O                  : {3.0e-6 * Tg^(-1.0) * exp(-59380/Tg)}
    He + O3 -> He + O + O2                 : {1.56e-9 * exp(-11490/Tg)}
    He* + He* -> He + He+ + e              : 4.5e-10
    He* + He* -> He2+ + e                  : 1.05e-9
    He* + He2* -> He + He + He+ + e        : 2.25e-11
    He* + He2* -> He + He2+ + e            : 1.275e-10
    He* + O2 -> He + O2+ + e               : 2.6e-10
    He* + O3 -> He + O + O2+ + e           : {2.6e-10 * (T0)^(0.5)}
    He2* + He -> He + He + He              : 4.9e-16
    He2* + He2* -> He + He + He + He+ + e  : 3.0e-10
    He2* + He2* -> He + He + He2+ + e      : 1.2e-9
    He2* + O2 -> He + He + O2              : {1.5e-15 * (T0)^(0.5)}
    He2* + O2 -> He + He + O2+ + e         : 3.6e-10
    He2* + O3 -> He + He + O + O2+ + e     : {3.6e-10 * (T0)^(0.5)}
    O + O3 -> O + O + O2                   : {9.4e-11 * exp(-11400/Tg)}
    O + O3 -> O2 + O2                      : {8.0e-12 * exp(-2060/Tg)}
    O2 + O2 -> O + O + O2                  : {6.6e-9 * (T0)^(-1.5) * exp(-59000/Tg)}
    O2 + O3 -> O + O2 + O2                 : {1.56e-9 * exp(-11490/Tg)}
    O3 + O3 -> O + O2 + O3                 : {1.56e-9 * exp(-11490/Tg)}
    O3 + O3 -> O2 + O2 + O2                : {7.47e-12 * exp(-9310/Tg)}
    He + He + He* -> He + He2*             : 1.5e-34
    He + He* + O2 -> He + He + O2+ + e     : {1.6e-31 * (T0)^(0.5)}
    He + He* + O3 -> He + He + O + O2+ + e : {1.6e-31 * (T0)^(0.5)}
    He + O + O -> He + O2                  : 1.0e-33
    He + O + O2 -> He + O3                 : {3.4e-34 * (T0)^(-1.2)}
    O + O + O -> O + O2                    : {9.21e-34 * (T0)^(-0.63)}
    O + O + O2 -> O + O3                   : {3.4e-34 * (T0)^(-1.2)}
    O + O + O2 -> O2 + O2                  : {2.56e-34 * (T0)^(-0.63)}
    O + O2 + O2 -> O2 + O3                 : {6.0e-34 * (T0)^(-2.8)}
    O + O2 + O3 -> O3 + O3                 : {2.3e-35 * exp(-1057/Tg)}
    He+ + e -> He                          : {2.0e-12 * (Teg)^(-1.5)}
    He2+ + e -> He + He                    : {5.0e-9 * Te^(-0.5)}
    O2+ + e -> O + O                       : {2.1e-7 * (Teg)^(-0.63)}
    O2+ + e -> O2                          : 4.0e-12
    O4+ + e -> O + O + O2                  : {2.0e-6 * (Teg)^(-1.0)}
    O4+ + e -> O2 + O2                     : {1.4e-6 * Te^(-0.5)}
    He+ + e + e -> He + e                  : {7.0e-20 * (Teg)^(-4.5)}
    He2+ + e + e -> He + He + e            : {7.0e-20 * (Teg)^(-4.5)}
    He2+ + He + e -> He + He + He          : {2.0e-27 * (Teg)^(-2.5)}
    O2+ + e + e -> O2 + e                  : {7.0e-20 * (Teg)^(-4.5)}
    O2+ + He + e -> He + O2                : {6.0e-27 * (Teg)^(-1.5)}
    O2+ + O2 + e -> O2 + O2                : {2.49e-29 * Te^(-1.5)}
    O4+ + e + e -> O2 + O2 + e             : {7.0e-20 * (Teg)^(-4.5)}
    O4+ + He + e -> He + O2 + O2           : {7.0e-20 * (Teg)^(-4.5)}
    O4+ + O2 + e -> O2 + O2 + O2           : {7.0e-20 * (Teg)^(-4.5)}
    He+ + O2- -> He + O2                   : {2.0e-7 * (T0)^(-1.0)}
    He2+ + O2- -> He + He + O2             : 1.0e-7
    O2+ + O2- -> O + O + O2                : 1.0e-7
    O2+ + O2- -> O2 + O2                   : {4.2e-7 * (T0)^(-0.5)}
    O4+ + O2- -> O + O + O2 + O2           : 2.0e-6
    O4+ + O2- -> O2 + O2 + O2              : 1.0e-7
    e + He -> He* + e                      : {4.2e-9 * Te^(0.31) * exp(-19.8/Te)}
    e + He -> He+ + e + e                  : {1.5e-9 * Te^(0.68) * exp(-24.6/Te)}
    e + He* -> He+ + e + e                 : {1.28e-7 * Te^(0.6) * exp(-4.78/Te)}
    e + He+ -> He*                         : {6.76e-13 * Te^(-0.5)}
    e + He2* -> He2+ + e + e               : {3.78e-13 * Te^(0.71) * exp(-3.4/Te)}
    e + He2+ -> He + He*                   : {5.0e-9 * (Teg)^(-0.5)}
    e + He2+ -> He2*                       : {1.5e-16 * (Teg)^(-1.5)}
    e + O2 -> O2+ + e + e                  : {9.0e-10 * Te^(2.0) * exp(-12.6/Te)}
    e + He + He+ -> He + He*               : 1.0e-27
    e + He + He2+ -> He + He + He*         : {5.0e-27 * (Teg)^(-1.0)}
    e + He + He2+ -> He + He2*             : {1.5e-27 * (Teg)^(-1.0)}
    e + e + He+ -> He* + e                 : {6.0e-20 * (Teg)^(-4.0)}
    e + e + He2+ -> He + He* + e           : {1.0e-20 * (Teg)^(-4.0)}
    e + e + He2+ -> He2* + e               : {3.0e-20 * (Teg)^(-4.0)}'
  [../]
[]

[Executioner]
  type = Transient
  end_time = 2e-3
  petsc_options_iname = '-snes_linesearch_type'
  petsc_options_value = 'basic'
  dtmax = 1e-5
  solve_type = LINEAR
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.9
    dt = 1e-11
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
  csv = true
[]
