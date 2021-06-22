dom0Scale=25.4e-3

[GlobalParams]
  potential_units = kV
  use_moles = true
[]

[Mesh]
  [./geo]
    type = FileMeshGenerator
    file = 'thesis_mesh.msh'
  [../]
[]

[Problem]
  type = FEProblem
  coord_type = RZ
  rz_coord_axis = Y
[]

[Variables]
  [./em]
  [../]

  [./Ar+]
  [../]

  [./Ar*]
  [../]

  [./mean_en]
  [../]

  [./potential]
  [../]

  [./Ex]
    initial_condition = 0.01
  [../]
  [./Ey]
    initial_condition = 0.01
  [../]

  [./SM_Ar*]
    initial_condition = 1.0
  [../]
[]

[Kernels]
#Electron Equations
  #Time Derivative term of electron
  [./em_time_deriv]
    type = TimeDerivativeLog
    variable = em
  [../]
  #Advection term of electron
  [./em_advection]
    type = EFieldAdvection
    variable = em
    potential = potential
    position_units = ${dom0Scale}
  [../]
  #Diffusion term of electrons
  [./em_diffusion]
    type = CoeffDiffusion
    variable = em
    position_units = ${dom0Scale}
  [../]
  #Net electron production from ionization
  [./em_ionization]
    type = ADEEDFReactionLog
    variable = em
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + em + Ar+'
    coefficient = 1
  [../]
  #Net electron production from step-wise ionization
  [./em_stepwise_ionization]
    type = ADEEDFReactionLog
    variable = em
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + em + Ar+'
    coefficient = 1
  [../]
  #Net electron production from metastable pooling
  [./em_pooling]
    type = ReactionSecondOrderLog
    variable = em
    v = Ar*
    w = Ar*
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    coefficient = 1
  [../]

#Argon Ion Equations
  #Time Derivative term of the ions
  [./Ar+_time_deriv]
    type = TimeDerivativeLog
    variable = Ar+
  [../]
  #Advection term of ions
  #[./Ar+_advection]
  #  type = ADEFieldAdvection
  #  variable = Ar+
  #  potential = potential
  #  position_units = ${dom0Scale}
  #[../]
  [./Ar+_advection]
    type = EffectiveEFieldAdvection
    variable = Ar+
    u = Ex
    v = Ey
    position_units = ${dom0Scale}
  [../]
  [./Ar+_diffusion]
    type = CoeffDiffusion
    variable = Ar+
    position_units = ${dom0Scale}
  [../]
  #Net ion production from ionization
  [./Ar+_ionization]
    type = ADEEDFReactionLog
    variable = Ar+
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + em + Ar+'
    coefficient = 1
  [../]
  #Net ion production from step-wise ionization
  [./Ar+_stepwise_ionization]
    type = ADEEDFReactionLog
    variable = Ar+
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + em + Ar+'
    coefficient = 1
  [../]
  #Net ion production from metastable pooling
  [./Ar+_pooling]
    type = ReactionSecondOrderLog
    variable = Ar+
    v = Ar*
    w = Ar*
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    coefficient = 1
  [../]

