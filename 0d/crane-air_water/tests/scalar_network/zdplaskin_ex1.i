[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 1
  nx = 1
[]

[Variables]
  [./e]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  [../]

  [./Ar+]
    family = SCALAR
    order = FIRST
    initial_condition = 1
  [../]

  [./Ar]
    family = SCALAR
    order = FIRST
    initial_condition = 2.5e19
    scaling = 2.5e-19
  [../]
[]

[ScalarKernels]
  [./de_dt]
    type = ODETimeDerivative
    variable = e
  [../]

  [./dAr+_dt]
    type = ODETimeDerivative
    variable = Ar+
  [../]

  [./dAr_dt]
    type = ODETimeDerivative
    variable = Ar
  [../]
[]

[ChemicalReactions]
  [./ScalarNetwork]
    species = 'e Ar+ Ar'
    file_location = 'Example1'
    reactions = 'e + Ar -> e + e + Ar+          : EEDF
                 e + Ar+ + Ar -> Ar + Ar       : 1e-25'

   [../]
[]

[AuxVariables]
  [./reduced_field]
    order = FIRST
    family = SCALAR
    initial_condition = 51e-21
  [../]
[]


[Executioner]
  type = Transient
  end_time = 0.25e-6
  dt = 1e-10
  solve_type = 'newton'
  dtmin = 1e-20
  dtmax = 1e-8
  petsc_options_iname = '-snes_linesearch_type'
  petsc_options_value = 'basic'
[]

[Preconditioning]
  active = 'smp'

  [./smp]
    type = SMP
    full = true
  [../]

  [./fd]
    type = FDP
    full = true
  [../]
[]

[Outputs]
  [./out]
    type = Exodus
    execute_on = 'TIMESTEP_END'
  [../]
[]
