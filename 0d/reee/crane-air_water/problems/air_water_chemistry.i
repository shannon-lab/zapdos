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
    initial_condition = 1e14
    #scaling = 1e-26
  [../]
  [./N2]
    family = SCALAR
    order = FIRST
    initial_condition = 1.834268645908762e19
    #scaling = 1e-27
  [../]

  [./N2A3]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 3.63397
    #scaling = 1e-9
  [../]

  [./N2B3]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 4.57333
    #scaling = 1e-9
  [../]

  [./N2a_1]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 1.00005
    #scaling = 1e-8
  [../]

  [./N2C3]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 0.979987
    #scaling = 1e-10
  [../]

  [./N]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 2.50519e12
    #scaling = 1e-28
  [../]

  [./N2D]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 4.90944e8
    #scaling = 1e-10
  [../]

  [./N2P]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 5.97146
    #scaling = 1e-9
  [../]

  [./N+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    #initial_condition = 1e14
    initial_condition = 9.51022e13
    #initial_condition = 1e12
    #scaling = 1e-10
  [../]

  [./N2+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0 
    initial_condition = 562515
    #scaling = 1e10
  [../]

  [./N3+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 7.30428e11
  [../]

  [./N4+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 16692
    #scaling = 1e10
  [../]

  [./O2]
    # Air is N2-O2 at ratio of 4:1
    family = SCALAR
    order = FIRST
    #initial_condition = 6.114228819695872e18
    initial_condition = 6.11423e18
    #scaling = 1e-28
  [../]

  [./O2a1]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 2.05996e8 
    #scaling = 1e-23
  [../]

  [./O2b1]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 8.57187e7
    #scaling = 1e-20
  [../]

  [./O24_ev]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 3901.58
    #scaling = 1e-13
  [../]

  [./O]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 1.45757e12
    #scaling = 1e-25
  [../]

  [./O1D]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 3.76547e10
    #scaling = 1e-7
  [../]

  [./O1S]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 2.14747e7
    #scaling = 1e-6
  [../]

  [./O3]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 1.36604e6
    #scaling = 1e-7
  [../]

  [./O+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 1.54331e11
    #scaling = 1e-26
  [../]

  [./O2+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 1.63506e12
    #scaling = 1e-24
  [../]

  [./O4+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 1.70956e8
  [../]

  [./O-]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 1017.8
    #scaling = 1e-6
  [../]

  [./O2-]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 1.06135e10
    #scaling = 1e-22
  [../]

  [./O3-]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 0.662671
    #scaling = 1e-5
  [../]

  [./O4-]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 2.519e8
  [../]

  [./NO]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 1.62814e11
    #scaling = 1e-6
  [../]

  [./NO+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 1.50926e12
    #scaling = 1e-26
  [../]

  [./NO-]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 383.94
    #scaling = 1e-10
  [../]

  [./O2pN2]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 8.7229e8
  [../]

  # Additional nitrogen-oxygen species

  [./N2O]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 1.09353
  [../]

  [./NO2]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 2.32561e6
  [../]

  [./NO3]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 36905.5
  [../]

  [./N2O5]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 1
  [../]

  [./N2O+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 83.2304
  [../]

  [./NO2+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 1.96466e9
  [../]

  [./N2O-]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 2.65752e-9
  [../]

  [./NO2-]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 0.000222808
  [../]

  [./NO3-]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 0.00102693
  [../]

  # Hydrogen species
  [./H+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 0.471921
  [../]

  [./H2+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 1.02207e-8
  [../]

  [./H3+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 3.28593e-16
  [../]

  [./OH+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 737.52
  [../]

  [./H2O+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 2.76098e11
  [../]

  [./H3O+]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 1.17493e9
  [../]

  [./H-]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 5.36936e-69
  [../]

  [./OH-]
    family = SCALAR
    order = FIRST
    #initial_condition = 0
    initial_condition = 4.43415
  [../]

  [./H]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 4.91087e8
  [../]

  [./H2]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 8.77879e10
  [../]

  [./OH]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 1.66475e9
  [../]

  [./HO2]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 1.11263
  [../]

  [./H2O2]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 1
  [../]

  [./HNO]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 0.999998
  [../]

  [./HNO2]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 1
  [../]

  [./HNO3]
    family = SCALAR
    order = FIRST
    #initial_condition = 1
    initial_condition = 0.99995
  [../]

  [./H2O]
    family = SCALAR
    order = FIRST
    #initial_condition = 2.504e17
    initial_condition = 2.504e17
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

  [./N2P_time_deriv]
    type = ODETimeDerivative
    variable = N2P
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

  # Hydrogen species
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
    property_file = 'air_test_04/electron_energy.txt'
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
    args = 'N2 O2 N2A3 N2B3 N2a_1 N2C3 N N2D N2P O2a1 O2b1 O24_ev O O1D O1S O3 NO N2O NO2 NO3 N2O5 H H2 OH HO2 H2O2 HNO HNO2 HNO3 H2O'
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
    value = '(0.5999e-7*tanh(2e4*(t%Tr)) + 1e-10)*(1.0 - 0.999*(0.5 + 0.5*tanh((t%Tr - 0.998e-4)/5e-9)))'
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
  #resid_vs_jac_scaling_param = 1
  #verbose = true
  #compute_scaling_once = false
  #end_time = 1e4
  end_time = 0.004
  dtmax = 1e-7
  line_search = 'basic'
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  #num_steps = 100
  #solve_type = PJFNK
  #solve_type = JFNK
  #solve_type = LINEAR
  #scheme = bdf2
  #scheme = crank-nicolson
  [./TimeIntegrator]
    #type = ActuallyExplicitEuler
    #type = ImplicitEuler
    #type = BDF2
    #type = ImplicitMidpoint
    type = LStableDirk2
    #type = LStableDirk2
    #type =  AStableDirk4
  [../]
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
  nl_abs_tol = 1e4  # Note that abs_tol in this case refers to number density. 
  #nl_abs_tol = 1e-10
  dtmin = 1e-20
  #dtmax = 1.1e-10
  #dtmax = 2e-9
  #dtmax = 1e-4
  l_max_its = 50
  #dt = 5e-11
  #num_steps = 54
  #steady_state_detection = true
  [./TimeStepper]
    type = IterationAdaptiveDT
    cutback_factor = 0.4
    dt = 1e-11
    # dt = 1.1
    growth_factor = 1.1
    optimal_iterations = 20
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
  #  e_max = 1e-8
  #  e_tol = 1e-7
  #[../]
[]

[Outputs]
  #[./species]
  #  type = CSV
  #  interval = 1
  #  show = 'N2 N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N2A3 N2B3 N2a_1 N2C3 N N2D N2P N+ N2+ N3+ N4+ O2 O2v1 O2v2 O2v3 O2v4 O2a1 O2b1 O24_ev O O1D O1S O3 O+ O2+ O4+ O- O2- O3- O4- NO NO+ NO- O2pN2 e N2O NO2 NO3 N2O5 N2O+ NO2+ N2O- NO2- NO3- reduced_field test'
  #[../]
  #[./reactions]
  #  type = CSV
  #  interval = 1
  #  hide = 'N2 N2v1 N2v2 N2v3 N2v4 N2v5 N2v6 N2v7 N2v8 N2A3 N2B3 N2a_1 N2C3 N N2D N2P N+ N2+ N3+ N4+ O2 O2v1 O2v2 O2v3 O2v4 O2a1 O2b1 O24_ev O O1D O1S O3 O+ O2+ O4+ O- O2- O3- O4- NO NO+ NO- O2pN2 e N2O NO2 NO3 N2O5 N2O+ NO2+ N2O- NO2- NO3- reduced_field test'
  #[../]
  [./temp]
    type = CSV
    show = 'N2 N2A3 N2B3 N2a_1 N2C3 N N2D N2P N+ N2+ N3+ N4+ O2 O2a1 O2b1 O24_ev O O1D O1S O3 O+ O2+ O4+ O- O2- O3- O4- NO NO+ NO- O2pN2 e N2O NO2 NO3 N2O5 N2O+ NO2+ N2O- NO2- NO3- H+ H2+ H3+ OH+ H2O+ H3O+ H- OH- H H2 OH HO2 H2O2 HNO HNO2 HNO3 H2O reduced_field Te'
  #execute_scalars_on = 'INITIAL TIMESTEP_END'
  [../]
  [./console]
    type = Console
    execute_scalars_on = 'none'
  [../]
[]

[ChemicalReactions]
  [./ScalarNetwork]
    species = 'N2 N2A3 N2B3 N2a_1 N2C3 N N2D N2P N+ N2+ N3+ N4+ O2 O2a1 O2b1 O24_ev O O1D O1S O3 O+ O2+ O4+ O- O2- O3- O4- NO N2O NO2 NO3 N2O5 NO+ N2O+ NO2+ NO- N2O- NO2- NO3- O2pN2 H+ H2+ H3+ OH+ H2O+ H3O+ H- OH- H H2 OH HO2 H2O2 HNO HNO2 HNO3 H2O e'
    num_particles = '2 2 2 2 2 1 1 1 1 2 3 4 2 2 2 2 1 1 1 3 1 2 4 1 2 3 4 2 3 3 4 7 2 3 3 2 3 3 4 4 1 2 3 2 3 4 1 2 1 2 2 3 4 3 4 5 3 1'
    balance_check = true
    charge_balance_check = false
    aux_species = 'NEUTRAL'
    reaction_coefficient_format = 'rate'
    include_electrons = true
    file_location = 'air_test_04'
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
    #lumped = 'N2 O2 N2A3 N2B3 N2a_1 N2C3 N N2D N2P O2a1 O2b1 O24_ev O O1D O1S O3 NO N2O NO2 NO3 N2O5 H H2 OH HO2 H2O2 HNO HNO2 HNO3 H2O'
    #lumped_name = 'NEUTRAL'
    track_rates = false

    # NOTE: rate coefficients units are cm^3 s^-1
    reactions = 'e + H2O -> H2O+ + e + e            : EEDF (C30_H2O_Ionization_13.50_eV) 
                 e + H2O -> H+ + OH + e + e         : EEDF (C31_H2O_Ionization_16.90_eV)
                 e + H2O -> OH+ + H + e + e         : EEDF (C32_H2O_Ionization_18.12_eV)
                 e + H2O -> O+ + H2 + e + e         : EEDF (C33_H2O_Ionization_19.00_eV)
                 e + H2O -> H2+ + O + e + e         : EEDF (C34_H2O_Ionization_20.70_eV)
                 e + H2O -> OH + H + e              : EEDF (C28_H2O_Excitation_0.0000_eV)
                 e + H2O -> H2 + O1D + e            : EEDF (C29_H2O_Excitation_0.0000_eV) 
                 e + H2  -> H + H + e               : EEDF (C76_H2_Excitation_8.90_eV)
                 e + H2 -> H2+ + e + e              : EEDF (C77_H2_Ionization_15.40_eV)
                 e + H2O -> H- + OH                 : EEDF (C25_H2O_Attachment)
                 e + H2O -> O- + H2                 : EEDF (C26_H2O_Attachment)
                 e + H2O -> OH- + H                 : EEDF (C27_H2O_Attachment)

                 #####
                 # excitation of electronic levels by electron impact (Bolsig+)
                 # Note that CRANE will need to be modified to allow duplicate reactions here...
                 #####
                 e + N2 -> e + N2A3                 : EEDF (C2_N2_Excitation_6.17_eV)
                 e + N2 -> e + N2A3                 : EEDF (C3_N2_Excitation_7.00_eV)
                 e + N2 -> e + N2A3                 : EEDF (C4_N2_Excitation_7.80_eV)
                 e + N2 -> e + N2B3                 : EEDF (C5_N2_Excitation_7.35_eV)
                 e + N2 -> e + N2B3                 : EEDF (C6_N2_Excitation_7.36_eV)
                 e + N2 -> e + N2B3                 : EEDF (C7_N2_Excitation_8.16_eV)
                 e + N2 -> e + N2a_1                : EEDF (C8_N2_Excitation_8.40_eV)
                 e + N2 -> e + N2a_1                : EEDF (C9_N2_Excitation_8.55_eV)
                 e + N2 -> e + N2a_1                : EEDF (C10_N2_Excitation_8.89_eV)
                 e + N2 -> e + N2C3                 : EEDF (C11_N2_Excitation_11.03_eV)
                 e + N2 -> e + N2C3                 : EEDF (C12_N2_Excitation_11.87_eV)
                 e + N2 -> e + N2C3                 : EEDF (C13_N2_Excitation_12.25_eV)
                 e + N2 -> e + N + N2D              : EEDF (C14_N2_Excitation_13.00_eV)
                 e + O2 -> e + O2a1                 : EEDF (C18_O2_Excitation_0.98_eV)
                 e + O2 -> e + O2b1                 : EEDF (C19_O2_Excitation_1.63_eV)
                 e + O2 -> e + O24_ev               : EEDF (C20_O2_Excitation_4.50_eV)
                 e + O2 -> e + O + O                : EEDF (C21_O2_Excitation_6.00_eV)
                 e + O2 -> e + O + O1D              : EEDF (C22_O2_Excitation_8.40_eV)
                 e + O2 -> e + O + O1S              : EEDF (C23_O2_Excitation_9.97_eV)
                 e + O2a1 -> e + O + O              : EEDF (C41_O2a1_Excitation_6.00_eV)
                 e + O -> e + O1D                   : EEDF (C50_O_Excitation_1.97_eV)
                 e + O -> e + O1S                   : EEDF (C51_O_Excitation_4.19_eV)
                 ####
                 # de-excitation of electronic levels by electron impact (BOLSIG+)
                 ####
                 e + N2A3 -> e + N2                 : EEDF (C35_N2A3_De-excitation_6.17_eV)
                 e + O2a1 -> e + O2                : EEDF (C38_O2a1_De-excitation_0.98_eV)
                 ####
                 # ionization by electron impact (BOLSIG+)
                 # note the missing data section in the inp file (4 extra reactions - not shown here)
                 ####
                 e + N -> e + e + N+                : EEDF (C48_N_Ionization_14.55_eV)
                 e + O -> e + e + O+                : EEDF (C52_O_Ionization_13.62_eV)
                 e + N2 -> e + e + N2+              : EEDF (C15_N2_Ionization_15.60_eV)
                 e + N2A3 -> e + e + N2+            : EEDF (C37_N2A3_Ionization_10.79_eV)
                 e + O2 -> e + e + O2+              : EEDF (C24_O2_Ionization_12.06_eV)
                 e + O2a1 -> e + e + O2+            : EEDF (C42_O2a1_Ionization_11.00_eV)
                 e + O2b1 -> e + e + O2+            : EEDF (C46_O2b1_Ionization_10.40_eV)
                 e + NO -> e + e + NO+              : EEDF (C62_NO_Ionization_9.26_eV)
                 e + N2O -> e + e + N2O+            : EEDF (C75_N2O_Ionization_12.89_eV)
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
                 e + O2 -> O- + O                     : EEDF (C16_O2_Attachment)
                 e + NO -> O- + N                     : EEDF (C53_NO_Attachment)
                 e + O3 -> O- + O2                    : EEDF (C63_O3_Attachment)
                 e + O3 -> O2- + O                    : EEDF (C64_O3_Attachment)
                 e + N2O -> NO- + N                   : EEDF (C67_N2O_Attachment)
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
                 NO- + NO+ + NEUTRAL -> NO + NO + NEUTRAL             : {2e-25 * (300/TionN2)^2.5}
                 e + N2O+ -> N2 + O                 : {2.0e-7 * (300/Te)^0.5}
                 e + NO2+ -> NO + O                 : {2.0e-7 * (300/Te)^0.5}
                 e + NO2 -> O- + NO                   : 1e-11
                 e + N2O + NEUTRAL -> N2O- + NEUTRAL  : 1e-31
                 O-  + NO -> NO2 + e                  : 2.6e-10
                 O-  + N2 -> N2O + e                  : 5.0e-13
                 NO- + N -> N2O + e                   : 5e-10 
                 N2O- + N -> NO + N2 + e              : 5e-10
                 NO2- + N -> NO + NO + e              : 5e-10
                 NO3- + N -> NO + NO2 + e             : 5e-10
                 NO- + O -> NO2 + e                   : 1.5e-10
                 N2O- + O -> NO + NO + e              : 1.5e-10
                 NO2- + O -> NO + O2 + e              : 1.5e-10
                 NO3- + O -> NO + O3 + e              : 1.5e-10
                 N2O- + N2A3 -> N2O + N2 + e          : 2.1e-9
                 NO2- + N2A3 -> NO2 + N2 + e          : 2.1e-9
                 NO3- + N2A3 -> NO3 + N2 + e          : 2.1e-9
                 N2O- + N2B3 -> N2O + N2 + e          : 2.5e-9
                 NO2- + N2B3 -> NO2 + N2 + e          : 2.5e-9
                 NO3- + N2B3 -> NO3 + N2 + e          : 2.5e-9
                 N2A3 + O2 -> N2O + O                 : {2.0e-14 * (Tgas/300)^0.55}
                 N2A3 + N2O -> N2 + N + NO            : 1.0e-11
                 N2A3 + NO2 -> N2 + O + NO            : 1.0e-12
                 N2D + N2O -> NO + N2                 : 3.5e-12
                 O1D + N2O -> NO + NO                 : 7.2e-11
                 O1D + N2O -> O2 + N2                 : 4.4e-11
                 O1S + N2O -> O + N2O                 : 6.3e-12
                 O1S + N2O -> O1D + N2O               : 3.1e-12
                 N + NO2 -> O + O + N2                : 9.1e-13
                 N + NO2 -> O + N2O                   : 3.0e-12
                 N + NO2 -> N2 + O2                   : 7.0e-13
                 N + NO2 -> NO + NO                   : 2.3e-12
                 O2- + N -> NO2 + e                   : 5.0e-10
                 O + NO -> NO2                        : 4.2e-18
                 O + N2O -> N2 + O2                   : {8.3e-12 * exp(-14000/Tgas)}
                 O + N2O -> NO + NO                   : {1.5e-10 * exp(-14090/Tgas)}
                 O + NO2 -> NO + O2                   : {9.1e-12 * (Tgas/300)^0.18}
                 O + NO3 -> O2 + NO2                  : 1.0e-11
                 N2 + O2 -> O + N2O                   : {2.5e-10 * exp(-50390/Tgas)}
                 NO + NO -> N + NO2                   : {3.3e-16 * (300/Tgas)^0.5 * exp(-39200/Tgas)}
                 NO + NO -> O + N2O                   : {2.2e-12 * exp(-32100/Tgas)}
                 NO + O2 -> O + NO2                   : {2.8e-12 * exp(-23400/Tgas)}
                 NO + O3 -> O2 + NO2                  : {2.5e-13 * exp(-765/Tgas)}
                 NO + N2O -> N2 + NO2                 : {4.6e-10 * exp(-25170/Tgas)}
                 NO + NO3 -> NO2 + NO2                : 1.7e-11
                 O2 + NO2 -> NO + O3                  : {2.8e-12 * exp(-25400/Tgas)}
                 NO2 + NO2 -> NO + NO + O2            : {3.3e-12 * exp(-13500/Tgas)}
                 NO2 + NO2 -> NO + NO3                : {4.5e-10 * exp(-18500/Tgas)}
                 NO2 + O3 -> O2 + NO3                 : {1.2e-13 * exp(-2450/Tgas)}
                 NO2 + NO3 -> NO + NO2 + O2           : {2.3e-13 * exp(-1600/Tgas)}
                 NO3 + O2 -> NO2 + O3                 : {1.5e-12 * exp(-15020/Tgas)}
                 NO3 + NO3 -> O2 + NO2 + NO2          : {4.3e-12 * exp(-3850/Tgas)}
                 N2O + N2 -> N2 + O + N2              : {1.2e-8 * (300/Tgas) * exp(-29000/Tgas)}
                 N2O + O2 -> N2 + O + O2              : {1.2e-8 * (300/Tgas) * exp(-29000/Tgas)}
                 N2O + NO -> N2 + O + NO              : {1.2e-8 * (300/Tgas) * exp(-29000/Tgas) * 2}
                 N2O + N2O -> N2 + O + N2O            : {1.2e-8 * (300/Tgas) * exp(-29000/Tgas) * 4}
                 NO2 + N2 -> N2 + O + N2              : {6.8e-6 * (300/Tgas)^2 * exp(-36180/Tgas)}
                 NO2 + O2 -> N2 + O + O2              : {6.8e-6 * (300/Tgas)^2 * exp(-36180/Tgas) * 0.78}
                 NO2 + NO -> N2 + O + NO              : {6.8e-6 * (300/Tgas)^2 * exp(-36180/Tgas) * 7.8}
                 NO2 + NO2 -> N2 + O + NO2            : {6.8e-6 * (300/Tgas)^2 * exp(-36180/Tgas) * 5.9}
                 NO3 + N2 -> NO2 + O + N2             : {3.1e-5 * (300/Tgas)^2 * exp(-25000/Tgas)}
                 NO3 + O2 -> NO2 + O + O2             : {3.1e-5 * (300/Tgas)^2 * exp(-25000/Tgas)}
                 NO3 + NO -> NO2 + O + NO             : {3.1e-5 * (300/Tgas)^2 * exp(-25000/Tgas)}
                 NO3 + N -> NO2 + O + N               : {3.1e-5 * (300/Tgas)^2 * exp(-25000/Tgas) * 10}
                 NO3 + O -> NO2 + O + O               : {3.1e-5 * (300/Tgas)^2 * exp(-25000/Tgas) * 10}
                 NO3 + N2 -> NO + O2 + N2             : {6.2e-5 * (300/Tgas)^2 * exp(-25000/Tgas)}
                 NO3 + O2 -> NO + O2 + O2             : {6.2e-5 * (300/Tgas)^2 * exp(-25000/Tgas)}
                 NO3 + NO -> NO + O2 + NO             : {6.2e-5 * (300/Tgas)^2 * exp(-25000/Tgas)}
                 NO3 + N -> NO + O2 + N               : {6.2e-5 * (300/Tgas)^2 * exp(-25000/Tgas) * 12}
                 NO3 + O -> NO + O2 + O               : {6.2e-5 * (300/Tgas)^2 * exp(-25000/Tgas) * 12}
                 N2O5 + NEUTRAL -> NO2 + NO3 + NEUTRAL : {2.1e-11 * (300/Tgas)^4.4 * exp(-11080/Tgas)}
                 O + N2 + NEUTRAL -> N2O + NEUTRAL    : {3.9e-35 * exp(-10400/Tgas)}
                 O + NO + N2 -> NO2 + N2              : {1.2e-31 * (300/Tgas)^1.8}
                 O + NO + O2 -> NO2 + O2              : {1.2e-31 * (300/Tgas)^1.8 * 0.78}
                 O + NO + NO -> NO2 + NO              : {1.2e-31 * (300/Tgas)^1.8 * 0.78}
                 O + NO2 + N2 -> NO3 + N2             : {8.9e-32 * (300/Tgas)^2}
                 O + NO2 + O2 -> NO3 + O2             : {8.9e-32 * (300/Tgas)^2}
                 O + NO2 + N -> NO3 + N               : {8.9e-32 * (300/Tgas)^2 * 13}
                 O + NO2 + O -> NO3 + O               : {8.9e-32 * (300/Tgas)^2 * 13}
                 O + NO2 + NO -> NO3 + NO             : {8.9e-32 * (300/Tgas)^2 * 2.4}
                 NO2 + NO3 + NEUTRAL -> N2O5 + NEUTRAL : {3.7e-30 * (300/Tgas)^4.1}
                 N+ + N2O -> NO+ + N2                             : 5.5e-10
                 O+ + N2O -> NO+ + NO                             : 2.3e-10
                 O+ + N2O -> N2O+ + O                             : 2.2e-10
                 O+ + N2O -> O2+ + N2                             : 2.0e-11
                 O+ + NO2 -> NO2+ + O                             : 1.6e-9
                 N2+ + N2O -> N2O+ + N2                           : 5.0e-10
                 N2+ + N2O -> NO+ + N + N2                        : 4.0e-10
                 N3+ + NO -> N2O+ + N2                            : 7.0e-11
                 NO2+ + NO -> NO+ + NO2                           : 2.9e-10
                 N2O+ + NO -> NO+ + N2O                           : 2.9e-10
                 O-   + NO2 -> NO2- + O                           : 1.2e-9
                 O-   + N2O -> NO-  + NO                          : 2.0e-10
                 O-   + N2O -> N2O- + O                           : 2.0e-12
                 NO-  + NO2 -> NO2- + NO                          : 7.4e-10
                 NO-  + N2O -> NO2- + N2                          : 2.8e-14
                 NO2- + O3 -> NO3- + O2                           : 1.8e-11
                 NO2- + NO2 -> NO3- + NO                          : 4.0e-12
                 NO2- + NO3 -> NO3- + NO2                         : 5.0e-10
                 NO2- + N2O5 -> NO3- + NO2 + NO2                  : 7.0e-10
                 NO3- + NO -> NO2- + NO2                          : 3.0e-15
                 O- + N2O+ -> O + N2O                             : {2e-7 * (300/TionN)^0.5}
                 O- + NO2+ -> O + NO2                             : {2e-7 * (300/TionN)^0.5}
                 O2- + N2O+ -> O2 + N2O                             : {2e-7 * (300/TionN)^0.5}
                 O2- + NO2+ -> O2 + NO2                             : {2e-7 * (300/TionN)^0.5}
                 O3- + N2O+ -> O3 + N2O                             : {2e-7 * (300/TionN)^0.5}
                 O3- + NO2+ -> O3 + NO2                             : {2e-7 * (300/TionN)^0.5}
                 NO- + N2O+ -> NO + N2O                             : {2e-7 * (300/TionN)^0.5}
                 NO- + NO2+ -> NO + NO2                             : {2e-7 * (300/TionN)^0.5}
                 N2O- + N+ -> N2O + N                                 : {2e-7 * (300/TionN)^0.5}
                 N2O- + N2+ -> N2O + N2                               : {2e-7 * (300/TionN)^0.5}
                 N2O- + O+ -> N2O + O                                 : {2e-7 * (300/TionN)^0.5}
                 N2O- + O2+ -> N2O + O2                               : {2e-7 * (300/TionN)^0.5}
                 N2O- + NO+ -> N2O + NO                               : {2e-7 * (300/TionN)^0.5}
                 N2O- + N2O+ -> N2O + N2O                             : {2e-7 * (300/TionN)^0.5}
                 N2O- + NO2+ -> N2O + NO2                             : {2e-7 * (300/TionN)^0.5}
                 NO2- + N+ -> NO2 + N                                 : {2e-7 * (300/TionN)^0.5}
                 NO2- + N2+ -> NO2 + N2                               : {2e-7 * (300/TionN)^0.5}
                 NO2- + O+ -> NO2 + O                                 : {2e-7 * (300/TionN)^0.5}
                 NO2- + O2+ -> NO2 + O2                               : {2e-7 * (300/TionN)^0.5}
                 NO2- + NO+ -> NO2 + NO                               : {2e-7 * (300/TionN)^0.5}
                 NO2- + N2O+ -> NO2 + N2O                             : {2e-7 * (300/TionN)^0.5}
                 NO2- + NO2+ -> NO2 + NO2                             : {2e-7 * (300/TionN)^0.5}
                 NO3- + N+ -> NO3 + N                                 : {2e-7 * (300/TionN)^0.5}
                 NO3- + N2+ -> NO3 + N2                               : {2e-7 * (300/TionN)^0.5}
                 NO3- + O+ -> NO3 + O                                 : {2e-7 * (300/TionN)^0.5}
                 NO3- + O2+ -> NO3 + O2                               : {2e-7 * (300/TionN)^0.5}
                 NO3- + NO+ -> NO3 + NO                               : {2e-7 * (300/TionN)^0.5}
                 NO3- + N2O+ -> NO3 + N2O                             : {2e-7 * (300/TionN)^0.5}
                 NO3- + NO2+ -> NO3 + NO2                             : {2e-7 * (300/TionN)^0.5}
                 O- + N2O+ -> O + N2 + O                            : 1e-7
                 O- + NO2+ -> O + N + O2                            : 1e-7
                 O2- + N2O+ -> O2 + N2 + O                            : 1e-7
                 O2- + NO2+ -> O2 + N + O2                            : 1e-7
                 O3- + N2O+ -> O3 + N2 + O                            : 1e-7
                 O3- + NO2+ -> O3 + N + O2                            : 1e-7
                 NO- + N2O+ -> NO + N2 + O                            : 1e-7
                 NO- + NO2+ -> NO + N + O2                            : 1e-7
                 N2O- + N2+ -> N2O + N + N                            : 1e-7
                 N2O- + N3+ -> N2O + N + N2                           : 1e-7
                 N2O- + N4+ -> N2O + N2 + N2                          : 1e-7
                 N2O- + O2+ -> N2O + O + O                            : 1e-7
                 N2O- + O4+ -> N2O + O2 + O2                          : 1e-7
                 N2O- + NO+ -> N2O + N + O                            : 1e-7
                 N2O- + N2O+ -> N2O + N2 + O                          : 1e-7
                 N2O- + NO2+ -> N2O + N + O2                          : 1e-7
                 N2O- + O2pN2 -> N2O + O2 + N2                        : 1e-7
                 NO2- + N2+ -> NO2 + N + N                            : 1e-7
                 NO2- + N3+ -> NO2 + N + N2                           : 1e-7
                 NO2- + N4+ -> NO2 + N2 + N2                          : 1e-7
                 NO2- + O2+ -> NO2 + O + O                            : 1e-7
                 NO2- + O4+ -> NO2 + O2 + O2                          : 1e-7
                 NO2- + NO+ -> NO2 + N + O                            : 1e-7
                 NO2- + N2O+ -> NO2 + N2 + O                          : 1e-7
                 NO2- + NO2+ -> NO2 + N + O2                          : 1e-7
                 NO2- + O2pN2 -> NO2 + O2 + N2                        : 1e-7
                 NO3- + N2+ -> NO3 + N + N                            : 1e-7
                 NO3- + N3+ -> NO3 + N + N2                           : 1e-7
                 NO3- + N4+ -> NO3 + N2 + N2                          : 1e-7
                 NO3- + O2+ -> NO3 + O + O                            : 1e-7
                 NO3- + O4+ -> NO3 + O2 + O2                          : 1e-7
                 NO3- + NO+ -> NO3 + N + O                            : 1e-7
                 NO3- + N2O+ -> NO3 + N2 + O                          : 1e-7
                 NO3- + NO2+ -> NO3 + N + O2                          : 1e-7
                 NO3- + O2pN2 -> NO3 + O2 + N2                        : 1e-7
                 O4- + N2O+ -> O2 + O2 + N2O                          : 1e-7 
                 O4- + NO2+ -> O2 + O2 + NO2                          : 1e-7 
                 O- + N2+ + NEUTRAL -> N2O + NEUTRAL                  : {2e-25 * (300/TionN)^2.5}
                 O3- + N2O+ + NEUTRAL -> O3 + N2O + NEUTRAL           : {2e-25 * (300/TionN2)^2.5}
                 O3- + NO2+ + NEUTRAL -> O3 + NO2 + NEUTRAL           : {2e-25 * (300/TionN2)^2.5}
                 NO- + N2O+ + NEUTRAL -> NO + N2O + NEUTRAL           : {2e-25 * (300/TionN2)^2.5}
                 NO- + NO2+ + NEUTRAL -> NO + NO2 + NEUTRAL           : {2e-25 * (300/TionN2)^2.5}
                 N2O- + N+ + NEUTRAL -> N2O + N + NEUTRAL             : {2e-25 * (300/TionN2)^2.5}
                 N2O- + N2+ + NEUTRAL -> N2O + N2 + NEUTRAL           : {2e-25 * (300/TionN2)^2.5}
                 N2O- + O+ + NEUTRAL -> N2O + O + NEUTRAL             : {2e-25 * (300/TionN2)^2.5}
                 N2O- + O2+ + NEUTRAL -> N2O + O2 + NEUTRAL           : {2e-25 * (300/TionN2)^2.5}
                 N2O- + NO+ + NEUTRAL -> N2O + NO + NEUTRAL           : {2e-25 * (300/TionN2)^2.5}
                 N2O- + N2O+ + NEUTRAL -> N2O + N2O + NEUTRAL         : {2e-25 * (300/TionN2)^2.5}
                 N2O- + NO2+ + NEUTRAL -> N2O + NO2 + NEUTRAL         : {2e-25 * (300/TionN2)^2.5}
                 NO2- + N+ + NEUTRAL -> NO2 + N + NEUTRAL             : {2e-25 * (300/TionN2)^2.5}
                 NO2- + N2+ + NEUTRAL -> NO2 + N2 + NEUTRAL           : {2e-25 * (300/TionN2)^2.5}
                 NO2- + O+ + NEUTRAL -> NO2 + O + NEUTRAL             : {2e-25 * (300/TionN2)^2.5}
                 NO2- + O2+ + NEUTRAL -> NO2 + O2 + NEUTRAL           : {2e-25 * (300/TionN2)^2.5}
                 NO2- + NO+ + NEUTRAL -> NO2 + NO + NEUTRAL           : {2e-25 * (300/TionN2)^2.5}
                 NO2- + N2O+ + NEUTRAL -> NO2 + N2O + NEUTRAL         : {2e-25 * (300/TionN2)^2.5}
                 NO2- + NO2+ + NEUTRAL -> NO2 + NO2 + NEUTRAL         : {2e-25 * (300/TionN2)^2.5}
                 NO3- + N+ + NEUTRAL -> NO3 + N + NEUTRAL             : {2e-25 * (300/TionN2)^2.5}
                 NO3- + N2+ + NEUTRAL -> NO3 + N2 + NEUTRAL           : {2e-25 * (300/TionN2)^2.5}
                 NO3- + O+ + NEUTRAL -> NO3 + O + NEUTRAL             : {2e-25 * (300/TionN2)^2.5}
                 NO3- + O2+ + NEUTRAL -> NO3 + O2 + NEUTRAL           : {2e-25 * (300/TionN2)^2.5}
                 NO3- + NO+ + NEUTRAL -> NO3 + NO + NEUTRAL           : {2e-25 * (300/TionN2)^2.5}
                 NO3- + N2O+ + NEUTRAL -> NO3 + N2O + NEUTRAL         : {2e-25 * (300/TionN2)^2.5}
                 NO3- + NO2+ + NEUTRAL -> NO3 + NO2 + NEUTRAL         : {2e-25 * (300/TionN2)^2.5}
                 O2+ + NO2 -> NO+ + O3                            : 1.0e-11
                 O2+ + NO2 -> NO2+ + O2                           : 6.6e-10
                 N3+ + O2 -> NO2+ + N2                            : 4.4e-11
                 O2-  + NO2 -> NO2- + O2                          : 7.0e-10
                 O2-  + NO3 -> NO3- + O2                          : 5.0e-10
                 O3-  + NO -> NO3- + O                            : 1.0e-11
                 O3-  + NO -> NO2- + O2                           : 2.6e-12
                 O3-  + NO2 -> NO2- + O3                          : 7.0e-11
                 O3-  + NO2 -> NO3- + O2                          : 2.0e-11
                 O3-  + NO3 -> NO3- + O3                          : 5.0e-10
                 O-  + NO + NEUTRAL -> NO2- + NEUTRAL     : 1.0e-29
                 O- + NO+ + NEUTRAL -> NO2 + NEUTRAL                  : {2e-25 * (300/TionN)^2.5}
                 O2- + N+ + NEUTRAL -> NO2 + NEUTRAL                  : {2e-25 * (300/TionN)^2.5}
                 O4- + NO -> NO3- + O2                            : 2.5e-10
                 O2- + NO+ + NEUTRAL -> NO3 + NEUTRAL                 : {2e-25 * (300/TionN)^2.5}
                 ###########
                 # Water Chemistry
                 ###########
                 e + H2+ -> H + H                   : {1.86e-7/(Te^0.43)}
                 e + H3+ -> H + H2                  : {5.2e-5/(Te^0.5)}
                 e + H3+ -> H + H + H               : {1.14e-5/(Te^0.97)}
                 e + H2O+ -> OH + H                 : {2.73e-6/(Te^0.5)}
                 e + H2O+ -> O + H2                 : {1.37e-6/(Te^0.5)}
                 e + H2O+ -> O + H + H              : {1.37e-6/(Te^0.5)}
                 e + H3O+ -> OH + H + H             : {5.46e-6/(Te^0.5)}
                 e + e + H+ -> H + e                : {1e-25*(Tgas/Te)^4.5}
                 e + e + H2+ -> H2 + e              : {1e-25*(Tgas/Te)^4.5}
                 e + e + OH+ -> OH + e              : {1e-25*(Tgas/Te)^4.5}
                 e + e + H2O+ -> H2O + e            : {1e-25*(Tgas/Te)^4.5}
                 e + HNO3 -> NO2- + OH              : 5e-8
                 O- + H2 -> H2O + e                 : 7e-10
                 O2- + H -> HO2 + e                 : 1.4e-9
                 NO- + H2 -> NO + H2 + e            : 2.3e-13
                 H- + O2 -> HO2 + e                 : 1.2e-9
                 H- + H -> H2 + e                   : 1.8e-9
                 OH- + O -> HO2 + e                 : 2e-10
                 OH- + H -> H2O + e                 : 1.8e-9
                 N+ + OH -> OH+ + N                 : 3.4e-10
                 N+ + OH -> NO+ + H                 : 3.4e-10
                 N+ + H2O -> H2O+ + N               : 1.19e-9
                 N+ + H2O -> NO+ + H2               : 2.1e-10
                 N2+ + H2O -> H2O+ + N2             : 2.3e-9
                 N4+ + H2 -> H2+ + N2 + N2          : {3e-10*exp(-1800/Tgas)}
                 N4+ + H2O -> H2O+ + N2 + N2        : 3e-9
                 O+ + H -> H+ + O                   : 6.8e-10
                 O+ + H2 -> OH+ + H                 : 1.7e-9
                 O+ + OH -> OH+ + O                 : 3.3e-10
                 O+ + OH -> O2+ + H                 : 3.6e-10
                 O+ + H2O -> H2O+ + O               : 3.2e-9
                 O- + H2 -> OH- + H                 : 3.3e-11
                 O- + H2O -> OH- + OH               : 1.4e-9
                 O2- + HNO3 -> NO3- + HO2           : 2.8e-10
                 O3- + H -> OH- + O2                : 8.4e-10
                 NO2- + H -> OH- + NO               : 4e-10
                 NO2- + HNO3 -> NO3- + HNO2         : 1.6e-9
                 H+ + O -> O+ + H                   : 3.8e-10
                 H+ + O2 -> O2+ + H                 : 1.17e-9
                 H+ + NO -> NO+ + H                 : 1.9e-9
                 H+ + H2 + NEUTRAL -> H3+ + NEUTRAL             : 3.1e-35
                 H+ + H2O -> H2O+ + H               : 8.2e-9
                 H- + N2O -> OH- + N2               : 1.1e-9
                 H- + NO2 -> NO2- + H               : 2.9e-9
                 H- + H2O -> OH- + H2               : 3.8e-9
                 H2+ + O2 -> O2+ + H2               : 7.83e-10
                 H2+ + H -> H+ + H2                 : 6.4e-10
                 H2+ + H2 -> H3+ + H                : 2e-9
                 H2+ + H2O -> H3O+ + H              : 3.43e-9
                 H2+ + H2O -> H2O+ + H2             : 3.86e-9
                 H3+ + O -> OH+ + H2                : 8e-10
                 H3+ + H2O -> H3O+ + H2             : 3e-9
                 H3+ + NO2 -> NO+ + OH + H2         : 7e-10
                 OH+ + O2 -> O2+ + OH               : 5.9e-10
                 OH+ + NO -> NO+ + OH               : 5.2e-10
                 OH+ + NO2 -> NO+ + HO2             : 1.3e-9
                 OH+ + N2O -> N2O+ + OH             : 2.13e-10
                 OH+ + H2 -> H2O+ + H               : 9.7e-10
                 OH+ + OH -> H2O+ + O               : 7e-10
                 OH+ + H2O -> H2O+ + OH             : 1.59e-9
                 OH+ + H2O -> H3O+ + O              : 1.3e-9
                 OH- + O3 -> O3- + OH               : 9e-10
                 OH- + NO2 -> NO2- + OH             : 1.9e-9
                 H2O+ + N -> NO+ + H2               : 1.9e-10
                 H2O+ + O -> O2+ + H2               : 5.5e-11
                 H2O+ + O2 -> O2+ + H2O             : 4.3e-10
                 H2O+ + NO -> NO+ + H2O             : 4.6e-10
                 H2O+ + NO2 -> NO2+ + H2O           : 1.2e-9
                 H2O+ + H2 -> H3O+ + H              : 7.6e-10
                 H2O+ + H2O -> H3O+ + OH            : 1.7e-9
                 H3O+ + NO -> NO+ + H + H2O         : 1.5e-12
                 H3O+ + N2O5 ->  NO2+ + HNO3 + H2O  : 5.5e-10
                 O+ + H- -> O + H                   : {2e-7*(300/Tgas)^0.5}
                 O+ + OH- -> O + OH                 : {2e-7*(300/Tgas)^0.5}
                 O2+ + H- -> H + O2                 : {2e-7*(300/Tgas)^0.5}
                 O2+ + H- -> H + O + O              : 1e-7
                 O2+ + OH- -> OH + O2               : {2e-7*(300/Tgas)^0.5}
                 O2+ + OH- -> OH + O + O            : 1e-7
                 O4+ + H- -> H + O2 + O2            : 1e-7
                 O4+ + OH- -> OH + O2 + O2          : 1e-7
                 N+ + H- -> N + H                   : {2e-7*(300/Tgas)^0.5}
                 N+ + OH- -> N + OH                 : {2e-7*(300/Tgas)^0.5}
                 N2+ + H- -> H + N2                 : {2e-7*(300/Tgas)^0.5}
                 N2+ + H- -> H + N + N              : 1e-7
                 N2+ + OH- -> OH + N2               : {2e-7*(300/Tgas)^0.5}
                 N2+ + OH- -> OH + N + N            : 1e-7
                 N2O+ + H- -> H + N2O               : {2e-7*(300/Tgas)^0.5}
                 N2O+ + H- -> H + N2 + O            : 1e-7
                 N2O+ + OH- -> OH + N2O             : {2e-7*(300/Tgas)^0.5}
                 N2O+ + OH- -> OH + N2 + O          : 1e-7
                 N3+ + H- -> H + N2 + N             : 1e-7
                 N3+ + OH- -> OH + N2 + N           : 1e-7
                 N3+ + H- -> H + N2 + N             : 1e-7
                 N3+ + OH- -> OH + N2 + N           : 1e-7
                 NO+ + H- -> H + NO                 : {2e-7*(300/Tgas)^0.5}
                 NO+ + H- -> H + N + O              : 1e-7
                 NO+ + OH- -> OH + NO               : {2e-7*(300/Tgas)^0.5}
                 NO+ + OH- -> OH + N + O            : 1e-7
                 NO2+ + H- -> H + NO2               : {2e-7*(300/Tgas)^0.5}
                 NO2+ + H- -> H + N + O2            : 1e-7
                 NO2+ + OH- -> OH + NO2             : {2e-7*(300/Tgas)^0.5}
                 NO2+ + OH- -> OH + N + O2          : 1e-7
                 H+ + N2O- -> N2O + H               : {2e-7*(300/Tgas)^0.5}
                 H+ + NO- -> NO + H                 : {2e-7*(300/Tgas)^0.5}
                 H+ + NO2- -> NO2 + H               : {2e-7*(300/Tgas)^0.5}
                 H+ + NO3- -> NO3 + H               : {2e-7*(300/Tgas)^0.5}
                 H+ + O- -> O + H                   : {2e-7*(300/Tgas)^0.5}
                 H+ + O2- -> O2 + H                 : {2e-7*(300/Tgas)^0.5}
                 H+ + O3- -> O3 + H                 : {2e-7*(300/Tgas)^0.5}
                 H+ + O4- -> O2 + O2 + H            : 1e-7
                 H+ + H- -> H + H                   : {2e-7*(300/Tgas)^0.5}
                 H+ + OH- -> OH + H                 : {2e-7*(300/Tgas)^0.5}
                 H2+ + N2O- -> N2O + H2             : {2e-7*(300/Tgas)^0.5}
                 H2+ + N2O- -> N2O + H + H          : 1e-7
                 H2+ + NO- -> NO + H2               : {2e-7*(300/Tgas)^0.5}
                 H2+ + NO- -> NO + H + H            : 1e-7
                 H2+ + NO2- -> NO2 + H2             : {2e-7*(300/Tgas)^0.5}
                 H2+ + NO2- -> NO2 + H + H          : 1e-7
                 H2+ + NO3- -> NO3 + H2             : {2e-7*(300/Tgas)^0.5}
                 H2+ + NO3- -> NO3 + H + H          : 1e-7
                 H2+ + O- -> O + H + H              : 1e-7
                 H2+ + O- -> O + H2                 : {2e-7*(300/Tgas)^0.5}
                 H2+ + O2- -> O2 + H + H            : 1e-7
                 H2+ + O2- -> O2 + H2               : {2e-7*(300/Tgas)^0.5}
                 H2+ + O3- -> O3 + H + H            : 1e-7
                 H2+ + O3- -> O3 + H2               : {2e-7*(300/Tgas)^0.5}
                 H2+ + O4- -> O2 + O2 + H2          : 1e-7
                 H2+ + H- -> H + H2                 : {2e-7*(300/Tgas)^0.5}
                 H2+ + H- -> H + H + H              : 1e-7
                 H2+ + OH- -> OH + H2               : {2e-7*(300/Tgas)^0.5}
                 H2+ + OH- -> OH + H + H            : 1e-7
                 H3+ + N2O- -> N2O + H + H2         : 1e-7
                 H3+ + NO- -> NO + H + H2           : 1e-7
                 H3+ + NO2- -> NO2 + H + H2         : 1e-7
                 H3+ + NO3- -> NO3 + H + H2         : 1e-7
                 H3+ + O- -> O + H + H2             : 1e-7
                 H3+ + O2- -> O2 + H + H2           : 1e-7
                 H3+ + O3- -> O3 + H + H2           : 1e-7
                 H3+ + O4- -> O2 + O2 + H + H2      : 1e-7
                 H3+ + H- -> H + H + H2             : 1e-7
                 H3+ + OH- -> OH + H + H2           : 1e-7
                 OH+ + N2O- -> N2O + OH             : {2e-7*(300/Tgas)^0.5}
                 OH+ + N2O- -> N2O + O + H          : 1e-7
                 OH+ + NO- -> NO + OH               : {2e-7*(300/Tgas)^0.5}
                 OH+ + NO- -> NO + O + H            : 1e-7
                 OH+ + NO2- -> NO2 + OH             : {2e-7*(300/Tgas)^0.5}
                 OH+ + NO2- -> NO2 + O + H          : 1e-7
                 OH+ + NO3- -> NO3 + OH             : {2e-7*(300/Tgas)^0.5}
                 OH+ + NO3- -> NO3 + O + H          : 1e-7
                 OH+ + O- -> O + O + H              : 1e-7
                 OH+ + O- -> O + OH                 : {2e-7*(300/Tgas)^0.5}
                 OH+ + O2- -> O2 + O + H            : 1e-7
                 OH+ + O2- -> O2 + OH               : {2e-7*(300/Tgas)^0.5}
                 OH+ + O3- -> O3 + O + H            : 1e-7
                 OH+ + O3- -> O3 + OH               : {2e-7*(300/Tgas)^0.5}
                 OH+ + O4- -> O2 + O2 + OH          : 1e-7
                 OH+ + H- -> H + OH                 : {2e-7*(300/Tgas)^0.5}
                 OH+ + H- -> H + O + H              : 1e-7
                 OH+ + OH- -> OH + OH               : {2e-7*(300/Tgas)^0.5}
                 OH+ + OH- -> OH + O + H            : 1e-7
                 H2O+ + N2O- -> N2O + H2O           : {2e-7*(300/Tgas)^0.5}
                 H2O+ + N2O- -> N2O + OH + H        : 1e-7
                 H2O+ + NO- -> NO + H2O             : {2e-7*(300/Tgas)^0.5}
                 H2O+ + NO- -> NO + OH + H          : 1e-7
                 H2O+ + NO2- -> NO2 + H2O           : {2e-7*(300/Tgas)^0.5}
                 H2O+ + NO2- -> NO2 + OH + H        : 1e-7
                 H2O+ + NO3- -> NO3 + H2O           : {2e-7*(300/Tgas)^0.5}
                 H2O+ + NO3- -> NO3 + OH + H        : 1e-7
                 H2O+ + O- -> O + OH + H            : 1e-7
                 H2O+ + O- -> O + H2O               : {2e-7*(300/Tgas)^0.5}
                 H2O+ + O2- -> O2 + OH + H          : 1e-7
                 H2O+ + O2- -> O2 + H2O             : {2e-7*(300/Tgas)^0.5}
                 H2O+ + O3- -> O3 + OH + H          : 1e-7
                 H2O+ + O3- -> O3 + H2O             : {2e-7*(300/Tgas)^0.5}
                 H2O+ + O4- -> O2 + O2 + H2O        : 1e-7
                 H2O+ + H- -> H + H2O               : {2e-7*(300/Tgas)^0.5}
                 H2O+ + H- -> H + OH + H            : 1e-7
                 H2O+ + OH- -> OH + H2O             : {2e-7*(300/Tgas)^0.5}
                 H2O+ + OH- -> OH + OH + H          : 1e-7
                 H3O+ + N2O- -> N2O + H2O + H       : 1e-7
                 H3O+ + NO- -> NO + H2O + H         : 1e-7
                 H3O+ + NO2- -> NO2 + H2O + H       : 1e-7
                 H3O+ + NO3- -> NO3 + H2O + H       : 1e-7
                 H3O+ + O- -> O + H2O + H           : 1e-7
                 H3O+ + O2- -> O2 + H2O + H         : 1e-7
                 H3O+ + O3- -> O3 + H2O + H         : 1e-7
                 H3O+ + O4- -> O2 + O2 + H2O + H    : 1e-7
                 H3O+ + H- -> H + H2O + H           : 1e-7
                 H3O+ + OH- -> OH + H2O + H         : 1e-7
                 N + OH -> H + NO                   : 7.5e-11
                 N + HO2 -> NO + OH                 : {1.7e-11*exp(-1000/Tgas)}
                 N2A3 + H2O -> H + OH + N2          : 5e-14
                 N2B3 + H2 -> N2A3 + H2             : 2.5e-11
                 O + H + NEUTRAL -> OH + NEUTRAL                : 1.62e-38
                 O + H2O2 -> OH + HO2               : {3.3e-11*exp(-2950/Tgas)}
                 O + HO2 -> OH + O2                 : {8.3e-11*exp(-500/Tgas)}
                 O + HNO -> OH + NO                 : 5.99e-11
                 O + HNO2 -> NO2 + OH               : {2e-11*exp(-3000/Tgas)}
                 O1D + H2 -> OH + H                 : 1.1e-10
                 O1D + H2O -> OH + OH               : 2.2e-10
                 O3 + H -> OH + O2                  : {2.8e-11*(Tgas/300)^0.75}
                 O3 + OH -> HO2 + O2                : {1.6e-12*exp(-1000/Tgas)}
                 O3 + HO2 -> OH + O2 + O2           : {1.4e-14*exp(-600/Tgas)}
                 NO + OH + NEUTRAL -> HNO2 + NEUTRAL            : {7.4e-37*(300/Tgas)^2.4}
                 NO + H + NEUTRAL -> HNO + NEUTRAL              : {1e-38*exp(300/Tgas)}
                 NO + HO2 -> OH + NO2               : {3.4e-12*exp(270/Tgas)}
                 NO + HO2 -> O2 + HNO               : {3.3e-13*exp(-1000/Tgas)}
                 NO2 + OH + NEUTRAL -> HNO3 + NEUTRAL           : {2.2e-36*(300/Tgas)^2.9}
                 NO3 + H -> OH + NO2                : {5.8e-10*exp(-750/Tgas)}
                 NO3 + OH -> HO2 + NO2              : 2e-11
                 NO3 + HO2 -> NO2 + OH + O2         : 4.8e-12
                 NO3 + HO2 -> HNO3 + O2             : 9.2e-13
                 H + O2 + NEUTRAL -> HO2 + NEUTRAL              : {5.4e-38*(Tgas/300)^(-1.8)}
                 H + H + NEUTRAL -> H2 + NEUTRAL                : {1.8e-36/Tgas}
                 H + OH + NEUTRAL -> H2O + NEUTRAL              : {6.1e-32/(Tgas^2)}
                 H + H2O2 -> OH + H2O               : {1.69e-11*exp(-1800/Tgas)}
                 H + H2O2 -> HO2 + H2               : {2.8e-12*exp(-1900/Tgas)}
                 H + HO2 -> H2 + O2                 : 5.6e-12
                 H + HO2 -> O + H2O                 : 2.4e-12
                 H + HO2 -> OH + OH                 : {4.2e-10*exp(-950/Tgas)}
                 H + HNO -> NO + H2                 : {3e-11*exp(-500/Tgas)}
                 H + HNO2 -> NO2 + H2               : {2e-11*exp(-3700/Tgas)}
                 H + HNO3 -> NO2 + H2O              : {1.39e-14*(Tgas/298)^3.29*exp(-3160/Tgas)}
                 H2 + OH ->  H + H2O                : {3.2e-11*exp(-2600/Tgas)}
                 OH + OH -> O + H2O                 : {8.8e-12*exp(-503/Tgas)}
                 OH + OH + NEUTRAL -> H2O2 + NEUTRAL            : {6.9e-37*(Tgas/300)^(-0.8)}
                 OH + HO2 -> O2 + H2O               : {4.8e-11*exp(250/Tgas)}
                 OH + H2O2 -> HO2 + H2O             : {2.9e-12*exp(250/Tgas)}
                 OH + HNO -> NO + H2O               : {8e-11*exp(-500/Tgas)}
                 OH + HNO2 -> NO2 + H2O             : {1.8e-11*exp(-390/Tgas)}
                 OH + HNO3 -> NO3 + H2O             : {1.5e-14*exp(650/Tgas)}
                 HO2 + HO2 -> H2O2 + O2             : {2.2e-13*exp(600/Tgas)}
                 HNO + O2 -> NO + HO2               : {5.25e-12*exp(-1510/Tgas)}
                 HNO + O2 -> NO2 + OH               : 1.66e-15
                 HNO + HNO -> N2O + H2O             : {1.4e-15*exp(-1600/Tgas)}
                 HNO2 + HNO2 -> NO + NO2 + H2O      : 1e-20
                 HNO2 + HNO3 -> NO2 + NO2 + H2O     : 1.6e-17'
                 
  [../]
[]