#Argon Excited Equations
  #Time Derivative term of excited Argon
  [./Ar*_time_deriv]
    type = TimeDerivativeLog
    variable = Ar*
  [../]
  #Diffusion term of excited Argon
  [./Ar*_diffusion]
    type = CoeffDiffusion
    variable = Ar*
    position_units = ${dom0Scale}
  [../]
  #Net excited Argon production from excitation
  [./Ar*_excitation]
    type = ADEEDFReactionLog
    variable = Ar*
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + Ar*'
    coefficient = 1
  [../]
  #Net excited Argon loss from step-wise ionization
  [./Ar*_stepwise_ionization]
    type = ADEEDFReactionLog
    variable = Ar*
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + em + Ar+'
    coefficient = -1
  [../]
  #Net excited Argon loss from superelastic collisions
  [./Ar*_collisions]
    type = ADEEDFReactionLog
    variable = Ar*
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + Ar'
    coefficient = -1
  [../]
  #Net excited Argon loss from quenching to resonant
  [./Ar*_quenching]
    type = ReactionSecondOrderLog
    variable = Ar*
    v = em
    w = Ar*
    reaction = 'em + Ar* -> em + Ar_r'
    coefficient = -1
    _w_eq_u = true
  [../]
  #Net excited Argon loss from  metastable pooling
  [./Ar*_pooling]
    type = ReactionSecondOrderLog
    variable = Ar*
    v = Ar*
    w = Ar*
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    coefficient = -2
    _v_eq_u = true
    _w_eq_u = true
  [../]
  #Net excited Argon loss from two-body quenching
  [./Ar*_2B_quenching]
    type = ReactionSecondOrderLog
    variable = Ar*
    v = Ar
    w = Ar*
    reaction = 'Ar* + Ar -> Ar + Ar'
    coefficient = -1
    _v_eq_u = true
  [../]
  #Net excited Argon loss from three-body quenching
  [./Ar*_3B_quenching]
    type = ReactionThirdOrderLog
    variable = Ar*
    v = Ar*
    w = Ar
    x = Ar
    reaction = 'Ar* + Ar + Ar -> Ar_2 + Ar'
    coefficient = -1
    _v_eq_u = true
    v_NonLog = true
  [../]

