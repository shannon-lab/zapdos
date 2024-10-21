[GlobalParams]
  #use_moles = true
[]

[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 1
[]

[Problem]
  type = FEProblem
[]

[Variables]
  # ALL VARIABLES ARE IN UNITS OF #/CM^3
  [./e]
    family = SCALAR
    order = FIRST
    #initial_condition = 1e18
    initial_condition = 41.4465316738928223
    #scaling = 1e-26
  [../]
  [./N2]
    family = SCALAR
    order = FIRST
    #initial_condition = 1.834268645908762e19
    initial_condition = 44.3557626108601489 
    #scaling = 1e-27
  [../]

  [./N2v1]
    family = SCALAR
    order = FIRST
  #  initial_condition = 40
    initial_condition = 0.6931471805599453
    #initial_condition = 20
    #scaling = 1e-25
  [../]

  [./N2v2]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-24
  [../]

  [./N2v3]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-23
  [../]

  [./N2v4]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-23
  [../]

  [./N2v5]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-23
  [../]

  [./N2v6]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-23
  [../]

  [./N2v7]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-23
  [../]

  [./N2v8]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-22
  [../]

  [./N2A3]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-9
  [../]

  [./N2B3]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-9
  [../]

  [./N2a_1]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-8
  [../]

  [./N2C3]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-10
  [../]

  [./N]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-28
  [../]

  [./N2D]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-10
  [../]

  [./N2P]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-9
  [../]

  [./N+]
    family = SCALAR
    order = FIRST
    initial_condition = 41.4465316738928223
    #scaling = 1e-10
  [../]

  [./N2+]
    family = SCALAR
    order = FIRST
    #initial_condition = -11.512925464970228420089957
    initial_condition = 0.6931471805599453
    #scaling = 1e10
  [../]

  [./N3+]
    family = SCALAR
    order = FIRST
    #initial_condition = -11.512925464970228420089957
    initial_condition = 0.6931471805599453
  [../]

  [./N4+]
    family = SCALAR
    order = FIRST
    #initial_condition = -11.512925464970228420089957
    initial_condition = 0.6931471805599453
    #scaling = 1e10
  [../]

  [./O2]
    # Air is N2-O2 at ratio of 4:1
    family = SCALAR
    order = FIRST
    #initial_condition = 6.114228819695872e18
    initial_condition = 43.257150322192039
    #scaling = 1e-28
  [../]

  [./O2v1]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-24
  [../]

  [./O2v2]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-23
  [../]

  [./O2v3]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-23
  [../]

  [./O2v4]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-23
  [../]

  [./O2a1]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-23
  [../]

  [./O2b1]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-20
  [../]

  [./O24_ev]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-13
  [../]

  [./O]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-25
  [../]

  [./O1D]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-7
  [../]

  [./O1S]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-6
  [../]

  [./O3]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-7
  [../]

  [./O+]
    family = SCALAR
    order = FIRST
    #initial_condition = -11.512925464970228420089957
    initial_condition = 0.6931471805599453
    #scaling = 1e-26
  [../]

  [./O2+]
    family = SCALAR
    order = FIRST
    #initial_condition = -11.512925464970228420089957
    initial_condition = 0.6931471805599453
    #scaling = 1e-24
  [../]

  [./O4+]
    family = SCALAR
    order = FIRST
    #initial_condition = -11.512925464970228420089957
    initial_condition = 0.6931471805599453
  [../]

  [./O-]
    family = SCALAR
    order = FIRST
    #initial_condition = -11.512925464970228420089957
    initial_condition = 0.6931471805599453
    #scaling = 1e-6
  [../]

  [./O2-]
    family = SCALAR
    order = FIRST
    #initial_condition = -11.512925464970228420089957
    initial_condition = 0.6931471805599453
    #scaling = 1e-22
  [../]

  [./O3-]
    family = SCALAR
    order = FIRST
    #initial_condition = -11.512925464970228420089957
    initial_condition = 0.6931471805599453
    #scaling = 1e-5
  [../]

  [./O4-]
    family = SCALAR
    order = FIRST
    #initial_condition = -11.512925464970228420089957
    initial_condition = 0.6931471805599453
  [../]

  [./NO]
    family = SCALAR
    order = FIRST
    initial_condition = 0.6931471805599453
    #scaling = 1e-6
  [../]

  [./NO+]
    family = SCALAR
    order = FIRST
    #initial_condition = -11.512925464970228420089957
    initial_condition = 0.6931471805599453
    #scaling = 1e-26
  [../]

  [./NO-]
    family = SCALAR
    order = FIRST
    #initial_condition = -11.512925464970228420089957
    initial_condition = 0.6931471805599453
    #scaling = 1e-10
  [../]

  [./O2pN2]
    family = SCALAR
    order = FIRST
    #initial_condition = -11.512925464970228420089957
    initial_condition = 0.6931471805599453
  [../]

[]

[ScalarKernels]
  [./e_time_deriv]
    type = ODETimeDerivativeLog
    variable = e
  [../]
  [./N2_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2
  [../]

  [./N2v1_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2v1
  [../]

  [./N2v2_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2v2
  [../]

  [./N2v3_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2v3
  [../]

  [./N2v4_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2v4
  [../]

  [./N2v5_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2v5
  [../]

  [./N2v6_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2v6
  [../]

  [./N2v7_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2v7
  [../]

  [./N2v8_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2v8
  [../]

  [./N2A3_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2A3
  [../]

  [./N2B3_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2B3
  [../]

  [./N2a_1_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2a_1
  [../]

  [./N2C3_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2C3
  [../]

  [./N_time_deriv]
    type = ODETimeDerivativeLog
    variable = N
  [../]

  [./N2D_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2D
  [../]

  [./N2P_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2P
  [../]

  [./Np_time_deriv]
    type = ODETimeDerivativeLog
    variable = N+
  [../]

  [./N2p_time_deriv]
    type = ODETimeDerivativeLog
    variable = N2+
  [../]

  [./N3p_time_deriv]
    type = ODETimeDerivativeLog
    variable = N3+
  [../]

  [./N4p_time_deriv]
    type = ODETimeDerivativeLog
    variable = N4+
  [../]

  [./O2_time_deriv]
    type = ODETimeDerivativeLog
    variable = O2
  [../]

  [./O2v1_time_deriv]
    type = ODETimeDerivativeLog
    variable = O2v1
  [../]

  [./O2v2_time_deriv]
    type = ODETimeDerivativeLog
    variable = O2v2
  [../]

  [./O2v3_time_deriv]
    type = ODETimeDerivativeLog
    variable = O2v3
  [../]

  [./O2v4_time_deriv]
    type = ODETimeDerivativeLog
    variable = O2v4
  [../]

  [./O2a1_time_deriv]
    type = ODETimeDerivativeLog
    variable = O2a1
  [../]

  [./O2b1_time_deriv]
    type = ODETimeDerivativeLog
    variable = O2b1
  [../]

  [./O24_ev_time_deriv]
    type = ODETimeDerivativeLog
    variable = O24_ev
  [../]

  [./O_time_deriv]
    type = ODETimeDerivativeLog
    variable = O
  [../]

  [./O1D_time_deriv]
    type = ODETimeDerivativeLog
    variable = O1D
  [../]

  [./O1S_time_deriv]
    type = ODETimeDerivativeLog
    variable = O1S
  [../]

  [./O3_time_deriv]
    type = ODETimeDerivativeLog
    variable = O3
  [../]

  [./Op_time_deriv]
    type = ODETimeDerivativeLog
    variable = O+
  [../]

  [./O2p_time_deriv]
    type = ODETimeDerivativeLog
    variable = O2+
  [../]

  [./O4p_time_deriv]
    type = ODETimeDerivativeLog
    variable = O4+
  [../]

  [./Om_time_deriv]
    type = ODETimeDerivativeLog
    variable = O-
  [../]

  [./O2m_time_deriv]
    type = ODETimeDerivativeLog
    variable = O2-
  [../]

  [./O3m_time_deriv]
    type = ODETimeDerivativeLog
    variable = O3-
  [../]

  [./O4m_time_deriv]
    type = ODETimeDerivativeLog
    variable = O4-
  [../]

  [./NO_time_deriv]
    type = ODETimeDerivativeLog
    variable = NO
  [../]

  [./NOp_time_deriv]
    type = ODETimeDerivativeLog
    variable = NO+
  [../]

  [./NOm_time_deriv]
    type = ODETimeDerivativeLog
    variable = NO-
  [../]

  [./O2pN2_time_deriv]
    type = ODETimeDerivativeLog
    variable = O2pN2
  [../]
[]

[Debug]
  #show_var_residual_norms = true
[]

[AuxVariables]
  #[./e]
  #  order = FIRST
  #  family = SCALAR
  #  initial_condition = 1e12
  #[../]
  #[./N2]
  #  # Air is N2-O2 at ratio of 4:1
  #  order = FIRST
  #  family = SCALAR
  #  initial_condition = 1.834268645908762e19
  #[../]
  
  [./NEUTRAL]
    # For now, NEUTRAL = N2 + O2
    order = FIRST
    family = SCALAR
    #initial_condition = 2.445692e19
  [../]

  [./ION]
    order = FIRST
    family = SCALAR
  [../]

  [./reduced_field]
    # Units: Td
    order = FIRST
    family = SCALAR
    #initial_condition = 100
  [../]
  [./voltage]
    order = FIRST
    family = SCALAR
    # for testing purposes only
  [../]

  [./TionN]
    order = FIRST
    family = SCALAR
    #initial_condition = 300
    initial_condition = 1018.383
  [../]

  [./TionN2]
    order = FIRST
    family = SCALAR
    #initial_condition = 300
    initial_condition = 1018.383
  [../]

  [./TionN3]
    order = FIRST
    family = SCALAR
    #initial_condition = 300
    initial_condition = 1018.383
  [../]

  [./TionN4]
    order = FIRST
    family = SCALAR
    #initial_condition = 300
    initial_condition = 1018.383
  [../]

  [./TeffN]
    order = FIRST
    family = SCALAR
    #initial_condition = 300
    initial_condition = 778.875
  [../]

  [./TeffN2]
    order = FIRST
    family = SCALAR
    #initial_condition = 300
    initial_condition = 659.1565
  [../]

  [./TeffN3]
    order = FIRST
    family = SCALAR
    #initial_condition = 300
    initial_condition = 587.3252
  [../]

  [./TeffN4]
    order = FIRST
    family = SCALAR
    #initial_condition = 300 
    initial_condition = 539.438
  [../]
[]

[AuxScalarKernels]
  #[./field_calc]
  #  type = ParsedAuxScalar
  #  variable = reduced_field
  #  #constant_names = 'A d w p o'
  #  #constant_expressions = '13.204851149149514 1486789.8154186027 50149412.89498433 -1.2796011330163444 -0.54054816147437'
  #  #function = 'A * exp(-d*t) * sin(w*t + p) + o'
  #  #execute_on = 'timestep_begin'
  #  #function = '100 * exp(-t)'
  #  function = 'voltage_time'
  #[../]
  [./field_calc]
    type = FunctionScalarAux
    variable = reduced_field
    function = reduced_field_time
    execute_on = 'initial timestep_begin'
  [../]

  [./voltage_calc]
    type = FunctionScalarAux
    variable = voltage
    function = voltage_time
    execute_on = 'initial timestep_begin'
  [../]

  [./neutral_sum]
    type = VariableSumLog
    variable = NEUTRAL
    args = 'N2 O2 N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N2A3 N2B3 N2a_1 N2C3 N N2D N2P O2v1 O2v2 O2v3 O2v4 O2a1 O2b1 O24_ev O O1D O1S O3 NO'
    execute_on = 'initial linear nonlinear'
  [../]

  [./ion_sum]
    type = VariableSumLog
    variable = ION
    args = 'N+ N2+ N3+ N4+ O+ O2+ O4+ O- O2- O3- O4- NO+ NO- O2pN2'
    execute_on = 'initial timestep_end'
  [../]
[]

[Functions]
  [./test_func]
    # Voltage [kV] / gap distance [mm] * n_neutral * 1e-21 to convert to Td
    type = ParsedFunction
    # This value adds a damping factor so that it doesn't change so dramatically at the recurrence time
    vars = 'A d w p o Tr xoff'
    vals = '13.204851149149514 1486789.8154186027 50149412.89498433 -1.2796011330163444 -0.54054816147437 1e-4 40e-10'
    #value = 'abs((A * exp(-d*(t%Tr-xoff)) * sin(w*(t%Tr-xoff) + p*2.455))*tanh(8e6*(t%Tr-xoff)))*1e6 / 2.445692e4' 
    #value = 'abs((A * exp(-d*(t%Tr-xoff)) * sin(w*(t%Tr-xoff) - 6.08777077)))*1e6 / 2.445692e4' 
    value = '0.5 + 0.5*tanh(8e8*(t%Tr - 1e-9))' 

  [../]
  [./reduced_field_time]
    # Voltage [kV] / gap distance [mm] * n_neutral * 1e-21 to convert to Td
    type = ParsedFunction
    # Tr is the period of repitition 
    #vars = 'A d w p o Tr'
    ##vals = '13.204851149149514 1486789.8154186027 50149412.89498433 -1.2796011330163444 -0.54054816147437 5e-6'
    #vals = '13.204851149149514 1486789.8154186027 50149412.89498433 -1.2796011330163444 -0.54054816147437 1e-4'
    #value = 'abs(A * exp(-d*(t%Tr)) * sin(w*(t%Tr) + p*2.455))*1e6 / 2.445692e4' 
    ##value = '100'

    # This value adds a damping factor so that it doesn't change so dramatically at the recurrence time
    vars = 'A d w p o Tr xoff'
    vals = '13.204851149149514 1486789.8154186027 50149412.89498433 -1.2796011330163444 -0.54054816147437 1e-4 40e-10'
    #value = 'abs((A * exp(-d*(t%Tr-xoff)) * sin(w*(t%Tr-xoff) - 6.08777077)))*1e6 / 2.445692e4' 
    value = 'abs((A * exp(-d*(t%Tr-xoff)) * sin(w*(t%Tr-xoff) - 6.08777077))*(0.5 + 0.5*tanh(1e9*((t%Tr)-5e-9))))*1e6 / 2.445692e4' 

  [../]
  #[./reduced_field_time]
  #  # Voltage [kV] / gap distance [mm] * n_neutral * 1e-21 to convert to Td
  #  type = ParsedFunction
  #  # Tr is the period of repitition 
  #  vars = 'A d w p o Tr'
  #  vals = '13.204851149149514 1486789.8154186027 50149412.89498433 -1.2796011330163444 -0.54054816147437 5e-6'
  #  value = 'abs((A * exp(-d*(t%Tr)) * sin(w*(t%Tr) + p))*1e6 / 2.445692e4)' 
  #  #value = 'A * exp(-d*t) * sin(w*t + p) + o' # Voltage [kV] / gap distance [mm] * n_neutral * 1e-21 to convert to Td
  #[../]
  [./voltage_time]
    # Voltage [kV] / gap distance [mm] * n_neutral * 1e-21 to convert to Td
    type = ParsedFunction
    vars = 'A d w p o Tr'
    #vals = '13.204851149149514 1486789.8154186027 50149412.89498433 -1.2796011330163444 -0.54054816147437 5e-6'
    vals = '13.204851149149514 1486789.8154186027 50149412.89498433 -1.2796011330163444 -0.54054816147437 1e-4'
    value = 'A * exp(-d*(t%Tr)) * sin(w*(t%Tr) + p*2.455)' 
    #value = 'A * exp(-d*t) * sin(w*t + p) + o' # Voltage [kV] / gap distance [mm] * n_neutral * 1e-21 to convert to Td
  [../]
  [./dts]
    type = ParsedFunction
    vars = 'Tr'
    #vals = '5e-6'
    vals = '1e-4'
    #value = '1.699e-9*tanh(5e6*(t%Tr)) + 1e-12'
    #value = '0.9999e-8*tanh(1e5*(t%Tr)) + 1e-14'
    #value = '(0.9999e-8*tanh(1e5*(t%Tr)) + 1e-12) / (exp(6.2e32*(t%Tr)^8))'
    value = '(0.9999e-8*tanh(1e5*(t%Tr)) + 1e-11)*(1.0 - 0.999*(0.5 + 0.5*tanh((t%Tr - 0.9998e-4)/1e-8)))'
  [../]
[]

[Preconditioning]
  active = 'smp'
  [./smp]
    type = SMP
    full = true
  [../]
  [./fdp]
    type = FDP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  automatic_scaling = true
  compute_scaling_once = false
  end_time = 1e4
  line_search = 'basic'
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  #solve_type = PJFNK
  #solve_type = LINEAR
  #scheme = bdf2
  #[./TimeIntegrator]
  #  #type = ImplicitMidpoint  # Works, but max timestep is lower than ImplicitEuler
  #  #type = ActuallyExplicitEuler  # This one works, but only with dtmax = 1.1e-10
  #  type = NewmarkBeta  # Works, with maximum dt ~ 2.04002e-10 as of 0.1 us
  #                      # should check out different options 
  #[../]
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -snes_linesearch_minlambda -snes_stol'
  petsc_options_value = 'lu NONZERO 1.e-10 1e-3 0'
  # petsc_options_iname = '-pc_type -sub_pc_type'
  # petsc_options_value = 'asm lu'
  # petsc_options_iname = '-snes_type'
  # petsc_options_value = 'test'
  nl_rel_tol = 1e-8
  #nl_abs_tol = 1e3  # Note that abs_tol in this case refers to number density. 
  #nl_abs_tol = 1e-10
  #dtmin = 1e-13
  dtmin = 1e-40
  #dtmax = 1.1e-10
  #dtmax = 2e-9
  #dtmax = 1e-4
  l_max_its = 50
  num_steps = 10000
  #steady_state_detection = true
  #[./TimeStepper]
  #  type = IterationAdaptiveDT
  #  cutback_factor = 0.4
  #  dt = 1e-12
  #  # dt = 1.1
  #  growth_factor = 1.05
  #  optimal_iterations = 15
  #[../]
  [./TimeStepper]
    type = FunctionDT
    function = dts
    min_dt = 1e-12
  [../]
  #[./TimeStepper]
  #  type = DT2
  #  dt = 1e-12
  #  #dt = 1e-5
  #  e_max = 1e14
  #  e_tol = 1e10
  #[../]
  #[./TimeStepper]
  #  type = SolutionTimeAdaptiveDT
  #  dt = 1e-12
  #[../]
  #[./TimeStepper]
  #  type = AB2PredictorCorrector
  #  dt = 1e-12
  #  e_max = 1e9
  #  e_tol = 1
  #[../]
[]

[Outputs]
  csv = true
  #exodus = true
  #interval = 1
  #interval = 4
  #interval = 5
  #interval = 10
  #[./exodus]
  #  type = Exodus
  #  execute_scalars_on = 'INITIAL TIMESTEP_END'
  #  #scalar_as_nodal = true
  #[../]
  show = 'N N+ N2 N2+ N2A3 N2B3 N2C3 N2D N2P N2a_1 N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N3+ N4+ NO NO+ NO- O O+ O- O1D O1S O2 O2+ O2- O24_ev O2a1 O2b1 O2v1 O2v2 O2v3 O2v4 O3 O3- O4+ O4- O2pN2 NEUTRAL e reduced_field'
  [./console]
    type = Console
    execute_scalars_on = 'none'
    # execute_on = 'initial'
  [../]
[]

[ChemicalReactions]
  [./ScalarNetwork]
    species = 'N2 N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N2A3 N2B3 N2a_1 N2C3 N N2D N2P N+ N2+ N3+ N4+ O2 O2v1 O2v2 O2v3 O2v4 O2a1 O2b1 O24_ev O O1D O1S O3 O+ O2+ O4+ O- O2- O3- O4- NO N2O NO2 NO3 N2O5 NO+ N2O+ NO2+ NO- N2O- NO2- NO3- O2pN2 e'
    aux_species = 'NEUTRAL'
    use_log = true
    #species = 'N2 N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N2A3 N2B3 N2a_1 N2C3 N N2D N2P N+ N2+ N3+ N4+ O2 O2v1 O2v2 O2v3 O2v4 O2a1 O2b1 O24_ev O O1D O1S O3 O+ O2+ O4+ O- O2- O3- O4- NO N2O NO2 NO3 N2O5 NO+ N2O+ NO2+ NO- N2O- NO2- NO3- O2pN2'
    #aux_species = 'NEUTRAL e'
    #aux_species = 'e'
    reaction_coefficient_format = 'rate'
    include_electrons = true
    file_location = 'air_test'
    electron_density = 'e'
    equation_variables = 'TeffN TeffN2 TeffN3 TeffN4 TionN TionN2 TionN3 TionN4'
    equation_constants = 'Te Tgas'
    #equation_values = '4 300'
    equation_values = '32480 300'
    rate_provider_var = 'reduced_field'
    #lumped_species = true
    #lumped = 'N2 O2 N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N2A3 N2B3 N2a_1 N2C3 N N2D N2P O2v1 O2v2 O2v3 O2v4 O2a1 O2b1 O24_ev O O1D O1S O3 NO'
    #lumped_name = 'NEUTRAL'
    track_rates = false

    # NOTE: rate coefficients units are cm^3 s^-1
    #reactions = 'e + N2 -> e + N2v1                 : EEDF (C2_N2_Excitation_0.29_eV)
    reactions = 'e + N2 -> e + N2v1                 : EEDF (C2_N2_Excitation_0.0000_eV)
                 e + N2 -> e + N2v1                 : EEDF (C3_N2_Excitation_0.29_eV) 
                 e + N2 -> e + N2v2                 : EEDF (C4_N2_Excitation_0.59_eV)
                 e + N2 -> e + N2v3                 : EEDF (C5_N2_Excitation_0.88_eV)
                 e + N2 -> e + N2v4                 : EEDF (C6_N2_Excitation_1.17_eV)
                 e + N2 -> e + N2v5                 : EEDF (C7_N2_Excitation_1.47_eV)
                 e + N2 -> e + N2v6                 : EEDF (C8_N2_Excitation_1.76_eV)
                 e + N2 -> e + N2v7                 : EEDF (C9_N2_Excitation_2.06_eV)
                 e + N2 -> e + N2v8                 : EEDF (C10_N2_Excitation_2.35_eV)
                 e + N2v1 -> e + N2                 : EEDF (C40_N2v1_De-excitation_0.29_eV)
                 e + N2v2 -> e + N2                 : EEDF (C41_N2v2_De-excitation_0.59_eV)
                 e + N2v3 -> e + N2                 : EEDF (C42_N2v3_De-excitation_0.88_eV)
                 e + N2v4 -> e + N2                 : EEDF (C43_N2v4_De-excitation_1.17_eV)
                 e + N2v5 -> e + N2                 : EEDF (C44_N2v5_De-excitation_1.47_eV)
                 e + N2v6 -> e + N2                 : EEDF (C45_N2v6_De-excitation_1.76_eV)
                 e + N2v7 -> e + N2                 : EEDF (C46_N2v7_De-excitation_2.06_eV)
                 e + N2v8 -> e + N2                 : EEDF (C47_N2v8_De-excitation_2.35_eV)
                 e + O2 -> e + O2v1                 : EEDF (C27_O2_Excitation_0.19_eV)
                 e + O2 -> e + O2v1                 : EEDF (C28_O2_Excitation_0.19_eV)
                 e + O2 -> e + O2v2                 : EEDF (C29_O2_Excitation_0.38_eV)
                 e + O2 -> e + O2v2                 : EEDF (C30_O2_Excitation_0.38_eV)
                 e + O2 -> e + O2v3                 : EEDF (C31_O2_Excitation_0.57_eV)
                 e + O2 -> e + O2v4                 : EEDF (C32_O2_Excitation_0.75_eV)
                 e + O2v1 -> e + O2                 : EEDF (C51_O2v1_De-excitation_0.19_eV)
                 e + O2v2 -> e + O2                 : EEDF (C52_O2v2_De-excitation_0.38_eV)
                 e + O2v3 -> e + O2                 : EEDF (C53_O2v3_De-excitation_0.57_eV)
                 e + O2v4 -> e + O2                 : EEDF (C54_O2v4_De-excitation_0.75_eV)
                 ######
                 # Vibrational-translational relaxation (Capitelli2000, page 105)
                 ######
                 N2v1 + N2 -> N2 + N2               : {7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas))}
                 N2v2 + N2 -> N2v1 + N2             : {2.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas))}
                 N2v3 + N2 -> N2v2 + N2             : {3.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas))}
                 N2v4 + N2 -> N2v3 + N2             : {4.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas))}
                 N2v5 + N2 -> N2v4 + N2             : {5.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas))}
                 N2v6 + N2 -> N2v5 + N2             : {6.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas))}
                 N2v7 + N2 -> N2v6 + N2             : {7.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas))}
                 N2v8 + N2 -> N2v7 + N2             : {8.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas))}
                 N2 + N2 -> N2v1 + N2               : {7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas)) * exp(-0.29*11605/Tgas)}
                 N2v1 + N2 -> N2v2 + N2             : {2.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas)) * exp(-0.29*11605/Tgas)}
                 N2v2 + N2 -> N2v3 + N2             : {3.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas)) * exp(-0.29*11605/Tgas)}
                 N2v3 + N2 -> N2v4 + N2             : {4.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas)) * exp(-0.29*11605/Tgas)}
                 N2v4 + N2 -> N2v5 + N2             : {5.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas)) * exp(-0.29*11605/Tgas)}
                 N2v5 + N2 -> N2v6 + N2             : {6.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas)) * exp(-0.29*11605/Tgas)}
                 N2v6 + N2 -> N2v7 + N2             : {7.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas)) * exp(-0.29*11605/Tgas)}
                 N2v7 + N2 -> N2v8 + N2             : {8.0 * 7.8e-12 * Tgas * exp(-218.0 / Tgas^(1./3.) + 690. / Tgas) / (1.0 - exp(-0.290*11605/Tgas)) * exp(-0.29*11605/Tgas)}
                 N2v1 + N -> N2 + N                 : {4.0e-16 * (Tgas / 300.0)^0.5}
                 N2v2 + N -> N2v1 + N               : {2.0 * 4.0e-16 * (Tgas / 300.0)^0.5}
                 N2v3 + N -> N2v2 + N               : {3.0 * 4.0e-16 * (Tgas / 300.0)^0.5}
                 N2v4 + N -> N2v3 + N               : {4.0 * 4.0e-16 * (Tgas / 300.0)^0.5}
                 N2v5 + N -> N2v4 + N               : {5.0 * 4.0e-16 * (Tgas / 300.0)^0.5}
                 N2v6 + N -> N2v5 + N               : {6.0 * 4.0e-16 * (Tgas / 300.0)^0.5}
                 N2v7 + N -> N2v6 + N               : {7.0 * 4.0e-16 * (Tgas / 300.0)^0.5}
                 N2v8 + N -> N2v7 + N               : {8.0 * 4.0e-16 * (Tgas / 300.0)^0.5}
                 N2 + N -> N2v1 + N                 : {4.0e-16 * (Tgas / 300.0)^0.5 * exp(-0.29*11605.0)}
                 N2v1 + N -> N2v2 + N               : {2.0 * 4.0e-16 * (Tgas / 300.0)^0.5 * exp(-0.29*11605.0)}
                 N2v2 + N -> N2v3 + N               : {3.0 * 4.0e-16 * (Tgas / 300.0)^0.5 * exp(-0.29*11605.0)}
                 N2v3 + N -> N2v4 + N               : {4.0 * 4.0e-16 * (Tgas / 300.0)^0.5 * exp(-0.29*11605.0)}
                 N2v4 + N -> N2v5 + N               : {5.0 * 4.0e-16 * (Tgas / 300.0)^0.5 * exp(-0.29*11605.0)}
                 N2v5 + N -> N2v6 + N               : {6.0 * 4.0e-16 * (Tgas / 300.0)^0.5 * exp(-0.29*11605.0)}
                 N2v6 + N -> N2v7 + N               : {7.0 * 4.0e-16 * (Tgas / 300.0)^0.5 * exp(-0.29*11605.0)}
                 N2v7 + N -> N2v8 + N               : {8.0 * 4.0e-16 * (Tgas / 300.0)^0.5 * exp(-0.29*11605.0)}
                 N2v1 + O -> N2 + O                 : {1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0))}
                 N2v2 + O -> N2v1 + O               : {2.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0))}
                 N2v3 + O -> N2v2 + O               : {3.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0))}
                 N2v4 + O -> N2v3 + O               : {4.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0))}
                 N2v5 + O -> N2v4 + O               : {5.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0))}
                 N2v6 + O -> N2v5 + O               : {6.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0))}
                 N2v7 + O -> N2v6 + O               : {7.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0))}
                 N2v8 + O -> N2v7 + O               : {8.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0))}
                 N2 + O -> N2v1 + O                 : {1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0)) * exp(-0.28*11605.0)}
                 N2v1 + O -> N2v2 + O               : {2.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0)) * exp(-0.28*11605.0)}
                 N2v2 + O -> N2v3 + O               : {3.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0)) * exp(-0.28*11605.0)}
                 N2v3 + O -> N2v4 + O               : {4.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0)) * exp(-0.28*11605.0)}
                 N2v4 + O -> N2v5 + O               : {5.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0)) * exp(-0.28*11605.0)}
                 N2v5 + O -> N2v6 + O               : {6.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0)) * exp(-0.28*11605.0)}
                 N2v6 + O -> N2v7 + O               : {7.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0)) * exp(-0.28*11605.0)}
                 N2v7 + O -> N2v8 + O               : {8.0 * 1.20e-13 * exp( - 27.6 / Tgas^(1.0/3.0)) * exp(-0.28*11605.0)}
                 O2v1 + O2 -> O2 + O2               : {1.35e-12 * Tgas * exp( - 137.9 / Tgas^(1.0/3.0) ) / ( 1.0 - exp(-0.19*11605.0) )}
                 O2v2 + O2 -> O2v1 + O2             : {2.0 * 1.35e-12 * Tgas * exp( - 137.9 / Tgas^(1.0/3.0) ) / ( 1.0 - exp(-0.19*11605.0) )}
                 O2v3 + O2 -> O2v2 + O2             : {3.0 * 1.35e-12 * Tgas * exp( - 137.9 / Tgas^(1.0/3.0) ) / ( 1.0 - exp(-0.19*11605.0) )}
                 O2v4 + O2 -> O2v3 + O2             : {4.0 * 1.35e-12 * Tgas * exp( - 137.9 / Tgas^(1.0/3.0) ) / ( 1.0 - exp(-0.19*11605.0) )}
                 O2 + O2 -> O2v1 + O2               : {1.35e-12 * Tgas * exp( - 137.9 / Tgas^(1.0/3.0) ) / ( 1.0 - exp(-0.19*11605.0) ) * exp(-0.19 * 11605)}
                 O2v1 + O2 -> O2v2 + O2             : {2.0 * 1.35e-12 * Tgas * exp( - 137.9 / Tgas^(1.0/3.0) ) / ( 1.0 - exp(-0.19*11605.0) ) * exp(-0.19 * 11605)}
                 O2v2 + O2 -> O2v3 + O2             : {3.0 * 1.35e-12 * Tgas * exp( - 137.9 / Tgas^(1.0/3.0) ) / ( 1.0 - exp(-0.19*11605.0) ) * exp(-0.19 * 11605)}
                 O2v3 + O2 -> O2v4 + O2             : {4.0 * 1.35e-12 * Tgas * exp( - 137.9 / Tgas^(1.0/3.0) ) / ( 1.0 - exp(-0.19*11605.0) ) * exp(-0.19 * 11605)}
                 O2v1 + O -> O2 + O                 : {4.5e-15 * Tgas * exp(-0.19 * 11605)}
                 O2v2 + O -> O2v1 + O               : {2.0 * 4.5e-15 * Tgas * exp(-0.19 * 11605)}
                 O2v3 + O -> O2v2 + O               : {3.0 * 4.5e-15 * Tgas * exp(-0.19 * 11605)}
                 O2v4 + O -> O2v3 + O               : {4.0 * 4.5e-15 * Tgas * exp(-0.19 * 11605)}
                 O2 + O -> O2v1 + O                 : {4.5e-15 * Tgas * exp(-0.19 * 11605)}
                 O2v1 + O -> O2v2 + O               : {2.0 * 4.5e-15 * Tgas * exp(-0.19 * 11605)}
                 O2v2 + O -> O2v3 + O               : {3.0 * 4.5e-15 * Tgas * exp(-0.19 * 11605)}
                 O2v3 + O -> O2v4 + O               : {4.0 * 4.5e-15 * Tgas * exp(-0.19 * 11605)}
                 #####
                 # excitation of electronic levels by electron impact (Bolsig+)
                 # Note that CRANE will need to be modified to allow duplicate reactions here...
                 #####
                 e + N2 -> e + N2A3                 : EEDF (C11_N2_Excitation_6.17_eV)
                 e + N2 -> e + N2A3                 : EEDF (C12_N2_Excitation_7.00_eV)
                 e + N2 -> e + N2A3                 : EEDF (C13_N2_Excitation_7.80_eV)
                 e + N2 -> e + N2B3                 : EEDF (C14_N2_Excitation_7.35_eV)
                 e + N2 -> e + N2B3                 : EEDF (C15_N2_Excitation_7.36_eV)
                 e + N2 -> e + N2B3                 : EEDF (C16_N2_Excitation_8.16_eV)
                 e + N2 -> e + N2a_1                : EEDF (C17_N2_Excitation_8.40_eV)
                 e + N2 -> e + N2a_1                : EEDF (C18_N2_Excitation_8.55_eV)
                 e + N2 -> e + N2a_1                : EEDF (C19_N2_Excitation_8.89_eV)
                 e + N2 -> e + N2C3                 : EEDF (C20_N2_Excitation_11.03_eV)
                 e + N2 -> e + N2C3                 : EEDF (C21_N2_Excitation_11.87_eV)
                 e + N2 -> e + N2C3                 : EEDF (C22_N2_Excitation_12.25_eV)
                 e + N2 -> e + N + N2D              : EEDF (C23_N2_Excitation_13.00_eV)
                 e + O2 -> e + O2a1                 : EEDF (C33_O2_Excitation_0.98_eV)
                 e + O2 -> e + O2b1                 : EEDF (C34_O2_Excitation_1.63_eV)
                 e + O2 -> e + O24_ev               : EEDF (C35_O2_Excitation_4.50_eV)
                 e + O2 -> e + O + O                : EEDF (C36_O2_Excitation_6.00_eV)
                 e + O2 -> e + O + O1D              : EEDF (C37_O2_Excitation_8.40_eV)
                 e + O2 -> e + O + O1S              : EEDF (C38_O2_Excitation_9.97_eV)
                 e + O2a1 -> e + O + O              : EEDF (C58_O2a1_Excitation_6.00_eV)
                 e + O -> e + O1D                   : EEDF (C63_O_Excitation_1.97_eV)
                 e + O -> e + O1S                   : EEDF (C64_O_Excitation_4.19_eV)
                 ####
                 # de-excitation of electronic levels by electron impact (BOLSIG+)
                 ####
                 e + N2A3 -> e + N2                 : EEDF (C48_N2A3_De-excitation_6.17_eV)
                 e + O2a1 -> e + O2                : EEDF (C55_O2a1_De-excitation_0.98_eV)
                 ####
                 # ionization by electron impact (BOLSIG+)
                 # note the missing data section in the inp file (4 extra reactions - not shown here)
                 ####
                 e + N -> e + e + N+                : EEDF (C61_N_Ionization_14.55_eV)
                 e + O -> e + e + O+                : EEDF (C65_O_Ionization_13.62_eV)
                 e + N2 -> e + e + N2+              : EEDF (C24_N2_Ionization_15.60_eV)
                 e + N2A3 -> e + e + N2+            : EEDF (C50_N2A3_Ionization_10.79_eV)
                 e + O2 -> e + e + O2+              : EEDF (C39_O2_Ionization_12.06_eV)
                 e + O2a1 -> e + e + O2+            : EEDF (C59_O2a1_Ionization_11.00_eV)
                 e + NO -> e + e + NO+              : EEDF (C75_NO_Ionization_9.26_eV)
                 ####
                 # electron-ion recombination
                 ####
                 e + N2+ -> N + N                   : {1.8e-7 * (300/Te)^0.39 * 0.5}
                 e + N2+ -> N + N2D                 : {1.8e-7 * (300/Te)^0.39 * 0.45}
                 e + N2+ -> N + N2P                 : {1.8e-7 * (300/Te)^0.39 * 0.05}
                 e + O2+ -> O + O                   : {2.7e-7 * (300/Te)^0.7 * 0.55}
                 e + O2+ -> O + O1D                 : {2.7e-7 * (300/Te)^0.7 * 0.40}
                 e + O2+ -> O + O1S                 : {2.7e-7 * (300/Te)^0.7 * 0.05}
                 e + NO+ -> O + N                   : {4.2e-7 * (300/Te)^0.85 * 0.2}
                 e + NO+ -> O + N2D                 : {4.2e-7 * (300/Te)^0.85 * 0.8}
                 e + N3+ -> N2 + N                  : {2.0e-7 * (300/Te)^0.5}
                 e + N4+ -> N2 + N2                 : {2.3e-6 * (300/Te)^0.53}
                 e + O4+ -> O2 + O2                 : {1.4e-6 * (300/Te)^0.5}
                 e + O2pN2 -> O2 + N2               : {1.3e-6 * (300/Te)^0.5}
                 e + e + N+ -> N + e                    : {7.0e-20 * (300/Te)^4.5}
                 e + e + O+ -> O + e                    : {7.0e-20 * (300/Te)^4.5}
                 e + N+ + NEUTRAL -> N + NEUTRAL    : {6.0e-27 * (300/Te)^1.5}
                 e + O+ + NEUTRAL -> O + NEUTRAL    : {6.0e-27 * (300/Te)^1.5}
                 ####
                 # electron attachment
                 # e + O2 + O2 -> O2- + O2              : EEDF (
                 # ^ Not sure what to do with this one. Never seen anything like it before.
                 ####
                 e + O2 -> O- + O                     : EEDF (C25_O2_Attachment)
                 e + NO -> O- + N                     : EEDF (C66_NO_Attachment)
                 e + O3 -> O- + O2                    : EEDF (C76_O3_Attachment)
                 e + O3 -> O2- + O                    : EEDF (C77_O3_Attachment)
                 e + O + O2 -> O- + O2                : 1e-31
                 e + O + O2 -> O2- + O                : 1e-31
                 e + O3 + NEUTRAL -> O3- + NEUTRAL    : 1e-31
                 e + NO + NEUTRAL -> NO- + NEUTRAL    : 1e-31
                 e + O2 + N2 -> O2- + N2              : {1.1e-31 * (300/Te)^2 * exp(-70/Tgas) * exp(1500*(Te-Tgas)/(Te*Tgas))}
                 ####
                 # electron detachment
                 ####
                 O-  + O -> O2  + e                   : 1.4e-10
                 O-  + N -> NO  + e                   : 2.6e-10
                 O-  + O2 -> O3  + e                  : 5.0e-15
                 O-  + O2a1 -> O3  + e                : 3.0e-10
                 O-  + O2b1 -> O   + O2 + e           : 6.9e-10
                 O-  + N2A3 -> O   + N2 + e           : 2.2e-9
                 O-  + N2B3 -> O   + N2 + e           : 1.9e-9
                 O-  + O3 -> O2  + O2 + e             : 3.0e-10
                 O2- + O -> O3  + e                   : 1.5e-10
                 O2- + O2 -> O2  + O2 + e             : {2.7e-10 * (TeffN2/300)^0.5 * exp(-5590/TeffN2)}
                 O2- + O2a1 -> O2  + O2 + e           : 2.0e-10
                 O2- + O2b1 -> O2  + O2 + e           : 3.6e-10
                 O2- + N2 -> O2  + N2 + e             : {1.9e-12 * (TeffN2/300)^0.5 * exp(-4990/TeffN2)}
                 O2- + N2A3 -> O2  + N2 + e           : 2.1e-9
                 O2- + N2B3 -> O2  + N2 + e           : 2.5e-9
                 O3- + O -> O2  + O2 + e              : 3.0e-10
                 ####
                 # Detachment for O3- NO- N2O- NO2- NO3- has to be verified (from inp source file)
                 ####
                 O3- + N -> NO + O2 + e               : 5e-10
                 O3- + N2A3 -> O3 + N2 + e            : 2.1e-9
                 NO- + N2A3 -> NO + N2 + e            : 2.1e-9
                 O3- + N2B3 -> O3 + N2 + e            : 2.5e-9
                 NO- + N2B3 -> NO + N2 + e            : 2.5e-9
                 ####
                 # optical transitions and predissociation (Capitelli2000, page 157)
                 ####
                 N2A3 -> N2                           : 0.5 
                 N2B3 -> N2A3                         : 1.34e5
                 N2a_1 -> N2                          : 1e2
                 N2C3 -> N2B3                         : 2.45e7
                 O2a1 -> O2                           : 2.6e-4
                 O2b1 -> O2a1                         : 1.5e-3
                 O2b1 -> O2                           : 8.5e-2
                 O24_ev -> O2                         : 11
                 ####
                 # quenching and excitation of N2 (Capitelli2000, page 159)
                 ####
                 N2A3 + O -> NO + N2D                 : 7e-12
                 N2A3 + O -> NO + O1S                 : 2.1e-11
                 N2A3 + N -> N2 + N                   : 2e-12
                 N2A3 + N -> N2 + N2P                 : {4.0e-11 * (300/Tgas)^0.667}
                 N2A3 + O2 -> N2 + O + O1D            : {2.1e-12 * (Tgas/300)^0.55}
                 N2A3 + O2 -> N2 + O2a1               : {2.0e-13 * (Tgas/300)^0.55}
                 N2A3 + O2 -> N2 + O2b1               : {2.0e-13 * (Tgas/300)^0.55}
                 N2A3 + N2 -> N2 + N2                 : 3e-16 
                 N2A3 + NO -> N2 + NO                 : 6.9e-11
                 N2A3 + N2A3 -> N2 + N2B3             : 3e-10
                 N2A3 + N2A3 -> N2 + N2C3             : 1.5e-10
                 N2B3 + N2 -> N2A3 + N2               : 3e-11
                 N2B3 + N2 -> N2 + N2                 : 2e-12
                 N2B3 + O2 -> N2 + O + O              : 3e-10
                 N2B3 + NO -> N2A3 + NO               : 2.4e-10
                 N2C3 + N2 -> N2a_1 + N2              : 1e-11
                 N2C3 + O2 -> N2 + O + O1S            : 3e-10
                 N2a_1 + N2 -> N2B3 + N2              : 1.93e-13
                 N2a_1 + O2 -> N2 + O + O             : 2.8e-11
                 N2a_1 + NO -> N2 + N + O             : 3.6e-10
                 N2a_1 + N2A3 -> N4+ + e              : 4e-12
                 N2a_1 + N2a_1 -> N4+ + e             : 1e-11
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
                 N2D + O -> N + O1D                   : 4e-13
                 N2D + O2 -> NO + O                   : 5.2e-12
                 N2D + NO -> N2 + O                   : 1.8e-10
                 N2D + N2 -> N + N2                   : {1.0e-13 * exp(-510/Tgas)}
                 N2P + N -> N + N                     : 1.8e-12
                 N2P + O -> N + O                     : 1.0e-12
                 N2P + N -> N2D + N                   : 6.0e-13
                 N2P + N2 -> N + N2                   : 6.0e-14
                 N2P + N2D -> N2+ + e                 : 1.0e-13
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
                 O2a1 + O3 -> O2 + O2 + O1D           : {5.2e-11 * exp(-2840/Tgas)}
                 O2a1 + O2a1 -> O2 + O2b1             : {7.0e-28 * Tgas^3.8 * exp(700/Tgas)}
                 O + O3 -> O2 + O2a1                  : {1.0e-11 * exp(-2300/Tgas)}
                 O2b1 + O -> O2a1 + O                 : 8.1e-14
                 O2b1 + O -> O2 + O1D                 : {3.4e-11 * (300/Tgas)^0.1 * exp(-4200/Tgas)}
                 O2b1 + O2 -> O2a1 + O2               : {4.3e-22 * Tgas^2.4 * exp(-281/Tgas)}
                 O2b1 + N2 -> O2a1 + N2               : {1.7e-15 * (Tgas/300)}
                 O2b1 + NO -> O2a1 + NO               : 6.0e-14
                 O2b1 + O3 -> O2 + O2 + O             : 2.2e-11
                 O24_ev + O -> O2 + O1S               : 9.0e-12
                 O24_ev + O2 -> O2b1 + O2b1           : 3.0e-13
                 O24_ev + N2 -> O2b1 + N2             : 9.0e-15
                 ####
                 # deactivation of O metastables (Capitelli2000, page 161)
                 ####
                 O1D + O -> O + O                     : 8.0e-12
                 O1D + O2 -> O + O2                   : {6.4e-12 * exp(67/Tgas)}
                 O1D + O2 -> O + O2a1                 : 1.0e-12
                 O1D + O2 -> O + O2b1                 : {2.6e-11 * exp(67/Tgas)}
                 O1D + N2 -> O + N2                   : 2.3e-11
                 O1D + O3 -> O2 + O + O               : 1.2e-10
                 O1D + O3 -> O2 + O2                  : 1.2e-10
                 O1D + NO -> O2 + N                   : 1.7e-10
                 O1S + O -> O1D + O                   : 5.0e-11 * exp(-300/Tgas)}
                 O1S + N -> O + N                     : 1.0e-12
                 O1S + O2 -> O1D + O2                 : {1.3e-12 * exp(-850/Tgas)}
                 O1S + O2 -> O + O + O                : {3.0e-12 * exp(-850/Tgas)}
                 O1S + N2 -> O + N2                   : 1.0e-17
                 O1S + O2a1 -> O + O24_ev             : 1.1e-10
                 O1S + O2a1 -> O1D + O2b1             : 2.9e-11
                 O1S + O2a1 -> O + O + O              : 3.2e-11
                 O1S + NO -> O + NO                   : 2.9e-10
                 O1S + NO -> O1D + NO                 : 5.1e-10
                 O1S + O3 -> O2 + O2                  : 2.9e-10
                 O1S + O3 -> O2 + O + O1D             : 2.9e-10
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
                 N + N -> N2+ + e                     : {2.7e-11 * exp(-6.74e4/Tgas)}
                 N + O -> NO+ + e                     : {1.6e-12 * (Tgas/300)^0.5 * (0.19+8.6*Tgas) * exp(-32000/Tgas)}
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
                 N4+ + N2 -> N2+ + N2 + N2                        : 1.0e-10
                 N4+ + O2 -> O2+ + N2 + N2                        : 2.5e-10
                 N4+ + O  -> O+ + N2 + N2                         : 2.5e-10
                 N4+ + N  -> N+ + N2 + N2                         : 1.0e-11
                 N4+ + NO -> NO+ + N2 + N2                        : 4.0e-10
                 O4+ + N2 -> O2pN2 + O2                           : {4.6e-12 * (TeffN4/300)^2.5 * exp(-2650/TeffN4)}
                 O4+ + O2 -> O2+ + O2 + O2                        : {3.3e-6  * (300/TeffN4)^4   * exp(-5030/TeffN4)}
                 O4+ + O2a1 -> O2+ + O2 + O2                      : 1.0e-10
                 O4+ + O2b1 -> O2+ + O2 + O2                      : 1.0e-10
                 O4+ + O      -> O2+ + O3                         : 3.0e-10
                 O4+ + NO     -> NO+ + O2 + O2                    : 1.0e-10
                 O2pN2 + N2 -> O2+ + N2 + N2                      : {1.1e-6 * (300/TeffN4)^5.3 * exp(-2360/TeffN4)}
                 O2pN2 + O2 -> O4+ + N2                           : 1.0e-9
                 N+ + N2 + N2 -> N3+ + N2                         : {1.7e-29 * (300/TeffN)^2.1}
                 N+ + O + NEUTRAL -> NO+ + NEUTRAL        : 1.0e-29
                 N+ + N + NEUTRAL -> N2+ + NEUTRAL        : 1.0e-29
                 O+ + N2 + NEUTRAL -> NO+ + N + NEUTRAL   : {6.0e-29 * (300/TeffN)^2}
                 O+ + O  + NEUTRAL -> O2+ + NEUTRAL       : 1.0e-29
                 O+ + N  + NEUTRAL -> NO+ + NEUTRAL       : 1.0e-29
                 N2+ + N2 + N2 -> N4+ + N2                        : {5.2e-29 * (300/TeffN2)^2.2}
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
                 O4- + N2 -> O2- + O2 + N2                        : {1.0e-10 * exp(-1044/TeffN4)}
                 O4- + O2 -> O2- + O2 + O2                        : {1.0e-10 * exp(-1044/TeffN4)}
                 O4- + O -> O3-  + O2                             : 4.0e-10
                 O4- + O -> O-   + O2  + O2                       : 3.0e-10
                 O4- + O2a1 -> O2-  + O2  + O2                    : 1.0e-10
                 O4- + O2b1 -> O2-  + O2  + O2                    : 1.0e-10
                 O-  + O2 + NEUTRAL -> O3- + NEUTRAL      : {1.1e-30 * (300./TeffN)}
                 O2- + O2 + NEUTRAL -> O4- + NEUTRAL      : {3.5e-31 * (300./TeffN2)}
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
                 O- + N4+ -> O + N2 + N2                            : 1e-7
                 O- + O2+ -> O + O + O                              : 1e-7
                 O- + O4+ -> O + O2 + O2                            : 1e-7
                 O- + NO+ -> O + N + O                              : 1e-7
                 O- + O2pN2 -> O + O2 + N2                          : 1e-7
                 O2- + N2+ -> O2 + N + N                              : 1e-7
                 O2- + N3+ -> O2 + N + N2                             : 1e-7
                 O2- + N4+ -> O2 + N2 + N2                            : 1e-7
                 O2- + O2+ -> O2 + O + O                              : 1e-7
                 O2- + O4+ -> O2 + O2 + O2                            : 1e-7
                 O2- + NO+ -> O2 + N + O                              : 1e-7
                 O2- + O2pN2 -> O2 + O2 + N2                          : 1e-7
                 O3- + N2+ -> O3 + N + N                              : 1e-7
                 O3- + N3+ -> O3 + N + N2                             : 1e-7
                 O3- + N4+ -> O3 + N2 + N2                            : 1e-7
                 O3- + O2+ -> O3 + O + O                              : 1e-7
                 O3- + O4+ -> O3 + O2 + O2                            : 1e-7
                 O3- + NO+ -> O3 + N + O                              : 1e-7
                 O3- + O2pN2 -> O3 + O2 + N2                          : 1e-7
                 NO- + N2+ -> NO + N + N                              : 1e-7
                 NO- + N3+ -> NO + N + N2                             : 1e-7
                 NO- + N4+ -> NO + N2 + N2                            : 1e-7
                 NO- + O2+ -> NO + O + O                              : 1e-7
                 NO- + O4+ -> NO + O2 + O2                            : 1e-7
                 NO- + NO+ -> NO + N + O                              : 1e-7
                 NO- + O2pN2 -> NO + O2 + N2                          : 1e-7
                 O4- + N+ -> O2 + O2 + N                              : 1e-7 
                 O4- + N2+ -> O2 + O2 + N2                            : 1e-7 
                 O4- + O+ -> O2 + O2 + O                              : 1e-7 
                 O4- + O2+ -> O2 + O2 + O2                            : 1e-7 
                 O4- + NO+ -> O2 + O2 + NO                            : 1e-7 
                 O4- + N3+ -> O2 + O2 + N2 + N                        : 1e-7 
                 O4- + N4+ -> O2 + O2 + N2 + N2                       : 1e-7 
                 O4- + O4+ -> O2 + O2 + O2 + O2                       : 1e-7 
                 O4- + O2pN2 -> O2 + O2 + O2 + N2                     : 1e-7 
                 O- + N+ + NEUTRAL -> O + N + NEUTRAL                 : {2e-25 * (300/TionN)^2.5}
                 O- + N2+ + NEUTRAL -> O + N2 + NEUTRAL               : {2e-25 * (300/TionN)^2.5}
                 O- + O+ + NEUTRAL -> O + O + NEUTRAL                 : {2e-25 * (300/TionN)^2.5}
                 O- + O2+ + NEUTRAL -> O + O2 + NEUTRAL               : {2e-25 * (300/TionN)^2.5}
                 O- + NO+ + NEUTRAL -> O + NO + NEUTRAL               : {2e-25 * (300/TionN)^2.5}
                 O2- + N+ + NEUTRAL -> O2 + N + NEUTRAL               : {2e-25 * (300/TionN)^2.5}
                 O2- + N2+ + NEUTRAL -> O2 + N2 + NEUTRAL             : {2e-25 * (300/TionN)^2.5}
                 O2- + O+ + NEUTRAL -> O2 + O + NEUTRAL               : {2e-25 * (300/TionN)^2.5}
                 O2- + O2+ + NEUTRAL -> O2 + O2 + NEUTRAL             : {2e-25 * (300/TionN)^2.5}
                 O2- + NO+ + NEUTRAL -> O2 + NO + NEUTRAL             : {2e-25 * (300/TionN)^2.5}
                 O- + N+ + NEUTRAL -> NO + NEUTRAL                    : {2e-25 * (300/TionN)^2.5}
                 O- + O+ + NEUTRAL -> O2 + NEUTRAL                    : {2e-25 * (300/TionN)^2.5}
                 O- + O2+ + NEUTRAL -> O3 + NEUTRAL                   : {2e-25 * (300/TionN)^2.5}
                 O2- + O+ + NEUTRAL -> O3 + NEUTRAL                   : {2e-25 * (300/TionN)^2.5}
                 ####
                 # Three-body recombination of O3- NO- N2O- NO2- NO3- has to be verified
                 ####
                 O3- + N+ + NEUTRAL -> O3 + N + NEUTRAL               : {2e-25 * (300/TionN2)^2.5}
                 O3- + N2+ + NEUTRAL -> O3 + N2 + NEUTRAL             : {2e-25 * (300/TionN2)^2.5}
                 O3- + O+ + NEUTRAL -> O3 + O + NEUTRAL               : {2e-25 * (300/TionN2)^2.5}
                 O3- + O2+ + NEUTRAL -> O3 + O2 + NEUTRAL             : {2e-25 * (300/TionN2)^2.5}
                 O3- + NO+ + NEUTRAL -> O3 + NO + NEUTRAL             : {2e-25 * (300/TionN2)^2.5}
                 NO- + N+ + NEUTRAL -> NO + N + NEUTRAL               : {2e-25 * (300/TionN2)^2.5}
                 NO- + N2+ + NEUTRAL -> NO + N2 + NEUTRAL             : {2e-25 * (300/TionN2)^2.5}
                 NO- + O+ + NEUTRAL -> NO + O + NEUTRAL               : {2e-25 * (300/TionN2)^2.5}
                 NO- + O2+ + NEUTRAL -> NO + O2 + NEUTRAL             : {2e-25 * (300/TionN2)^2.5}
                 NO- + NO+ + NEUTRAL -> NO + NO + NEUTRAL             : {2e-25 * (300/TionN2)^2.5}'
                 
  [../]
[]
