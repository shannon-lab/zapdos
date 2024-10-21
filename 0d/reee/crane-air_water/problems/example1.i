[Mesh]
  # 'Dummy' mesh - a mesh is always needed to run MOOSE, but
  # scalar variables do not exist on the mesh.
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 1
  nx = 1
[]

[Variables]
  # ODE variables
  [./x]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  [../]

  [./y]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  [../]
[]

[ScalarKernels]
  # Time derivatives
  [./dx_dt]
    type = ODETimeDerivative
    variable = x
  [../]
  [./dy_dt]
    type = ODETimeDerivative
    variable = y
  [../]
[]

[ChemicalReactions]
  [./ScalarNetwork]
    species = 'x y'
    reaction_coefficient_format = 'rate'
    track_rates = True
    reactions = 'x -> x + x             : 0.666667
                 x + y -> y             : 1.333333
                 y + x -> x + y + y     : 1
                 y -> z                 : 1'
  [../]
[]

[Executioner]
  type = Transient
  start_time = 0
  end_time = 50
  dt = 0.1
  solve_type = newton
  scheme = crank-nicolson
[]

[Preconditioning]
  [./smp]
    type = SMP
    full = true
  [../]
[]

[Outputs]
  csv = true
  [./console]
    type = Console
    # execute_scalars_on = 'none'
  [../]
[]
