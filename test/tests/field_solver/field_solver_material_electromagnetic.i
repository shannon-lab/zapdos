# Temporary electromagnetic test for FieldSolverMaterial object
# Domain: 2D square, x=[0,1], y=[0,1]
# Expected output:
#   e_field = (1, 2, 0)
#   field_output = (1, 2, 0)

[Mesh]
  [./generated]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 50
    ny = 50
    elem_type = QUAD8
  [../]
[]

[Problem]
  solve = false
[]

[AuxVariables]
  [./field_output]
    family = NEDELEC_ONE
    order = FIRST
  [../]
  [./e_field]
    family = LAGRANGE_VEC
    order = FIRST
  [../]
[]

[ICs]
  [./e_field_ic]
    type = VectorConstantIC
    x_value = 1
    y_value = 2
    variable = e_field
  [../]
[]

[AuxKernels]
  [./field_output_aux]
    type = ADVectorMaterialRealVectorValueAux
    property = 'field_solver_interface_property'
    variable = field_output
  [../]
[]

[Materials]
  [./field_solver]
    type = FieldSolverMaterial
    electric_field = e_field
    solver = electromagnetic
    block = 0
  [../]
[]

[Executioner]
  type = Steady
  solve_type = 'NEWTON'
[]

[Outputs]
  [./out]
    type = Exodus
    show = 'e_field field_output'
  [../]
[]
