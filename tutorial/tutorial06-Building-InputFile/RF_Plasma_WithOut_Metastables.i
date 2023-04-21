dom0Scale = 25.4e-3

[GlobalParams]
  potential_units = kV
  use_moles = true
[]

[Mesh]
  [geo]
    type = FileMeshGenerator
    file = 'Lymberopoulos_paper.msh'
  []
  [left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = geo
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

[DriftDiffusionAction]
  [Plasma]
    electrons = em
    charged_particle = Ar+
    field = potential
    Is_field_unique = true
    mean_energy = mean_en
    position_units = ${dom0Scale}
    Additional_Outputs = 'ElectronTemperature Current EField'
  []
[]

[Reactions]
  [Argon]
    species = 'em Ar+'
    aux_species = 'Ar'
    reaction_coefficient_format = 'rate'
    gas_species = 'Ar'
    electron_energy = 'mean_en'
    electron_density = 'em'
    include_electrons = true
    file_location = 'rate_coefficients'
    potential = 'potential'
    use_log = true
    use_ad = true
    position_units = ${dom0Scale}
    block = 0
    reactions = 'em + Ar -> em + Ar*        : EEDF [-11.56] (reaction1)
                 em + Ar -> em + em + Ar+   : EEDF [-15.7] (reaction2)'
  []
[]

[AuxVariables]
  [x_node]
  []

  [Ar]
  []
[]

[AuxKernels]
  [x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
  []

  [Ar_val]
    type = FunctionAux
    variable = Ar
    function = 'log(3.22e22/6.022e23)'
    execute_on = INITIAL
  []
[]

[BCs]
  #Voltage Boundary Condition
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

  #Boundary conditions for electons
  [em_physical_right]
    type = LymberopoulosElectronBC
    variable = em
    boundary = 'right'
    emission_coeffs = 0.01
    ks = 1.19e5
    ions = Ar+
    potential = potential
    position_units = ${dom0Scale}
  []
  [em_physical_left]
    type = LymberopoulosElectronBC
    variable = em
    boundary = 'left'
    emission_coeffs = 0.01
    ks = 1.19e5
    ions = Ar+
    potential = potential
    position_units = ${dom0Scale}
  []

  #Boundary conditions for ions
  [Ar+_physical_right_advection]
    type = LymberopoulosIonBC
    variable = Ar+
    potential = potential
    boundary = 'right'
    position_units = ${dom0Scale}
  []
  [Ar+_physical_left_advection]
    type = LymberopoulosIonBC
    variable = Ar+
    potential = potential
    boundary = 'left'
    position_units = ${dom0Scale}
  []

  #Boundary conditions for mean energy
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
  [potential_bc_func]
    type = ParsedFunction
    expression = '0.100*sin(2*3.1415926*13.56e6*t)'
  []
  [potential_ic_func]
    type = ParsedFunction
    expression = '0.100 * (25.4e-3 - x)'
  []
  [density_ic_func]
    type = ParsedFunction
    expression = 'log((1e13 + 1e15 * (1-x/1)^2 * (x/1)^2)/6.022e23)'
  []
  [energy_density_ic_func]
    type = ParsedFunction
    expression = 'log(3./2.) + log((1e13 + 1e15 * (1-x/1)^2 * (x/1)^2)/6.022e23)'
  []
[]

[Materials]
  [GasBasics]
    type = GasElectronMoments
    interp_trans_coeffs = false
    interp_elastic_coeff = false
    ramp_trans_coeffs = false
    user_p_gas = 133.322
    em = em
    potential = potential
    mean_en = mean_en
    user_electron_mobility = 30.0
    user_electron_diffusion_coeff = 119.8757763975
    property_tables_file = rate_coefficients/electron_moments.txt
  []
  [gas_species_0]
    type = ADHeavySpecies
    heavy_species_name = Ar+
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    mobility = 0.144409938
    diffusivity = 6.428571e-3
  []
  [gas_species_2]
    type = ADHeavySpecies
    heavy_species_name = Ar
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 0.0
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
  end_time = 7.3746e-5
  dt = 1e-9
  dtmin = 1e-14
  scheme = bdf2
  solve_type = NEWTON

  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -snes_linesearch_minlambda'
  petsc_options_value = 'lu NONZERO 1.e-10 1e-3'

  nl_rel_tol = 1e-08
  l_max_its = 20
[]

[Outputs]
  perf_graph = true
  [out]
    type = Exodus
  []
[]
