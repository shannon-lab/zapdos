#This file performs the 1 rf cycle needed in RF_Plasma_acceleration_Shooting.i

dom0Scale=25.4e-3

[GlobalParams]
  potential_units = kV
  use_moles = true
[]

[Mesh]
  type = FileMesh
  file = 'Lymberopoulos_paper.msh'
[]

[MeshModifiers]
  [./left]
    type = SideSetsFromNormals
    normals = '-1 0 0'
    new_boundary = 'left'
  [../]
  [./right]
    type = SideSetsFromNormals
    normals = '1 0 0'
    new_boundary = 'right'
  [../]
[]

[Problem]
  type = FEProblem
[]

[DriftDiffusionAction]
  [./Plasma]
    electrons = em
    charged_particle = Ar+
    Neutrals = Ar*
    potential = potential
    Is_potential_unique = true
    mean_energy = mean_en
    position_units = ${dom0Scale}
  [../]
[]

[Reactions]
  [./Argon]
    species = 'Ar* em Ar+'
    aux_species = 'Ar'
    reaction_coefficient_format = 'rate'
    gas_species = 'Ar'
    electron_energy = 'mean_en'
    electron_density = 'em'
    include_electrons = true
    file_location = 'rate_coefficients'
    potential = 'potential'
    use_log = true
    position_units = ${dom0Scale}
    block = 0
    reactions = 'em + Ar -> em + Ar*        : EEDF [-11.56] (reaction1)
                 em + Ar -> em + em + Ar+   : EEDF [-15.7] (reaction2)
                 em + Ar* -> em + Ar        : EEDF [11.56] (reaction3)
                 em + Ar* -> em + em + Ar+  : EEDF [-4.14] (reaction4)
                 em + Ar* -> em + Ar_r      : 1.2044e11
                 Ar* + Ar* -> Ar+ + Ar + em : 373364000
                 Ar* + Ar -> Ar + Ar        : 1806.6
                 Ar* + Ar + Ar -> Ar_2 + Ar : 39890.9324'
  [../]
[]

[Variables]
  [./SMDeriv]
  [../]
[]

[Kernels]
  #Argon Excited Equations For Shooting Method
  #Time Derivative term of excited Argon
  [./SM_Ar*_time_deriv]
    type = TimeDerivative
    variable = SMDeriv
  [../]
  #Diffusion term of excited Argon
  [./SM_Ar*_diffusion]
    type = CoeffDiffusionForShootMethod
    variable = SMDeriv
    density = Ar*
    position_units = ${dom0Scale}
  [../]
  #Net excited Argon loss from superelastic collisions
  [./SM_Ar*_collisions]
    type = EEDFReactionLogForShootMethod
    variable = SMDeriv
    density = Ar*
    electron = em
    energy = mean_en
    reaction = 'em + Ar* -> em + Ar'
    number = 2
    coefficient = -1
  [../]
  #Net excited Argon loss from step-wise ionization
  [./SM_Ar*_stepwise_ionization]
    type = EEDFReactionLogForShootMethod
    variable = SMDeriv
    density = Ar*
    electron = em
    energy = mean_en
    reaction = 'em + Ar* -> em + em + Ar+'
    number = 3
    coefficient = -1
  [../]
  #Net excited Argon loss from quenching to resonant
  [./SM_Ar*_quenching]
    type = ReactionSecondOrderLogForShootMethod
    variable = SMDeriv
    density = Ar*
    v = em
    reaction = 'em + Ar* -> em + Ar_r'
    number = 4
    coefficient = -1
  [../]
  #Net excited Argon loss from  metastable pooling
  [./SM_Ar*_pooling]
    type = ReactionSecondOrderLogForShootMethod
    variable = SMDeriv
    density = Ar*
    v = Ar*
    reaction = 'Ar* + Ar* -> Ar+ + Ar + em'
    number = 5
    coefficient = -2
  [../]
  #Net excited Argon loss from two-body quenching
  [./SM_Ar*_2B_quenching]
    type = ReactionSecondOrderLogForShootMethod
    variable = SMDeriv
    density = Ar*
    v = Ar
    reaction = 'Ar* + Ar -> Ar + Ar'
    number = 6
    coefficient = -1
  [../]
  #Net excited Argon loss from three-body quenching
  [./SM_Ar*_3B_quenching]
    type = ReactionThirdOrderLogForShootMethod
    variable = SMDeriv
    density = Ar*
    v = Ar
    w = Ar
    reaction = 'Ar* + Ar + Ar -> Ar_2 + Ar'
    number = 7
    coefficient = -1
  [../]
