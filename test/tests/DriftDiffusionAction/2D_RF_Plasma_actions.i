dom0Scale = 25.4e-3

[GlobalParams]
  potential_units = V
  use_moles = true
[]

[Mesh]
  type = FileMesh
  file = 'GEC_mesh_coarse.msh'
  coord_type = RZ
  rz_coord_axis = Y
[]

#Effective potentials and their kernels are not defined by the
#DriftDiffusionAction, but charged particles effective by
#this potential can by defined by the action.
[Variables]
  [potential_ion]
  []
[]

#Action the supplies the drift-diffusion equations
#This action also adds JouleHeating and the ChargeSourceMoles_KV Kernels
[DriftDiffusionAction]
  [Plasma]
    electrons = em
    secondary_charged_particles = Ar+
    Neutrals = Ar*
    mean_energy = mean_en
    field = potential
    eff_fields = potential_ion
    eff_fields_property_names = potential_ion_property
    Is_field_unique = true
    using_offset = false
    position_units = ${dom0Scale}
    Additional_Outputs = 'ElectronTemperature Current EField'
  []
[]

#The Kernels supply the sources terms
[Kernels]
  #Net electron production from ionization
  [em_ionization]
    type = EEDFReactionLog
    variable = em
    electrons = em
    target = Ar
    mean_energy = mean_en
    reaction = 'em + Ar -> em + em + Ar+'
    coefficient = 1
  []
  #Net electron production from step-wise ionization
  [em_stepwise_ionization]
    type = EEDFReactionLog
    variable = em
    electrons = em
    target = Ar*
    mean_energy = mean_en
    reaction = 'em + Ar* -> em + em + Ar+'
    coefficient = 1
  []
  #Net electron production from metastable pooling
  [em_pooling]
    type = ReactionSecondOrderLog
    variable = em
    v = Ar*
    w = Ar*
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    coefficient = 1
  []

  #Net ion production from ionization
  [Ar+_ionization]
    type = EEDFReactionLog
    variable = Ar+
    electrons = em
    target = Ar
    mean_energy = mean_en
    reaction = 'em + Ar -> em + em + Ar+'
    coefficient = 1
  []
  #Net ion production from step-wise ionization
  [Ar+_stepwise_ionization]
    type = EEDFReactionLog
    variable = Ar+
    electrons = em
    target = Ar*
    mean_energy = mean_en
    reaction = 'em + Ar* -> em + em + Ar+'
    coefficient = 1
  []
  #Net ion production from metastable pooling
  [Ar+_pooling]
    type = ReactionSecondOrderLog
    variable = Ar+
    v = Ar*
    w = Ar*
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    coefficient = 1
  []

  #Net excited Argon production from excitation
  [Ar*_excitation]
    type = EEDFReactionLog
    variable = Ar*
    electrons = em
    target = Ar
    mean_energy = mean_en
    reaction = 'em + Ar -> em + Ar*'
    coefficient = 1
  []
  #Net excited Argon loss from step-wise ionization
  [Ar*_stepwise_ionization]
    type = EEDFReactionLog
    variable = Ar*
    electrons = em
    target = Ar*
    mean_energy = mean_en
    reaction = 'em + Ar* -> em + em + Ar+'
    coefficient = -1
  []
  #Net excited Argon loss from superelastic collisions
  [Ar*_collisions]
    type = EEDFReactionLog
    variable = Ar*
    electrons = em
    target = Ar*
    mean_energy = mean_en
    reaction = 'em + Ar* -> em + Ar'
    coefficient = -1
  []
  #Net excited Argon loss from quenching to resonant
  [Ar*_quenching]
    type = EEDFReactionLog
    variable = Ar*
    electrons = em
    target = Ar*
    mean_energy = mean_en
    reaction = 'em + Ar* -> em + Ar_r'
    coefficient = -1
  []
  #Net excited Argon loss from  metastable pooling
  [Ar*_pooling]
    type = ReactionSecondOrderLog
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
    type = ReactionSecondOrderLog
    variable = Ar*
    v = Ar*
    w = Ar
    reaction = 'Ar* + Ar -> Ar + Ar'
    coefficient = -1
    _v_eq_u = true
  []
  #Net excited Argon loss from three-body quenching
  [Ar*_3B_quenching]
    type = ReactionThirdOrderLog
    variable = Ar*
    v = Ar*
    w = Ar
    x = Ar
    reaction = 'Ar* + Ar + Ar -> Ar_2 + Ar'
    coefficient = -1
    _v_eq_u = true
  []

  #Energy loss from ionization
  [Ionization_Loss]
    type = EEDFEnergyLog
    variable = mean_en
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + em + Ar+'
    threshold_energy = -15.7
  []
  #Energy loss from excitation
  [Excitation_Loss]
    type = EEDFEnergyLog
    variable = mean_en
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + Ar*'
    threshold_energy = -11.56
  []
  #Energy loss from step-wise ionization
  [Stepwise_Ionization_Loss]
    type = EEDFEnergyLog
    variable = mean_en
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + em + Ar+'
    threshold_energy = -4.14
  []
  #Energy gain from superelastic collisions
  [Collisions_Loss]
    type = EEDFEnergyLog
    variable = mean_en
    electrons = em
    target = Ar*
    reaction = 'em + Ar* -> em + Ar'
    threshold_energy = 11.56
  []
  # Energy loss from elastic collisions
  [Elastic_loss]
    type = EEDFElasticLog
    variable = mean_en
    electrons = em
    target = Ar
    reaction = 'em + Ar -> em + Ar'
  []

  #Effective potential for the Ions
  [Ion_potential_time_deriv]
    type = TimeDerivative
    variable = potential_ion
  []
  [Ion_potential_reaction]
    type = ScaledReaction
    variable = potential_ion
    collision_freq = 1283370.875
  []
  [Ion_potential_coupled_force]
    type = CoupledForce
    variable = potential_ion
    v = potential
    coef = 1283370.875
  []
