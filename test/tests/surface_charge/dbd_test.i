# This example sets up a simple varying-voltage discharge with a
# dielectric at the right boundary.
#
# Two charged particle species are considered, creatively named 'pos'
# and 'neg'. They both have the same initial conditions and boundary
# conditions; the only difference is their charge.
# As the voltage varies, the particle flux to the right boundary
# (including both advection and diffusion) will switch polarity and
# the surface charge will become increasingly negative or positive.
#
# The left boundary is a driven electrode with a sinusoidal waveform.
# A dielectric boundary condition including surface charge accumulation
# is included on the right boundary.
#
# Note that without surface charge the electric field across both
# boundaries should be identical since their permittivities are
# both set to the same value.
# Surface charge shields the electric field in the gas region,
# preventing strong field buildup.

dom0Scale = 1e-4
dom1Scale = 1e-4

[GlobalParams]
  #offset = 40
  potential_units = kV
  use_moles = true
[]

[Mesh]
  # The mesh file generates the appropriate 1D mesh, but the interfaces
  # needed for the potential and surface charge have not been defined.
  # Here SideSetsBetweenSubdomainsGenerator is used to generate the
  # appropriate interfaces at the dielectrics.
  #
  # Block 0 = plasma region
  # Block 1 = dielectric
  [file]
    type = FileMeshGenerator
    file = 'dbd_mesh.msh'
  []
  [plasma_right]
    # plasma master
    type = SideSetsBetweenSubdomainsGenerator
    primary_block = '0'
    paired_block = '1'
    new_boundary = 'plasma_right'
    input = file
  []
  [dielectric_left]
    # left dielectric master
    type = SideSetsBetweenSubdomainsGenerator
    primary_block = '1'
    paired_block = '0'
    new_boundary = 'dielectric_left'
    input = plasma_right
  []
  [left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = dielectric_left
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

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Executioner]
  type = Transient
  automatic_scaling = true
  compute_scaling_once = false
  end_time = 10e-5
  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  #num_steps = 1
  #petsc_options = '-snes_converged_reason -snes_linesearch_monitor -snes_test_jacobian'
  solve_type = NEWTON
  line_search = 'basic'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount -snes_stol'
  petsc_options_value = 'lu NONZERO 1.e-10 0'
  nl_rel_tol = 1e-8
  nl_div_tol = 1e4
  l_max_its = 100
  nl_max_its = 25

  dtmin = 1e-22
  dtmax = 1e-6
  #dt = 1e-8
  [TimeSteppers]
    [Adaptive]
      type = IterationAdaptiveDT
      cutback_factor = 0.4
      dt = 1e-9
      growth_factor = 1.2
      optimal_iterations = 30
    []
  []
[]

[Outputs]
  perf_graph = true
  [out]
    type = Exodus
    output_material_properties = true
    show_material_properties = 'surface_charge'
  []
[]

[AuxVariables]
  [neg_density]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []
  [pos_density]
    order = CONSTANT
    family = MONOMIAL
    block = 0
  []

  [Efield]
    order = CONSTANT
    family = MONOMIAL
  []

  [x]
    order = CONSTANT
    family = MONOMIAL
  []
[]

[AuxKernels]
  [neg_calc]
    type = DensityMoles
    variable = neg_density
    density_log = neg
    execute_on = 'initial timestep_end'
    block = 0
  []
  [pos_calc]
    type = DensityMoles
    variable = pos_density
    density_log = pos
    execute_on = 'initial timestep_end'
    block = 0
  []
  #[Arp_calc]
  #  type = DensityMoles
  #  variable = Arp_density
  #  density_log = Arp
  #  execute_on = 'initial timestep_end'
  #  block = 0
  #[]
  [x_d0]
    type = Position
    variable = x
    position_units = ${dom0Scale}
    execute_on = 'initial timestep_end'
    block = 0
  []
  [x_d1]
    type = Position
    variable = x
    position_units = ${dom1Scale}
    execute_on = 'initial timestep_end'
    block = 1
  []
  [Efield_g]
    type = Efield
    component = 0
    variable = Efield
    position_units = ${dom0Scale}
    block = 0
  []
  [Efield_l]
    type = Efield
    component = 0
    variable = Efield
    position_units = ${dom1Scale}
    block = 1
  []
[]