[]


[AuxVariables]
  [./x_node]
  [../]

  [./Ar]
  [../]
[]

[AuxKernels]
  [./x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
  [../]

  [./Ar_val]
    type = ConstantAux
    variable = Ar
    # value = 3.22e22
    value = -2.928623
    execute_on = INITIAL
  [../]
[]


[BCs]
  [./potential_left]
    type = FunctionDirichletBC
    variable = potential
    boundary = 'left'
    function = potential_bc_func
  [../]
  [./potential_dirichlet_right]
    type = DirichletBC
    variable = potential
    boundary = 'right'
    value = 0
  [../]

  [./em_physical_right]
    type = LymberopoulosElectronBC
    variable = em
    boundary = 'right'
    gamma = 0.01
    ks = 1.19e5
    ion = Ar+
    potential = potential
    position_units = ${dom0Scale}
  [../]
  [./em_physical_left]
    type = LymberopoulosElectronBC
    variable = em
    boundary = 'left'
    gamma = 0.01
    ks = 1.19e5
    ion = Ar+
    potential = potential
    position_units = ${dom0Scale}
  [../]

  [./Ar+_physical_right_advection]
    type = LymberopoulosIonBC
    variable = Ar+
    potential = potential
    boundary = 'right'
    position_units = ${dom0Scale}
  [../]
  [./Ar+_physical_left_advection]
    type = LymberopoulosIonBC
    variable = Ar+
    potential = potential
    boundary = 'left'
    position_units = ${dom0Scale}
  [../]

  [./Ar*_physical_right_diffusion]
    type = LogDensityDirichletBC
    variable = Ar*
    boundary = 'right'
    value = 1e-5
  [../]
  [./Ar*_physical_left_diffusion]
    type = LogDensityDirichletBC
    variable = Ar*
    boundary = 'left'
    value = 1e-5
  [../]

  [./mean_en_physical_right]
    type = ElectronTemperatureDirichletBC
    variable = mean_en
    em = em
    value = 0.5
    boundary = 'right'
  [../]
  [./mean_en_physical_left]
    type = ElectronTemperatureDirichletBC
    variable = mean_en
    em = em
    value = 0.5
    boundary = 'left'
  [../]
[]

[Functions]
  [./potential_bc_func]
    type = ParsedFunction
    value = '0.100*sin(2*pi*13.56e6*t)'
  [../]
[]

[Materials]
  [./GasBasics]
    type = GasElectronMoments
    em = em
    potential = potential
    mean_en = mean_en
    user_electron_mobility = 30.0
    user_electron_diffusion_coeff = 119.8757763975
    user_p_gas = 133.322
    property_tables_file = Argon_reactions_paper_RateCoefficients/electron_moments.txt
    interp_trans_coeffs = false
    interp_elastic_coeff = false
    ramp_trans_coeffs = false
  [../]
  [./gas_species_0]
    type = HeavySpeciesMaterial
    heavy_species_name = Ar+
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    mobility = 0.144409938
    diffusivity = 6.428571e-3
  [../]
  [./gas_species_1]
    type = HeavySpeciesMaterial
    heavy_species_name = Ar*
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
    diffusivity = 7.515528e-3
  [../]
  [./gas_species_2]
    type = HeavySpeciesMaterial
    heavy_species_name = Ar
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
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
  end_time = 73.74631268e-9
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 fgmres 1e-3'
  l_max_its = 20

  scheme = bdf2
  dt = 1e-9
  dtmin = 1e-14
[]

[Outputs]
  perf_graph = true
  [./out]
    type = Exodus
  [../]
[]
