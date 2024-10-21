[Mesh]
  # 'Dummy' mesh - a mesh is always needed to run MOOSE, but
  # scalar variables do not exist on the mesh.
  type = GeneratedMesh
  dim = 3
  xmin = 0
  xmax = 1
  nx = 200
[]

[Variables]
  # ODE variables
  [./x]
    initial_condition = 10
  [../]

  [./y]
    initial_condition = 10
  [../]

  [./dummy]
    initial_condition = 5
  [../]
[]

[Kernels]
  # Time derivatives
  [./dx_dt]
    type = TimeDerivative
    variable = x
  [../]
  [./dy_dt]
    type = TimeDerivative
    variable = y
  [../]
  [./ddummy_dt]
    type = TimeDerivative
    variable = dummy
  [../]
[]

[Reactions]
  [./test01]
    species = 'x y dummy'
    reaction_coefficient_format = 'rate'
    equation_variables = 'H2O'
    track_rates = True
    reactions = '
                 x + y -> y  : 0.4
                 x -> x + x  : 1.1
                 y + x -> x + y + y  : 0.1
                 y -> z  : 0.4
                 x + y -> dummy : {1e-5*H2O}'
  [../]
[]

[AuxVariables]
  [./H2O]
    order = FIRST
    initial_condition = 100
  [../]
[]

[Executioner]
  type = Transient
  start_time = 0
  end_time = 100
  dt = 0.05
  num_steps = 2000
  solve_type = newton
  scheme = crank-nicolson
  # Note: don't use crank-nicolson for a "real" chemistry simulation. It works for this case, but may not in general.
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Outputs]
  exodus = true
[]