#Voltage Equations
  #Voltage term in Poissons Eqaution
  [./potential_diffusion_dom0]
    type = CoeffDiffusionLin
    variable = potential
    position_units = ${dom0Scale}
  [../]
  #Ion term in Poissons Equation
    [./Ar+_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = Ar+
  [../]
  #Electron term in Poissons Equation
  [./em_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = em
  [../]

  [./EffEfield_X_time_deriv]
    type = TimeDerivative
    variable = Ex
  [../]
  [./EffEfield_X_ForceBody]
    type = EffectiveEField
    variable = Ex
    potential = potential
    #nu = 12833708.75
    nu = 1668609.922
    component = 0
    position_units = ${dom0Scale}
  [../]
  [./EffEfield_Y_time_deriv]
    type = TimeDerivative
    variable = Ey
  [../]
  [./EffEfield_Y_ForceBody]
    type = EffectiveEField
    variable = Ey
    potential = potential
    #nu = 12833708.75
    nu = 1668609.922
    component = 1
    position_units = ${dom0Scale}
  [../]


#Electron Energy Equations
  #Time Derivative term of electron energy
  [./mean_en_time_deriv]
    type = TimeDerivativeLog
    variable = mean_en
  [../]
  #Advection term of electron energy
  [./mean_en_advection]
    type = EFieldAdvection
    variable = mean_en
    potential = potential
    position_units = ${dom0Scale}
  [../]
  #Diffusion term of electrons energy
  [./mean_en_diffusion]
    type = CoeffDiffusion
    variable = mean_en
    position_units = ${dom0Scale}
  [../]
  #The correction for electrons energy's diffusion term
  [./mean_en_diffusion_correction]
    type = ThermalConductivityDiffusion
    variable = mean_en
    em = em
    position_units = ${dom0Scale}
  [../]
  #Joule Heating term
  [./mean_en_joule_heating]
    type = JouleHeating
    variable = mean_en
    potential = potential
    em = em
    position_units = ${dom0Scale}
  [../]
  #Energy loss from ionization
  [./Ionization_Loss]
    type = ADEEDFEnergyLog
    variable = mean_en
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + em + Ar+'
    threshold_energy = -15.7
  [../]
  #Energy loss from excitation
  [./Excitation_Loss]
    type = ADEEDFEnergyLog
    variable = mean_en
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + Ar*'
    threshold_energy = -11.56
  [../]
  #Energy loss from step-wise ionization
  [./Stepwise_Ionization_Loss]
    type = ADEEDFEnergyLog
    variable = mean_en
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + em + Ar+'
    threshold_energy = -4.14
  [../]
  #Energy gain from superelastic collisions
  [./Collisions_Loss]
    type = ADEEDFEnergyLog
    variable = mean_en
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + Ar'
    threshold_energy = 11.56
  [../]
  ##Energy loss from ionization
  [./Elastic_Loss]
    type = ADEEDFElasticLog
    variable = mean_en
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + Ar'
  [../]

###################################################################################

#Argon Excited Equations
  #Time Derivative term of excited Argon
  [./SM_Ar*_time_deriv]
    type = MassLumpedTimeDerivative
    variable = SM_Ar*
    enable = false
  [../]
  #Diffusion term of excited Argon
  [./SM_Ar*_diffusion]
   type = CoeffDiffusionForShootMethod
   variable = SM_Ar*
   density = Ar*
   position_units = ${dom0Scale}
   enable = false
  [../]
  #Net excited Argon loss from step-wise ionization
  [./SM_Ar*_stepwise_ionization]
    type = EEDFReactionLogForShootMethod
    variable = SM_Ar*
    electron = em
    density = Ar*
    reaction = 'em + Ar* -> em + em + Ar+'
    coefficient = -1
    enable = false
  [../]
  #Net excited Argon loss from superelastic collisions
  [./SM_Ar*_collisions]
    type = EEDFReactionLogForShootMethod
    variable = SM_Ar*
    electron = em
    density = Ar*
    reaction = 'em + Ar* -> em + Ar'
    coefficient = -1
    enable = false
  [../]
  #Net excited Argon loss from quenching to resonant
  [./SM_Ar*_quenching]
    type = ReactionSecondOrderLogForShootMethod
    variable = SM_Ar*
    density = Ar*
    v = em
    reaction = 'em + Ar* -> em + Ar_r'
    coefficient = -1
    enable = false
  [../]
  #Net excited Argon loss from  metastable pooling
  [./SM_Ar*_pooling]
    type = ReactionSecondOrderLogForShootMethod
    variable = SM_Ar*
    density = Ar*
    v = Ar*
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    coefficient = -2
    enable = false
  [../]
  #Net excited Argon loss from two-body quenching
  [./SM_Ar*_2B_quenching]
    type = ReactionSecondOrderLogForShootMethod
    variable = SM_Ar*
    density = Ar*
    v = Ar
    reaction = 'Ar* + Ar -> Ar + Ar'
    coefficient = -1
    enable = false
  [../]
  #Net excited Argon loss from three-body quenching
  [./SM_Ar*_3B_quenching]
    type = ReactionThirdOrderLogForShootMethod
    variable = SM_Ar*
    density = Ar*
    v = Ar
    w = Ar
    reaction = 'Ar* + Ar + Ar -> Ar_2 + Ar'
    coefficient = -1
    enable = false
  [../]

  [./SM_Ar*_Null]
    type = NullKernel
    variable = SM_Ar*
  [../]
[]

#Variables for scaled nodes and background gas
[AuxVariables]
  [./SM_Ar*Reset]
    initial_condition = 1.0
  [../]
  [./Ar*S]
  [../]

  [./x_node]
  [../]

  [./Ar]
  [../]

  [./Te]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./x]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./em_lin]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Ar+_lin]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Ar*_lin]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./Efield_X]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Efield_Y]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

