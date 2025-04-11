dom0Scale=25.4e-3

# [GlobalParams]
#   potential_units = kV
#   use_moles = true
# []

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

[Variables]
  [Ar*]
  []
[]

[AuxVariables]
  [Ar*S]
  []
  [Ar*T]
  []

  [SM_Ar*]
  []
  [SM_Ar*Reset]
    initial_condition = 1.0
  []

  [x_node]
  []
  [x]
    order = CONSTANT
    family = MONOMIAL
  []
[]

[Kernels]
  [Shoot_Method]
    type = ShootMethodLog
    variable = Ar*
    density_at_start_cycle = Ar*S
    density_at_end_cycle = Ar*T
    sensitivity_variable = SM_Ar*
    growth_limit = 100
  []
[]

[AuxKernels]
  [Constant_SM_Ar*Reset]
    type = ConstantAux
    variable = SM_Ar*Reset
    value = 1.0
    execute_on = 'TIMESTEP_BEGIN'
  []

  [x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
  []
  [x_g]
    type = Position
    variable = x
    position_units = ${dom0Scale}
  []
[]

[BCs]
  #Boundary conditions for metastables
    [Ar*_physical_right_value]
      type = DirichletBC
      variable = Ar*
      boundary = 'right'
      value = -50.0
    []
    [Ar*_physical_left_value]
      type = DirichletBC
      variable = Ar*
      boundary = 'left'
      value = -50.0
    []
[]

[Postprocessors]
  [Meta_Relative_Diff]
    type = RelativeElementL2Difference
    variable = Ar*
    other_variable = Ar*S
    execute_on = 'TIMESTEP_END'
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
  type = Steady

  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON

  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'

  # abort_on_solve_fail = true
[]

[Outputs]
  print_perf_log = true
  [out]
    type = Exodus
  []
[]
