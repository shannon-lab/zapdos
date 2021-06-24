dom0Scale=25.4e-3

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
  [./Ar*]
  [../]
[]

[AuxVariables]
  [./Ar*S]
  [../]
  [./Ar*T]
  [../]

  [./SM_Ar*]
  [../]
  [./SM_Ar*Reset]
    initial_condition = 1.0
  [../]

  [./x_node]
  [../]
  [./x]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  [./Shoot_Method]
    type = ShootMethodLog
    variable = Ar*
    density_at_start_cycle = Ar*S
    density_at_end_cycle = Ar*T
    sensitivity_variable = SM_Ar*
    #growth_limit = 100
    #growth_limit = 200
    growth_limit = 50
  [../]
[]

[AuxKernels]
  [./Constant_SM_Ar*Reset]
    type = ConstantAux
    variable = SM_Ar*Reset
    value = 1.0
    execute_on = 'TIMESTEP_BEGIN'
  [../]

  [./x_ng]
    type = Position
    variable = x_node
    position_units = ${dom0Scale}
  [../]
  [./x_g]
    type = Position
    variable = x
    position_units = ${dom0Scale}
  [../]
[]

[BCs]
  #Boundary conditions for metastables
  [./Ar*_physical_diffusion]
    type = ADDirichletBC
    variable = Ar*
    boundary = 'Top_Electrode Bottom_Electrode Walls'
    value = -50.0
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
  type = Steady

  petsc_options = '-snes_converged_reason -snes_linesearch_monitor'
  solve_type = NEWTON
  line_search = none
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu NONZERO 1.e-10'
[]

[Outputs]
  #print_perf_log = true
  #[./out_NONLINEAR]
  #  type = Exodus
  #  execute_on = 'NONLINEAR'
  #[../]
  #[./out_LINEAR]
  #  type = Exodus
  #  execute_on = 'LINEAR'
  #[../]
  [./out]
    type = Exodus
  [../]
[]