#Kernels that define the scaled nodes and background gas
[AuxKernels]
  [./Ar*S_for_Shooting]
    type = QuotientAux
    variable = Ar*S
    numerator = Ar*
    denominator = 1.0
    enable = false
    execute_on = 'TIMESTEP_END'
  [../]

  [./Constant_SM_Ar*Reset]
    type = ConstantAux
    variable = SM_Ar*Reset
    value = 1.0
    execute_on = INITIAL
  [../]

  [./x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
  [../]

  [./Ar_val]
    type = FunctionAux
    variable = Ar
    # value = 3.22e22
    function = 'log(3.22e21/6.02e23)'
    execute_on = INITIAL
  [../]

  [./Te]
    type = ElectronTemperature
    variable = Te
    electron_density = em
    mean_en = mean_en
  [../]
  [./x_g]
    type = Position
    variable = x
    position_units = ${dom0Scale}
  [../]

  [./em_lin]
    type = DensityMoles
    variable = em_lin
    density_log = em
  [../]
  [./Ar+_lin]
    type = DensityMoles
    variable = Ar+_lin
    density_log = Ar+
  [../]
  [./Ar*_lin]
    type = DensityMoles
    variable = Ar*_lin
    density_log = Ar*
  [../]

  [./Efield_X_calc]
    type = Efield
    component = 0
    potential = potential
    variable = Efield_X
    position_units = ${dom0Scale}
  [../]
  [./Efield_Y_calc]
    type = Efield
    component = 1
    potential = potential
    variable = Efield_Y
    position_units = ${dom0Scale}
  [../]
[]

[BCs]
  #Voltage Boundary Condition, same as in paper
    [./potential_top_plate]
      type = FunctionDirichletBC
      variable = potential
      boundary = 'Top_Electrode'
      function = potential_top_bc_func
    [../]
    [./potential_bottom_plate]
      type = FunctionDirichletBC
      variable = potential
      boundary = 'Bottom_Electrode'
      function = potential_bottom_bc_func
    [../]
    [./potential_dirichlet_bottom_plate]
      type = DirichletBC
      variable = potential
      boundary = 'Walls'
      value = 0
    [../]
    #[./potential_Dielectric]
    #  type = EconomouDielectricWithEffEfieldBC
    #  variable = potential
    #  boundary = 'Top_Insulator Bottom_Insulator'
    #  em = em
    #  ip = Ar+
    #  Ex = Ex
    #  Ey = Ey
    #  mean_en = mean_en
    #  dielectric_constant = 1.859382e-11
    #  thickness = 0.0127
    #  users_gamma = 0.01
    #  position_units = ${dom0Scale}
    #[../]
    #[./potential_Dielectric]
    #  type = ADDielectricBC
    #  variable = potential
    #  boundary = 'Top_Insulator Bottom_Insulator'
    #  dielectric_constant = 1.859382e-11
    #  thickness = 0.0127
    #  position_units = ${dom0Scale}
    #[../]
    [./potential_Dielectric]
      type = DielectricBCWithEffEfield
      variable = potential
      em = em
      mean_en = mean_en
      ip = Ar+
      Ex = Ex
      Ey = Ey
      dielectric_constant = 1.859382e-11
      thickness = 0.0127
      users_gamma = 0.01
      position_units = ${dom0Scale}
      boundary = 'Top_Insulator Bottom_Insulator'
    [../]

#New Boundary conditions for electons, same as in paper
  [./em_physical_diffusion]
    type = SakiyamaElectronDiffusionBC
    variable = em
    mean_en = mean_en
    boundary = 'Top_Electrode Bottom_Electrode Top_Insulator Bottom_Insulator Walls'
    position_units = ${dom0Scale}
  [../]
  [./em_Ar+_second_emissions]
    type = SakiyamaSecondaryElectronWithEffEfieldBC
    variable = em
    mean_en = mean_en
    Ex = Ex
    Ey = Ey
    ip = Ar+
    users_gamma = 0.01
    boundary = 'Top_Electrode Bottom_Electrode Top_Insulator Bottom_Insulator Walls'
    position_units = ${dom0Scale}
  [../]

#New Boundary conditions for ions, should be the same as in paper
  [./Ar+_physical_advection]
    type = SakiyamaIonAdvectionWithEffEfieldBC
    variable = Ar+
    Ex = Ex
    Ey = Ey
    boundary = 'Top_Electrode Bottom_Electrode Top_Insulator Bottom_Insulator Walls'
    position_units = ${dom0Scale}
  [../]

#New Boundary conditions for ions, should be the same as in paper
#(except the metastables are not set to zero, since Zapdos uses log form)
  [./Ar*_physical_diffusion]
    type = ADDirichletBC
    variable = Ar*
    boundary = 'Top_Electrode Bottom_Electrode Top_Insulator Bottom_Insulator Walls'
    value = -50.0
  [../]

#New Boundary conditions for mean energy, should be the same as in paper
  [./mean_en_physical_diffusion]
    type = SakiyamaEnergyDiffusionBC
    variable = mean_en
    em = em
    boundary = 'Top_Electrode Bottom_Electrode Top_Insulator Bottom_Insulator Walls'
    position_units = ${dom0Scale}
  [../]
  [./mean_en_Ar+_second_emissions]
    type = SakiyamaEnergySecondaryElectronWithEffEfieldBC
    variable = mean_en
    em = em
    ip = Ar+
    Ex = Ex
    Ey = Ey
    potential = potential
    Tse_equal_Te = false
    user_se_energy = 0.75
    se_coeff = 0.01
    boundary = 'Top_Electrode Bottom_Electrode Top_Insulator Bottom_Insulator Walls'
    position_units = ${dom0Scale}
  [../]
[]

#Initial Conditions
[ICs]
  [./em_ic]
    #type = FunctionIC
    #variable = em
    #function = density_ic_func
    type = BoundingBoxIC
    variable = em
    int_width = 0.059
    inside = -24.8
    outside = -31.7
    x1 = 0.0
    #x2 = 1.92
    x2 = 7.87
    y1 = 1.5
    y2 = 2.5
  [../]
  [./Ar+_ic]
    #type = FunctionIC
    #variable = Ar+
    #function = density_ic_func
    type = BoundingBoxIC
    variable = Ar+
    int_width = 0.059
    inside = -24.8
    outside = -31.7
    x1 = 0.0
    #x2 = 1.92
    x2 = 7.87
    y1 = 1.5
    y2 = 2.5
  [../]
  [./Ar*_ic]
    #type = FunctionIC
    #variable = Ar*
    #function = density_ic_func
    type = BoundingBoxIC
    variable = Ar*
    int_width = 0.059
    inside = -24.8
    outside = -31.7
    x1 = 0.0
    #x2 = 2.059
    #x2 = 1.92
    x2 = 7.87
    y1 = 1.5
    y2 = 2.5
  [../]
  [./mean_en_ic]
    #type = FunctionIC
    #variable = mean_en
    #function = energy_density_ic_func
    type = BoundingBoxIC
    variable = mean_en
    int_width = 0.059
    inside = -24.4
    outside = -31.3
    x1 = 0.0
    #x2 = 1.92
    x2 = 7.87
    y1 = 1.5
    y2 = 2.5
  [../]
[]

#Functions for IC and Potential BC
[Functions]
  [./potential_top_bc_func]
    type = ParsedFunction
    value = '0.050*sin(2*pi*40e6*t)'
  [../]
  [./potential_bottom_bc_func]
    type = ParsedFunction
    value = '-0.050*sin(2*pi*40e6*t)'
  [../]
  [./density_ic_func]
    type = ParsedFunction
    #value = 'log((1e13 + 1e15 * (1-x/(1.0))^2 * (x/(1.0))^2)/6.02e23)'
    #value = 'log((1e10)/6.02e23)'
    value = 'if(y > 1.5 & y < 2.5,
                log((1e10 + (-0.5 * ( tanh((x - 2.15)/0.059) - 1))*(10^15*((2.5-y)^2 * (y - 1.5)^2) + 1e13))/6.02e23),
                log(1e10/6.02e23))'
  [../]
  [./energy_density_ic_func]
    type = ParsedFunction
    #value = 'log(3./2.) + log((1e13 + 1e15 * (1-x/(1.0))^2 * (x/(1.0))^2)/6.02e23)'
    #value = 'log((3./2.)) + log((1e10)/6.02e23)'
    value = 'if(y > 1.5 & y < 2.5,
                log((3./2.)) + log((1e10 + (-0.5 * ( tanh((x - 2.15)/0.059) - 1))*(10^15*((2.5-y)^2 * (y - 1.5)^2) + 1e13))/6.02e23),
                log((3./2.)) + log(1e10/6.02e23))'
  [../]
