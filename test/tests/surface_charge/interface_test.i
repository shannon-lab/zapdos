# This example is a simple steady state potential with a constant
# surface charge.
# The surface charge is taken into account with an interface kernel,
# causing a discontinuity in the electric field.
# A MatchedValueBC is also needed to ensure the potential is
# continuous across the two regions.

dom0Scale = 1e-4
dom1Scale = 1e-4

[Mesh]
  # The mesh file generates the appropriate 1D mesh, but the interfaces
  # needed for the potential and surface charge have not been defined.
  # Here SideSetsBetweenSubdomainsGenerator is used to generate the
  # appropriate interfaces at the dielectrics.
  #
  # Block 0 = left dielectric
  # Block 1 = plasma region
  # Block 2 = right dielectric
  [file]
    type = FileMeshGenerator
    file = 'interface_mesh.msh'
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
  type = Steady
  automatic_scaling = true
  solve_type = NEWTON
  #petsc_options = '-snes_test_jacobian'
[]

[Outputs]
  perf_graph = true
  [out]
    type = Exodus
  []
[]

[Variables]
  [potential_dom0]
    block = 0
  []
  [potential_dom1]
    block = 1
  []
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
[]

[InterfaceKernels]
  # At the dielectric interfaces, the potential is required to be continuous
  # in value but discontinuous in slope due to surface charge accumulation.
  #
  # The potential requires two different boundary conditions on each side:
  #    (1) An InterfaceKernel to provide the Neumann boundary condition
  #    (2) A MatchedValueBC to ensure that the potential remains continuous
  [potential_left]
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
[]

[Functions]
  # Define a sinusoidal voltage pulse with a frequency of 50 kHz
  # Amplitude is set to 750 Volts
  # (Note that here the amplitude is set to 0.75. Potential units are
  # typically included as kV, not V. This option is set in the
  # GlobalParams block.)
  [potential_input]
    type = ParsedFunction
    symbol_names = 'f0'
    symbol_values = '50e3'
    #expression = '-0.75*sin(2*3.1415926*f0*t)'
    expression = '-0.75'
  []

  # Set the initial condition to a line from -10 V on the left and
  # 0 on the right.
  # (Poisson solver tends to struggle with a uniformly zero potential IC.)
  [potential_ic_func]
    type = ParsedFunction
    expression = '-0.75 * (2.0001e-4 - x)'
  []
[]

[Materials]
  #########
  # Define secondary electron emission coefficients on the left and right
  # dielectrics.
  #########
  [se_left]
    type = GenericConstantMaterial
    boundary = 'plasma_right'
    prop_names = 'se_coeff'
    prop_values = '0.01'
  []

  [gas_constants]
    type = GenericConstantMaterial
    block = 1
    prop_names = ' e       N_A      k_boltz  eps         se_energy T_gas  massem   p_gas'
    prop_values = '1.6e-19 6.022e23 1.38e-23 8.854e-12   1.        400    9.11e-31 1.01e5'
  []

  # Create a constant surface charge on the boundary named 'plasma_side'
  [sc_test]
    type = ADGenericConstantMaterial
    boundary = 'plasma_right'
    prop_names = 'surface_charge'
    prop_values = '-1e-6'
  []

  [dielectric_left_side]
    type = ADGenericConstantMaterial
    prop_names = 'diffpotential_dom0'
    prop_values = '8.85e-12'
    block = 0
  []
  [gas_phase]
    type = ADGenericConstantMaterial
    prop_names = 'diffpotential_dom1'
    prop_values = '8.85e-11'
    block = 1
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
