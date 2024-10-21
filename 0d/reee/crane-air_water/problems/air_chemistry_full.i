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
    initial_condition = 1e18
    #scaling = 1e-26
  [../]
  [./N2]
    family = SCALAR
    order = FIRST
    initial_condition = 1.834268645908762e19
    #scaling = 1e-27
  [../]

  [./N2v1]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-25
  [../]

  [./N2v2]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-24
  [../]

  [./N2v3]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-23
  [../]

  [./N2v4]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-23
  [../]

  [./N2v5]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-23
  [../]

  [./N2v6]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-23
  [../]

  [./N2v7]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-23
  [../]

  [./N2v8]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-22
  [../]

  [./N2A3]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-9
  [../]

  [./N2B3]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-9
  [../]

  [./N2a_1]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-8
  [../]

  [./N2C3]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-10
  [../]

  [./N]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-28
  [../]

  [./N2D]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-10
  [../]

  [./N2meta]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-9
  [../]

  [./N+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 1e18
    #initial_condition = 1e12
    #scaling = 1e-10
  [../]

  [./N2+]
    family = SCALAR
    order = FIRST
    initial_condition = 0 
    #scaling = 1e10
  [../]

  [./N3+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  [../]

  [./N4+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e10
  [../]

  [./O2]
    # Air is N2-O2 at ratio of 4:1
    family = SCALAR
    order = FIRST
    initial_condition = 6.114228819695872e18
    #scaling = 1e-28
  [../]

  [./O2v1]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-24
  [../]

  [./O2v2]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-23
  [../]

  [./O2v3]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-23
  [../]

  [./O2v4]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-23
  [../]

  [./O2a1]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-23
  [../]

  [./O2b1]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-20
  [../]

  [./O24_ev]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-13
  [../]

  [./O]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-25
  [../]

  [./O1D]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-7
  [../]

  [./O1S]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-6
  [../]

  [./O3]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-7
  [../]

  [./O+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-26
  [../]

  [./O2+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-24
  [../]

  [./O4+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  [../]

  [./O-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-6
  [../]

  [./O2-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-22
  [../]

  [./O3-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-5
  [../]

  [./O4-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  [../]

  [./NO]
    family = SCALAR
    order = FIRST
    initial_condition = 1
    #scaling = 1e-6
  [../]

  [./NO+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-26
  [../]

  [./NO-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
    #scaling = 1e-10
  [../]

  [./O2pN2]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  [../]

  # Additional nitrogen-oxygen species

  [./N2O]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  [../]

  [./NO2]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  [../]

  [./NO3]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  [../]

  [./N2O5]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  [../]

  [./N2O+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  [../]

  [./NO2+]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  [../]

  [./N2O-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  [../]

  [./NO2-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
  [../]

  [./NO3-]
    family = SCALAR
    order = FIRST
    initial_condition = 0
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

  [./N2v1_time_deriv]
    type = ODETimeDerivative
    variable = N2v1
  [../]

  [./N2v2_time_deriv]
    type = ODETimeDerivative
    variable = N2v2
  [../]

  [./N2v3_time_deriv]
    type = ODETimeDerivative
    variable = N2v3
  [../]

  [./N2v4_time_deriv]
    type = ODETimeDerivative
    variable = N2v4
  [../]

  [./N2v5_time_deriv]
    type = ODETimeDerivative
    variable = N2v5
  [../]

  [./N2v6_time_deriv]
    type = ODETimeDerivative
    variable = N2v6
  [../]

  [./N2v7_time_deriv]
    type = ODETimeDerivative
    variable = N2v7
  [../]

  [./N2v8_time_deriv]
    type = ODETimeDerivative
    variable = N2v8
  [../]

  [./N2A3_time_deriv]
    type = ODETimeDerivative
    variable = N2A3
  [../]

  [./N2B3_time_deriv]
    type = ODETimeDerivative
    variable = N2B3
  [../]

  [./N2a_1_time_deriv]
    type = ODETimeDerivative
    variable = N2a_1
  [../]

  [./N2C3_time_deriv]
    type = ODETimeDerivative
    variable = N2C3
  [../]

  [./N_time_deriv]
    type = ODETimeDerivative
    variable = N
  [../]

  [./N2D_time_deriv]
    type = ODETimeDerivative
    variable = N2D
  [../]

  [./N2meta_time_deriv]
    type = ODETimeDerivative
    variable = N2meta
  [../]

  [./Np_time_deriv]
    type = ODETimeDerivative
    variable = N+
  [../]

  [./N2meta_time_deriv]
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

  [./O2v1_time_deriv]
    type = ODETimeDerivative
    variable = O2v1
  [../]

  [./O2v2_time_deriv]
    type = ODETimeDerivative
    variable = O2v2
  [../]

  [./O2v3_time_deriv]
    type = ODETimeDerivative
    variable = O2v3
  [../]

  [./O2v4_time_deriv]
    type = ODETimeDerivative
    variable = O2v4
  [../]

  [./O2a1_time_deriv]
    type = ODETimeDerivative
    variable = O2a1
  [../]

  [./O2b1_time_deriv]
    type = ODETimeDerivative
    variable = O2b1
  [../]

  [./O24_ev_time_deriv]
    type = ODETimeDerivative
    variable = O24_ev
  [../]

  [./O_time_deriv]
    type = ODETimeDerivative
    variable = O
  [../]

  [./O1D_time_deriv]
    type = ODETimeDerivative
    variable = O1D
  [../]

  [./O1S_time_deriv]
    type = ODETimeDerivative
    variable = O1S
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

  [./O2pN2_time_deriv]
    type = ODETimeDerivative
    variable = O2pN2
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
  [./Te]
    order = FIRST
    family = SCALAR
    initial_condition = 32000
  [../]
  [./test]
    order = FIRST
    family = SCALAR
  [../]
  
  [./NEUTRAL]
    # For now, NEUTRAL = N2 + O2
    order = FIRST
    family = SCALAR
    #initial_condition = 2.445692e19
  [../]

  #[./ION]
  #  order = FIRST
  #  family = SCALAR
  #[../]

  [./reduced_field]
    # Units: Td
    order = FIRST
    family = SCALAR
    #initial_condition = 100
  [../]
  #[./voltage]
  #  order = FIRST
  #  family = SCALAR
  #  # for testing purposes only
  #[../]

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
  [./Te_read]
    type = DataReadScalar
    variable = Te
    sampler = reduced_field
    scale_factor = 7733.52643
    property_file = 'air_test/electron_energy.txt'
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  [../]

  [./test_calc]
    type = FunctionScalarAux
    variable = test
    #function = test_func
    function = dts
    execute_on = 'initial timestep_begin'
  [../]

  [./field_calc]
    type = FunctionScalarAux
    variable = reduced_field
    function = reduced_field_time
    execute_on = 'initial timestep_begin'
  [../]

  #[./voltage_calc]
  #  type = FunctionScalarAux
  #  variable = voltage
  #  function = voltage_time
  #  execute_on = 'initial timestep_begin'
  #[../]

  [./neutral_sum]
    type = VariableSum
    variable = NEUTRAL
    args = 'N2 O2 N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N2A3 N2B3 N2a_1 N2C3 N N2D N2meta O2v1 O2v2 O2v3 O2v4 O2a1 O2b1 O24_ev O O1D O1S O3 NO N2O NO2 NO3 N2O5'
    execute_on = 'initial linear nonlinear'
  [../]

  #[./ion_sum]
  #  type = VariableSum
  #  variable = ION
  #  args = 'N+ N2+ N3+ N4+ O+ O2+ O4+ O- O2- O3- O4- NO+ NO- O2pN2'
  #  execute_on = 'initial timestep_end'
  #[../]
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
    #value = 'abs((A * exp(-d*(t%Tr-xoff)) * sin(w*(t%Tr-xoff) - 6.08777077)))*1e6 / 2.445692e4' 
    #value = 'abs((A * exp(-d*(t%Tr-xoff)) * sin(w*(t%Tr-xoff) - 6.08777077))*(0.5 + 0.5*tanh(1e9*((t%Tr)-5e-9))))*1e6 / 2.445692e4' 
    value = 'abs((A * exp(-d*(t%Tr-xoff)) * sin(w*(t%Tr-xoff) - 6.083))*(0.5 + 0.5*tanh(1e9*((t%Tr)-5e-9))))*1e6 / 2.445692e4' 

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
    value = '(0.5999e-7*tanh(2e4*(t%Tr)) + 2e-11)*(1.0 - 0.999*(0.5 + 0.5*tanh((t%Tr - 0.998e-4)/5e-9)))'
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
  end_time = 0.004
  line_search = 'basic'
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -snes_linesearch_minlambda -snes_stol -ksp_type'
  petsc_options_value = 'lu NONZERO 1.e-10 1e-3 0 fgmres'
  nl_rel_tol = 1e-8
  nl_abs_tol = 1e4  # Note that abs_tol in this case refers to number density. 
  l_max_its = 50
  [./TimeStepper]
    type = FunctionDT
    function = dts
    min_dt = 1e-16
  [../]
[]

[Outputs]
  [./test]
    type = CSV
    show = 'N2 N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N2A3 N2B3 N2a_1 N2C3 N N2D N2meta N+ N2+ N3+ N4+ O2 O2v1 O2v2 O2v3 O2v4 O2a1 O2b1 O24_ev O O1D O1S O3 O+ O2+ O4+ O- O2- O3- O4- NO NO+ NO- O2pN2 e N2O NO2 NO3 N2O5 N2O+ NO2+ N2O- NO2- NO3- reduced_field Te'
  [../]
  [./console]
    type = Console
    execute_scalars_on = 'none'
  [../]
[]

[ChemicalReactions]
  [./ScalarNetwork]
    species = 'N2 N2A3 N2B3 N2a_1 N2C3 N N2D N2meta N+ N2+ N3+ N4+ O2 O2a1 O2b1 O24_ev O O1D O1S O3 O+ O2+ O4+ O- O2- O3- O4- NO N2O NO2 NO3 N2O5 NO+ N2O+ NO2+ NO- N2O- NO2- NO3- O2pN2 e'
    num_particles = '2 2 2 2 2 2 2 2 2 2 2 2 2 1 1 1 1 2 3 4 2 2 2 2 2 2 2 2 1 1 1 3 1 2 4 1 2 3 4 2 3 3 4 7 2 3 3 2 3 3 4 4 1'
    balance_check = true
    charge_balance_check = false
    aux_species = 'NEUTRAL'
    #species = 'N2 N2A3 N2B3 N2a_1 N2C3 N N2D N2meta N+ N2+ N3+ N4+ O2 O2a1 O2b1 O24_ev O O1D O1S O3 O+ O2+ O4+ O- O2- O3- O4- NO N2O NO2 NO3 N2O5 NO+ N2O+ NO2+ NO- N2O- NO2- NO3- O2pN2'
    #aux_species = 'NEUTRAL e'
    #aux_species = 'e'
    reaction_coefficient_format = 'rate'
    include_electrons = true
    file_location = 'air_test'
    electron_density = 'e'
    #equation_variables = 'TeffN TeffN2 TeffN3 TeffN4 TionN TionN2 TionN3 TionN4'
    #equation_constants = 'Te Tgas'
    ##equation_values = '4 300'
    #equation_values = '32480 300'
    equation_variables = 'TeffN TeffN2 TeffN3 TeffN4 TionN TionN2 TionN3 TionN4 Te'
    equation_constants = 'Tgas'
    equation_values = '300'
    rate_provider_var = 'reduced_field'
    #lumped_species = true
    #lumped = 'N2 O2 N2A3 N2B3 N2a_1 N2C3 N N2D N2meta O2a1 O2b1 O24_ev O O1D O1S O3 NO'
    #lumped_name = 'NEUTRAL'
    track_rates = false

    # NOTE: rate coefficients units are cm^3 s^-1
    reactions = '
                 e + N2+ -> N + N2meta                 : {1.8e-7 * (300/Te)^0.39 * 0.05}
                 ####
                 # electron detachment
                 ####
                 O2- + O2 -> O2  + O2 + e             : {2.7e-10 * (TeffN2/300)^0.5 * exp(-5590/TeffN2)}
                 O2- + N2 -> O2  + N2 + e             : {1.9e-12 * (TeffN2/300)^0.5 * exp(-4990/TeffN2)}
                 N2A3 + N -> N2 + N2meta              : {4.0e-11 * (300/Tgas)^0.667}
                 ####
                 # deactivation of N metastables (Capitelli2000, page 161)
                 ####
                 N2meta + N -> N + N                     : 1.8e-12
                 N2meta + O -> N + O                     : 1.0e-12
                 N2meta + N2 -> N + N2                   : 6.0e-14
                 N2meta + O2 -> NO + O                   : 2.6e-12
                 N2meta + NO -> N2A3 + O                 : 3.0e-11
                 ####
                 # quenching and excitation of O2 (Capitelli2000, page 160)
                 ####

                 ####
                 # bimolecular nitrogen-oxygen reactions (Capitelli2000, page 168)
                 # Two missing reactions: 
                 # N + O3 -> NO + O2 : < 2.0e-16
                 ####
                 
                 ####
                 # dissociation of nitrogen-oxygen molecules (Capitelli2000, page 169)
                 ####
                 
                 ####
                 # positive ion reactions (Capitelli, 179)
                 ####
                 O+ + N2 -> NO+ + N                               : {( 1.5 - 2.0e-3*TeffN + 9.6e-7*TeffN^2 ) * 1.0e-12}
                 O+ + O2 -> O2+ + O                               : {2.0e-11 * (300/TeffN)^0.5}
                 O+ + O3 -> O2+ + O2                              : 1.0e-10
                 O+ + NO -> O2+ + N                               : 3.0e-12
                 N2+ + O2 -> O2+ + N2                             : {6.0e-11 * (300/TeffN2)^0.5}
                 N2+ + O  -> NO+ + N                              : {1.3e-10 * (300/TeffN2)^0.5}
                 N2+ + O3 -> O2+ + O + N2                         : 1.0e-10
                 N2+ + N  -> N+ + N2                              : {7.2e-13 * (TeffN2/300)}
                 ####
                 O-   + O2a1 -> O2-  + O                          : 1.0e-10
                 O2-  + O -> O-   + O2                            : 3.3e-10
                 ####
                 # ion-ion recombination (Kossyi1992)
                 ####
                                 
  [../]
[]
######################
                 

                 [O2p_secondary_energy_left]
                  type = SecondaryElectronEnergyBC
                  variable = mean_en
                  boundary = 'left'
                  potential = potential
                  em = em
                  ip = 'O2p'
                  r = 0
                  position_units = ${dom0Scale}
                  
                []
                 