[]

#Material properties of species and background gas
[Materials]
  [./field_solver]
    type = FieldSolverMaterial
    potential = potential
  [../]
  [./GasBasics]
    #If elecron mobility and diffusion are NOT constant, set
    #"interp_elastic_coeff = true". This lets the mobility and
    #diffusivity to be energy dependent, as dictated by the txt file
    type = GasElectronMoments
    em = em
    mean_en = mean_en
    interp_elastic_coeff = false
    interp_trans_coeffs = false
    ramp_trans_coeffs = false
    user_p_gas = 133.33
    user_T_gas = 300
    user_electron_mobility = 300.0
    user_electron_diffusion_coeff = 1198.757763975
    property_tables_file = Argon_reactions_RateCoefficients/electron_moments.txt
  [../]
  [./gas_species_0]
    type = ADHeavySpecies
    heavy_species_name = Ar+
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    mobility = 1.44409938
    diffusivity = 6.428571e-2
  [../]
  [./gas_species_2]
    type = ADHeavySpecies
    heavy_species_name = Ar
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
  [../]
  [./gas_species_1]
    type = ADHeavySpecies
    heavy_species_name = Ar*
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
    diffusivity = 7.515528e-2
  [../]
  [./reaction_00]
    type = InterpolatedCoefficientLinear
    mean_energy = mean_en
    property_file = 'Argon_reactions_RateCoefficients/reaction_em + Ar -> em + Ar.txt'
    #property_file = 'Argon_reactions_paper_RateCoefficients/reaction_em + Ar -> em + Ar.txt'
    reaction = 'em + Ar -> em + Ar'
    file_location = ''
    electrons = em
  [../]
  [./reaction_0]
    type = InterpolatedCoefficientLinear
    mean_energy = mean_en
    property_file = 'Argon_reactions_RateCoefficients/reaction_em + Ar -> em + Ar*.txt'
    #property_file = 'Argon_reactions_paper_RateCoefficients/reaction_em + Ar -> em + Ar*.txt'
    reaction = 'em + Ar -> em + Ar*'
    file_location = ''
    electrons = em
  [../]
  [./reaction_1]
    type = InterpolatedCoefficientLinear
    mean_energy = mean_en
    property_file = 'Argon_reactions_RateCoefficients/reaction_em + Ar -> em + em + Ar+.txt'
    #property_file = 'Argon_reactions_paper_RateCoefficients/reaction_em + Ar -> em + em + Ar+.txt'
    reaction = 'em + Ar -> em + em + Ar+'
    file_location = ''
    electrons = em
  [../]
  [./reaction_2]
    type = InterpolatedCoefficientLinear
    mean_energy = mean_en
    property_file = 'Argon_reactions_RateCoefficients/reaction_em + Ar* -> em + Ar.txt'
    #property_file = 'Argon_reactions_paper_RateCoefficients/reaction_em + Ar* -> em + Ar.txt'
    reaction = 'em + Ar* -> em + Ar'
    file_location = ''
    electrons = em
  [../]
  [./reaction_3]
    type = InterpolatedCoefficientLinear
    mean_energy = mean_en
    property_file = 'Argon_reactions_RateCoefficients/reaction_em + Ar* -> em + em + Ar+.txt'
    #property_file = 'Argon_reactions_paper_RateCoefficients/reaction_em + Ar* -> em + em + Ar+.txt'
    reaction = 'em + Ar* -> em + em + Ar+'
    file_location = ''
    electrons = em
  [../]
  [./reaction_4]
    type = GenericRateConstant
    reaction = 'em + Ar* -> em + Ar_r'
    #reaction_rate_value = 2e-13
    reaction_rate_value = 1.2044e11
  [../]
  [./reaction_5]
    type = GenericRateConstant
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    #reaction_rate_value = 6.2e-16
    reaction_rate_value = 373364000
  [../]
  [./reaction_6]
    type = GenericRateConstant
    reaction = 'Ar* + Ar -> Ar + Ar'
    #reaction_rate_value = 3e-21
    reaction_rate_value = 1806.6
  [../]
  [./reaction_7]
    type = GenericRateConstant
    reaction = 'Ar* + Ar + Ar -> Ar_2 + Ar'
    #reaction_rate_value = 1.1e-43
    reaction_rate_value = 39890.9324
  [../]

  #[./Surface_Charge]
  #  type = ADSurfaceCharge_DielectricBC
  #  boundary = 'Top_Insulator Bottom_Insulator'
  #  electron = em
  #  mean_en = mean_en
  #  ion = Ar+
  #  Ex = Ex
  #  Ey = Ey
  #  gamma = 0.01
  #  position_units = ${dom0Scale}
  #[../]
