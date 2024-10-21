[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 1
  nx = 1
[]

[Variables]
  [e]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  []

  [H2O]
    family = SCALAR
    order = FIRST
    initial_condition = 33.3679e21
  []

  [H2O+]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  []

  [H2O-]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  []

  [H]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  []

  [OH]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  []

  [N2]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  []
  
  [N2g]
    order = FIRST
    family = SCALAR
    initial_condition = 1.93e19
  []

  [NO2]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  []
  
  [NO2g]
    order = FIRST
    family = SCALAR
    initial_condition = 1.16e14
  []
  
  [ONOOH]
    order = FIRST
    family = SCALAR
    initial_condition = 1
  []
[]

[ScalarKernels]
  [de_dt]
    type = ODETimeDerivative
    variable = e
  []

  [dH2O_dt]
    type = ODETimeDerivative
    variable = H2O
  []

  [dH2O+_dt]
    type = ODETimeDerivative
    variable = H2O+
  []

  [dH2O-_dt]
    type = ODETimeDerivative
    variable = H2O-
  []

  [dH_dt]
    type = ODETimeDerivative
    variable = H
  []

  [dOH_dt]
    type = ODETimeDerivative
    variable = OH
  []

  [dN2_dt]
    type = ODETimeDerivative
    variable = N2
  []

  [dN2g_dt]
    type = ODETimeDerivative
    variable = N2g
  []

  [dNO2_dt]
    type = ODETimeDerivative
    variable = NO2
  []

  [dNO2g_dt]
    type = ODETimeDerivative
    variable = NO2g
  []

  [dONOOH_dt]
    type = ODETimeDerivative
    variable = ONOOH
  []
[]

[AuxVariables]
  [e]
    order = FIRST
    family = SCALAR
  []
  
  [M]
    order = FIRST
    family = SCALAR
  []
  
  [hN2]
    order = FIRST
    family = SCALAR
    initial_condition = 1.6e-2
  []
  
  [hNO2]
    order = FIRST
    family = SCALAR
    initial_condition = 0.28
  []
[]

[AuxScalarKernels]
  [neutral_sum]
    type = VariableSum
    variable = M
    args = 'N2'
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []

[]

[GlobalReactions]
  [Air]
    species = 'N2 N2g NO2 NO2g H2O H2O+ H2O- H + OH ONOOH e'
    file_location = 'data'
    aux_species = 'M'

    # These are parameters required equation-based rate coefficients
    equation_constants = 'pi Area Vp'
    equation_values = '3.141 4.84 400'
    equation_variables = 'hN2 hNO2 N2 N2g NO2 NO2g'
    electron_density = 'e'
    include_electrons = true

    reactions = '
    N2g -> N2               : {if(N2/(N2g*0.99)<hN2,Vp*2*(hN2*N2g - N2)/(hN2*N2g),0)}
    N2 -> N2g               : {if(N2/N2g>hN2,(N2 - hN2*N2g)*(Vp/Area)*2,0)}
    NO2g -> NO2             : {if(NO2/(NO2g*0.99)<hNO2,Vp*2*(hNO2*NO2g - NO2)/(hNO2*NO2g),0)}
    NO2 -> NO2g             : {if(NO2/NO2g>hNO2,(NO2 - hNO2*NO2g)*(Vp/Area)*2,0)}
    H2O -> H2O+ + e         : 1e-20
    e + H2O -> H2O-         : 5e-15
    H2O- + H2O+ -> H + OH + H2O : 1e-9
    OH + H -> H2O           : 3e-11
    H2O -> H + OH           : 1e-20
    ONOOH + H2O -> OH + NO2 + H2O : 1.24e-23
    NO2 + OH -> ONOOH       : 1.99e-11
'
  []
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Debug]
  show_var_residual_norms = false
[]

[Executioner]
  type = Transient
  automatic_scaling = true
  compute_scaling_once = false
  end_time = 10
  solve_type = NEWTON
  dtmin = 1e-15
  dtmax = 1e-4
  line_search = 'none'
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_factor_shift_type -pc_factor_shift_amount -snes_linesearch_minlambda'
  petsc_options_value = 'NONZERO 1.e-10 1e-3'
  steady_state_detection = false
  l_max_its = 20
  nl_max_its = 30
  [TimeSteppers]
    [adaptive]
      type = IterationAdaptiveDT
      cutback_factor = 0.925
      dt = 1e-8
      growth_factor = 1.01
    []
  []
[]

[Outputs]
  [out1]
    type = CSV
    interval = 1
  []

  [console]
    type = Console
    execute_scalars_on = 'none'
  []
[]