[Variables]
  [potential_dom0]
    block = 0
  []
  [potential_dom1]
    block = 1
  []

  [neg]
    block = 0
  []
  [pos]
    block = 0
  []
  #[mean_en]
  #  block = 0
  #[]
  #[Arp]
  #  block = 0
  #[]
[]

[Kernels]
  [potential_diffusion_dom0]
    type = CoeffDiffusionLin
    variable = potential_dom0
    block = 0
    position_units = ${dom0Scale}
  []
  [potential_diffusion_dom1]
    type = CoeffDiffusionLin
    variable = potential_dom1
    block = 1
    position_units = ${dom1Scale}
  []

  # Potential source terms
  #[em_source]
  #  type = ChargeSourceMoles_KV
  #  variable = potential_dom0
  #  charged = em
  #  block = 0
  #[]
  #[Arp_source]
  #  type = ChargeSourceMoles_KV
  #  variable = potential_dom0
  #  charged = Arp
  #  block = 0
  #[]
  #
  # Electrons
  #[d_em_dt]
  #  type = TimeDerivativeLog
  #  variable = em
  #  block = 0
  #[]
  [neg_advection]
    type = EFieldAdvection
    variable = neg
    position_units = ${dom0Scale}
    block = 0
  []
  [neg_diffusion]
    type = CoeffDiffusion
    variable = neg
    position_units = ${dom0Scale}
    block = 0
  []

  [pos_advection]
    type = EFieldAdvection
    variable = pos
    position_units = ${dom0Scale}
    block = 0
  []
  [pos_diffusion]
    type = CoeffDiffusion
    variable = pos
    position_units = ${dom0Scale}
    block = 0
  []
  #[em_offset]
  #  type = LogStabilizationMoles
  #  variable = em
  #  block = 0
  #[]
  #
  #[d_mean_en_dt]
  #  type = TimeDerivativeLog
  #  variable = mean_en
  #  block = 0
  #[]
  #[mean_en_advection]
  #  type = ADEFieldAdvection
  #  em = em
  #  variable = mean_en
  #  potential = potential_dom0
  #  position_units = ${dom0Scale}
  #  block = 0
  #[]
  #[mean_en_diffusion]
  #  type = ADCoeffDiffusion
  #  variable = mean_en
  #  position_units = ${dom0Scale}
  #  block = 0
  #[]
  #[mean_en_joule_heating]
  #  type = ADJouleHeating
  #  variable = mean_en
  #  em = em
  #  potential = potential_dom0
  #  position_units = ${dom0Scale}
  #  block = 0
  #[]
  #[mean_en_offset]
  #  type = LogStabilizationMoles
  #  variable = mean_en
  #  block = 0
  #[]
  #
  #[d_Arp_dt]
  #  type = TimeDerivativeLog
  #  variable = Arp
  #  block = 0
  #[]
  #[Arp_advection]
  #  type = ADEFieldAdvection
  #  variable = Arp
  #  potential = potential_dom0
  #  position_units = ${dom0Scale}
  #  block = 0
  #[]
  #[Arp_diffusion]
  #  type = ADCoeffDiffusion
  #  variable = Arp
  #  position_units = ${dom0Scale}
  #  block = 0
  #[]
  #[Arp_offset]
  #  type = LogStabilizationMoles
  #  variable = Arp
  #  block = 0
  #[]
[]

[InterfaceKernels]
  # At the dielectric interfaces, the potential is required to be continuous
  # in value but discontinuous in slope due to surface charge accumulation.
  #
  # The potential requires two different boundary conditions on each side:
  #    (1) An InterfaceKernel to provide the Neumann boundary condition
  #    (2) A MatchedValueBC to ensure that the potential remains continuous
  #
  # This interface kernel simply applies a dielectric BC with surface charge
  # accumulation.
  [potential_right]
    type = PotentialSurfaceCharge
    neighbor_var = potential_dom1
    variable = potential_dom0
    position_units = ${dom0Scale}
    neighbor_position_units = ${dom1Scale}
    boundary = plasma_right
  []

[]

