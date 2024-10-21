[GlobalParams]
  use_moles = true
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
    #initial_condition = 6e5
    initial_condition = 1e18
    #scaling = 1e-26
  [../]

  [./N2]
    family = SCALAR
    order = FIRST
    initial_condition = 1.97816e25
    #scaling = 1e-27
  [../]

  [./N2A3]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-9
  [../]

  [./N2B3]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-9
  [../]

  [./N]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-28
  [../]

  [./N2D]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-10
  [../]

  [./N+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 1e5
    #initial_condition = 1e12
    #scaling = 1e-10
  [../]

  [./N2+]
    family = SCALAR
    order = FIRST
    #initial_condition = 1e5 
    initial_condition = 1e18
    #scaling = 1e10
  [../]

  [./N3+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./N4+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e10
  [../]

  [./O2]
    # Air is N2-O2 at ratio of 4:1
    family = SCALAR
    order = FIRST
    initial_condition = 5.008e24
    #scaling = 1e-28
  [../]

  [./O2a1]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-23
  [../]

  [./O]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-25
  [../]

  [./O1D]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-7
  [../]

  [./O3]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-7
  [../]

  [./O+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-26
  [../]

  [./O2+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-24
  [../]

  [./O4+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./O-]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-6
  [../]

  [./O2-]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-22
  [../]

  [./O3-]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-5
  [../]

  [./O4-]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./NO]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-6
  [../]

  [./NO+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-26
  [../]

  [./NO-]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
    #scaling = 1e-10
  [../]

  [./N2O]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./NO2]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./NO3]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./N2O5]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./N2O+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./NO2+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./N2O-]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./NO2-]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./NO3-]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./N2O3]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./N2O4]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  # Hydrogen species
  [./H+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./H2+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./H3+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./OH+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./H2O+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./H3O+]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./H-]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./OH-]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./H]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./H2]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./OH]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./HO2]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./H2O2]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./HNO]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./HNO2]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./HNO3]
    family = SCALAR
    order = FIRST
    initial_condition = 1e5
  [../]

  [./H2O]
    family = SCALAR
    order = FIRST
    initial_condition = 2.504e23
  [../]
[]

[ScalarKernels]
  [./e_time_deriv]
    type = ODETimeDerivative
    variable = e
  [../]
  [./N2_time_deriv]
    type = ODETimeDerivative
    variable = N2
  [../]

  [./N2A3_time_deriv]
    type = ODETimeDerivative
    variable = N2A3
  [../]

  [./N2B3_time_deriv]
    type = ODETimeDerivative
    variable = N2B3
  [../]

  [./N_time_deriv]
    type = ODETimeDerivative
    variable = N
  [../]

  [./N2D_time_deriv]
    type = ODETimeDerivative
    variable = N2D
  [../]

  [./Np_time_deriv]
    type = ODETimeDerivative
    variable = N+
  [../]

  [./N2p_time_deriv]
    type = ODETimeDerivative
    variable = N2+
  [../]

  [./N3p_time_deriv]
    type = ODETimeDerivative
    variable = N3+
  [../]

  [./N4p_time_deriv]
    type = ODETimeDerivative
    variable = N4+
  [../]

  [./O2_time_deriv]
    type = ODETimeDerivative
    variable = O2
  [../]

  [./O2a1_time_deriv]
    type = ODETimeDerivative
    variable = O2a1
  [../]

  [./O_time_deriv]
    type = ODETimeDerivative
    variable = O
  [../]

  [./O1D_time_deriv]
    type = ODETimeDerivative
    variable = O1D
  [../]

  [./O3_time_deriv]
    type = ODETimeDerivative
    variable = O3
  [../]

  [./Op_time_deriv]
    type = ODETimeDerivative
    variable = O+
  [../]

  [./O2p_time_deriv]
    type = ODETimeDerivative
    variable = O2+
  [../]

  [./O4p_time_deriv]
    type = ODETimeDerivative
    variable = O4+
  [../]

  [./Om_time_deriv]
    type = ODETimeDerivative
    variable = O-
  [../]

  [./O2m_time_deriv]
    type = ODETimeDerivative
    variable = O2-
  [../]

  [./O3m_time_deriv]
    type = ODETimeDerivative
    variable = O3-
  [../]

  [./O4m_time_deriv]
    type = ODETimeDerivative
    variable = O4-
  [../]

  [./NO_time_deriv]
    type = ODETimeDerivative
    variable = NO
  [../]

  [./NOp_time_deriv]
    type = ODETimeDerivative
    variable = NO+
  [../]

  [./NOm_time_deriv]
    type = ODETimeDerivative
    variable = NO-
  [../]

  # Additional nitrogen-oxygen species
  [./N2O_time_deriv]
    type = ODETimeDerivative
    variable = N2O
  [../]
  [./NO2_time_deriv]
    type = ODETimeDerivative
    variable = NO2
  [../]
  [./NO3_time_deriv]
    type = ODETimeDerivative
    variable = NO3
  [../]
  [./N2O3_time_deriv]
    type = ODETimeDerivative
    variable = N2O3
  [../]
  [./N2O4_time_deriv]
    type = ODETimeDerivative
    variable = N2O4
  [../]
  [./N2O5_time_deriv]
    type = ODETimeDerivative
    variable = N2O5
  [../]
  [./N2O+_time_deriv]
    type = ODETimeDerivative
    variable = N2O+
  [../]
  [./NO2+_time_deriv]
    type = ODETimeDerivative
    variable = NO2+
  [../]
  [./N2O-_time_deriv]
    type = ODETimeDerivative
    variable = N2O-
  [../]
  [./NO2-_time_deriv]
    type = ODETimeDerivative
    variable = NO2-
  [../]
  [./NO3-_time_deriv]
    type = ODETimeDerivative
    variable = NO3- 
  [../]

  # Hydrogen Species
  [./Hp_time_deriv]
    type = ODETimeDerivative
    variable = H+
  [../]

  [./H2p_time_deriv]
    type = ODETimeDerivative
    variable = H2+
  [../]

  [./H3p_time_deriv]
    type = ODETimeDerivative
    variable = H3+
  [../]

  [./OHp_time_deriv]
    type = ODETimeDerivative
    variable = OH+
  [../]

  [./H2Op_time_deriv]
    type = ODETimeDerivative
    variable = H2O+
  [../]

  [./H3Op_time_deriv]
    type = ODETimeDerivative
    variable = H3O+
  [../]

  [./Hm_time_deriv]
    type = ODETimeDerivative
    variable = H-
  [../]

  [./OHm_time_deriv]
    type = ODETimeDerivative
    variable = OH-
  [../]

  [./H_time_deriv]
    type = ODETimeDerivative
    variable = H
  [../]

  [./H2_time_deriv]
    type = ODETimeDerivative
    variable = H2
  [../]

  [./OH_time_deriv]
    type = ODETimeDerivative
    variable = OH
  [../]

  [./HO2_time_deriv]
    type = ODETimeDerivative
    variable = HO2
  [../]

  [./H2O2_time_deriv]
    type = ODETimeDerivative
    variable = H2O2
  [../]

  [./HNO_time_deriv]
    type = ODETimeDerivative
    variable = HNO
  [../]

  [./HNO2_time_deriv]
    type = ODETimeDerivative
    variable = HNO2
  [../]

  [./HNO3_time_deriv]
    type = ODETimeDerivative
    variable = HNO3
  [../]

  [./H2O_time_deriv]
    type = ODETimeDerivative
    variable = H2O
  [../]