[]

[AuxVariables]
  [x_node]
  []

  [y_node]
  []

  [rho]
    order = CONSTANT
    family = MONOMIAL
  []

  [Ar]
  []

  [emRate]
    order = CONSTANT
    family = MONOMIAL
    block = 'plasma'
  []
  [exRate]
    order = CONSTANT
    family = MONOMIAL
    block = 'plasma'
  []
  [swRate]
    order = CONSTANT
    family = MONOMIAL
    block = 'plasma'
  []
  [deexRate]
    order = CONSTANT
    family = MONOMIAL
    block = 'plasma'
  []
  [quRate]
    order = CONSTANT
    family = MONOMIAL
    block = 'plasma'
  []
  [poolRate]
    order = CONSTANT
    family = MONOMIAL
    block = 'plasma'
  []
  [TwoBRate]
    order = CONSTANT
    family = MONOMIAL
    block = 'plasma'
  []
  [ThreeBRate]
    order = CONSTANT
    family = MONOMIAL
    block = 'plasma'
  []
[]

[AuxKernels]
  [emRate]
    type = ProcRateForRateCoeff
    variable = emRate
    v = em
    w = Ar
    reaction = 'em + Ar -> em + em + Ar+'
  []
  [exRate]
    type = ProcRateForRateCoeff
    variable = exRate
    v = em
    w = Ar*
    reaction = 'em + Ar -> em + Ar*'
  []
  [swRate]
    type = ProcRateForRateCoeff
    variable = swRate
    v = em
    w = Ar*
    reaction = 'em + Ar* -> em + em + Ar+'
  []
  [deexRate]
    type = ProcRateForRateCoeff
    variable = deexRate
    v = em
    w = Ar*
    reaction = 'em + Ar* -> em + Ar'
  []
  [quRate]
    type = ProcRateForRateCoeff
    variable = quRate
    v = em
    w = Ar*
    reaction = 'em + Ar* -> em + Ar_r'
  []
  [poolRate]
    type = ProcRateForRateCoeff
    variable = poolRate
    v = Ar*
    w = Ar*
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
  []
  [TwoBRate]
    type = ProcRateForRateCoeff
    variable = TwoBRate
    v = Ar*
    w = Ar
    reaction = 'Ar* + Ar -> Ar + Ar'
  []
  [ThreeBRate]
    type = ProcRateForRateCoeffThreeBody
    variable = ThreeBRate
    v = Ar*
    w = Ar
    x = Ar
    reaction = 'Ar* + Ar + Ar -> Ar_2 + Ar'
  []

  [x_ng]
    type = Position
    variable = x_node
    component = 0
    position_units = ${dom0Scale}
  []

  [y_ng]
    type = Position
    variable = y_node
    component = 1
    position_units = ${dom0Scale}
  []

  [Ar_val]
    type = ConstantAux
    variable = Ar
    # value = 3.22e2
    value = -5.231208
    execute_on = INITIAL
  []
