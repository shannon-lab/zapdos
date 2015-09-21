[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 100
  ny = 10
  xmax = 0.2      # Length of test chamber
  ymax = 0.2      # Test chamber radius
[]

[Variables]
  active = 'diffused'

  [./diffused]
    order = FIRST
    family = LAGRANGE
  [../]
[]


  [AuxVariables]
  [./velocity_x]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./velocity_y]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./velocity_z]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]


#[Functions]
#  active = 'bc_func forcing_func'
#
#  # A ParsedFunction allows us to supply analytic expressions
#  # directly in the input file
#  [./bc_func]
#    type = ParsedFunction
#    value = sin(alpha*pi*x)
#    vars = 'alpha'
#    vals = '16'
#  [../]
#
#  # This function is an actual compiled function
#  # We could have used ParsedFunction for this as well
#  [./forcing_func]
#    type = ExampleFunction
#    alpha = 16
#  [../]
#[]

[Kernels]
  active = 'diff euler'

  [./diff]
    type = Diffusion
    variable = diffused
  [../]

  [./euler]
    type = ExampleTimeDerivative
    variable = diffused
    time_coefficient = 1.0
  [../]

  []

#  [AuxKernels]
#  [./velocity_x]
#    type = DarcyVelocity
#    variable = velocity_x
#    component = x
#    execute_on = timestep_end
#    darcy_pressure = diffused
#  [../]
#  [./velocity_y]
#    type = DarcyVelocity
#    variable = velocity_y
#    component = y
#    execute_on = timestep_end
#    darcy_pressure = diffused
#  [../]
#  [./velocity_z]
#    type = DarcyVelocity
#    variable = velocity_z
#    component = z
#    execute_on = timestep_end
#    darcy_pressure = diffused
#  [../]
#[]

[BCs]

 [./inlet]
    type = DirichletBC
    variable = diffused
    boundary = 'bottom'
    value = 0
  [../]

  [./outlet]
    type = DirichletBC
    variable = diffused
    boundary = 'top'
    value = 1
  [../]

  []

#  [Materials]
#    [./column]
#      type = PackedColumn
#      block = 0
#      ball_radius = 1
#    [../]
#  []

  [Problem]
  type = FEProblem
  coord_type = RZ
  rz_coord_axis = X
[]

[Executioner]
  type = Transient
  num_steps = 30
  dt = 0.0005
  solve_type = PJFNK
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  execute_on = 'timestep_end'
  file_base = out
  exodus = true
[]