[]

[Debug]
  #show_var_residual_norms = true
[]

[AuxVariables]
  [./Te]
    order = FIRST
    family = SCALAR
    initial_condition = 32000
  [../]
  [./ee]
    order = FIRST
    family = SCALAR
    initial_condition = 0.1
  [../]
  
  [./M]
    # For now, NEUTRAL = N2 + O2
    order = FIRST
    family = SCALAR
    #initial_condition = 2.445692e19
  [../]

  [./reduced_field]
    # Units: Td
    order = FIRST
    family = SCALAR
    #initial_condition = 100
  [../]
[]

[AuxScalarKernels]
  [./Te_read]
    type = DataReadScalar
    variable = Te
    sampler = reduced_field
    scale_factor = 7733.52643
    property_file = 'air_test/electron_energy.txt'
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  [../]

  [./ee_read]
    type = DataReadScalar
    variable = ee
    sampler = reduced_field
    property_file = 'air_test/electron_energy.txt'
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  [../]

  [./field_calc]
    type = FunctionScalarAux
    variable = reduced_field
    function = reduced_field_time
    execute_on = 'initial timestep_begin'
  [../]

  [./neutral_sum]
    type = VariableSum
    variable = M
    args = 'N2 O2 N2A3 N2B3 N N2D O2a1 O O1D O3 NO N2O NO2 NO3 N2O3 N2O4 N2O5 H H2 OH HO2 H2O2 HNO HNO2 HNO3 N2 O2 H2O'
    execute_on = 'initial linear nonlinear'
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
    vars = 'A d w p o Tr xoff'
    vals = '13.204851149149514 1486789.8154186027 50149412.89498433 -1.2796011330163444 -0.54054816147437 1e-4 40e-10'
    value = 'abs((A * exp(-d*(t%Tr-xoff)) * sin(w*(t%Tr-xoff) - 6.083))*(0.5 + 0.5*tanh(1e9*((t%Tr)-5e-9))))*1e6 / 2.445692e4' 
    #value = '1000'

  [../]

  #[./voltage_time]
  #  # Voltage [kV] / gap distance [mm] * n_neutral * 1e-21 to convert to Td
  #  type = ParsedFunction
  #  vars = 'A d w p o Tr'
  #  #vals = '13.204851149149514 1486789.8154186027 50149412.89498433 -1.2796011330163444 -0.54054816147437 5e-6'
  #  vals = '13.204851149149514 1486789.8154186027 50149412.89498433 -1.2796011330163444 -0.54054816147437 1e-4'
  #  value = 'A * exp(-d*(t%Tr)) * sin(w*(t%Tr) + p*2.455)' 
  #  #value = 'A * exp(-d*t) * sin(w*t + p) + o' # Voltage [kV] / gap distance [mm] * n_neutral * 1e-21 to convert to Td
  #[../]
  [./dts]
    type = ParsedFunction
    vars = 'Tr'
    #vals = '5e-6'
    vals = '1e-4'
    #value = '(0.9999e-8*tanh(4e5*(t%Tr)) + 1e-11)*(1.0 - 0.999*(0.5 + 0.5*tanh((t%Tr - 0.9998e-4)/1e-8)))'
    #value = '(0.9999e-7*tanh(2e4*(t%Tr)) + 1e-10)*(1.0 - 0.999*(0.5 + 0.5*tanh((t%Tr - 0.998e-4)/5e-9)))'
    #value = '(0.5999e-7*tanh(2e4*(t%Tr)) + 1e-10)*(1.0 - 0.999*(0.5 + 0.5*tanh((t%Tr - 0.998e-4)/5e-9)))'
    value = 'if((t%Tr)<1e-6,1e-10,1e-8)'
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
  #end_time = 1e4
  end_time = 0.004
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
  nl_rel_tol = 1e-5
  nl_abs_tol = 1e6  # Note that abs_tol in this case refers to number density. 
  #nl_abs_tol = 1e-10
  dtmin = 1e-20
  #dtmax = 1.1e-10
  #dtmax = 2e-9
  #dtmax = 1e-4
  l_max_its = 50
  #num_steps = 54
  #steady_state_detection = true
  [./TimeIntegrator]
    type = ImplicitMidpoint
  [../]
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.4
    dt = 1e-7
    # dt = 1.1
    growth_factor = 1.01
    optimal_iterations = 15
  [../]
  #[./TimeStepper]
  #  type = FunctionDT
  #  function = dts
  #  min_dt = 1e-16
  #[../]
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

#[Outputs]
#  csv = true
#  interval = 1
#  show = 'N2 N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N2A3 N2B3 N2a_1 N2C3 N N2D N2P N+ N2+ N3+ N4+ O2 O2v1 O2v2 O2v3 O2v4 O2a1 O2b1 O24_ev O O1D O1S O3 O+ O2+ O4+ O- O2- O3- O4- NO NO+ NO- O2pN2 e N2O NO2 NO3 N2O5 N2O+ NO2+ N2O- NO2- NO3- reduced_field test'
#  [./console]
#    type = Console
#    execute_scalars_on = 'none'
#  [../]
#[]

