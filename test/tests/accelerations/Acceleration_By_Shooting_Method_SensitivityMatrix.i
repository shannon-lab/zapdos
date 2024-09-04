dom0Scale = 25.4e-3

[GlobalParams]
  potential_units = kV
  use_moles = true
[]

[Mesh]
  [file]
    type = FileMeshGenerator
    file = 'Lymberopoulos_paper.msh'
  []
  [left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = file
  []
  [right]
    type = SideSetsFromNormalsGenerator
    normals = '1 0 0'
    new_boundary = 'right'
    input = left
  []
[]

[Problem]
  type = FEProblem
[]

[Variables]
  [em]
  []

  [Ar+]
  []

  [Ar*]
  []

  [mean_en]
  []

  [potential]
  []

  [SMDeriv]
  []
[]

[Kernels]
  #Electron Equations (Same as in paper)
  #Time Derivative term of electron
  [em_time_deriv]
    type = ElectronTimeDerivative
    variable = em
  []
  #Advection term of electron
  [em_advection]
    type = EFieldAdvection
    variable = em
    position_units = ${dom0Scale}
  []
  #Diffusion term of electrons
  [em_diffusion]
    type = CoeffDiffusion
    variable = em
    position_units = ${dom0Scale}
  []
  #Net electron production from ionization
  [em_ionization]
    type = ADEEDFReactionLog
    variable = em
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + em + Ar+'
    coefficient = 1
  []
  #Net electron production from step-wise ionization
  [em_stepwise_ionization]
    type = ADEEDFReactionLog
    variable = em
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + em + Ar+'
    coefficient = 1
  []
  #Net electron production from metastable pooling
  [em_pooling]
    type = ADReactionSecondOrderLog
    variable = em
    v = Ar*
    w = Ar*
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    coefficient = 1
  []

  #Argon Ion Equations (Same as in paper)
  #Time Derivative term of the ions
  [Ar+_time_deriv]
    type = ElectronTimeDerivative
    variable = Ar+
  []
  #Advection term of ions
  [Ar+_advection]
    type = EFieldAdvection
    variable = Ar+
    position_units = ${dom0Scale}
  []
  [Ar+_diffusion]
    type = CoeffDiffusion
    variable = Ar+
    position_units = ${dom0Scale}
  []
  #Net ion production from ionization
  [Ar+_ionization]
    type = ADEEDFReactionLog
    variable = Ar+
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + em + Ar+'
    coefficient = 1
  []
  #Net ion production from step-wise ionization
  [Ar+_stepwise_ionization]
    type = ADEEDFReactionLog
    variable = Ar+
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + em + Ar+'
    coefficient = 1
  []
  #Net ion production from metastable pooling
  [Ar+_pooling]
    type = ADReactionSecondOrderLog
    variable = Ar+
    v = Ar*
    w = Ar*
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    coefficient = 1
  []

  #Argon Excited Equations (Same as in paper)
  #Time Derivative term of excited Argon
  [Ar*_time_deriv]
    type = ElectronTimeDerivative
    variable = Ar*
  []
  #Diffusion term of excited Argon
  [Ar*_diffusion]
    type = CoeffDiffusion
    variable = Ar*
    position_units = ${dom0Scale}
  []
  #Net excited Argon production from excitation
  [Ar*_excitation]
    type = ADEEDFReactionLog
    variable = Ar*
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + Ar*'
    coefficient = 1
  []
  #Net excited Argon loss from step-wise ionization
  [Ar*_stepwise_ionization]
    type = ADEEDFReactionLog
    variable = Ar*
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + em + Ar+'
    coefficient = -1
  []
  #Net excited Argon loss from superelastic collisions
  [Ar*_collisions]
    type = ADEEDFReactionLog
    variable = Ar*
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + Ar'
    coefficient = -1
  []
  #Net excited Argon loss from quenching to resonant
  [Ar*_quenching]
    type = ADEEDFReactionLog
    variable = Ar*
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + Ar_r'
    coefficient = -1
  []
  #Net excited Argon loss from  metastable pooling
  [Ar*_pooling]
    type = ADReactionSecondOrderLog
    variable = Ar*
    v = Ar*
    w = Ar*
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    coefficient = -2
    _v_eq_u = true
    _w_eq_u = true
  []
  #Net excited Argon loss from two-body quenching
  [Ar*_2B_quenching]
    type = ADReactionSecondOrderLog
    variable = Ar*
    v = Ar*
    w = Ar
    reaction = 'Ar* + Ar -> Ar + Ar'
    coefficient = -1
    _v_eq_u = true
  []
  #Net excited Argon loss from three-body quenching
  [Ar*_3B_quenching]
    type = ADReactionThirdOrderLog
    variable = Ar*
    v = Ar*
    w = Ar
    x = Ar
    reaction = 'Ar* + Ar + Ar -> Ar_2 + Ar'
    coefficient = -1
    _v_eq_u = true
  []

  #Voltage Equations (Same as in paper)
  #Voltage term in Poissons Eqaution
  [potential_diffusion_dom0]
    type = CoeffDiffusionLin
    variable = potential
    position_units = ${dom0Scale}
  []
  #Ion term in Poissons Equation
  [Ar+_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = Ar+
  []
  #Electron term in Poissons Equation
  [em_charge_source]
    type = ChargeSourceMoles_KV
    variable = potential
    charged = em
  []

  #Since the paper uses electron temperature as a variable, the energy equation is in
  #a different form but should be the same physics
  #Time Derivative term of electron energy
  [mean_en_time_deriv]
    type = ElectronTimeDerivative
    variable = mean_en
  []
  #Advection term of electron energy
  [mean_en_advection]
    type = EFieldAdvection
    variable = mean_en
    position_units = ${dom0Scale}
  []
  #Diffusion term of electrons energy
  [mean_en_diffusion]
    type = CoeffDiffusion
    variable = mean_en
    position_units = ${dom0Scale}
  []
  #Joule Heating term
  [mean_en_joule_heating]
    type = JouleHeating
    variable = mean_en
    em = em
    position_units = ${dom0Scale}
  []
  #Energy loss from ionization
  [Ionization_Loss]
    type = ADEEDFEnergyLog
    variable = mean_en
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + em + Ar+'
    threshold_energy = -15.7
  []
  #Energy loss from excitation
  [Excitation_Loss]
    type = ADEEDFEnergyLog
    variable = mean_en
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + Ar*'
    threshold_energy = -11.56
  []
  #Energy loss from step-wise ionization
  [Stepwise_Ionization_Loss]
    type = ADEEDFEnergyLog
    variable = mean_en
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + em + Ar+'
    threshold_energy = -4.14
  []
  #Energy gain from superelastic collisions
  [Collisions_Loss]
    type = ADEEDFEnergyLog
    variable = mean_en
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + Ar'
    threshold_energy = 11.56
  []

  #Argon Excited Equations For Shooting Method
  #Time Derivative term of excited Argon
  [SM_Ar*_time_deriv]
    type = TimeDerivative
    variable = SMDeriv
  []
  #Diffusion term of excited Argon
  [SM_Ar*_diffusion]
    type = CoeffDiffusionForShootMethod
    variable = SMDeriv
    density = Ar*
    position_units = ${dom0Scale}
  []
  #Net excited Argon loss from step-wise ionization
  [SM_Ar*_stepwise_ionization]
    type = EEDFReactionLogForShootMethod
    variable = SMDeriv
    density = Ar*
    electron = em
    reaction = 'em + Ar* -> em + em + Ar+'
    coefficient = -1
  []
  #Net excited Argon loss from superelastic collisions
  [SM_Ar*_collisions]
    type = EEDFReactionLogForShootMethod
    variable = SMDeriv
    density = Ar*
    electron = em
    reaction = 'em + Ar* -> em + Ar'
    coefficient = -1
  []
  #Net excited Argon loss from quenching to resonant
  [SM_Ar*_quenching]
    type = ReactionSecondOrderLogForShootMethod
    variable = SMDeriv
    density = Ar*
    v = em
    reaction = 'em + Ar* -> em + Ar_r'
    coefficient = -1
  []
  #Net excited Argon loss from  metastable pooling
  [SM_Ar*_pooling]
    type = ReactionSecondOrderLogForShootMethod
    variable = SMDeriv
    density = Ar*
    v = Ar*
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    coefficient = -2
  []
  #Net excited Argon loss from two-body quenching
  [SM_Ar*_2B_quenching]
    type = ReactionSecondOrderLogForShootMethod
    variable = SMDeriv
    density = Ar*
    v = Ar
    reaction = 'Ar* + Ar -> Ar + Ar'
    coefficient = -1
  []
  #Net excited Argon loss from three-body quenching
  [SM_Ar*_3B_quenching]
    type = ReactionThirdOrderLogForShootMethod
    variable = SMDeriv
    density = Ar*
    v = Ar
    w = Ar
    reaction = 'Ar* + Ar + Ar -> Ar_2 + Ar'
    coefficient = -1
  []
[]

[AuxVariables]
  [emDeBug]
  []
  [Ar+_DeBug]
  []
  [Ar*_DeBug]
  []
  [mean_enDeBug]
  []

  [Te]
    order = CONSTANT
    family = MONOMIAL
  []

  [x]
    order = CONSTANT
    family = MONOMIAL
  []

  [x_node]
  []

  [rho]
    order = CONSTANT
    family = MONOMIAL
  []

  [em_lin]
    order = CONSTANT
    family = MONOMIAL
  []

  [Ar+_lin]
    order = CONSTANT
    family = MONOMIAL
  []

  [Ar*_lin]
    order = CONSTANT
    family = MONOMIAL
  []

  [Ar]
  []

  [Efield]
    order = CONSTANT
    family = MONOMIAL
  []

  [Current_em]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [Current_Ar]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [emRate]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [exRate]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [swRate]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [deexRate]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [quRate]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [poolRate]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [TwoBRate]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [ThreeBRate]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
[]

[AuxKernels]
  [emDeBug]
    type = DebugResidualAux
    variable = emDeBug
    debug_variable = em
    #execute_on = 'LINEAR NONLINEAR TIMESTEP_BEGIN'
  []
  [Ar+_DeBug]
    type = DebugResidualAux
    variable = Ar+_DeBug
    debug_variable = Ar+
    #execute_on = 'LINEAR NONLINEAR TIMESTEP_BEGIN'
  []
  [mean_enDeBug]
    type = DebugResidualAux
    variable = mean_enDeBug
    debug_variable = mean_en
    #execute_on = 'LINEAR NONLINEAR TIMESTEP_BEGIN'
  []
  [Ar*_DeBug]
    type = DebugResidualAux
    variable = Ar*_DeBug
    debug_variable = Ar*
    #execute_on = 'LINEAR NONLINEAR TIMESTEP_BEGIN'
  []

  [emRate]
    type = ADProcRateForRateCoeff
    variable = emRate
    v = em
    w = Ar
    reaction = 'em + Ar -> em + em + Ar+'
  []
  [exRate]
    type = ADProcRateForRateCoeff
    variable = exRate
    v = em
    w = Ar*
    reaction = 'em + Ar -> em + Ar*'
  []
  [swRate]
    type = ADProcRateForRateCoeff
    variable = swRate
    v = em
    w = Ar*
    reaction = 'em + Ar* -> em + em + Ar+'
  []
  [deexRate]
    type = ADProcRateForRateCoeff
    variable = deexRate
    v = em
    w = Ar*
    reaction = 'em + Ar* -> em + Ar'
  []
  [quRate]
    type = ADProcRateForRateCoeff
    variable = quRate
    v = em
    w = Ar*
    reaction = 'em + Ar* -> em + Ar_r'
  []
  [poolRate]
    type = ADProcRateForRateCoeff
    variable = poolRate
    v = Ar*
    w = Ar*
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
  []
  [TwoBRate]
    type = ADProcRateForRateCoeff
    variable = TwoBRate
    v = Ar*
    w = Ar
    reaction = 'Ar* + Ar -> Ar + Ar'
  []
  [ThreeBRate]
    type = ADProcRateForRateCoeffThreeBody
    variable = ThreeBRate
    v = Ar*
    w = Ar
    x = Ar
    reaction = 'Ar* + Ar + Ar -> Ar_2 + Ar'
  []
  [Te]
    type = ElectronTemperature
    variable = Te
    electron_density = em
    mean_en = mean_en
  []
  [x_g]
    type = Position
    variable = x
    position_units = ${dom0Scale}
  []

  [x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
  []

  [em_lin]
    type = DensityMoles
    variable = em_lin
    density_log = em
  []
  [Ar+_lin]
    type = DensityMoles
    variable = Ar+_lin
    density_log = Ar+
  []
  [Ar*_lin]
    type = DensityMoles
    variable = Ar*_lin
    density_log = Ar*
  []

  [Ar_val]
    type = ConstantAux
    variable = Ar
    # value = 3.22e22
    value = -2.928623
    execute_on = INITIAL
  []

  [Efield_calc]
    type = Efield
    component = 0
    variable = Efield
    position_units = ${dom0Scale}
  []
  [Current_em]
    type = ADCurrent
    density_log = em
    variable = Current_em
    art_diff = false
    block = 0
    position_units = ${dom0Scale}
  []
  [Current_Ar]
    type = ADCurrent
    density_log = Ar+
    variable = Current_Ar
    art_diff = false
    block = 0
    position_units = ${dom0Scale}
  []
[]

[BCs]
  #Voltage Boundary Condition, same as in paper
  [potential_left]
    type = FunctionDirichletBC
    variable = potential
    boundary = 'left'
    function = potential_bc_func
    preset = false
  []
  [potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = 'right'
    value = 0
    preset = false
  []

  #New Boundary conditions for electons, same as in paper
  [em_physical_right]
    type = LymberopoulosElectronBC
    variable = em
    boundary = 'right'
    emission_coeffs = 0.01
    #gamma = 1
    ks = 1.19e5
    #ks = 0.0
    ions = Ar+
    position_units = ${dom0Scale}
  []
  [em_physical_left]
    type = LymberopoulosElectronBC
    variable = em
    boundary = 'left'
    emission_coeffs = 0.01
    #gamma = 1
    ks = 1.19e5
    #ks = 0.0
    ions = Ar+
    position_units = ${dom0Scale}
  []

  #New Boundary conditions for ions, should be the same as in paper
  [Ar+_physical_right_advection]
    type = LymberopoulosIonBC
    variable = Ar+
    boundary = 'right'
    position_units = ${dom0Scale}
  []
  [Ar+_physical_left_advection]
    type = LymberopoulosIonBC
    variable = Ar+
    boundary = 'left'
    position_units = ${dom0Scale}
  []

  #New Boundary conditions for ions, should be the same as in paper
  #(except the metastables are not set to zero, since Zapdos uses log form)
  [Ar*_physical_right_diffusion]
    type = LogDensityDirichletBC
    variable = Ar*
    boundary = 'right'
    value = 1e-5
  []
  [Ar*_physical_left_diffusion]
    type = LogDensityDirichletBC
    variable = Ar*
    boundary = 'left'
    value = 1e-5
  []

  #New Boundary conditions for mean energy, should be the same as in paper
  [mean_en_physical_right]
    type = ElectronTemperatureDirichletBC
    variable = mean_en
    electrons = em
    value = 0.5
    boundary = 'right'
  []
  [mean_en_physical_left]
    type = ElectronTemperatureDirichletBC
    variable = mean_en
    electrons = em
    value = 0.5
    boundary = 'left'
  []

[]

[Functions]
  [potential_bc_func]
    type = ParsedFunction
    expression = '0.100*sin(2*pi*13.56e6*t)'
  []
[]

[Materials]
  [field_solver]
    type = FieldSolverMaterial
    potential = potential
  []
  [GasBasics]
    type = GasElectronMoments
    interp_trans_coeffs = false
    interp_elastic_coeff = false
    ramp_trans_coeffs = false
    user_p_gas = 133.322
    em = em
    mean_en = mean_en
    user_electron_mobility = 30.0
    user_electron_diffusion_coeff = 119.8757763975
    property_tables_file = Argon_reactions_paper_RateCoefficients/electron_moments.txt
  []
  [gas_species_0]
    type = ADHeavySpecies
    heavy_species_name = Ar+
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    mobility = 0.144409938
    diffusivity = 6.428571e-3
  []
  [gas_species_1]
    type = ADHeavySpecies
    heavy_species_name = Ar*
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
    diffusivity = 7.515528e-3
  []
  [gas_species_2]
    type = ADHeavySpecies
    heavy_species_name = Ar
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
  []
  [reaction_0]
    type = ADZapdosEEDFRateConstant
    mean_energy = mean_en
    property_file = 'Argon_reactions_paper_RateCoefficients/reaction_em + Ar -> em + Ar*.txt'
    reaction = 'em + Ar -> em + Ar*'
    electrons = em
  []
  [reaction_1]
    type = ADZapdosEEDFRateConstant
    mean_energy = mean_en
    property_file = 'Argon_reactions_paper_RateCoefficients/reaction_em + Ar -> em + em + Ar+.txt'
    reaction = 'em + Ar -> em + em + Ar+'
    electrons = em
  []
  [reaction_2]
    type = ADZapdosEEDFRateConstant
    mean_energy = mean_en
    property_file = 'Argon_reactions_paper_RateCoefficients/reaction_em + Ar* -> em + Ar.txt'
    reaction = 'em + Ar* -> em + Ar'
    electrons = em
  []
  [reaction_3]
    type = ADZapdosEEDFRateConstant
    mean_energy = mean_en
    property_file = 'Argon_reactions_paper_RateCoefficients/reaction_em + Ar* -> em + em + Ar+.txt'
    reaction = 'em + Ar* -> em + em + Ar+'
    electrons = em
  []
  [reaction_4]
    type = ADGenericRateConstant
    reaction = 'em + Ar* -> em + Ar_r'
    #reaction_rate_value = 2e-13
    reaction_rate_value = 1.2044e11
  []
  [reaction_5]
    type = ADGenericRateConstant
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    #reaction_rate_value = 6.2e-16
    reaction_rate_value = 373364000
  []
  [reaction_6]
    type = ADGenericRateConstant
    reaction = 'Ar* + Ar -> Ar + Ar'
    #reaction_rate_value = 3e-21
    reaction_rate_value = 1806.6
  []
  [reaction_7]
    type = ADGenericRateConstant
    reaction = 'Ar* + Ar + Ar -> Ar_2 + Ar'
    #reaction_rate_value = 1.1e-43
    reaction_rate_value = 39890.9324
  []
[]

#New postprocessor that calculates the inverse of the plasma frequency
[Postprocessors]
  [InversePlasmaFreq]
    type = PlasmaFrequencyInverse
    variable = em
    use_moles = true
    execute_on = 'INITIAL TIMESTEP_BEGIN'
  []
[]

[Preconditioning]
  active = 'smp'
  [smp]
    type = SMP
    full = true
  []

  [fdp]
    type = FDP
    full = true
  []
[]

[Executioner]
  type = Transient
  end_time = 73.74631268e-9
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 fgmres 1e-3'
  nl_rel_tol = 1e-08
  #nl_abs_tol = 7.6e-5 #Commit out do to test falure on Mac
  dtmin = 1e-14
  l_max_its = 20

  scheme = bdf2
  dt = 1e-9
[]

[Outputs]
  perf_graph = true
  [out]
    type = Exodus
  []
[]
