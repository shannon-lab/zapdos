[Mesh]
  [./file]
    type = FileMeshGenerator
    file = 'Sample_Periodic_Diffusion.msh'
  [../]
  [./left]
    type = SideSetsFromNormalsGenerator
    normals = '-1 0 0'
    new_boundary = 'left'
    input = file
  [../]
  [./right]
    type = SideSetsFromNormalsGenerator
    normals = '1 0 0'
    new_boundary = 'right'
    input = left
  [../]
[]

[Problem]
  type = FEProblem
[]

[Variables]
  [./y]
  [../]
[]

[Kernels]
  [./Time_Deriv]
    type = TimeDerivative
    variable = y
  [../]
  [./Diff]
    type = MatDiffusion
    variable = y
    diffusivity = 'diffy'
  [../]
  [./First_Term]
    type = BodyForce
    variable = y
    function = '0.25 * sin(2.0*pi * t) * sin(2.0*pi * t)'
  [../]
  [./Second_Term]
    type = ReactionFirstOrder
    variable = y
    v = y
    coefficient = -1
    reaction = 'firstorder'
    _v_eq_u = true
  [../]
  [./Thrid_Term]
    type = ReactionSecondOrder
    variable = y
    v = y
    w = y
    coefficient = -1
    reaction = 'secondorder'
    _v_eq_u = true
    _w_eq_u = true
  [../]
[]

[BCs]
  [./Walls]
    type = DirichletBC
    variable = y
    value = 0
    boundary = 'left right'
  [../]
[]

[Materials]
  [./gas_species_0]
    type = GenericConstantMaterial
    prop_names = 'diffy'
    prop_values = 0.001
  [../]
  [./firstorder_coefficient]
    type = GenericRateConstant
    reaction = 'firstorder'
    reaction_rate_value = 0.05
  [../]
  [./secondorder_coefficient]
    type = GenericRateConstant
    reaction = 'secondorder'
    reaction_rate_value = 0.015
  [../]
[]

[PeriodicRelativeNodalDifference]
  [./Periodic_Y_Diff]
    periodic_variable = y
    cycle_frequency = 1.0
    num_cycles = 75
    starting_cycle = 25
  [../]
[]

[Postprocessors]
  [./diff_counter]
    type = PeriodicComparisonCounter
    value1 = y_periodic_difference
    value2 = 1e-5
    frequency = 1
    comparison_type = less_than
  [../]
[]

[UserObjects]
  [./End]
    type = Terminator
    expression = '(if(diff_counter>=10,1,0)) = 1'
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
  end_time = 100

  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  petsc_options_iname = '-pc_type -ksp_type'
  petsc_options_value = 'lu gmres'

  dtmin = 1e-14
  scheme = bdf2
  dt = 0.01

[]

[Outputs]
  perf_graph = true
  [./out]
    type = Exodus
  [../]
[]