[]

#Acceleration Schemes are dictated by MultiApps, Transfers,
#and PeriodicControllers
[MultiApps]
  #MultiApp of Acceleration by Shooting Method
  [./Shooting]
    type = FullSolveMultiApp
    input_files = 'RF_Plasma_NoActions_2DGEC_100mTorr_EffEfield_Shooting_ES_default_40.i'
    execute_on = 'TIMESTEP_END'
    enable = false
  [../]
[]


[Transfers]
  #MultiApp Transfers for Acceleration by Shooting Method
  [./SM_Ar*Reset_to_Shooting]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Shooting
    source_variable = SM_Ar*Reset
    variable = SM_Ar*Reset
    enable = false
  [../]

  [./Ar*_to_Shooting]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Shooting
    source_variable = Ar*
    variable = Ar*
    enable = false
  [../]
  [./Ar*S_to_Shooting]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Shooting
    source_variable = Ar*S
    variable = Ar*S
    enable = false
  [../]
  [./Ar*T_to_Shooting]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Shooting
    source_variable = Ar*
    variable = Ar*T
    enable = false
  [../]
  [./SMDeriv_to_Shooting]
    type = MultiAppCopyTransfer
    direction = to_multiapp
    multi_app = Shooting
    source_variable = SM_Ar*
    variable = SM_Ar*
    enable = false
  [../]

  [./Ar*New_from_Shooting]
    type = MultiAppCopyTransfer
    direction = from_multiapp
    multi_app = Shooting
    source_variable = Ar*
    variable = Ar*
    enable = false
  [../]
  [./SM_Ar*Reset_from_Shooting]
    type = MultiAppCopyTransfer
    direction = from_multiapp
    multi_app = Shooting
    source_variable = SM_Ar*Reset
    variable = SM_Ar*
    enable = false
  [../]