[BCs]
  # Interface BCs:
  [match_potential]
    type = MatchedValueBC
    variable = potential_dom1
    v = potential_dom0
    boundary = 'dielectric_left'
  []

  # Electrode and ground BCs:
  # Electrode is at x = 0, named 'left'
  [potential_left]
    type = FunctionDirichletBC
    variable = potential_dom0
    function = potential_input
    boundary = 'left'
  []

  # Ground is at x = 0.3 mm, named 'right'
  [potential_dirichlet_right]
    type = DirichletBC
    variable = potential_dom1
    boundary = right
    value = 0
  []

  # Both charged species will have a specified dirichlet BC on the driven electrode
  # and a diffusion BC on the right side.
  # As the voltage varies with time, the charged particle flux on the right will
  # switch between positive and negative, effectively changing the surface
  # charge polarity.
  [neg_left]
    type = DirichletBC
    variable = neg
    value = -10
    boundary = 'left'
  []
  [neg_right]
    type = HagelaarIonDiffusionBC
    variable = neg
    r = 0
    position_units = ${dom0Scale}
    boundary = 'plasma_right'
  []

  [pos_left]
    type = DirichletBC
    variable = pos
    value = -10
    boundary = 'left'
  []
  [pos_right]
    type = HagelaarIonDiffusionBC
    variable = pos
    r = 0
    position_units = ${dom0Scale}
    boundary = 'plasma_right'
  []
[]

[ICs]
  [potential_dom0_ic]
    type = FunctionIC
    variable = potential_dom0
    function = potential_ic_func
  []
  [potential_dom1_ic]
    type = FunctionIC
    variable = potential_dom1
    function = potential_ic_func
  []

  [neg_ic]
    type = ConstantIC
    variable = neg
    value = -10
    block = 0
  []
  [pos_ic]
    type = ConstantIC
    variable = pos
    value = -10
    block = 0
  []
[]

[Functions]
  # Define a sinusoidal voltage pulse with a frequency of 50 kHz
  # Amplitude is set to 200 Volts
  # (Note that here the amplitude is set to 0.2. Potential units are
  # typically included as kV, not V. This option is set in the
  # GlobalParams block.)
  [potential_input]
    type = ParsedFunction
    symbol_names = 'f0'
    symbol_values = '50e3'
    expression = '-0.2*sin(2*3.1415926*f0*t)'
  []

  # Set the initial condition to a line from -10 V on the left and
  # 0 on the right.
  # (Poisson solver tends to struggle with a uniformly zero potential IC.)
  [potential_ic_func]
    type = ParsedFunction
    expression = '-0.001 * (2.000e-4 - x)'
  []
[]

[Materials]
  # This material creates a boundary-restricted material property called "surface_charge"
  # The value of surface charge is based on the total charged particle flux impacting
  # the specified boundary.
  # In this case we have two charged species, 'pos' (positively charged) and 'neg'
  # (negatively charged).
  [surface_charge_material]
    type = ADSurfaceCharge
    species = 'neg pos'
    position_units = ${dom0Scale}
    boundary = 'plasma_right'
  []

  # This just defines some constants that Zapdos needs to run.
  [gas_constants]
    type = GenericConstantMaterial
    block = 0
    prop_names = ' e       N_A      k_boltz  eps         se_energy T_gas  massem   p_gas'
    prop_values = '1.6e-19 6.022e23 1.38e-23 8.854e-12   1.        400    9.11e-31 1.01e5'
  []

  #
  [dielectric_left_side]
    type = ADGenericConstantMaterial
    prop_names = 'diffpotential_dom0'
    prop_values = '8.85e-12'
    block = 0
  []
  [gas_phase]
    type = ADGenericConstantMaterial
    prop_names = 'diffpotential_dom1'
    prop_values = '8.85e-12'
    block = 1
  []

  ######
  # HeavySpeciesMaterial defines charge, mass, transport coefficients, and
  # temperature for each species.
  #
  # Transport coefficients and temperature are defined as ADMaterialProperties.
  # Although they currently (as of June 16, 2020) remain constant, future
  # implementations may include mixture-averaged diffusion coefficients and
  # effective ion temperatures with nonlinear dependence on other variables.
  ######
  [gas_species_0]
    type = ADHeavySpecies
    heavy_species_name = neg
    heavy_species_mass = 6.64e-26
    heavy_species_charge = -1.0
    diffusivity = 1.6897e-5
    block = 0
  []
  [gas_species_2]
    type = ADHeavySpecies
    heavy_species_name = pos
    heavy_species_mass = 6.64e-26
    heavy_species_charge = 1.0
    diffusivity = 1.6897e-5
    block = 0
  []

  [field_solver0]
    type = FieldSolverMaterial
    potential = potential_dom0
    block = 0
  []

  [field_solver1]
    type = FieldSolverMaterial
    potential = potential_dom1
    block = 1
  []
[]