[Outputs]
  #[./species]
  #  type = CSV
  #  interval = 1
  #  show = 'N2 N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N2A3 N2B3 N2a_1 N2C3 N N2D N2P N+ N2+ N3+ N4+ O2 O2v1 O2v2 O2v3 O2v4 O2a1 O2b1 O24_ev O O1D O1S O3 O+ O2+ O4+ O- O2- O3- O4- NO NO+ NO- O2pN2 e N2O NO2 NO3 N2O5 N2O+ NO2+ N2O- NO2- NO3- reduced_field test'
  #[../]
  [./reactions]
    type = CSV
    interval = 1
    hide = 'N+ N2+ N3+ N4+ O+ O2+ O4+ NO+ N2O+ NO2+ H+ H2+ H3+ OH+ H2O+ H3O+ e O- O2- O3- O4- NO- N2O- NO2- NO3- H- OH- N2D N2A3 N2B3 O1D H N O O2a1 O3 NO N2O NO2 NO3 N2O3 N2O4 N2O5 H2 OH HO2 H2O2 HNO HNO2 HNO3 N2 O2 H2O reduced_field Te ee'
  [../]
  [./test]
    type = CSV
    show = 'N+ N2+ N3+ N4+ O+ O2+ O4+ NO+ N2O+ NO2+ H+ H2+ H3+ OH+ H2O+ H3O+ e O- O2- O3- O4- NO- N2O- NO2- NO3- H- OH- N2D N2A3 N2B3 O1D H N O O2a1 O3 NO N2O NO2 NO3 N2O3 N2O4 N2O5 H2 OH HO2 H2O2 HNO HNO2 HNO3 N2 O2 H2O reduced_field Te ee'
  #execute_scalars_on = 'INITIAL TIMESTEP_END'
  [../]
  [./console]
    type = Console
    execute_scalars_on = 'none'
  [../]
[]