[]

#The Action the add the TimePeriod Controls to turn off and on the MultiApps
[PeriodicControllers]
  [./Shooting]
    Enable_at_cycle_start = '*::Ar*S_for_Shooting'

    Enable_during_cycle = '*::SM_Ar*_time_deriv *::SM_Ar*_diffusion *::SM_Ar*_stepwise_ionization
                           *::SM_Ar*_collisions *::SM_Ar*_quenching *::SM_Ar*_pooling
                           *::SM_Ar*_2B_quenching *::SM_Ar*_3B_quenching'

    Enable_at_cycle_end = 'MultiApps::Shooting
                           *::SM_Ar*Reset_to_Shooting *::Ar*_to_Shooting
                           *::Ar*S_to_Shooting *::Ar*T_to_Shooting
                           *::SMDeriv_to_Shooting *::Ar*New_from_Shooting
                           *::SM_Ar*Reset_from_Shooting'
    cycle_frequency = 40e6
    starting_cycle = 100
    cycles_between_controls = 100
    cycles_per_controls = 1
    num_controller_set = 2000
    name = Shooting
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
  end_time = 1.25e-5 #500 RF cycles at 40 MHz
  #end_time = 5e-4
  #end_time = 1e-7

  automatic_scaling = true
  compute_scaling_once = false

  solve_type = NEWTON
  line_search = none
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor -ksp_view'
  #petsc_options = '-snes_monitor -snes_converged_reason -snes_linesearch_monitor -ksp_monitor_true_residual -ksp_converged_reason'
  petsc_options_iname = '-pc_type -pc_factor_mat_solver_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu superlu_dist NONZERO 1.e-10'

  nl_rel_tol = 1e-10
  nl_abs_tol = 1e-11

  scheme = newmark-beta
  dt = 4e-10
  dtmin = 1e-14
[]

[Outputs]
  perf_graph = true
  [./out]
    type = Exodus
  [../]
[]
