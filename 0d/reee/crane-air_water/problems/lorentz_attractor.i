[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 1
[]

[Variables]
  [./x]
    family = SCALAR
    order = FIRST
    # initial_condition = 10.1
    initial_condition = 1.0
  [../]

  [./y]
    family = SCALAR
    order = FIRST
    initial_condition = 1.0
  [../]

  [./z]
    family = SCALAR
    order = FIRST
    initial_condition = 1.0
  [../]
[]

[ScalarKernels]
  [./dx_dt]
    type = ODETimeDerivative
    variable = x
  [../]

  [./dy_dt]
    type = ODETimeDerivative
    variable = y
  [../]

  [./dz_dt]
    type = ODETimeDerivative
    variable = z
  [../]
[]

[ChemicalReactions]
  [./ScalarNetwork]
    species = 'x y z'
    equation_constants = 'sigma R p'
    equation_values = '10.0 8.0/3.0 28.0'

    reactions = 'x -> a  : {sigma}
                 y -> x + y  : {sigma}
                 x -> x + y  : {p}
                 y -> a  : 1.0
                 x + z -> x + y + z  : -1.0
                 x + y -> x + y + z  : 1.0
                 z -> a  : {R}'
  [../]
[]

[Executioner]
  type = Transient
  end_time = 50
  dt = 0.01
  solve_type = NEWTON
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
[]
