# Electrostatic test for FieldSolverMaterial object
# Domain: 2D square, x=[0,1], y=[0,1]
# BCs: potential(0,y) = 2, potential(1,y) = 0
# Expected output values:
#   potential = -2*x + 2
#   field_output = (2, 0, 0)

[Mesh]
  [./generated]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 50
    ny = 50
    elem_type = QUAD8
  [../]
[]

[Variables]
  [./potential]
  [../]
[]

[AuxVariables]
  [./dummy_efield]
    family = NEDELEC_ONE
    order = FIRST
  [../]
  [./field_output]
    family = NEDELEC_ONE
    order = FIRST
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = potential
  [../]
[]

[AuxKernels]
  [./field_output_aux]
    type = ADVectorMaterialRealVectorValueAux
    property = 'field_solver_interface_property'
    variable = field_output
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = potential
    boundary = left
    value = 2
  [../]
  [./right]
    type = DirichletBC
    variable = potential
    boundary = right
    value = 0
  [../]
[]

[Materials]
  active = field_solver
  [./field_solver]
    type = FieldSolverMaterial
    potential = potential
    block = 0
  [../]
  [./field_solver_error_check]
    type = FieldSolverMaterial
    block = 0
  [../]
[]

[Executioner]
  type = Steady
  solve_type = 'NEWTON'
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  [./out]
    type = Exodus
    show = 'potential field_output'
  [../]
[]
