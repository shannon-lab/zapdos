[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 1
  nx = 1
[]

[Variables]
  [eg]
    family = SCALAR
    order = FIRST
    initial_condition = 501.8518769
  []

  [eaq]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  []

  [N]
    family = SCALAR
    order = FIRST
    initial_condition = 6013165301180.5
  []

  [Naq]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  []
[]

[ScalarKernels]
  [deg_dt]
    type = ODETimeDerivative
    variable = eg
  []

  [deaq_dt]
    type = ODETimeDerivative
    variable = eaq
  []
  
  [dN_dt]
    type = ODETimeDerivative
    variable = N
  []
  
  [dNaq_dt]
    type = ODETimeDerivative
    variable = Naq
  []
[]

[GlobalReactions]
  [Air]
    species = 'eg eaq N Naq'
    file_location = 'data'

    equation_constants = 'N2 N2O N2O3 N2O4 N2O5 NO NO+ NO2 NO2+ NO2- NO3 NO3- O O2 O2- O2a O3 O4+ e'
    equation_values = '1.93e+19	9.88858e+13	2637607.661	3259209.552	1.46975e+12 22635703537	998225.6757	1.38694e+13	19682003.68	114072.2637	4.23389e+11	20562740.76	2.59402e+11 5.39e+18	2426.040526	1.42882e+13	7.41e+16	493.2483978	501.8518769'
    equation_variables = 'Te'
    track_rates = true

    reactions = '
    eg -> eaq + eg    : 1
    N -> Naq + N      : {1e-10*Te}
    '
  []
[]

[Debug]
  show_var_residual_norms = false
[]

[AuxVariables]
  [Te]
    order = FIRST
    family = SCALAR
    initial_condition = 10
  []
[]

[Executioner]
  type = Transient
  automatic_scaling = true
  compute_scaling_once = false
  end_time = 0.001
  solve_type = NEWTON
  dtmin = 1e-15
  dtmax = 1e-5
  line_search = 'basic'
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_factor_shift_type -pc_factor_shift_amount -snes_linesearch_minlambda'
  petsc_options_value = 'NONZERO 1.e-10 1e-3'
  steady_state_detection = false
  l_max_its = 10
  nl_max_its = 15
  [TimeSteppers]
    [cst1]
      type = CSVTimeSequenceStepper
      column_index = 0
      file_name = 'dt.csv'
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
    execute_scalars_on = 'none'
  []
[]
