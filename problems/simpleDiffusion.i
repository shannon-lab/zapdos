[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 40
  xmax = 2
[]

[Variables]
  [./concentration]
  [../]
[]

[ICs]
  active = 'null_ic'
  [./null_ic]
    type = ConstantIC
    variable = 'concentration'
    value = 0.0
  [../]
[]

[Kernels]
  [./time_derivative]
    type = TimeDerivative
    variable = concentration
  [../]
  [./diffusion]
    type = CoeffDiffusion
    variable = concentration
    string = zH2Op
  [../]
[]

[BCs]
  [./left_wall]
    type = DirichletBC # Simple u=value BC
    variable = concentration
    boundary = left
    value = 1
  [../]
[]

[Materials]
  [./whole_domain]
    block = 0
    type = Water
  [../]
[]

[Problem]
  type = FEProblem # This is the "normal" type of Finite Element Problem in MOOSE
[]

[Executioner]
  type = Transient
  dt = 0.05
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
  end_time = 2
#  trans_ss_check = true
#  ss_check_tol = 1e-8
  nl_rel_tol = 1e-2
  l_tol = 1e-1
#  nl_abs_tol = 1e-3
  l_max_its = 9
  nl_max_its = 3
  scheme = crank-nicolson
[]

[Outputs]
  exodus = true # Output Exodus format
[]