[]

[BCs]
  #Voltage Boundary Condition, same as in paper
  [potential_top_plate]
    type = FunctionDirichletBC
    variable = potential
    boundary = 'Top_Electrode'
    function = potential_top_bc_func
    preset = false
  []
  [potential_bottom_plate]
    type = FunctionDirichletBC
    variable = potential
    boundary = 'Bottom_Electrode'
    function = potential_bottom_bc_func
    preset = false
  []
  [potential_dirichlet_bottom_plate]
    type = DirichletBC
    variable = potential
    boundary = 'Walls'
    value = 0
    preset = false
  []
  [potential_Dielectric]
    type = EconomouDielectricBC
    variable = potential
    boundary = 'Top_Insulator Bottom_Insulator'
    electrons = em
    ions = Ar+
    ion_potentials = potential_ion
    electron_energy = mean_en
    dielectric_constant = 1.859382e-11
    thickness = 0.0127
    emission_coeffs = 0.01
    position_units = ${dom0Scale}
  []

  #New Boundary conditions for electons, same as in paper
  [em_physical_diffusion]
    type = SakiyamaElectronDiffusionBC
    variable = em
    electron_energy = mean_en
    boundary = 'Top_Electrode Bottom_Electrode Top_Insulator Bottom_Insulator Walls'
    position_units = ${dom0Scale}
  []
  [em_Ar+_second_emissions]
    type = SakiyamaSecondaryElectronBC
    variable = em
    field_property_name = potential_ion_property
    ions = Ar+
    emission_coeffs = 0.01
    boundary = 'Top_Electrode Bottom_Electrode Top_Insulator Bottom_Insulator Walls'
    position_units = ${dom0Scale}
  []

  #New Boundary conditions for ions, should be the same as in paper
  [Ar+_physical_advection]
    type = SakiyamaIonAdvectionBC
    variable = Ar+
    field_property_name = potential_ion_property
    boundary = 'Top_Electrode Bottom_Electrode Top_Insulator Bottom_Insulator Walls'
    position_units = ${dom0Scale}
  []

  #New Boundary conditions for ions, should be the same as in paper
  #(except the metastables are not set to zero, since Zapdos uses log form)
  [Ar*_physical_diffusion]
    type = LogDensityDirichletBC
    variable = Ar*
    boundary = 'Top_Electrode Bottom_Electrode Top_Insulator Bottom_Insulator Walls'
    value = 100
  []

  #New Boundary conditions for mean energy, should be the same as in paper
  [mean_en_physical_diffusion]
    type = SakiyamaEnergyDiffusionBC
    variable = mean_en
    electrons = em
    boundary = 'Top_Electrode Bottom_Electrode Top_Insulator Bottom_Insulator Walls'
    position_units = ${dom0Scale}
  []
  [mean_en_Ar+_second_emissions]
    type = SakiyamaEnergySecondaryElectronBC
    variable = mean_en
    electrons = em
    ions = Ar+
    field_property_name = potential_ion_property
    Tse_equal_Te = true
    emission_coeffs = 0.01
    boundary = 'Top_Electrode Bottom_Electrode Top_Insulator Bottom_Insulator Walls'
    position_units = ${dom0Scale}
  []
[]

[ICs]
  [em_ic]
    type = FunctionIC
    variable = em
    function = density_ic_func
  []
  [Ar+_ic]
    type = FunctionIC
    variable = Ar+
    function = density_ic_func
  []
  [Ar*_ic]
    type = FunctionIC
    variable = Ar*
    function = meta_density_ic_func
  []
  [mean_en_ic]
    type = FunctionIC
    variable = mean_en
    function = energy_density_ic_func
  []

  [potential_ic]
    type = FunctionIC
    variable = potential
    function = potential_ic_func
  []
[]

