[Mesh]
  type = GeneratedMesh
  nx = 10
  xmax = 1
  ny = 10
  ymax = 1
  dim = 2
[]

[Problem]
  type = FEProblem
  coord_type = RZ
  rz_coord_axis = X
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Steady
  solve_type = NEWTON
  petsc_options = '-snes_converged_reason -ksp_converged_reason'
[]

[Outputs]
  perf_graph = true
  [./out]
    type = Exodus
  [../]
[]

[Kernels]
  [./diff_u]
    type = Diffusion
    variable = u
  [../]
[]

[Variables]
  [./u]
  [../]
[]

[BCs]
  [./source]
    type = PenaltyDirichletBC
    variable = u
    boundary = 'right'
    value = 1
    penalty = 100
  [../]
  [./vacuum]
    boundary = 'top'
    type = VacuumBC
    variable = u
  [../]
[]

[Functions]
  [./exact_fn]
    type = ConstantFunction
    value = 1
  [../]
[]

[ICs]
  [./u]
    type = ConstantIC
    value = 1
    variable = u
  [../]
[]