[ChemicalReactions]
  [./ScalarNetwork]
    species = 'N+ N2+ N3+ N4+ O+ O2+ O4+ NO+ N2O+ NO2+ H+ H2+ H3+ OH+ H2O+ H3O+ e O- O2- O3- O4- NO- N2O- NO2- NO3- H- OH- N2D N2A3 N2B3 O1D H N O O2a1 O3 NO N2O NO2 NO3 N2O3 N2O4 N2O5 H2 OH HO2 H2O2 HNO HNO2 HNO3 N2 O2 H2O'
    num_particles = '1 2 3 4 1 2 4 2 3 3 1 2 3 2 3 4 1 1 2 3 4 2 3 3 4 1 2 1 2 2 1 1 1 1 2 3 2 3 3 4 5 6 7 2 2 3 4 3 4 5 2 2 3'
    balance_check = true
    charge_balance_check = false
    aux_species = 'M'
    reaction_coefficient_format = 'rate'
    include_electrons = true
    file_location = 'air_test'
    electron_density = 'e'
    equation_variables = 'Te ee'
    equation_constants = 'Tg'
    equation_values = '300'
    rate_provider_var = 'reduced_field'
    #track_rates = true
    track_rates = false




















































































































































    # NOTE: rate coefficients units are cm^3 s^-1
    reactions = 'e + N2  -> N2D + N + e             : {3.99e-17*(ee^(2.24))*exp(-9.1/ee)}
                 e + N2  -> N2A3 + e                : {3.34e-16*(ee^(-0.06))*exp(-8.5/ee)}
                 e + N2  -> N2B3 + e                : {8.44e-15*(ee^(-0.33))*exp(-9.15/ee)}
                 e + N2  -> N2+ + e + e             : {1e-16*(ee^(1.9))*exp(-14.6/ee)}
                 e + N   -> N2D + e                 : {5.06e-15*exp(-10.8/(ee^(3.95)))}
                 e + N   -> N+ + e + e              : {1.45e-17*(ee^2.78)*exp(-8.54/ee)}
                 e + O2  -> O + O + e               : {2.03e-14*(ee^(-0.1))*exp(-8.47/ee)}
                 e + O2  -> O1D + O + e             : {1.82e-14*(ee^(-0.13))*exp(-10.7/ee)}
                 e + O2  -> O2a1 + e                : {1.04e-15*exp(-2.59/ee)}
                 e + O2  -> O2+ + e + e             : {9.54e-12*(ee^(-1.05))*exp(-55.6/ee)}
                 e + O3  -> O + O2 + e              : {1.78e-12*(ee^(-0.614))*exp(-11.5/ee)}
                 e + O   -> O1D + e                 : {7.46e-15*exp(-5.56/(ee^1.47))}
                 e + O   -> O+ + e + e              : {4.75e-15*(ee^0.61)*exp(-22.1/ee)}
                 e + H2O -> H2O+ + e + e            : {9.65e-18*(ee^2.53)*exp(-8.99/ee)}
                 e + H2O -> OH+ + H + e + e         : {9.89e-12*(ee^(-1.64))*exp(-67.6/ee)} 
                 e + H2O -> H+ + OH + e + e         : {7.45e-15*(ee^0.34)*exp(-54.2/ee)}
                 e + H2O -> O+ + H2 + e + e         : {7.4e-16*(ee^0.45)*exp(-55.5/ee)}
                 e + H2O -> H2+ + O + e + e         : {8.49e-15*(ee^(-1.23))*exp(-74.0/ee)}
                 e + H2O -> OH + H + e              : {5.15e-15*(ee^0.62)*exp(-10.9/ee)}
                 e + H2O -> H2 + O1D + e            : {5.19e-18*(ee^1.2)*exp(-13.8/ee)}
                 e + H2  -> H + H + e               : {3.29e-15*(ee^0.578)*exp(-7.56/ee)}
                 e + H2 -> H2+ + e + e              : {4e-17*(ee^2.13)*exp(-14.9/ee)}
                 e + N2O5 -> NO2+ + NO3 + e + e     : {2.43e-17*(ee^2.77)*exp(-14.9/ee)}
                 e + N+ + M -> N + M                : {3.12e-35/(Te^1.5)}
                 e + N2+ -> N + N                   : {1.66e-12/(Te^0.7)}
                 e + N2+ -> N2D + N                 : {1.5e-12/(Te^0.7)}
                 e + N2+ + M -> N2 + M              : {3.12e-35/(Te^1.5)}
                 e + N3+ -> N2 + N                  : {3.46e-12/(Te^0.5)}
                 e + N4+ -> N2 + N2                 : {4.73e-11/(Te^0.53)}
                 e + O+ + M -> O + M               : {3.12e-35/(Te^1.5)}
                 e + O2+ -> O + O                   : {1.68e-11/(Te^0.7)}
                 e + O2+ -> O + O1D                 : {1.24e-11/(Te^0.7)}
                 e + O2+ + M -> O2 + M              : {3.12e-35/(Te^1.5)}
                 e + O4+ -> O2 + O2                 : {2.42e-11/(Te^0.5)}
                 e + N2O+ -> N2 + O                 : {3.46e-12/(Te^0.5)}
                 e + NO+ -> N + O                   : {1.07e-11/(Te^0.85)}
                 e + NO+ -> N2D + O                 : {4.28e-11/(Te^0.85)}
                 e + NO+ + M -> NO + M              : {3.12e-35/(Te^1.5)}
                 e + NO2+ -> NO + O                 : {3.46e-12/(Te^0.5)}
                 e + H2+ -> H + H                   : {1.86e-13/(Te^0.43)}
                 e + H3+ -> H + H2                  : {5.2e-11/(Te^0.5)}
                 e + H3+ -> H + H + H               : {1.14e-11/(Te^0.97)}
                 e + H2O+ -> OH + H                 : {2.73e-12/(Te^0.5)}
                 e + H2O+ -> O + H2                 : {1.37e-12/(Te^0.5)}
                 e + H2O+ -> O + H + H              : {1.37e-12/(Te^0.5)}
                 e + H3O+ -> OH + H + H             : {5.46e-12/(Te^0.5)}
                 e + e + N+ -> N + e                : {1e-31*(Tg/Te)^4.5}
                 e + e + N2+ -> N2 + e              : {1e-31*(Tg/Te)^4.5}
                 e + e + O+ -> O + e                : {1e-31*(Tg/Te)^4.5}
                 e + e + O2+ -> O2 + e              : {1e-31*(Tg/Te)^4.5}
                 e + e + NO+ -> NO + e              : {1e-31*(Tg/Te)^4.5}
                 e + e + H+ -> H + e                : {1e-31*(Tg/Te)^4.5}
                 e + e + H2+ -> H2 + e              : {1e-31*(Tg/Te)^4.5}
                 e + e + OH+ -> OH + e              : {1e-31*(Tg/Te)^4.5}
                 e + e + H2O+ -> H2O + e            : {1e-31*(Tg/Te)^4.5}
                 e + O + O2 -> O- + O2              : 1e-43
                 e + O + O2 -> O2- + O              : 1e-43
                 e + O2 + O2 -> O2- + O2            : {1.4e-41*(Tg/Te)*exp(-600/Tg)*exp(700*(Te-Tg)/(Te*Tg))}
                 e + O2 + N2 -> O2- + N2            : {1.1e-43*(Tg/Te)^2*exp(-70/Tg)*exp(1500*(Te-Tg)/(Te*Tg))}
                 e + O2 -> O- + O                   : {2.63e-16*(ee^(-0.495))*exp(-5.65/ee)}
                 e + O2 -> O2-                      : {9.72e-15*(ee^(-1.62))*exp(-14.2/ee)}
                 e + O3 -> O- + O2                  : 1e-17
                 e + O3 -> O2- + O                  : 1e-15
                 e + O3 + M -> O3- + M              : 1e-43
                 e + N2O -> O- + N2                 : 2e-16
                 e + NO + M -> NO- + M              : 8e-43
                 e + NO2 -> O- + NO                 : 1e-17
                 e + NO2 + M -> NO2- + M            : 1.5e-42
                 e + NO3 + M -> NO3- + M            : 1e-42
                 e + H2O -> H- + OH                 : {4.42e-14*(ee^(-2))*exp(-13.39/ee)}
                 e + H2O -> O- + H2                 : {2.97e-15*(ee^(-1.56))*exp(-13.67/ee)}
                 e + H2O -> OH- + H                 : {9.6e-16*(ee^(-1.7))*exp(-13.31/ee)}
                 e + HNO3 -> NO2- + OH              : 5e-14
                 O- + N -> NO + e                   : 2.6e-16
                 O- + N2 -> N2O + e                 : 1e-18
                 O- + N2A3 -> N2 + O + e            : 2.2e-15
                 O- + N2B3 -> N2 + O + e            : 1.9e-15
                 O- + O -> O2 + e                   : 1.4e-16
                 O- + O2 -> O3 + e                  : 1e-18
                 O- + O2a1 -> O3 + e                : 3e-16
                 O- + O3 -> O2 + O2 + e             : 3e-16
                 O- + NO -> NO2 + e                 : 2.6e-16
                 O- + H2 -> H2O + e                 : 7e-16
                 O2- + N -> NO2 + e                 : 5e-16
                 O2- + N2 -> N2 + O2 + e            : {1.9e-18*(Tg/300)^0.5*exp(-4990/Tg)}
                 O2- + N2A3 -> N2 + O2 + e          : 2.1e-15
                 O2- + N2B3 -> N2 + O2 + e          : 2.5e-15
                 O2- + O -> O3 + e                  : 1.5e-16
                 O2- + O2 -> O2 + O2 + e            : {2.7e-16*(Tg/300)^0.5*exp(-5590/Tg)}
                 O2- + O3 -> O3 + O2 + e            : 6e-16
                 O2- + O2a1 -> O2 + O2 + e          : 2e-16
                 O2- + H -> HO2 + e                 : 1.4e-15
                 O3- + O -> O2 + O2 + e             : 3e-16
                 O3- + O2 -> O3 + O2 + e            : 2.3e-16
                 O3- + O3 -> O2 + O2 + O2 + e       : 3e-16
                 NO- + M -> NO + M + e              : 2.40e-19
                 NO- + NO -> NO + NO + e            : 5e-18
                 NO- + N2O -> NO + N2O + e          : 5.1e-18
                 NO- + H2 -> NO + H2 + e            : 2.3e-19
                 NO2- + O -> NO3 + e                : 1e-18
                 NO2- + N -> N2 + O2 + e            : 1e-18
                 NO3- + O -> NO2 + O2 + e           : 1e-18
                 NO3- + N -> N2 + O3 + e            : 1e-18
                 H- + O2 -> HO2 + e                 : 1.2e-15
                 H- + H -> H2 + e                   : 1.8e-15
                 OH- + O -> HO2 + e                 : 2e-16
                 OH- + H -> H2O + e                 : 1.8e-15
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
                 N+ + OH -> OH+ + N                 : 3.4e-16
                 N+ + OH -> NO+ + H                 : 3.4e-16
                 N+ + H2O -> H2O+ + N               : 1.19e-15
                 N+ + H2O -> NO+ + H2               : 2.1e-16
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
                 N2+ + H2O -> H2O+ + N2             : 2.3e-15
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
                 N4+ + H2 -> H2+ + N2 + N2          : {3e-16*exp(-1800/Tg)}
                 N4+ + H2O -> H2O+ + N2 + N2        : 3e-15
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
                 O+ + H -> H+ + O                   : 6.8e-16
                 O+ + H2 -> OH+ + H                 : 1.7e-15
                 O+ + OH -> OH+ + O                 : 3.3e-16
                 O+ + OH -> O2+ + H                 : 3.6e-16
                 O+ + H2O -> H2O+ + O               : 3.2e-15
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
                 O- + H2 -> OH- + H                 : 3.3e-17
                 O- + H2O -> OH- + OH               : 1.4e-15
                 O2- + O -> O- + O2                 : 3.3e-16
                 O2- + O2 + M -> O4- + M            : {3.5e-43*(300/Tg)}
                 O2- + O3 -> O3- + O2               : 3.5e-16
                 O2- + N2O -> O3- + N2              : 1e-17
                 O2- + NO2 -> NO2- + O2             : 7e-16
                 O2- + NO3 -> NO3- + O2             : 5e-16
                 O2- + HNO3 -> NO3- + HO2           : 2.8e-16
                 O3- + O -> O2- + O2                : 1e-17
                 O3- + NO -> NO2- + O2              : 1e-17
                 O3- + NO -> NO3- + O               : 1e-17
                 O3- + NO2 -> NO3- + O2             : 2e-17
                 O3- + NO2 -> NO2- + O3             : 7e-17
                 O3- + NO3 -> NO3- + O3             : 5e-16
                 O3- + H -> OH- + O2                : 8.4e-16
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
                 NO2- + H -> OH- + NO               : 4e-16
                 NO2- + N2O -> NO3- + N2            : 5e-19
                 NO2- + HNO3 -> NO3- + HNO2         : 1.6e-15
                 NO3- + NO ->  NO2- + NO2           : 3e-21
                 H+ + O -> O+ + H                   : 3.8e-16
                 H+ + O2 -> O2+ + H                 : 1.17e-15
                 H+ + NO -> NO+ + H                 : 1.9e-15
                 H+ + H2 + M -> H3+ + M             : 3.1e-41
                 H+ + H2O -> H2O+ + H               : 8.2e-15
                 H- + N2O -> OH- + N2               : 1.1e-15
                 H- + NO2 -> NO2- + H               : 2.9e-15
                 H- + H2O -> OH- + H2               : 3.8e-15
                 H2+ + O2 -> O2+ + H2               : 7.83e-16
                 H2+ + H -> H+ + H2                 : 6.4e-16
                 H2+ + H2 -> H3+ + H                : 2e-15
                 H2+ + H2O -> H3O+ + H              : 3.43e-15
                 H2+ + H2O -> H2O+ + H2             : 3.86e-15
                 H3+ + O -> OH+ + H2                : 8e-16
                 H3+ + H2O -> H3O+ + H2             : 3e-15
                 H3+ + NO2 -> NO+ + OH + H2         : 7e-16
                 OH+ + O2 -> O2+ + OH               : 5.9e-16
                 OH+ + NO -> NO+ + OH               : 5.2e-16
                 OH+ + NO2 -> NO+ + HO2             : 1.3e-15
                 OH+ + N2O -> N2O+ + OH             : 2.13e-16
                 OH+ + H2 -> H2O+ + H               : 9.7e-16
                 OH+ + OH -> H2O+ + O               : 7e-16
                 OH+ + H2O -> H2O+ + OH             : 1.59e-15
                 OH+ + H2O -> H3O+ + O              : 1.3e-15
                 OH- + O3 -> O3- + OH               : 9e-16
                 OH- + NO2 -> NO2- + OH             : 1.9e-15
                 H2O+ + N -> NO+ + H2               : 1.9e-16
                 H2O+ + O -> O2+ + H2               : 5.5e-17
                 H2O+ + O2 -> O2+ + H2O             : 4.3e-16
                 H2O+ + NO -> NO+ + H2O             : 4.6e-16
                 H2O+ + NO2 -> NO2+ + H2O           : 1.2e-15
                 H2O+ + H2 -> H3O+ + H              : 7.6e-16
                 H2O+ + H2O -> H3O+ + OH            : 1.7e-15
                 H3O+ + NO -> NO+ + H + H2O         : 1.5e-18
                 H3O+ + N2O5 ->  NO2+ + HNO3 + H2O  : 5.5e-16
                 O+ + O- -> O + O                   : {2e-13*(300/Tg)^0.5}
                 O+ + O2- -> O2 + O                 : {2e-13*(300/Tg)^0.5}
                 O+ + O3- -> O3 + O                 : {2e-13*(300/Tg)^0.5}
                 O+ + O4- -> O2 + O2 + O            : 1e-13
                 O+ + N2O- -> N2O + O               : {2e-13*(300/Tg)^0.5}
                 O+ + NO- -> NO + O                 : {2e-13*(300/Tg)^0.5}
                 O+ + NO2- -> NO2 + O               : {2e-13*(300/Tg)^0.5}
                 O+ + NO3- -> NO3 + O               : {2e-13*(300/Tg)^0.5}
                 O+ + H- -> O + H                   : {2e-13*(300/Tg)^0.5}
                 O+ + OH -> O + OH                  : {2e-13*(300/Tg)^0.5}
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
                 O2+ + H- -> H + O2                 : {2e-13*(300/Tg)^0.5}
                 O2+ + H- -> H + O + O              : 1e-13
                 O2+ + OH- -> OH + O2               : {2e-13*(300/Tg)^0.5}
                 O2+ + OH- -> OH + O + O            : 1e-13
                 O4+ + O- -> O + O2 + O2            : 1e-13
                 O4+ + O2- -> O2 + O2 + O2          : 1e-13
                 O4+ + O3- -> O3 + O2 + O2          : 1e-13
                 O4+ + O4- -> O2 + O2 + O2 + O2     : 1e-13
                 O4+ + N2O- -> N2O + O2 + O2        : 1e-13
                 O4+ + NO- -> NO + O2 + O2          : 1e-13
                 O4+ + NO2- -> NO2 + O2 + O2        : 1e-13
                 O4+ + NO3- -> NO3 + O2 + O2        : 1e-13
                 O4+ + H- -> H + O2 + O2            : 1e-13
                 O4+ + OH- -> OH + O2 + O2          : 1e-13
                 N+ + N2O- -> N2O + N               : {2e-13*(300/Tg)^0.5}
                 N+ + NO- -> NO + N                 : {2e-13*(300/Tg)^0.5}
                 N+ + NO2- -> NO2 + N               : {2e-13*(300/Tg)^0.5}
                 N+ + NO3- -> NO3 + N               : {2e-13*(300/Tg)^0.5}
                 N+ + O- -> O + N                   : {2e-13*(300/Tg)^0.5}
                 N+ + O2- -> O2 + N                 : {2e-13*(300/Tg)^0.5}
                 N+ + O3- -> O3 + N                 : {2e-13*(300/Tg)^0.5}
                 N+ + O4- -> O2 + O2 + N            : 1e-13
                 N+ + H- -> N + H                   : {2e-13*(300/Tg)^0.5}
                 N+ + OH- -> N + OH                 : {2e-13*(300/Tg)^0.5}
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
                 N2+ + H- -> H + N2                 : {2e-13*(300/Tg)^0.5}
                 N2+ + H- -> H + N + N              : 1e-13
                 N2+ + OH- -> OH + N2               : {2e-13*(300/Tg)^0.5}
                 N2+ + OH- -> OH + N + N            : 1e-13
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
                 N2O+ + H- -> H + N2O               : {2e-13*(300/Tg)^0.5}
                 N2O+ + H- -> H + N2 + O            : 1e-13
                 N2O+ + OH- -> OH + N2O             : {2e-13*(300/Tg)^0.5}
                 N2O+ + OH- -> OH + N2 + O          : 1e-13
                 N3+ + N2O- -> N2O + N2 + N         : 1e-13
                 N3+ + NO- -> NO + N2 + N           : 1e-13
                 N3+ + NO2- -> NO2 + N2 + N         : 1e-13
                 N3+ + NO3- -> NO3 + N2 + N         : 1e-13
                 N3+ + O- -> O + N2 + N             : 1e-13
                 N3+ + O2- -> O2 + N2 + N           : 1e-13
                 N3+ + O3- -> O3 + N2 + N           : 1e-13
                 N3+ + O4- -> O2 + O2 + N + N2      : 1e-13
                 N3+ + H- -> H + N2 + N             : 1e-13
                 N3+ + OH- -> OH + N2 + N           : 1e-13
                 N3+ + N2O- -> N2O + N2 + N         : 1e-13
                 N3+ + NO- -> NO + N2 + N           : 1e-13
                 N3+ + NO2- -> NO2 + N2 + N         : 1e-13
                 N3+ + NO3- -> NO3 + N2 + N         : 1e-13
                 N3+ + O- -> O + N2 + N             : 1e-13
                 N3+ + O2- -> O2 + N2 + N           : 1e-13
                 N3+ + O3- -> O3 + N2 + N           : 1e-13
                 N3+ + O4- -> O2 + O2 + N + N2      : 1e-13
                 N3+ + H- -> H + N2 + N             : 1e-13
                 N3+ + OH- -> OH + N2 + N           : 1e-13
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
                 NO+ + H- -> H + NO                 : {2e-13*(300/Tg)^0.5}
                 NO+ + H- -> H + N + O              : 1e-13
                 NO+ + OH- -> OH + NO               : {2e-13*(300/Tg)^0.5}
                 NO+ + OH- -> OH + N + O            : 1e-13
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
                 NO2+ + H- -> H + NO2               : {2e-13*(300/Tg)^0.5}
                 NO2+ + H- -> H + N + O2            : 1e-13
                 NO2+ + OH- -> OH + NO2             : {2e-13*(300/Tg)^0.5}
                 NO2+ + OH- -> OH + N + O2          : 1e-13
                 H+ + N2O- -> N2O + H               : {2e-13*(300/Tg)^0.5}
                 H+ + NO- -> NO + H                 : {2e-13*(300/Tg)^0.5}
                 H+ + NO2- -> NO2 + H               : {2e-13*(300/Tg)^0.5}
                 H+ + NO3- -> NO3 + H               : {2e-13*(300/Tg)^0.5}
                 H+ + O- -> O + H                   : {2e-13*(300/Tg)^0.5}
                 H+ + O2- -> O2 + H                 : {2e-13*(300/Tg)^0.5}
                 H+ + O3- -> O3 + H                 : {2e-13*(300/Tg)^0.5}
                 H+ + O4- -> O2 + O2 + H            : 1e-13 
                 H+ + H- -> H + H                   : {2e-13*(300/Tg)^0.5}
                 H+ + OH- -> OH + H                 : {2e-13*(300/Tg)^0.5}
                 H2+ + N2O- -> N2O + H2             : {2e-13*(300/Tg)^0.5}
                 H2+ + N2O- -> N2O + H + H          : 1e-13
                 H2+ + NO- -> NO + H2               : {2e-13*(300/Tg)^0.5}
                 H2+ + NO- -> NO + H + H            : 1e-13
                 H2+ + NO2- -> NO2 + H2             : {2e-13*(300/Tg)^0.5}
                 H2+ + NO2- -> NO2 + H + H          : 1e-13
                 H2+ + NO3- -> NO3 + H2             : {2e-13*(300/Tg)^0.5}
                 H2+ + NO3- -> NO3 + H + H          : 1e-13
                 H2+ + O- -> O + H + H              : 1e-13
                 H2+ + O- -> O + H2                 : {2e-13*(300/Tg)^0.5}
                 H2+ + O2- -> O2 + H + H            : 1e-13
                 H2+ + O2- -> O2 + H2               : {2e-13*(300/Tg)^0.5}
                 H2+ + O3- -> O3 + H + H            : 1e-13
                 H2+ + O3- -> O3 + H2               : {2e-13*(300/Tg)^0.5}
                 H2+ + O4- -> O2 + O2 + H2          : 1e-13
                 H2+ + H- -> H + H2                 : {2e-13*(300/Tg)^0.5}
                 H2+ + H- -> H + H + H              : 1e-13
                 H2+ + OH- -> OH + H2               : {2e-13*(300/Tg)^0.5}
                 H2+ + OH- -> OH + H + H            : 1e-13
                 H3+ + N2O- -> N2O + H + H2         : 1e-13
                 H3+ + NO- -> NO + H + H2           : 1e-13
                 H3+ + NO2- -> NO2 + H + H2         : 1e-13
                 H3+ + NO3- -> NO3 + H + H2         : 1e-13
                 H3+ + O- -> O + H + H2             : 1e-13
                 H3+ + O2- -> O2 + H + H2           : 1e-13
                 H3+ + O3- -> O3 + H + H2           : 1e-13
                 H3+ + O4- -> O2 + O2 + H + H2      : 1e-13
                 H3+ + H- -> H + H + H2             : 1e-13
                 H3+ + OH- -> OH + H + H2           : 1e-13
                 OH+ + N2O- -> N2O + OH             : {2e-13*(300/Tg)^0.5}
                 OH+ + N2O- -> N2O + O + H          : 1e-13
                 OH+ + NO- -> NO + OH               : {2e-13*(300/Tg)^0.5}
                 OH+ + NO- -> NO + O + H            : 1e-13
                 OH+ + NO2- -> NO2 + OH             : {2e-13*(300/Tg)^0.5}
                 OH+ + NO2- -> NO2 + O + H          : 1e-13
                 OH+ + NO3- -> NO3 + OH             : {2e-13*(300/Tg)^0.5}
                 OH+ + NO3- -> NO3 + O + H          : 1e-13
                 OH+ + O- -> O + O + H              : 1e-13
                 OH+ + O- -> O + OH                 : {2e-13*(300/Tg)^0.5}
                 OH+ + O2- -> O2 + O + H            : 1e-13
                 OH+ + O2- -> O2 + OH               : {2e-13*(300/Tg)^0.5}
                 OH+ + O3- -> O3 + O + H            : 1e-13
                 OH+ + O3- -> O3 + OH               : {2e-13*(300/Tg)^0.5}
                 OH+ + O4- -> O2 + O2 + OH          : 1e-13
                 OH+ + H- -> H + OH                 : {2e-13*(300/Tg)^0.5}
                 OH+ + H- -> H + O + H              : 1e-13
                 OH+ + OH- -> OH + OH               : {2e-13*(300/Tg)^0.5}
                 OH+ + OH- -> OH + O + H            : 1e-13
                 H2O+ + N2O- -> N2O + H2O           : {2e-13*(300/Tg)^0.5}
                 H2O+ + N2O- -> N2O + OH + H        : 1e-13
                 H2O+ + NO- -> NO + H2O             : {2e-13*(300/Tg)^0.5}
                 H2O+ + NO- -> NO + OH + H          : 1e-13
                 H2O+ + NO2- -> NO2 + H2O           : {2e-13*(300/Tg)^0.5}
                 H2O+ + NO2- -> NO2 + OH + H        : 1e-13
                 H2O+ + NO3- -> NO3 + H2O           : {2e-13*(300/Tg)^0.5}
                 H2O+ + NO3- -> NO3 + OH + H        : 1e-13
                 H2O+ + O- -> O + OH + H            : 1e-13
                 H2O+ + O- -> O + H2O               : {2e-13*(300/Tg)^0.5}
                 H2O+ + O2- -> O2 + OH + H          : 1e-13
                 H2O+ + O2- -> O2 + H2O             : {2e-13*(300/Tg)^0.5}
                 H2O+ + O3- -> O3 + OH + H          : 1e-13
                 H2O+ + O3- -> O3 + H2O             : {2e-13*(300/Tg)^0.5}
                 H2O+ + O4- -> O2 + O2 + H2O        : 1e-13
                 H2O+ + H- -> H + H2O               : {2e-13*(300/Tg)^0.5}
                 H2O+ + H- -> H + OH + H            : 1e-13
                 H2O+ + OH- -> OH + H2O             : {2e-13*(300/Tg)^0.5}
                 H2O+ + OH- -> OH + OH + H          : 1e-13
                 H3O+ + N2O- -> N2O + H2O + H       : 1e-13
                 H3O+ + NO- -> NO + H2O + H         : 1e-13
                 H3O+ + NO2- -> NO2 + H2O + H       : 1e-13
                 H3O+ + NO3- -> NO3 + H2O + H       : 1e-13
                 H3O+ + O- -> O + H2O + H           : 1e-13
                 H3O+ + O2- -> O2 + H2O + H         : 1e-13
                 H3O+ + O3- -> O3 + H2O + H         : 1e-13
                 H3O+ + O4- -> O2 + O2 + H2O + H    : 1e-13
                 H3O+ + H- -> H + H2O + H           : 1e-13
                 H3O+ + OH- -> OH + H2O + H         : 1e-13
                 N + N + M -> N2 + M                : {8.3e-46*exp(500/Tg)}
                 N + NO -> N2 + O                   : {2.1e-17*exp(100/Tg)}
                 N + NO2 -> N2O + O                 : {5.8e-18*exp(220/Tg)}
                 N + NO2 -> N2 + O + O              : 9.1e-19
                 N + NO2 -> NO + NO                 : 6e-19
                 N + NO2 -> N2 + O2                 : 7e-19
                 N + O + M -> NO + M                : {6.3e-45*exp(140/Tg)}
                 N + O2 -> NO + O                   : {1.5e-17*exp(-3600/Tg)}
                 N + O3 -> NO + O2                  : 5e-22
                 N + OH -> H + NO                   : 7.5e-17
                 N + HO2 -> NO + OH                 : {1.7e-17*exp(-1000/Tg)}
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
                 N2A3 + H2O -> H + OH + N2          : 5e-20
                 N2B3 + N2 -> N2A3 + N2             : 5e-17
                 N2B3 -> N2A3                       : 1.25e5
                 N2B3 + NO -> N2A3 + NO             : 2.4e-16
                 N2B3 + O2 -> N2 + O + O            : 3e-16
                 N2B3 + H2 -> N2A3 + H2             : 2.5e-17
                 O + O + M -> O2 + M                : {3.2e-47*exp(900/Tg)}
                 O + O2 + M -> O3 + M               : {3.4e-46*(300/Tg)^1.2}
                 O + O3 -> O2 + O2                  : {8e-18*exp(-2060/Tg)}
                 O + NO + M -> NO2 + M              : {1e-43*(300/Tg)^1.6}
                 O + NO2 -> NO + O2                 : {6.5e-18*exp(120/Tg)}
                 O + NO2 + M -> NO3 + M             : {9e-44*(300/Tg)^2}
                 O + NO3 -> O2 + NO2                : 1.7e-17
                 O + H + M -> OH + M                : 1.62e-44
                 O + OH -> H + O2                   : {2.2e-17*exp(-350/Tg)}
                 O + H2O2 -> OH + HO2               : {3.3e-17*exp(-2950/Tg)}
                 O + HO2 -> OH + O2                 : {8.3e-17*exp(-500/Tg)}
                 O + HNO -> OH + NO                 : 5.99e-17
                 O + HNO2 -> NO2 + OH               : {2e-17*exp(-3000/Tg)}
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
                 O1D + H2 -> OH + H                 : 1.1e-16
                 O1D + H2O -> OH + OH               : 2.2e-16
                 O2a1 + O2 -> O2 + O2               : {3.8e-24*exp(-205/Tg)}
                 O2a1 + O3 -> O + O2 + O2           : {5.2e-17*exp(-2840/Tg)}
                 O2a1 + M -> O2 + M                 : 8e-27
                 O2a1 + NO -> O2 + NO               : 2.5e-17
                 O2a1 + N2 -> O2 + N2               : 1.5e-24
                 O3 + NO -> NO2 + O2                : {1.8e-18*exp(-1370/Tg)}
                 O3 + NO2 -> NO3 + O2               : {1.4e-19*exp(-2470/Tg)}
                 O3 + M -> O + O2 + M               : {3.92e-16*exp(-11400/Tg)}
                 O3 + H -> OH + O2                  : {2.8e-17*(Tg/300)^0.75}
                 O3 + OH -> HO2 + O2                : {1.6e-18*exp(-1000/Tg)}
                 O3 + HO2 -> OH + O2 + O2           : {1.4e-20*exp(-600/Tg)}
                 NO + NO2 + M -> N2O3 + M           : {3.09e-46*(300/Tg)^7.7}
                 NO + NO3 -> NO2 + NO2              : {1.8e-17*exp(110/Tg)}
                 NO + OH + M -> HNO2 + M            : {7.4e-43*(300/Tg)^2.4}
                 NO + H + M -> HNO + M              : {1e-44*exp(300/Tg)}
                 NO + HO2 -> OH + NO2               : {3.4e-18*exp(270/Tg)}
                 NO + HO2 -> O2 + HNO               : {3.3e-19*exp(-1000/Tg)}
                 NO2 + NO2 + M -> N2O4 + M          : {1.17e-45*(300/Tg)^3.8}
                 NO2 + NO3 + M -> N2O5 + M          : {2.8e-42*(300/Tg)^3.5}
                 NO2 + NO3 -> NO2 + NO + O2         : {2.3e-19*exp(-1600/Tg)}
                 NO2 + H -> OH + NO                 : 1.47e-16
                 NO2 + OH + M -> HNO3 + M           : {2.2e-42*(300/Tg)^2.9}
                 NO3 + NO3 -> NO2 + NO2 + O2        : {5e-18*exp(-3000/Tg)}
                 NO3 + H -> OH + NO2                : {5.8e-16*exp(-750/Tg)}
                 NO3 + OH -> HO2 + NO2              : 2e-17
                 NO3 + HO2 -> NO2 + OH + O2         : 4.8e-18
                 NO3 + HO2 -> HNO3 + O2             : 9.2e-19
                 N2O3 + M -> NO + NO2 + M           : {1.03e-16*exp(-2628/Tg)}
                 N2O4 + M -> NO2 + NO2 + M          : {1.09e-13*exp(-4952/Tg)}
                 N2O5 + M -> NO2 + NO3 + M          : {1e-9*(300/Tg)^3.5*exp(-11000/Tg)}
                 H + O2 + M -> HO2 + M              : {5.4e-44*(Tg/300)^(-1.8)}
                 H + H + M -> H2 + M                : {1.8e-42/Tg}
                 H + OH + M -> H2O + M              : {6.1e-38/(Tg^2)}
                 H + H2O2 -> OH + H2O               : {1.69e-17*exp(-1800/Tg)}
                 H + H2O2 -> HO2 + H2               : {2.8e-18*exp(-1900/Tg)}
                 H + HO2 -> H2 + O2                 : 5.6e-18
                 H + HO2 -> O + H2O                 : 2.4e-18
                 H + HO2 -> OH + OH                 : {4.2e-16*exp(-950/Tg)}
                 H + HNO -> NO + H2                 : {3e-17*exp(-500/Tg)}
                 H + HNO2 -> NO2 + H2               : {2e-17*exp(-3700/Tg)}
                 H + HNO3 -> NO2 + H2O              : {1.39e-20*(Tg/298)^3.29*exp(-3160/Tg)}
                 H2 + OH ->  H + H2O                : {3.2e-17*exp(-2600/Tg)}
                 OH + OH -> O + H2O                 : {8.8e-18*exp(-503/Tg)}
                 OH + OH + M -> H2O2 + M            : {6.9e-43*(Tg/300)^(-0.8)}
                 OH + HO2 -> O2 + H2O               : {4.8e-17*exp(250/Tg)}
                 OH + H2O2 -> HO2 + H2O             : {2.9e-18*exp(250/Tg)}
                 OH + HNO -> NO + H2O               : {8e-17*exp(-500/Tg)}
                 OH + HNO2 -> NO2 + H2O             : {1.8e-17*exp(-390/Tg)}
                 OH + HNO3 -> NO3 + H2O             : {1.5e-20*exp(650/Tg)}
                 HO2 + HO2 -> H2O2 + O2             : {2.2e-19*exp(600/Tg)}
                 HNO + O2 -> NO + HO2               : {5.25e-18*exp(-1510/Tg)}
                 HNO + O2 -> NO2 + OH               : 1.66e-21
                 HNO + HNO -> N2O + H2O             : {1.4e-21*exp(-1600/Tg)}
                 HNO2 + HNO2 -> NO + NO2 + H2O      : 1e-26
                 HNO2 + HNO3 -> NO2 + NO2 + H2O     : 1.6e-23'
  [../]
[]