[Functions]
  [potential_top_bc_func]
    type = ParsedFunction
    expression = '50*sin(2*3.1415926*13.56e6*t)'
  []
  [potential_bottom_bc_func]
    type = ParsedFunction
    expression = '-50*sin(2*3.1415926*13.56e6*t)'
  []
  [potential_ic_func]
    type = ParsedFunction
    expression = 0
  []
  [density_ic_func]
    type = ParsedFunction
    expression = 'log((1e14)/6.022e23)'
  []
  [meta_density_ic_func]
    type = ParsedFunction
    expression = 'log((1e16)/6.022e23)'
  []
  [energy_density_ic_func]
    type = ParsedFunction
    expression = 'log((3./2.) * 4) + log((1e14)/6.022e23)'
  []
[]

[Materials]
  [GasBasics]
    type = ElectronTransportCoefficients
    interp_trans_coeffs = true
    ramp_trans_coeffs = false
    user_p_gas = 133.322
    em = em
    mean_en = mean_en
    property_tables_file = Argon_reactions_paper_RateCoefficients/electron_moments.txt
  []
  [gas_permittivity]
    type = ElectrostaticPermittivity
    potential = potential
  []
  [gas_species_0]
    type = ADHeavySpecies
    heavy_species_name = Ar+
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    mobility = 1.44409938
    diffusivity = 6.428571e-2
  []
  [gas_species_1]
    type = ADHeavySpecies
    heavy_species_name = Ar*
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
    diffusivity = 7.515528e-2
  []
  [gas_species_2]
    type = ADHeavySpecies
    heavy_species_name = Ar
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
  []
  [reaction_00]
    type = ZapdosEEDFRateConstant
    mean_energy = mean_en
    property_file = 'Argon_reactions_paper_RateCoefficients/ar_elastic.txt'
    reaction = 'em + Ar -> em + Ar'
    electrons = em
  []
  [reaction_0]
    type = ZapdosEEDFRateConstant
    property_file = 'Argon_reactions_paper_RateCoefficients/ar_excitation.txt'
    reaction = 'em + Ar -> em + Ar*'
    mean_energy = mean_en
    electrons = em
  []
  [reaction_1]
    type = ZapdosEEDFRateConstant
    property_file = 'Argon_reactions_paper_RateCoefficients/ar_ionization.txt'
    reaction = 'em + Ar -> em + em + Ar+'
    mean_energy = mean_en
    electrons = em
  []
  [reaction_2]
    type = ZapdosEEDFRateConstant
    reaction = 'em + Ar* -> em + Ar'
    property_file = 'Argon_reactions_paper_RateCoefficients/ar_deexcitation.txt'
    mean_energy = mean_en
    electrons = em
  []
  [reaction_3]
    type = ZapdosEEDFRateConstant
    reaction = 'em + Ar* -> em + em + Ar+'
    property_file = 'Argon_reactions_paper_RateCoefficients/ar_excited_ionization.txt'
    mean_energy = mean_en
    electrons = em
  []
  [reaction_4]
    type = GenericRateConstant
    reaction = 'em + Ar* -> em + Ar_r'
    #reaction_rate_value = 2e-13
    reaction_rate_value = 1.2044e11
  []
  [reaction_5]
    type = GenericRateConstant
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    #reaction_rate_value = 6.2e-16
    reaction_rate_value = 373364000
  []
  [reaction_6]
    type = GenericRateConstant
    reaction = 'Ar* + Ar -> Ar + Ar'
    #reaction_rate_value = 3e-21
    reaction_rate_value = 1806.6
  []
  [reaction_7]
    type = GenericRateConstant
    reaction = 'Ar* + Ar + Ar -> Ar_2 + Ar'
    #reaction_rate_value = 1.1e-42
    reaction_rate_value = 398909.324
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
  #end_time = 7.4e-3
  end_time = 1e-7
  dtmax = 1e-9
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 fgmres 1e-3'
  nl_rel_tol = 1e-12
  #nl_abs_tol = 7.6e-5
  dtmin = 1e-14
  l_max_its = 20

  #Time steps based on the inverse of the plasma frequency
  #[TimeSteppers]
  #  [Postprocessor]
  #    type = PostprocessorDT
  #    postprocessor = InversePlasmaFreq
  #    scale = 0.1
  #  []
  #[]
[]

[Outputs]
  file_base = '2D_RF_out'
  perf_graph = true
  [out]
    type = Exodus
  []
[]
